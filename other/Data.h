#ifndef _Data_h
#define _Data_h

#include <vector>

struct Neuron {
  std::vector<double> values, inputs;
  double error;
  double target;
};

struct Layer {
  unsigned char size;
  Neuron * nodes;
};

#endif
