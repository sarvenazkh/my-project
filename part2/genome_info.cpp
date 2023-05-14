#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include <Eigen/Dense>
#include "genome_info.h"

void Chromosome_info::mkMapPosFromLocus_info()
{
    MapPos.resize(get_num_loci());
    for(unsigned i=0;i<MapPos.size();i++){
        MapPos[i]=(*this)[i].map_pos;
    }
}

unsigned Genome_info::getTotalLoci()
{
    unsigned totalLoci=0;
    for(auto &i: *this   ){
        totalLoci += i.get_num_loci();
    }
    
    return(totalLoci);
}
