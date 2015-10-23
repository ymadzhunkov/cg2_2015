// =====================================================================================
//
//       Filename:  main.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  13.10.2015  9,43,53
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include <cstdlib>
#include <iostream>

float randu() {
   const int maxi = 2147483647;
   const float rmaxi = 1.0f/maxi;
   static int state = 1244432;
   state *= 65539;
   if (state < 0) {
      state += maxi;
      state += 1;
   }
   return state * rmaxi;

}
using namespace std;
int main() {

   for (int i = 0; i < 10000; i++) {
      float x = randu();
      float y = randu();
      float z = randu();
      cout << x << " " << y << " " << z << " " << 9 * x - 6 * y + z << endl;
   }
   

}
