 #include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include"cell.h"
using namespace std;
string complement(string s){
    for(int i=0;i<s.size();i++){
        if(s[i]=='A')
            s[i]='T';
        else if(s[i]=='C')
            s[i]='G';
        else if(s[i]=='T')
            s[i]='A';
        else if(s[i]=='G')
            s[i]='C';
    }
    return s;
}
bool is_palidrome(string s){
    for(int i=0;i<s.size()/2;i++){
        string x=complement(string(1,s[s.size()-i-1]));
        if(s[i]!=x[0])
            return false;
    }
        return true;
}
void Gene:: setRNA(string s){
    RNA=s;
}
void Gene:: setDNA(string s1,string s2){
    DNA[0]=s1;
    DNA[1]=s2;
}
void Gene::make_DNA(){
    DNA[0]=RNA;
    DNA[1]=complement(RNA);
}
 void Gene:: small_mutation_RNA(char a,char b,int n){
    int flag=0;
    for(int i=0;i<RNA.size();i++){
        if(RNA[i]==a && flag<n){
            RNA[i]=b;
            flag++;
        }
    }
    cout<<RNA<<endl;
 }
 void Gene::small_mutation_DNA(char a,char b,int n){
    int flag=0;
    for(int i=0;i<DNA[0].size();i++){
        if((DNA[0][i]==a || DNA[1][i]==a)&& flag<n){
            if(DNA[0][i]==a){
                DNA[0][i]=b;
                string x=complement(string(1,b));
                DNA[1][i]=x[0];
                flag++;
            }
            else{
                DNA[1][i]=b;
                string x=complement(string(1,b));
                DNA[0][i]=x[0];
                flag++;
            }
        }
    }
    cout<<DNA[0]<<endl<<DNA[1]<<endl;
 }
 void Gene::big_mutation_RNA(string s1,string s2){
    int pos=RNA.find(s1);
    RNA.replace(pos,s1.size(),s2);
    cout<<RNA<<endl;
 }
 void Gene::big_mutation_DNA(string s1,string s2){
     int pos1=DNA[0].size(),pos2=DNA[1].size();
     if(DNA[0].find(s1)!=string::npos)
        pos1=DNA[0].find(s1);
     if(DNA[1].find(s1)!=string::npos)
        pos2=DNA[1].find(s1);
    if(pos1<pos2){
        DNA[0].replace(pos1,s1.size(),s2);
        string temp=complement(s2);
        DNA[1].replace(pos1,s1.size(),temp);
    }
    else{
        DNA[1].replace(pos2,s1.size(),s2);
        string temp=complement(s2);
        DNA[0].replace(pos2,s1.size(),temp);
    }
    cout<<DNA[0]<<endl<<DNA[1];
 }
 void Gene::reverse_mutation_RNA(string s){
    if(RNA.find(s)!=string::npos){
        int pos=RNA.find(s);
        reverse(s.begin(),s.end());
        RNA.replace(pos,s.size(),s);
        cout<<RNA;
    }
    else
    cout<<"NOT FOUND!";
 }
void Gene::reverse_mutation_DNA(string s){
    int pos1=DNA[0].size(),pos2=DNA[1].size();
    if(DNA[0].find(s)!=string::npos)
        pos1=DNA[0].find(s);
    if(DNA[1].find(s)!=string::npos)
        pos2=DNA[1].find(s);

    reverse(s.begin(),s.end());
    string temp=complement(s);
    if(pos1<pos2){
        DNA[0].replace(pos1,s.size(),s);
        DNA[1].replace(pos1,s.size(),temp);
    }
    else{
        DNA[1].replace(pos2,s.size(),s);
        DNA[0].replace(pos2,s.size(),temp);
    }
    cout<<DNA[0]<<endl<<DNA[1];
}
void Cell:: show(){
for(int i=0;i<chro.size();i++){
    cout<<chro[i].DNA[0]<<endl
        <<chro[i].DNA[1]<<endl;
        
}
    
}
void Cell::receive_chro(int n){
    Gene g;
    for(int i=0;i<n;i++){
        string s1,s2;
        cin>>s1>>s2;
        g.DNA[0]=s1;
        g.DNA[1]=s2;
        chro.push_back(g);
    }
}
void Cell::die(){
    int count=0,count_AT=0,count_CG=0;
    for(int i=0;i<chro.size();i++){
        for(int j=0;j<chro[i].DNA[0].size();j++){
            string x=complement(string(1,chro[i].DNA[1][j]));
            if(chro[i].DNA[0][j]!=x[0])
                count++;
            if(chro[i].DNA[0][j]=='A'||chro[i].DNA[0][j]=='T')
                count_AT++;
            else
                count_CG++;

        }
        if(count>5 || count_AT>3*count_CG)
            chro.erase(chro.begin()+i);
    }
    show();
}
void Cell::small_mutation(char a,char b,int n,int m){
    m=m-1;
    int flag=0;
    string x=complement(string(1,b));
    for(int i=0;i<chro[m].DNA[0].size();i++){
        if((chro[m].DNA[0][i]==a || chro[m].DNA[1][i]==b)&& flag<n){
            if(chro[m].DNA[0][i]==a){
                chro[m].DNA[0][i]=b;
                chro[m].DNA[1][i]=x[0];
            }
            else{
                chro[m].DNA[1][i]=b;
                chro[m].DNA[0][i]=x[0];
            }
        }
    }
    show();
}
void Cell::big_mutation(string s1,int n,string s2,int m){
    n=n-1;
    m=m-1;
    int posn1=chro[n].DNA[0].size();
    int posn2=chro[n].DNA[1].size();
    int posm1=chro[m].DNA[0].size();
    int posm2=chro[m].DNA[1].size();
    if(chro[n].DNA[0].find(s1)!=string::npos)
        posn1=chro[n].DNA[0].find(s1);
    if(chro[n].DNA[1].find(s1)!=string::npos)
        posn2=chro[n].DNA[1].find(s1);
    if(chro[m].DNA[0].find(s2)!=string::npos)
        posm1=chro[m].DNA[0].find(s2);
    if(chro[m].DNA[1].find(s2)!=string::npos)
        posm2=chro[m].DNA[1].find(s2);
    if(posn1<posn2){
        chro[n].DNA[0].replace(posn1,s1.size(),s2);
        chro[n].DNA[1].replace(posn1,s1.size(),complement(s2));
    }
    else{
        chro[n].DNA[1].replace(posn2,s1.size(),s2);
        chro[n].DNA[0].replace(posn2,s1.size(),complement(s2));
    }
    if(posm1<posm2){
        chro[m].DNA[0].replace(posm1,s2.size(),s1);
        chro[m].DNA[1].replace(posm1,s2.size(),complement(s1));
    }
    else{
        chro[m].DNA[1].replace(posm2,s2.size(),s1);
        chro[m].DNA[0].replace(posm2,s2.size(),complement(s1));
    }
    show();
}       
void Cell::reverse_mutation(string s,int n){
    int pos1=chro[n-1].DNA[0].size();
    int pos2=chro[n-1].DNA[1].size();
    if(chro[n-1].DNA[0].find(s)!=string::npos)
        pos1=chro[n-1].DNA[0].find(s);
    if(chro[n-1].DNA[1].find(s)!=string::npos)
        pos2=chro[n-1].DNA[1].find(s);
    reverse(s.begin(),s.end());
    string temp=complement(s);
    if(pos1<pos2){
       chro[n-1].DNA[0].replace(pos1,s.size(),s);
       chro[n-1].DNA[1].replace(pos1,s.size(),temp); 
    }
    else{
       chro[n-1].DNA[1].replace(pos2,s.size(),s);
       chro[n-1].DNA[0].replace(pos2,s.size(),temp);  
    }
    show();
    }
void Cell::palindrome(int n){
    n=n-1;
    string s=chro[n].DNA[0];
    string s1=chro[n].DNA[1];
    for(int i=0;i<s.size();i++){
        string temp="";
        temp+=s[i];
        for(int j=i;j<s.size()-1;j++){
            temp+=s[j+1];
            if(is_palidrome(temp) && temp.size()>2 && temp.size()%2==0)
                cout<<temp<<endl;
        }

    }
      for(int i=0;i<s1.size();i++){
        string temp="";
        temp+=s1[i];
        for(int j=i;j<s1.size()-1;j++){
            temp+=s1[j+1];
            if(is_palidrome(temp) && temp.size()>2 && temp.size()%2==0)
                cout<<temp<<endl;
        }

    }
}
 