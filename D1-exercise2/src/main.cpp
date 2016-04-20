#include <iostream>
#include <fstream>
#include <cstdint>
#include "MyRNG.h"
#include "GaussRNG.h"

using namespace std;

int main(int argc, char** argv){

  int Nrand = 200000;
  double* myrand = new double[Nrand];

  GaussRNG rng(0., 0.5);

  rng.SetSeed(1234);

  for(int j = 0; j < Nrand; j++)
    myrand[j] = rng.ExtractRN();

  // Histogram data
  double xmin = -3., xmax = 3.;
  int Nbin = 60, NData = 0;
  int index;
  double delta = (xmax - xmin) / ((double) Nbin);

  double* x_vec = new double[Nbin];
  int* n_data = new int[Nbin];
  
  for(int j = 0; j < Nbin; j++){
    // array with the mean point of all the bins
    x_vec[j]  = xmin + (2*j+1)*0.5*delta;
    // bin size
    n_data[j] = 0;
  }
  
  for(int j = 0; j < Nrand; j++){
    index = (int) ((myrand[j] - xmin) / delta);

    if(myrand[j] < xmin or myrand[j] > xmax)
      continue;

    NData++;
    n_data[index]++;
  }

  ofstream f("NormGauss.dat");

  for(int j = 0; j < Nbin; j++)
    f << x_vec[j] << "\t" << n_data[j]/(NData*delta) << endl;

  f.close();

  delete [] myrand;

  return 0;
}
