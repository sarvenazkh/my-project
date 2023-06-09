#include "animal_class.h"
#include "genome_info.h"

#define ORIGIN_MAX 1000000

void AnimalClass::sampleFounder()
{
    sireId=0;
    damId=0;
    initFounderPosOri();
    initFounderHaps();
}

void AnimalClass::sampleFounder(vector<string> tokens1,vector<string> tokens2)
{
    sireId=0;
    damId=0;
    initFounderPosOri();
    inputFounderHaps(tokens1,GenomePat);
    inputFounderHaps(tokens2,GenomeMat);
}

void AnimalClass::initFounderPosOri()
{
    unsigned numChromosomePair = G.get_num_chrom();
    for(unsigned i=0;i<numChromosomePair;i++){
        GenomePat[i].ori.resize(1);
        GenomePat[i].ori[0]=countChromosome;
        GenomePat[i].pos.resize(1);
        GenomePat[i].pos[0]=0;
        
        GenomeMat[i].ori.resize(1);
        GenomeMat[i].ori[0]=countChromosome+1;
        GenomeMat[i].pos.resize(1);
        GenomeMat[i].pos[0]=0;
        
    }
    countChromosome += 2;
}


void AnimalClass::initFounderHaps()
{
    unsigned numChromosomePair = G.get_num_chrom();
    
    for(unsigned i=0;i<numChromosomePair;i++)
    {
        unsigned numLoci=G[i].get_num_loci();
        GenomePat[i].haplotype.resize(numLoci);
        GenomeMat[i].haplotype.resize(numLoci);
        
        for(unsigned j=0;j<numLoci;j++)
        {
            binomial_distribution<int> Binom(1,G[i][j].alleleFreq);
            GenomePat[i].haplotype[j]= Binom(randGen);
            GenomeMat[i].haplotype[j]= Binom(randGen);
        }
    }
}


void AnimalClass::inputFounderHaps(vector<string> tokens,vector<chromosome> &Genome)
{
    unsigned numChromosomePair = G.get_num_chrom();
    
    for(unsigned i=0;i<numChromosomePair;i++)
    {
        unsigned numLoci=G[i].get_num_loci();
        Genome[i].haplotype.resize(numLoci);
        for(unsigned j=0;j<numLoci;j++){
            Genome[i].haplotype[j] = stod(tokens[j]);
            
            G[i][j].alleleFreq    += stod(tokens[j]);
        }
     }
}


void AnimalClass::sampleMyPosOri(AnimalClass& father, AnimalClass& mother)
{
    sireId  = father.myId;
    damId   = mother.myId;
    sampleOnePosOri(father,GenomePat);
    sampleOnePosOri(mother,GenomeMat);
}

void AnimalClass::sampleOnePosOri(AnimalClass& individual, vector<chromosome> &Genome)
{
    chromosome *currentChrom;
    unsigned numChromosomePair = G.get_num_chrom();
    

    ArrayXf tempPos;
    ArrayXi tempOri;
    tempPos.resize(ORIGIN_MAX);
    tempOri.resize(ORIGIN_MAX);
    
    for(unsigned i=0;i<numChromosomePair;i++)
    {
        double chrLength = G[i].chr_length;
        unsigned binomialN = chrLength*3 + 1;
        vector<float> rPos;
        binomial_distribution<int> Binom(binomialN,chrLength/binomialN);
        int numCrossover=Binom(randGen);
        
        uniform_real_distribution<float> u(0,1);
        for (unsigned k=0; k<numCrossover; k++)
        {
            rPos.push_back(chrLength*u(randGen));
        }
        rPos.push_back(chrLength);
        sort(rPos.begin(),rPos.end());
        
        unsigned   startPosParent=0;
        unsigned   startPosMe=0;
        
        currentChrom = (u(randGen)<0.5)?&individual.GenomePat[i]:&individual.GenomeMat[i];
        
        for(unsigned j=0;j<rPos.size();j++){
            
            unsigned numCopy=(currentChrom->pos < rPos[j]).count()-startPosParent;
            tempPos.block(startPosMe,0,numCopy,1)=currentChrom->pos.block(startPosParent,0,numCopy,1);
            tempOri.block(startPosMe,0,numCopy,1)=currentChrom->ori.block(startPosParent,0,numCopy,1);
            
            currentChrom=(currentChrom==&individual.GenomePat[i])?&individual.GenomeMat[i]:&individual.GenomePat[i];
            
            startPosParent=(currentChrom->pos < rPos[j]).count();
            startPosMe+=numCopy;
            tempPos(startPosMe)=rPos[j];
            tempOri(startPosMe)=currentChrom->ori(startPosParent-1);
            startPosMe++;
        } 
        
        unsigned keep=0;
        Genome[i].pos.resize(startPosMe);
        Genome[i].ori.resize(startPosMe);
        Genome[i].pos[0]=tempPos[0];
        Genome[i].ori[0]=tempOri[0];
        
        for(unsigned m=1;m < startPosMe-1; m++)
        {
            if(tempOri[m]!=tempOri[m-1])
            {
                keep=keep+1;
                Genome[i].pos[keep]=tempPos[m];
                Genome[i].ori[keep]=tempOri[m];
            }
        }
        unsigned PosOriSize=keep+1;
        Genome[i].pos.conservativeResize(PosOriSize);
        Genome[i].ori.conservativeResize(PosOriSize);
    }
}

void AnimalClass::sampleMyMutation()
{
    if(!G.mapPosDone) G.mkMapPos();
    sampleOneMutation(GenomePat);
    sampleOneMutation(GenomeMat);
}

void AnimalClass::sampleOneMutation(vector<chromosome> &Genome)
{
    
    unsigned numChromosomePair = G.get_num_chrom();
    
    for(unsigned i=0;i<numChromosomePair;i++){
        
        vector<float> mutPos;
        
        unsigned nLoci=G[i].get_num_loci();
        binomial_distribution<int> Binom(nLoci,G.mutRate);
        int nMut=Binom(randGen);
        
        if(nMut)
        {
            uniform_real_distribution<float> u(0,1);
            for (unsigned k=0; k<nMut; k++)
            {
                unsigned which  = unsigned(nLoci*u(randGen));
                if(which!=nLoci){
                    mutPos.push_back(G[i].MapPos(which));     
                }
            }
            
            for(unsigned j=0;j<nMut;j++){
                
                if(mutPos[j]!=G[i].chr_length)
                {

                    unsigned count    =(Genome[i].pos <= mutPos[j]).count();
                    
                    float   startPos  =Genome[i].pos(count-1);
                    
                    float   endPos;
                    
                    if(count!=Genome[i].pos.size()){
                        endPos =Genome[i].pos(count);
                        
                    }else{
                        endPos =G[i].chr_length;
                    }
                    
                    int myOri=Genome[i].ori(count-1);
                    
                    Genome[i].ori(count-1)=countChromosome;
                    
                    countChromosome++;
                    
                    mutantInfo *mutant = new mutantInfo();
                    mutant->whichOri        =myOri;
                    mutant->whichStartPos   =startPos;
                    mutant->whichEndPos     =endPos;
                    mutant->mutPos          =mutPos[j];
                    
                    AnimalClass::mutants.push_back(mutant);
                    
                }
            }
        }
    }
}

void AnimalClass::sampleNonFounder(AnimalClass& father, AnimalClass& mother)
{
    sireId=father.myId;
    damId=mother.myId;
    sampleMyPosOri(father,mother);
    sampleMyMutation();
};

ArrayXf AnimalClass::getMyHapSeg(int i,int myOri,int start,int numcopy){
    
    if(myOri< 2*founders.size()){
        
        unsigned whichFounder=unsigned(myOri/2);
        chromosome* GenomePatOrMatInThisFounder= (myOri%2)? &AnimalClass::founders[whichFounder]->GenomeMat[i]: &AnimalClass::founders[whichFounder]->GenomePat[i];        //i.e. GenomePat or GenomeMat in this founder "whichFounder"
        
        return(GenomePatOrMatInThisFounder->haplotype.block(start,0,numcopy,1));
        
    }else{
        
        mutantInfo* thisMutant  =AnimalClass::mutants[myOri-2*founders.size()];
        auto myMutPos    =thisMutant->mutPos;
        auto myStartPos  =thisMutant->whichStartPos;
        auto myEndPos    =thisMutant->whichEndPos;
        auto myNewOri    =thisMutant->whichOri;
        
        unsigned myStartLocus   =(G[i].MapPos < myStartPos).count();
        unsigned myNEWnumcopy   =(G[i].MapPos < myEndPos).count()-myStartLocus;
        unsigned myMutationLoci =(G[i].MapPos <= myMutPos).count()-myStartLocus; // should be <= because mutations recorded as

        if(!(thisMutant->val).size()){
            
            
            thisMutant->val.resize(myNEWnumcopy);
            thisMutant->val=getMyHapSeg(i,myNewOri,myStartLocus,myNEWnumcopy); 
            
            unsigned myMutIndex=myMutationLoci-1;  
            
            thisMutant->val(myMutIndex)= 1-thisMutant->val(myMutIndex);
            
        }
        
        unsigned myStartKeep=start-myStartLocus;
        return((thisMutant->val).block(myStartKeep,0,numcopy,1));
        
        
    }
    
}

void AnimalClass::getMyHaps()
{
    getOneHaps(GenomePat);
    getOneHaps(GenomeMat);
}


void AnimalClass::getOneHaps(vector<chromosome> &Genome)
{
    unsigned numChromosomePair = G.get_num_chrom();
    
    for(unsigned i=0;i<numChromosomePair;i++)
    {
        
        unsigned numLoci=G[i].get_num_loci();
        Genome[i].haplotype.resize(numLoci);
        
        unsigned numOri = Genome[i].ori.size();
        
        for(unsigned segment=0;segment<numOri;segment++)
        {
            unsigned   numcopy;
            unsigned   start=(G[i].MapPos<Genome[i].pos[segment]).count();
            int        myOri=Genome[i].ori[segment];
            
            if(segment!= numOri-1)
            {
                numcopy=(G[i].MapPos<Genome[i].pos[segment+1]).count()-start;
            }else
            {
                numcopy=(G[i].MapPos<G[i].chr_length).count()-start;
            }
            
            Genome[i].haplotype.block(start,0,numcopy,1)
            =getMyHapSeg(i,myOri,start,numcopy); 
        }
    }
}


void AnimalClass::getMyGenotype()
{
    unsigned numChromosomePair = G.get_num_chrom();
    unsigned numTotalLoci=0;
    
    for(unsigned i=0;i<numChromosomePair;i++){
        numTotalLoci+=G[i].get_num_loci();
    }
    myGenotype.resize(numTotalLoci);
    
    unsigned start=0;
    for(unsigned i=0;i<numChromosomePair;i++){
        
        unsigned numLoci=G[i].get_num_loci();
        myGenotype.block(start,0,numLoci,1)= GenomePat[i].haplotype+GenomeMat[i].haplotype;
        start+=numLoci;
    }
    
    cout<<"Genotyping individual "<< this->myId <<endl;
}


void AnimalClass::display()
{
    IOFormat CommaInitFmt(StreamPrecision, DontAlignCols, ", ", ", ", "", "", " << ", ";");
    unsigned numChromosomePair = G.get_num_chrom();
    for(unsigned i=0;i<numChromosomePair;i++){
        cout<<"These are positions on chromosome "<<i<<" for pat"<<endl;
        cout<< GenomePat[i].pos.format(CommaInitFmt)<<endl;
        cout<<"These are origins on chromosome "<<i<<" for pat"<<endl;
        cout<< GenomePat[i].ori.format(CommaInitFmt)<<endl;
        cout<<"These are positions on chromosome "<<i<<" for mat"<<endl;
        cout<< GenomeMat[i].pos.format(CommaInitFmt)<<endl;
        cout<<"These are origins on chromosome "<<i<<" for mat"<<endl;
        cout<< GenomeMat[i].ori.format(CommaInitFmt)<<endl;
    }
};

unsigned AnimalClass::displayNumPos()
{
    unsigned sumSizePat=0;
    unsigned sumSizeMat=0;
    for(unsigned i=0;i<G.get_num_chrom();i++){
        sumSizePat+=GenomePat[i].pos.size();
        sumSizeMat+=GenomeMat[i].pos.size();
    }
    return((sumSizePat+sumSizeMat)/2);
};














