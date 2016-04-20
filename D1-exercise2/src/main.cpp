#include <iostream>
#include <fstream>
#include <cstdint>
#include "MyRNG.h"

using namespace std;

void print_output_file(string out, int N, double* dat){

  char* NameFile = &out[0];
  ofstream f(NameFile);

#ifdef __DEBUG
  cout << "Within print_output_file; namefile is " << out << endl;
#endif
  
  if(f.is_open()){
    
    for(int j = 0; j < N - 3; j++){
      for(int k = 0; k < 3; k++)
	f << dat[j + k] << "\t";
      f << endl;
    }    
    f.close();
  }
  else
    cout << "Unable to open file\n";
}

int main(int argc, char** argv){

  int Nrand = 10000;
  double* myrand = new double[Nrand];
  double correlation = 0.;
  
  MyRNG rng;
  rng.set_seed(1234);

  for(int j = 0; j < Nrand; j++)
    myrand[j] = rng.my_lcg();

  // calculate correlation
  for(int j = 0; j < Nrand-2; j++)
    correlation += myrand[j]*myrand[j+1];

  correlation /= Nrand;

  cout << "the correlation obtained for the obtained random sequence is: " << correlation << endl;

  print_output_file("RandLCG.dat", Nrand, myrand);
  
  delete [] myrand;

  return 0;
}
