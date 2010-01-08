
#include <iostream>
using namespace std;

#include "Net.h"

#include <stdlib.h>

int main (int argc, char **argv) {

  srand((unsigned)time(0));  

  vector<unsigned char> base_size;
  base_size.push_back(3);
  base_size.push_back(3);
  base_size.push_back(2);
  base_size.push_back(1);
  Net net(base_size);
  double z = 0;
  double input[][3] = {
    {z,z,z},
    {z,z,1},
    {z,1,z},
    {z,1,1},
    {1,z,z},
    {1,z,1},
    {1,1,z},
    {1,1,1}
  };
  double out [][1] = {{z},{1}};
  Net::Teaching teach [] = {
    {3,1,input[0],out[0]},
    {3,1,input[1],out[1]},
    {3,1,input[2],out[1]},
    {3,1,input[3],out[0]},
    {3,1,input[4],out[1]},
    {3,1,input[5],out[0]},
    {3,1,input[6],out[0]},
    {3,1,input[7],out[1]}
  };

  //net.teach(teach, 8, 20);
  //for(unsigned char i=0; i<30; ++i)
    
  //while (.2 < net.backprop(teach,8));
  while(true) 
    cout << net.backprop(teach,8) << endl;

  cout << "test\n";
  
  for(unsigned char test=0;test < 8; ++test) {
    net.run(input[test]);
    cout << net.get(0) << "  \t" << *(teach[test].result) << endl;
  }
  //cout << net.check(teach, 8) << endl;
}

