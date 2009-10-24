#ifndef _Net_h
#define _Net_h

#include <vector>
#include "Data.h"

class Net {
 private:
  std::vector<unsigned char> layerSize;
  short working;
  Layer * Layers;
  double beta;
  void processLayer(Layer*);
  void processNeuron(Neuron*);
  void teachLayer(Layer*);
  void teachNeuron(Neuron*);

  double sCurve(int, double);
 public:
  Net(std::vector<unsigned char>);
  std::vector<float> run(std::vector<float>);
  float teach(std::vector<float>, std::vector<float>);
  void fix(double);
};


#endif
