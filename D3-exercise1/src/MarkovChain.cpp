#include <iostream>
#include <cmath>
#include "MarkovChain.h"

MarkovChain::MarkovChain(int N){

  dim_ = N;
  h_ = 0.1;
  N_Accept_ = 0;
  U01.SetSeed(1234);
  
#ifdef __DEBUG
  std::cout << "Within MarkovChain constructor; dimension of domain = " << dim_ << std::endl;
#endif

}

MarkovChain::~MarkovChain(){
#ifdef __DEBUG
  std::cout << "Within MarkovChain destructor;\n";
#endif
}

void MarkovChain::initialize(double* MyArr){

#ifdef __DEBUG
  std::cout << "Within MarkovChain::initialize function;\n";
#endif
  
  U01.FillArray(MyArr, dim_);
  std::cout << "MyDistribFunc: " << MyDistribFunc(MyArr) << std::endl;
}

double MarkovChain::MyDistribFunc(double* MyArr){

  double sum = 0.;

  for(int j = 0; j < dim_; j++){
    sum += MyArr[j];
    if(MyArr[j] < 0. or MyArr[j] > 1.)
      return 0.;
  }

  return sum / 5.;
}

double MarkovChain::GetNewPoint(double* MyArr){

  double* Next  = new double[dim_];
  double* MyRnd = new double[dim_];
  double P_Old, P_New, PJump, RetVal;
  
  U01.FillArray(MyRnd, dim_);
  
  for(int j = 0; j < dim_; j++)
    Next[j] = MyArr[j] + 2.*(MyRnd[j] - 0.5)*h_;

  P_Old = MyDistribFunc(MyArr);
  P_New = MyDistribFunc(Next);

  PJump = P_New / P_Old;

  if(PJump > 1.){
    for(int j = 0; j < dim_; j++)
      MyArr[j] = Next[j];

    RetVal = P_New;
    N_Accept_++;
  }
  else if(PJump > U01.ExtractRN()){
    for(int j = 0; j < dim_; j++)
      MyArr[j] = Next[j];

    RetVal = P_New;
    N_Accept_++;
  }
  else
    RetVal = P_Old;
  
  delete [] Next;
  delete [] MyRnd;

  return RetVal;
}
