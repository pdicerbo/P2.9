#include <iostream>
#include <fstream>
#include <cmath>
#include "MyRNG.h"
#include "GaussRNG.h"
#include "MarkovChain.h"

//#define pi 3.14159265358979323846

using namespace std;

double MyFunc(double* MyArr, int N){

  double sum = 0.;
  
  for(int j = 0; j < N; j++)
    sum += MyArr[j];

  return sum*sum;
}

int main(int argc, char** argv){

  int Nend = 20000;
  int SpaceDim = 10;
  double* MyRand = new double[SpaceDim];
  double MyP, MeanF, MeanFSquare;
  double FuncVal, MyIntegral, MySigmaSquare;
  double RealValue = 155./6.;
  
  MarkovChain MC(SpaceDim);

  MC.initialize(MyRand);

  ofstream f("MyInteg.dat");
  
  int Nrand = 200000;
  int counter = 0;
  MeanF = 0.;
  MeanFSquare = 0.;
  MySigmaSquare = 0.;
    
  for(int k = 0; k < Nrand; k++){
      MyP = MC.GetNewPoint(MyRand);
      
      FuncVal = MyFunc(MyRand, SpaceDim);
      FuncVal /= MyP;

      if((k+1) % 101 == 0){
	counter++;
	MeanF += FuncVal;
	MeanFSquare += FuncVal * FuncVal;

	MyIntegral = MeanF / counter;
	
	MySigmaSquare =  (MeanFSquare/counter - MyIntegral * MyIntegral)/(counter+1);

	f << k << "\t" << MyIntegral << "\t" << sqrt(MySigmaSquare) << endl;
      }
  }

  cout << "With " << Nend << " evaluation, \n\tMyIntegral = " << MyIntegral <<
    "; TrueValue = " << RealValue <<
    "; the difference with true value is " << MyIntegral - RealValue <<
    " sigma = " << sqrt(MySigmaSquare) << endl;

  f.close();
  
  delete [] MyRand;

  return 0;
}
