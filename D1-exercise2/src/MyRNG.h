#ifndef __MYRNG
#define __MYRNG

class MyRNG{

public:
  MyRNG();
  ~MyRNG();
  void set_seed(int);
  int get_seed();
  double my_lcg();
  
private:
  int a_ = 16807;
  int m_ = 2147483647;
  int q_ = (int) (m_/a_);
  int r_ = m_ % a_;
  int seed_, status_;
};

#endif /* __MYRNG.H */
