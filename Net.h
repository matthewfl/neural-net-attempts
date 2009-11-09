#ifndef _Net_h
#define _Net_h

#include <vector>

class Net {
 public:
  struct Neuron {
    double value;
    double bias;
    std::vector<double> weight;
  };
  struct Layer {
    unsigned char size;
    Neuron * nodes;
  };
  struct Grade {
    Net * net;
    double grade;
    double _part;
  };
  struct Teaching {
    unsigned char inputSize, resultSize;
    double * input;
    double * result;
  };

 private: ////
  unsigned int size;
  Layer * layers;
  void zero ();
  void swap(Net*);
  void nodeFix();
  void backpropagation (Teaching*);
  void enumerate(std::vector<Grade>&); 
  void emptyGrade(std::vector<Grade>&);
 public: ////
  bool operator == (Net&);
  Net& operator = (Net&);
  ~Net ();
  Net (Net *);
  Net (std::vector<unsigned char>);
  std::vector<unsigned char> Size ();
  void run (double*);
  double get (unsigned char);
  double check (Teaching*);
  double check(Teaching*, unsigned int);
  void build(std::vector<Grade>);
  void teach (Teaching*, unsigned int, float);
  
};


#endif
