#include <iostream>
#include <fstream>
#include <cmath>
#include "MyRNG.h"
#include "GaussRNG.h"

using namespace std;

double MyFunc(double* MyArr, int N){

  double sum = 0.;
  
  for(int j = 0; j < N; j++)
    sum += MyArr[j];

  return sum*sum;
}

int main(int argc, char** argv){

  int Nend = 200000;
  int SpaceDim = 10;
  double* MyRand = new double[SpaceDim];
  double MeanF = 0.;
  double MeanFSquare = 0.;
  double FuncVal, MyIntegral, MySigmaSquare;
  
  MyRNG rng; // the range of MyFunc is [0,1]

  ofstream f("MyIntegral.dat");
  
  for(int Nrand = 1000; Nrand <= Nend; Nrand += 1000){

    rng.SetSeed(1234);
    MeanF = 0.;
    MeanFSquare = 0.;
    
    for(int k = 0; k < Nrand; k++){
      rng.FillArray(MyRand, SpaceDim);
      FuncVal = MyFunc(MyRand, SpaceDim);
      
      MeanF += FuncVal;
      MeanFSquare += FuncVal * FuncVal;
      
    }
    
    MyIntegral = MeanF /((double) Nrand);
    MeanFSquare /= Nrand;
    MySigmaSquare = 1./(Nrand - 1) * (MeanFSquare - MyIntegral);
    
    cout << "MyIntegral = " << MyIntegral << " diff = " << MyIntegral - 155./6. <<
      " sigma_square = " << MySigmaSquare << endl;

    f << Nrand << "\t" << MyIntegral << "\t" << sqrt(MySigmaSquare) << endl;
  }

  f.close();
  
  delete [] MyRand;

  return 0;
}
