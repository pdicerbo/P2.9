#ifndef __MYRNG
#define __MYRNG

class MyRNG{

public:
  MyRNG();
  MyRNG(double, double);
  ~MyRNG();
  void SetSeed(int);
  int GetSeed();
  double ExtractRN();
  void FillArray(double*, int);
  
private:
  int a_ = 16807;
  int m_ = 2147483647;
  int q_ = (int) (m_/a_);
  int r_ = m_ % a_;
  int seed_, status_;
  double xmin_ = 0.;
  double xmax_ = 1.;
};

#endif /* __MYRNG.H */
