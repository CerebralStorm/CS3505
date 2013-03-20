// use this command to include all needed info to compile.
// g++ -I ../include/ -L../lib test.cc `pkg-config --cflags --libs libavutil libavformat libavcodec`


#include <iostream>

#ifndef INT64_C
#define INT64_C(c) (c ## LL)
#define UINT64_C(c) (c ## ULL)
#endif

extern "C"
{

#include "libavutil/mathematics.h"

}

using namespace std;

int main ()
{
  int64_t result;

  result = av_gcd(39, 91);
  
  cout << "Hello: " << result << endl;
  
  return 0;
}
