#include <iostream>

using namespace std;

#include "Net.h"

int main (int argc, char *argv[]) {
  vector<unsigned char> size;
  unsigned char s[] = {3,3,2,1};
  size.insert(size.begin(), s, s+4);
  Net net ( size );
  
  cout << "ok\n";

  char data[][4] = {
  // I  XOR  I  XOR  I  =  I
    {0,0,0,0},
    {1,0,0,1},
    {1,1,0,0},
    {0,1,0,1},
    {0,0,1,1},
    {0,1,1,0},
    {1,0,1,0},
    {1,1,1,1}
  };
  /*
  char data[][4] = {
  // I  XOR  I  XOR  I  =  I
    {-1,-1,-1,-1},
    {1,-1,-1,1},
    {1,1,-1,-1},
    {-1,1,-1,1},
    {-1,-1,1,1},
    {-1,1,1,-1},
    {1,-1,1,-1},
    {1,1,1,1}
  };
  */

  for(unsigned char count=0;count<10;++count) {
  for(char a=7;a>=0;--a) {
    vector<float> in, out;
    in.insert(in.begin(), data[a], data[a]+3);
    out.push_back(data[a][3]);
    cout << "before\n";
    cout << net.teach(in, out) << endl;
    cout << net.run(in)[0] << endl; 
    net.fix(-.01);
  } 
  // net.fix(-.05);
  }
  
}
