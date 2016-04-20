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
  
  if(next < 0)
    next += m_;

  status_ = next;

  return ((double) next) / ((double) m_);
}

