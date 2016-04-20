#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

class MyRNG{

public:
  MyRNG();
  ~MyRNG();
  void set_seed(int);
  int get_seed();
  double my_lcg();
  double infamous_choice();
  
private:
  int a_ = 16807;
  int m_ = 2147483647;
  int q_, r_, seed_, status_;

};

MyRNG::MyRNG(){

#ifdef __DEBUG
  cout << "Within constructor;\na = " << a_ << " m = " << m_ << endl;
#endif
  q_ = (int) (m_/a_);
  r_ = m_ % a_;
  
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

// #ifdef __DEBUG
//   cout << "Within my_lcg function\n";
// #endif
  
  if(next < 0)
    next += m_;

  status_ = next;

  return ((double) next) / ((double) m_);
}

double MyRNG::infamous_choice(){
  int64_t next = (a_ * status_);
  next = next % m_;

  status_ = (int) next;

  return ((double) next) / ((double) m_);
}

class BadRNG{

public:
  BadRNG();
  ~BadRNG();
  void set_seed(int);
  int get_seed();
  double infamous_choice();
  
private:
  int64_t a_ = 65539;
  int64_t m_ = 2147483648;
  int64_t q_, r_, seed_, status_;

};

BadRNG::BadRNG(){

#ifdef __DEBUG
  cout << "Within constructor;\na = " << a_ << " m = " << m_ << endl;
#endif

  q_ = (int) (m_/a_);
  r_ = m_ % a_;
  
}

BadRNG::~BadRNG(){
#ifdef __DEBUG
  cout << "Within distructor\n";
#endif
}

void BadRNG::set_seed(int s){
  seed_ = s;
  status_ = s;

#ifdef __DEBUG
  cout << "Choosed seed is " << seed_ << endl;
#endif
}

int BadRNG::get_seed(){
#ifdef __DEBUG
  cout << "Within actual_seed function\n";
#endif
  return seed_;
}

double BadRNG::infamous_choice(){
  int64_t next = (a_ * status_);
  next = next % m_;

  status_ = next;

  return ((double) next) / ((double) m_);
}


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
    
    // f << N << " ciao\n";

    f.close();
  }
  else
    cout << "Unable to open file\n";
}

int main(int argc, char** argv){

  int Nrand = 10000;
  // int Nrand = 10;
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

  // "infamous" section
  BadRNG InfCh;
  InfCh.set_seed(1234);

  for(int j = 0; j < Nrand; j++)
    myrand[j] = InfCh.infamous_choice();

  // calculate correlation
  for(int j = 0; j < Nrand-2; j++)
    correlation += myrand[j]*myrand[j+1];

  correlation /= Nrand;

  cout << "the correlation obtained for the obtained random sequence is: " << correlation << endl;
  print_output_file("InfamousLCG.dat", Nrand, myrand);
  
  delete [] myrand;

  return 0;
}
