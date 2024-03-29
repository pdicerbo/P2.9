#include <iostream>
#include <fstream>
#include <cstdint>

using namespace std;

class MyRNG{

public:
  MyRNG();
  ~MyRNG();
  void SetSeed(int);
  int GetSeed();
  double ExtractRN();
  
private:
  int a_ = 16807;
  int m_ = 2147483647;
  int q_ = (int) (m_/a_);
  int r_ = m_ % a_;
  int seed_, status_;
};

MyRNG::MyRNG(){
#ifdef __DEBUG
  cout << "Within MyRNG constructor;\na = " << a_ << " m = " << m_ <<
    " q = " << q_ << " r = " << r_ << endl;
#endif
}

MyRNG::~MyRNG(){
#ifdef __DEBUG
  cout << "Within MyRNG destructor\n";
#endif
}

void MyRNG::SetSeed(int s){
  seed_ = s;
  status_ = s;

#ifdef __DEBUG
  cout << "Within MyRNG::SetSeed function:\nChoosed seed is " << seed_ << endl;
#endif
}

int MyRNG::GetSeed(){
#ifdef __DEBUG
  cout << "Within MyRNG::GetSeed function\n";
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

class BadRNG{

public:
  BadRNG();
  ~BadRNG();
  void SetSeed(int);
  int GetSeed();
  double InfamousChoice();
  
private:
  int64_t a_ = 65539;
  int64_t m_ = 2147483648;
  int64_t q_, r_, seed_, status_;

};

BadRNG::BadRNG(){

#ifdef __DEBUG
  cout << "Within BadRNG constructor;\na = " << a_ << " m = " << m_ << endl;
#endif

  q_ = (int) (m_/a_);
  r_ = m_ % a_;
  
}

BadRNG::~BadRNG(){
#ifdef __DEBUG
  cout << "Within BadRNG destructor\n";
#endif
}

void BadRNG::SetSeed(int s){
  seed_ = s;
  status_ = s;

#ifdef __DEBUG
  cout << "Within BadRNG::SetSeed function:\nChoosed seed is " << seed_ << endl;
#endif
}

int BadRNG::GetSeed(){
#ifdef __DEBUG
  cout << "Within BadRNG::GetSeed function\n";
#endif
  return seed_;
}

double BadRNG::InfamousChoice(){
  int64_t next = (a_ * status_) % m_;

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
  rng.SetSeed(1234);

  for(int j = 0; j < Nrand; j++)
    myrand[j] = rng.ExtractRN();

  // calculate correlation
  for(int j = 0; j < Nrand-2; j++)
    correlation += myrand[j]*myrand[j+1];

  correlation /= Nrand;

  cout << "the correlation obtained for the obtained random sequence is: " << correlation << endl;

  print_output_file("RandLCG.dat", Nrand, myrand);

  // "infamous" section
  BadRNG InfCh;
  InfCh.SetSeed(1234);

  for(int j = 0; j < Nrand; j++)
    myrand[j] = InfCh.InfamousChoice();

  // calculate correlation
  for(int j = 0; j < Nrand-2; j++)
    correlation += myrand[j]*myrand[j+1];

  correlation /= Nrand;

  cout << "the correlation obtained for the obtained random sequence is: " << correlation << endl;
  print_output_file("InfamousLCG.dat", Nrand, myrand);
  
  delete [] myrand;

  return 0;
}
