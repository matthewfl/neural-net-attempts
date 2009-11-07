
#include <iostream>
using namespace std;

#include "Net.h"

double * aa (double * r) {
  return r;
}

int main (int argc, char **argv) {
  vector<unsigned char> base_size;
  unsigned char base_size_a[] = {3,3,2,1};
  base_size.assign(4, *base_size_a);
  Net net(base_size);
  double input[][3] = {
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},
    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
  };
  double out [][1] = {{0},{1}};
  Net::Teaching teach [] = {
    {3,1,input[0],out[0]},
    {3,1,input[1],out[1]},
    {3,1,input[2],out[1]},
    {3,1,input[3],out[0]},
    {3,1,input[4],out[1]},
    {3,1,input[5],out[0]},
    {3,1,input[6],out[0]},
    {3,1,input[7],out[1]},
  };

  cout << net.check(teach, 8) << endl;
  Net other(net.Size());
  cout << other.check(teach, 8) << endl;
  Net another (net.Size());
  cout << another.check(teach, 8);
}

