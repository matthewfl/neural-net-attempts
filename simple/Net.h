#ifndef _Net_h
#define _Net_h

#include <vector>
struct Neuron;

class Net {
 private:
  std::vector<unsigned char> size;
  std::vector <short> process(Neuron*, std::vector<short>);
 public:
  Net(std::vector<unsigned char>);
  void load (); // some data needed
  std::vector<short> run (std::vector<short>);
  
};


#endif
