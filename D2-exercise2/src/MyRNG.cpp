#include <iostream>
#include <fstream>
#include <cstdint>
#include "MyRNG.h"

MyRNG::MyRNG(){
#ifdef __DEBUG
  std::cout << "Within MyRNG constructor;\na = " << a_ << " m = " << m_ <<
    " q = " << q_ << " r = " << r_ << std::endl;
#endif
}

MyRNG::MyRNG(double a, double b){
#ifdef __DEBUG
  std::cout << "Within MyRNG(double, double) constructor;\na = " << a_ << " m = " << m_ <<
    " q = " << q_ << " r = " << r_ << std::endl;
#endif
  xmin_ = a;
  xmax_ = b;
}

MyRNG::~MyRNG(){
#ifdef __DEBUG
  std::cout << "Within MyRNG destructor\n";
#endif
}

void MyRNG::SetSeed(int s){
  seed_ = s;
  status_ = s;

#ifdef __DEBUG
  std::cout << "Within MyRNG::SetSeed function\nChoosed seed is " << seed_ << std::endl;
#endif
}

int MyRNG::GetSeed(){
#ifdef __DEBUG
  std::cout << "Within MyRNG::GetSeed function\n";
#endif
  return seed_;
}

double MyRNG::ExtractRN(){
  int next = a_ * (status_ % q_) - r_ * (status_ / q_);
  double rn;
  
  if(next < 0)
    next += m_;

  status_ = next;

  rn = ((double) next) / ((double) m_);
  
  return (xmin_ + (xmax_-xmin_)*rn);
}

void MyRNG::FillArray(double* arr, int N){

  for(int j = 0; j < N; j++)
    arr[j] = this->ExtractRN();

}
