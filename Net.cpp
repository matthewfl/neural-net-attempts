#include "Net.h"

#include <stdlib.h>
#include <vector>
#include <math.h>

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


void Net::swap (Net * other) {
  unsigned int temp = size;
  Layer * lTemp = layers;
  size = other->size;
  layers = other->layers;
  other->size = temp;
  other->layers = lTemp;
}

Net & Net::operator= (Net & o) {
  Net nn(o);
  swap(&nn);
  return *this;
}

Net::~Net () {
  for(unsigned int working=0;working < size; ++working) {
    delete[] layers[working].nodes;
  }
  delete[] layers;
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

void Net::run (double * input) {
  // clean up Net before running
  zero();
  // load the data into the Neural Net
  for(unsigned char load = 0; load < layers->size; ++load) {
    layers->nodes[load].value = input[load];
  }
  
  // comput the data
  for(unsigned int working=0; working < size-1; ++working) { // layer
    for(unsigned char node =0; node < layers[working].size; ++node) { // node
      for(unsigned char weight=0;weight < layers[working].nodes[node].weight.size(); ++weight) { // weight
	layers[working+1].nodes[weight].value += layers[working].nodes[node].value * layers[working].nodes[node].weight[weight];
      }
    }
  }
}

double Net::get(unsigned char node) {
  if(layers[size-1].size > node)
    return layers[size-1].nodes[node].value;
  return -100; // bad
}

double Net::check(Net::Teaching * teach) {
  double diff=0;
  unsigned char count=0;
  if(teach->inputSize == layers->size) {
    run(teach->input);
    for(unsigned char check=0; check < layers[size-1].size; ++check) {
      ++count;
      diff += abs(get(check) - teach->result[check]);
    }
  }
  return diff/count;
}

double Net::check(Net::Teaching * teach, unsigned int count) {
  double out=0;
  for(unsigned int working = 0; working < count; ++working) {
    out += check(teach + working);
  }
  return count/out;
}

void Net::build (vector<Net::Grade> data) {
  double total=0;
  for(unsigned int working=0; working < data.size(); ++working) {
    total += data[working].grade;
  }
  for(unsigned int working=0; working < data.size(); ++working) {
    data[working]._part = data[working].grade/total;
  }
}
