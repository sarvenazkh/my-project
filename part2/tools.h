#ifndef __GenSim1_3__tools__
#define __GenSim1_3__tools__

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include <string>
#include <Eigen/Dense>
#include <random>
#include <time.h>


using namespace Eigen;
using namespace std;

static default_random_engine randGenTool;
VectorXi sample_without_replace(VectorXi &vec , int k); 


double getDouble(std::string& Str) ;  


class corrClass{
public:
    float sumA,sumB;
    float sumA2,sumB2,sumAB;
    float varA,varB,covAB,r,alpha,beta,num;
    float meanA,meanB;
    unsigned n;
    Eigen::ArrayXf vecA,vecB;
    
    corrClass(unsigned dim);
    void initialize(Eigen::VectorXf a, Eigen::VectorXf b);
    void getCorr(void);
    float getVariance(Eigen::VectorXf a);
};

string currentDateTime();



#endif  