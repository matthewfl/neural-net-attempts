#include "Net.h"

#include <stdlib.h>
#include <vector>

using namespace std;

Net::Net (Net * from) { // make a copy of the Neural Net
  size = from->size;
  layers = new Layer[size];
  for(unsigned int working = 0; working < size; ++working) {
    layers[working].size = from->layers[working].size;
    layers[working].nodes = new Neuron[layers[working].size];
    for(unsigned char node = 0; node < layers[working].size; ++node) {
      layers[working].nodes[node].weight = from->layers[working].nodes[node].weight;
    }
  }
}

Net::Net (vector<unsigned char> ss) {
  size = ss.size();
  layers = new Layer[size];
  for(unsigned int working = 0; working < ss.size(); ++working) {
    layers[working].size = ss[working];
    layers[working].nodes = new Neuron[layers[working].size];
    if(working < ss.size()-1)
      for(unsigned char node = 0; node < layers[working].size; ++node) {
	for(unsigned char weight = 0; weight < ss[working+1]; ++weight) {
	  layers[working].nodes[node].weight.push_back( ((double)rand()*2)/RAND_MAX -1 );
	}
      }
  }
}

vector<unsigned char> Net::Size () {
  vector<unsigned char> ret;
  for(unsigned int working = 0; working < size; ++working) {
    ret.push_back(layers[working].size);
  }
  return ret;
}

void Net::zero () {
  /// zero out all of the values before running
  for(unsigned int working = 0; working < size; ++working) {
    for(unsigned char node = 0; node < layers[working].size; ++node) {
      layers[working].nodes[node].value = 0;
    }
  }
}


