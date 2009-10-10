#ifndef _NeuralNet_NeuralNet_h
#define _NeuralNet_NeuralNet_h

#include "config.h"
#include "pre.h"

#include <vector>
#include <string>x
#include <matthewfl/pointpool.hpp>

namespace NeuralNet {
  class Net {
  private:
    std::vector<Neuron*> first;
    std::vector<Neuron*> last;
    matthewfl::PointPool point;
    void compute (Neuron*);
  public:
    Net (std::string);
    ~Net ();
    std::string save ();
    std::vector <int> run(std::vector<int>);
  };

}


#endif
