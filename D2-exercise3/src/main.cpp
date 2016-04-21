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

double MyProbDistrib(double* MyArr, double sigma, int N){

  double sum = 0.;
  double val;
  
  for(int j = 0; j < N; j++)
    sum += MyArr[j]*MyArr[j];

  val = exp(-sum/(2.*sigma*sigma))*pow(2.*pi*sigma*sigma,-5);
  
  return val;
}

int main(int argc, char** argv){

  int Nend = 20000;
  int SpaceDim = 10;
  double* MyRand = new double[SpaceDim];
  double MeanF, MeanFSquare;
  double FuncVal, MyIntegral, MySigmaSquare;
  double sigma = 1.;
  double RealValue = 10*pow(2.*pi,5);
  
  GaussRNG rng(0., sigma);
  ofstream f("MyIntegral.dat");
  
  for(int Nrand = 100; Nrand < Nend; Nrand += 100){
    rng.SetSeed(1234);
    MeanF = 0.;
    MeanFSquare = 0.;
    
    for(int k = 0; k < Nrand; k++){
      rng.FillArray(MyRand, SpaceDim);
      
      FuncVal = MyFunc(MyRand, sigma, SpaceDim);
      FuncVal /= MyProbDistrib(MyRand, sigma, SpaceDim);
      
      MeanF += FuncVal;
      MeanFSquare += FuncVal * FuncVal;
    }

    MeanF /= (double) Nrand;
    MeanFSquare /= Nrand;
    
    MyIntegral = MeanF;
    MySigmaSquare =  (MeanFSquare - MeanF * MeanF)/(Nrand - 1);

    f << Nrand << "\t" << MyIntegral << "\t" << sqrt(MySigmaSquare) << endl;
  }

  cout << "With " << Nend << " evaluation, \n\tMyIntegral = " << MyIntegral <<
    "; TrueValue = " << RealValue <<
    "; the difference with true value is " << MyIntegral - RealValue <<
    " sigma = " << sqrt(MySigmaSquare) << endl;

  f.close();
  
  delete [] MyRand;

  return 0;
}
