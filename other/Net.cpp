#include "Net.h"
#include <stdlib.h>
#include <math.h>

Net::Net(unsigned char _size, unsigned char * layer) {
  size = _size;
  layers = new Layer[size];
  for(unsigned char a=0;a<size;++a) {
    layers[a].nodes = new Neuron[layer[a]];
    if(a<size-1)
      for(unsigned char n=0;n<layer[a];++n) {
	for(unsigned char x=0;x<layer[a+1];++x)
	  layers[a].nodes[n].values.push_back(((double)rand())/(RAND_MAX/2)-1);
      }
  }
}

double Net::get(unsigned char n) {
  Layer * l = layers + size-1;
  if(n < l->size ) {
    return getValue(l->nodes + n);
  }else{
    return -100; // bad
  }
}

double Net::getValue(Neuron * n) {
  double ret=0;
  for(unsigned char c=0;c < n->inputs.size(); ++c) 
    ret += n->inputs[c];
  return ret;
}

void Net::run(double * input) {
  // load in the first layer data
  for(unsigned char first=0;first<layers->size;++first) {
    layers->nodes[first].inputs[0] = input[first];
  }
  
  Layer * working = layers;
  for(unsigned char on=1;on<size;++on) { // each layer
    for(unsigned char node=0;node<working->size;++node) { // each node
      double value = getValue(working->nodes + node);
      for(unsigned char val=0;val < working->nodes[node].values.size(); ++val) { // each value
      }
    }
    ++working;
  }

}


double Net::sigmoid(double x) {
  
}
