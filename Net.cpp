#include "Net.h"

#include <stdlib.h>
#include <vector>
#include <math.h>

#include <iostream>
#include <iomanip>

using namespace std;

Net::Net (Net * from) { // make a copy of the Neural Net
  size = from->size;
  layers = new Layer[size];
  for(unsigned int working = 0; working < size; ++working) {
    layers[working].size = from->layers[working].size;
    layers[working].nodes = new Neuron[layers[working].size];
    for(unsigned char node = 0; node < layers[working].size; ++node) {
      layers[working].nodes[node].weight = from->layers[working].nodes[node].weight;
      layers[working].nodes[node].bias = from->layers[working].nodes[node].bias;
    }
  }
}

Net::Net (vector<unsigned char> ss) {
  size = ss.size();
  layers = new Layer[size];
  for(unsigned int working = 0; working < size; ++working) {
    layers[working].size = ss[working];
    layers[working].nodes = new Neuron[layers[working].size];
    if(working < size-1)
      for(unsigned char node = 0; node < layers[working].size; ++node) {
	layers[working].nodes[node].bias =  ((double)rand()*2)/RAND_MAX -1;
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
  cout << "copy\n";
  Net nn(o);
  cout << "swap\n";
  swap(&nn);
  cout << "return\n";
  return *this;
}

bool Net::operator == (Net & o) {
  if(o.size != size) return false;
  for(unsigned int working=0; working < size; ++working) {
    if(layers[working].size != o.layers[working].size) return false;
    for(unsigned char node=0; node < layers[working].size; ++node) {
      if(layers[working].nodes[node].weight.size () != o.layers[working].nodes[node].weight.size()
	 || layers[working].nodes[node].bias != o.layers[working].nodes[node].bias) 
	return false;
      for(unsigned char weight=0; weight < layers[working].nodes[node].weight.size(); ++weight) {
	if(layers[working].nodes[node].weight[weight] != o.layers[working].nodes[node].weight[weight]) return false;
      }
    }
  }
  return true;
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
      layers[working].nodes[node].value = layers[working].nodes[node].bias;
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
  
  // compute the data
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
  unsigned char count=0;
  double diff=0;
  if(teach->inputSize == layers->size) {
    run(teach->input);
    for(unsigned char check=0; check < layers[size-1].size; ++check) {
      ++count;
      diff += pow(get(check) - teach->result[check], 2);
    }
  }
  // cout << diff << "/" <<(int) count << endl;
  return diff/count;
}

double Net::check(Net::Teaching * teach, unsigned int count) {
  double out=0;
  for(unsigned int working = 0; working < count; ++working) {
    out += check(teach + working);
    // cout <<"check " <<  out << endl;
  }
  return out/count;
}

void Net::build (vector<Net::Grade> data) {
  double total=0;
  for(unsigned int working=0; working < data.size(); ++working) {
    total += data[working].grade;
  }
  for(unsigned int working=0; working < data.size(); ++working) {
    data[working]._part = data[working].grade/total;
  }
  // cout << "build: " << total << endl;
  for(unsigned int working=0; working < size; ++working) { // now compute each layer
    for(unsigned char node=0; node < layers[working].size; ++node) { // each node
      double bias=0;
      for(unsigned int inputs=0; inputs < data.size(); ++inputs) {
	bias += data[inputs].net->layers[working].nodes[node].bias * data[inputs]._part;
      }
      layers[working].nodes[node].bias = bias;
      for(unsigned char weight=0; weight < layers[working].nodes[node].weight.size(); ++weight) { // each weight
	double value=0; 
	for(unsigned int inputs=0; inputs < data.size(); ++inputs) { // compute the value for each node
	  value += data[inputs].net->layers[working].nodes[node].weight[weight] * data[inputs]._part;
	}
	layers[working].nodes[node].weight[weight] = value;
      }
    }
  }
  // cout << "done\n";
}

void Net::teach(Net::Teaching * teach, unsigned int ss, float maxError) {
  vector<Grade> nets;
  nets.push_back ((Grade){
      new Net(this),
	1,0
	});
  nets.push_back((Grade){
      new Net(Size()),
	1,0
	});
  double worth=0, oldWorth=0, lowWorth=0;
  unsigned char sameCount=0;
  Net * n;
  do {
    lowWorth=worth-.00000000000001;
    //cout << "loop\n";
    /*
    n = new Net(Size());
    n->build(nets);
    nets.push_back((Grade){
	n,
	  0,0
	  });
    */
    nets.push_back((Grade){
	new Net(Size()),
	  0,0
	  });
    for(int working= nets.size() > 100?nets.size()/2:5; (working >0 && nets.size() > 15) || (nets.size() > 1000 && working > -10000); --working) {
      unsigned int randA = rand()%nets.size();
      unsigned int randB = rand()%nets.size();
      if(*nets[randA].net == *nets[randB].net) {
	delete nets[randA].net;
	nets.erase(nets.begin() + randA);
      }
    }
    for(unsigned int working=0;working < nets.size(); ++working) {
      double temp = nets[working].net->check(teach, ss);
      if(temp == 0) {
	swap(&Net(nets[working].net));
	return;
      }
      nets[working].grade = ((double)1) / temp;
    }
    n = new Net(Size());
    n->build(nets);
    for(unsigned int working=0; working < nets.size(); ++working) {
      if(nets[working].grade > worth) {
	swap(&Net(nets[working].net));
	worth = nets[working].grade;
      }else if(nets[working].grade < worth*.9 || lowWorth > worth) {
	lowWorth = worth;
	delete nets[working].net;
	nets.erase(nets.begin() + working);
	--working;
      }
    }
    nets.push_back((Grade){n,0,0});
    for(unsigned char count=0; count < 5; ++count) {
      n = new Net(this);
      n->nodeFix();
      nets.push_back((Grade){n,0,0});
    }
    cout << nets.size() << "\t" << fixed <<  setprecision(45) <<  worth << "\t\t" << worth - lowWorth <<  endl;
    if(sameCount > 10)
      enumerate(nets);
    if(worth > maxError) break;
    if(worth == oldWorth) {
      ++sameCount;
      if(sameCount > 50) {
	cout << "clean\n";
	emptyGrade(nets);
	cout << "enumerate\n";
	enumerate(nets);
	sameCount=0;
      }
    }else{
      oldWorth = worth;
      sameCount=0;
    }
  } while(true);

  for(unsigned int working=0; working < nets.size(); ++working)
    delete nets[working].net;
}

void Net::backpropagation (Net::Teaching * data) {
  run(data->input);
  
}

void Net::nodeFix () {
  //chose a random node
  int ll = rand()%size;
  Neuron * node = layers[ll].nodes + rand()%layers[ll].size;
  for(unsigned char weight=0; weight < node->weight.size(); ++weight) {
    node->weight[weight] = ((double)rand()*2)/RAND_MAX-1;
  }
}

void Net::emptyGrade(vector<Net::Grade> & nets) {
  for(unsigned int working=0; working < nets.size(); ++working) {
    delete nets[working].net;
  }
  nets.erase(nets.begin(), nets.end()); // delete all
}

double simpleRand () { // return a rand number between 0 and 1
  return ((double)rand())/RAND_MAX;
}

void Net::enumerate(vector<Net::Grade> & nets) {
  nets.push_back((Grade){
      new Net(this),0,0
    });
  Net * n;
  for(unsigned int working=0; working < size; ++working) { // layer
    for(unsigned char node=0; node < layers[working].size; ++node) { // node
      // first work on the bias
      // try each possible with a random number + and -
      n = new Net(this);
      n->layers[working].nodes[node].bias += simpleRand()*.5;
      nets.push_back((Grade){n,0,0});
      n = new Net(this);
      n->layers[working].nodes[node].bias -= simpleRand()*.5;
      nets.push_back((Grade){n,0,0});
      // work on the weights for each node
      for(unsigned char weight=0; weight < layers[working].nodes[node].weight.size(); ++weight) {
	n = new Net(this);
	n->layers[working].nodes[node].weight[weight] += simpleRand()*.5;
	nets.push_back((Grade){n,0,0});
	n = new Net(this);
	n->layers[working].nodes[node].weight[weight] -= simpleRand()*.5;
	nets.push_back((Grade){n,0,0});
	n = new Net(this);
	n->layers[working].nodes[node].weight[weight] = simpleRand()*2-1;
	nets.push_back((Grade){n,0,0});
      }
    }
  }
}
