#ifndef __MYRNG
#define __MYRNG

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

#endif /* __MYRNG.H */
