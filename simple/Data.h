#ifndef _Data_h
#define _Data_h

#include <vector>

struct Neuron {
  std::vector<float> values;
  double input;
  double error;
};

struct Layer {
  unsigned char size;
  Neuron * nodes;
};



#endif
