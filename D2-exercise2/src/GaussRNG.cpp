#include <iostream>
#include <cmath>
#include "GaussRNG.h"

#define pi 3.14159265358979323846

GaussRNG::GaussRNG(double mean, double sigma){

  mean_  = mean;
  sigma_ = sigma;
  IsNotVoid_ = false;
  
#ifdef __DEBUG
  std::cout << "Within GaussRNG constructor; mean = " << mean_ << " sigma " << sigma_ << std::endl;
#endif

}

GaussRNG::~GaussRNG(){
#ifdef __DEBUG
  std::cout << "Within GaussRNG destructor;\n";
#endif
}

void GaussRNG::SetSeed(int s){
#ifdef __DEBUG
  std::cout << "Within GaussRNG::SetSeed function; seed = " << s << "\n";
#endif
  U_.SetSeed(s);
}

int GaussRNG::GetSeed(){
#ifdef __DEBUG
  std::cout << "Within GaussRNG::GetSeed function;\n";
#endif
  return U_.GetSeed();
}

double GaussRNG::ExtractRN(){
  double R, theta, u0, u1;

  if(IsNotVoid_){

    IsNotVoid_ = false;

    return NextVal_;
  }
  else{
    u0 = U_.ExtractRN();
    u1 = U_.ExtractRN();
  
    R = sqrt(-2.*sigma_*sigma_*log(1. - u0));
    theta = 2.*pi*u1;
    
    NextVal_ = R*sin(theta) + mean_;
    IsNotVoid_ = true;
    
    return (R*cos(theta)+mean_);
  }
}
