#include "Net.h"
#include <stdlib.h>
#include <math.h>

// quick

#include <iostream>
#define debug(n) \
  std::cout << __FILE__ << ":" << __LINE__ << "\t" << n << "\n";

Net::Net(unsigned char _size, unsigned char * layer) {
  beta = .25;
  size = _size;
  layers = new Layer[size];
  for(unsigned char a=0;a<size;++a) {
    layers[a].nodes = new Neuron[layer[a]];
    layers[a].size = layer[a];
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
  for(unsigned char c=0;c < n->inputs.size(); ++c) { 
    ret += n->inputs[c];
    debug(n->inputs[c]);
  }
  // get the avg
  return ret/n->inputs.size();
  //return ret;
}

void Net::run(double * input) {
  // load in the first layer data
  for(unsigned char first=0; first<layers->size; ++first) {
    layers->nodes[first].inputs.push_back(input[first]);
  }
  
  Layer * working = layers;
  Layer * endL = layers + size-1;
  //for(unsigned char on=0; on<size; ++on) { // each layer
  while (working != endL) {  // each layer
    Layer * sending = working+1;
    debug(working << " " << sending);
    for(unsigned char node=0; node<working->size; ++node) { // each node
      Neuron * of = working->nodes + node;
      double value = getValue(of);
      debug("value " << value);
      Neuron * sendNode = sending->nodes;
      for(unsigned char val=0; val < of->values.size(); ++val) { // each value
	debug(of->values[val] * value);
	debug(sendNode->inputs.size());
	sendNode->inputs.push_back(of->values[val] * value);

	++sendNode;
      }
      debug(sending->nodes[0].inputs.size());
    }
    ++working;
  }

}

void Net::teach (double * in, double * target) {
  run(in);
  Layer * working = layers + size-1;
  
  double tempError;
  // compute the error for the output layer
  for(unsigned char node = 0; node < working->size; ++node) {
    working->nodes[node].target = target[node];
    tempError = target[node] - getValue(working->nodes + node);
    working->nodes[node].error = pow(tempError,3);
  }
  Layer * endL = working;
  working = layers;
  while(working != endL) { // each layer
    targetValues();
    
    for(unsigned char on=0; on < working->size; ++on) { // each node
      Neuron * node = working->nodes+on;
      double value = getValue(node);
      for(unsigned char connect=0; connect < node->values.size(); ++connect) { // for each connection
	node->values[connect] += beta*(node->values[connect] - (working+1)->nodes[connect].target / value);
	//std::cout << "\t\t" << node->values[connect] << " + beta*(" <<  node->values[connect] << " - " << (working+1)->nodes[connect].target << " / " << value << "\n";
      }
      
    }

    ++working;
  }
  
}


void Net::targetValues() {
  // compute all of the target values
  // only compute all of the target values
  Layer * working = layers+size-2;
  while(working != layers-1) { // for each layer
    Layer * from = working+1;

    for(unsigned char _node=0;_node < working->size; ++_node) { // for each node per layer
      Neuron * node = working->nodes + _node;
      for(unsigned char val=0;val < node->values.size();++val) { // for each value in a node
	// correction: from->nodes[val].inputs[_node] - fron->nodes[val].target;
	node->target += from->nodes[val].target / node->values[val];
	std::cout << "target: " << node->target << "\n";
      }
      node->target /= node->values.size();
    }

    --working;
  }
}

double Net::sigmoid(double x) {
  return x/sqrt(1+x*x);
}
