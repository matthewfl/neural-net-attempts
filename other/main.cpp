#include <iostream>
#include "Net.h"

using namespace std;

int main (int argc, char **argv) {
  unsigned char size[] = {3,3,2,1};
  Net net(4, size);
  
  double XOR[][4] = {
    {0,0,0,0},
    {0,0,1,1},
    {0,1,0,1},
    {0,1,1,0},
    {1,0,0,1},
    {1,0,1,0},
    {1,1,0,0},
    {1,1,1,1} // 8
  };
  for(unsigned int times=0;times<10;++times) {
    for(unsigned char each=0;each<8;++each) {
      net.teach(XOR[each],XOR[each]+3);
    }
  }
  
  //net.run(in);

  //cout << net.get(0) << endl;

  return 0;
}
