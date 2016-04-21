#ifndef __GAUSSRNG
#define __GAUSSRNG

#include "MyRNG.h"

class GaussRNG{

 public:
  GaussRNG(double, double);
  ~GaussRNG();
  void SetSeed(int);
  int GetSeed();
  double ExtractRN();
  void FillArray(double*, int);
  
 private:
  bool IsNotVoid_;
  MyRNG U_;
  double mean_, sigma_;
  double NextVal_;
};
#endif
