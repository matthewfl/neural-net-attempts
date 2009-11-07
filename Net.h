#ifndef _Net_h
#define _Net_h

#include <vector>

class Net {
 public:
  struct Neuron {
    double value;
    std::vector<double> weight;
  };
  struct Layer {
    unsigned char size;
    Neuron * nodes;
  };

 private: ////
  unsigned int size;
  Layer * layers;
 public: ////
  Net (Net *);
  Net (std::vector<unsigned char>);
  std::vector<unsigned char> size ();

};


#endif
