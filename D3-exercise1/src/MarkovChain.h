#ifndef __MARKOVCHAIN
#define __MARKOVCHAIN

#include "MyRNG.h"

class MarkovChain{

 public:
  MarkovChain(int);
  ~MarkovChain();
  void initialize(double*);
  double GetNewPoint(double*);
  
 private:
  MyRNG U01;
  double MyDistribFunc(double*);
  int dim_;
  double h_;
  int N_Accept_;
};
#endif
