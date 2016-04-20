#include <iostream>

using namespace std;

class MyRNG{

public:
  MyRNG(int, int);
  ~MyRNG();
  void set_seed(int);
  int get_seed();
  double my_lcg();
  
private:
  int a_, m_, q_, r_, seed_, status_;

};

MyRNG::MyRNG(int a, int m){

#ifdef __DEBUG
  cout << "Within constructor;\n";
#endif
  a_ = a;
  m_ = m;
  q_ = (int) (m/a);
  r_ = m % a;
  
}

MyRNG::~MyRNG(){
#ifdef __DEBUG
  cout << "Within distructor\n";
#endif
}

void MyRNG::set_seed(int s){
  seed_ = s;
  status_ = s;

#ifdef __DEBUG
  cout << "Choosed seed is " << seed_ << endl;
#endif
}

int MyRNG::get_seed(){
#ifdef __DEBUG
  cout << "Within actual_seed function\n";
#endif
  return seed_;
}

double MyRNG::my_lcg(){
  int next = a_ * (status_ % q_) - r_ * (status_ / q_);

#ifdef __DEBUG
  cout << "Within my_lcg function\n";
#endif
  
  if(next < 0)
    next += m_;

  status_ = next;

  return ((double) next) / ((double) m_);
}

int main(int argc, char** argv){

  int m = 2147483647;
  int a = 16807;
  // int Nrand = 10000;
  int Nrand = 10;
  MyRNG rng(a, m);
  double myrand;
  
  rng.set_seed(1234);

  for(int j = 0; j < Nrand; j++){
    myrand = rng.my_lcg();
    cout << "Random number " << j << " is " << myrand << endl;
  }  

  return 0;
}
