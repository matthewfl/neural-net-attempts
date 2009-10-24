#include "Net.h"
#include <stdlib.h>
#include <math.h>

#include <iostream>

using namespace std;

Net::Net(vector<unsigned char> s) {
  layerSize = s;
  Layers = new Layer[s.size()];
  beta = .25;
  for(unsigned short i=0;i<s.size();++i) {
    Layers[i].size = s[i];
    Layers[i].nodes = new Neuron[s[i]];
    if(s.size() > i+1) {
      for(unsigned short a=0;a<s[i];++a) {
	for(unsigned short t=0;t<s[i+1];++t) 
	  Layers[i].nodes[a].values.push_back(((float)rand()-RAND_MAX/2)/RAND_MAX);
      }
    }
  }
}

void Net::fix(double e) {
  beta += e*beta;
}


vector<float> Net::run (vector<float> data) {
  for(unsigned char at=0; at<layerSize[0] && at<data.size();++at) {
    Layers[0].nodes[at].input = data[at];
  }
  for(working=0; working<layerSize.size()-1; ++working) {
    processLayer(Layers + working);
  }
  vector <float> ret;
  unsigned short size = layerSize.size() -1;
  for(unsigned char at=0; at<layerSize.back(); ++at) {
    ret.push_back(Layers[size].nodes[at].input);
  }
  return ret;
}

void Net::processLayer (Layer * layer) {
  if(working < layerSize.size()) // reset the layer input
    for(unsigned char a=0;a < Layers[working+1].size; ++a) 
      Layers[working+1].nodes[a].input = 0;

  for(unsigned char s=0;s<layer->size;++s) {
    processNeuron(layer->nodes + s);
  }
}

void Net::processNeuron(Neuron * neuron) {
  neuron->input = 1/(1+exp(-neuron->input));
  for(unsigned char at=0; at < neuron->values.size(); ++at) {
    Layers[working+1].nodes[at].input += neuron->values[at] * neuron->input;
  }
}


float Net::teach(vector<float> input, vector<float> output) {
  vector<float> result = run(input);
  Layer * last = Layers + layerSize.size()-1;
  double ret=0;
  // find the error of each result
  for(unsigned char check = 0; check < result.size() && check < output.size(); ++check) {
    cout << output[check] << ":" << result[check] << endl;
    ret += last->nodes[check].error = (result[check])*(1-result[check])*(output[check]-result[check]);
  }
  cout << "ret: " << ret << "\nbeta: " << beta << endl;
  // teach the layers in reverse
  for(working = layerSize.size() - 2;working >=0; --working) {
    teachLayer(Layers + working);
  }

  return ret;
}



void Net::teachLayer(Layer * layer) {
  for(unsigned char at=0;at<layer->size;++at) {
    teachNeuron(layer->nodes + at);
  }
}

void Net::teachNeuron (Neuron * neuron) {
  neuron->error = 0;
  // compute the Neuron error
  Layer * from = Layers + working + 1;
  int size = Layers[working].size;
  double value=0;
  for(unsigned char on=0;on < neuron->values.size();++on) {
    value += neuron->values[on];
  }
  for(unsigned char on=0;on < neuron->values.size();++on) {
    neuron->error += pow(from->nodes[on].error * neuron->values[on] / value, 2);
    cout << "ne: "<< neuron->error << "\t" << neuron->values[on] << "\t";
    neuron->values[on] = neuron->values[on] - sCurve(size, from->nodes[on].error);
    cout << "nv: " << neuron->values[on] <<endl;
  }
}



double Net::sCurve(int size, double value) {
  double ret =  value/sqrt(size - 1  + value*value)*beta;
  cout << "sc: " <<  ret <<  "\t";
  return ret;
}

/*

float Net::teach(vector<float> input, vector<float> output) {
  run(input);
  Layer * last = Layers + layerSize.size() -1;
  for(unsigned char node=0;node<last->size;++node) {
    // delta
    last->nodes[node].error = last->nodes[node].input*(1-last->nodes[node])*(output[node]-last->nodes[node]);
  }
  
}
*/
