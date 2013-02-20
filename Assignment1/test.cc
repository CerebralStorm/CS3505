#include <iostream>  

using namespace std;

int main ()
{
  int d = 19;
  int * pd = &d;
  int & ri = d;
  cout << "D is : " << d << endl;
  cout << "pD is : " << pd << endl;   
  cout << "ri is : " << ri << endl; 


  char * c = new char[100];

  for(int i = 0; i < 100; i++)
  {
    c[i]='X';
  } 

  delete []c; 
}

// n = n->next;
// n = (*n).next;
// static_cast<int>(d);