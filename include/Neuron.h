#ifndef _NeuralNet_Neuron_h
#define _NeuralNet_Neuron_h

#include "config.h"
#include "pre.h"

namespace NeuralNet {
  class Neuron {
  private:
    friend class Net;
    Neuron ();
  public:
    ~Neuron ();
  };
};

#endif
