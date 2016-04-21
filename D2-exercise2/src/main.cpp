#include <iostream>
#include <fstream>
#include <cmath>
#include "MyRNG.h"
#include "GaussRNG.h"

#define pi 3.14159265358979323846

using namespace std;

double MyFunc(double* MyArr, double sigma, int N){

  double sum = 0.;
  double val;
  
  for(int j = 0; j < N; j++)
    sum += MyArr[j]*MyArr[j];

  val = sum*exp(-sum/(2.*sigma*sigma));
  
  return val;
}

int main(int argc, char** argv){

  int Nrand = 20000;
  int SpaceDim = 10;
  double* MyRand = new double[SpaceDim];
  double MeanF = 0.;
  double MeanFSquare = 0.;
  double FuncVal, MyIntegral, MySigmaSquare;
  double sigma = 1.;
  double RealValue = 10*pow(2.*pi,5);
  double MyVolume  = pow(12.*sigma, 10);
  
  MyRNG rng(-6.*sigma, 6.*sigma); // the range of MyFunc is [-6.*sigma,6.*sigma]

  rng.SetSeed(1234);
      
  for(int k = 0; k < Nrand; k++){
    rng.FillArray(MyRand, SpaceDim);
    FuncVal = MyFunc(MyRand, sigma, SpaceDim);
    
    MeanF += FuncVal;
    MeanFSquare += FuncVal * FuncVal;
  }

  MeanF /= (double) Nrand;
  MeanFSquare /= Nrand;

  MyIntegral = MeanF * MyVolume; // 12.*sigma is the size of the interval
  MySigmaSquare = 1./(Nrand - 1) * (MeanFSquare - MeanF * MeanF);
  
  cout << "With " << Nrand << " evaluation, \n\tMyIntegral = " << MyIntegral <<
    "; TrueValue = " << RealValue <<
    "; the difference with true value is " << MyIntegral - RealValue <<
    " sigma = " << MyVolume*sqrt(MySigmaSquare) << endl;

  
  delete [] MyRand;

  return 0;
}
