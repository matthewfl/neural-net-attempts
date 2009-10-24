#ifndef _Net_h
#define _Net_h

#include "Data.h"


class Net {
 private:
  unsigned char size;
  Layer * layers;
  double getValue(Neuron*);
  double sigmoid(double);
 public:
  Net(unsigned char, unsigned char*);
  void run (double*);
  double get(unsigned char);
};



#endif
