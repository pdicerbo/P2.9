#include <iostream>
#include <fstream>
#include <cstdint>
#include "MyRNG.h"

MyRNG::MyRNG(){
#ifdef __DEBUG
  std::cout << "Within constructor;\na = " << a_ << " m = " << m_ <<
    " q = " << q_ << " r = " << r_ << std::endl;
#endif
}

MyRNG::~MyRNG(){
#ifdef __DEBUG
  std::cout << "Within distructor\n";
#endif
}

void MyRNG::set_seed(int s){
  seed_ = s;
  status_ = s;

#ifdef __DEBUG
  std::cout << "Choosed seed is " << seed_ << std::endl;
#endif
}

int MyRNG::get_seed(){
#ifdef __DEBUG
  std::cout << "Within actual_seed function\n";
#endif
  return seed_;
}

double MyRNG::my_lcg(){
  int next = a_ * (status_ % q_) - r_ * (status_ / q_);
  
  if(next < 0)
    next += m_;

  status_ = next;

  return ((double) next) / ((double) m_);
}

