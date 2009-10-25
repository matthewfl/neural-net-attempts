#ifndef _Net_h
#define _Net_h

#include "Data.h"


class Net {
 private:
  unsigned char size;
  Layer * layers;
  double beta;
  double getValue(Neuron*);
  double sigmoid(double);
  void targetValues ();
 public:
  Net(unsigned char, unsigned char*);
  void run (double*);
  double get(unsigned char);
  void teach (double*, double*);
};



#endif
