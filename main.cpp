
#include <iostream>
using namespace std;

#include "Net.h"

int main (int argc, char **argv) {
  vector<unsigned char> base_size;
  unsigned char base_size_a[] = {3,3,2,1};
  base_size.assign(4, *base_size_a);
  Net net(base_size);
  

}

