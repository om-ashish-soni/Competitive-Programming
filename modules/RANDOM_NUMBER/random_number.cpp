// This header file is 
// for time
#include <ctime> 
#include <iostream>
#include <random>
using namespace std;
  
int main()
{
  // Using the constructor to
  // initialize with a seed value
  mt19937 mt(time(nullptr)); 
  
  // Operator() is used to 
  // generate random numbers
  cout << mt() << '\n';
  return 0;
}
