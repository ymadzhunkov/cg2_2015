// =====================================================================================
//
//       Filename:  main.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:   8.08.2015 17,48,07
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include <stddef.h>
#include <stdio.h>
#include "randomgenerator.h"
int main() {
   RandomGenerator<double> * rng = newRandomGeneratorD(GT_Ranmar, 3232); 
   for (size_t i = 0; i < 1024 * 128; i++) {
      printf("%f\n", rng->getGaussian());
   }
   delete rng; rng = NULL;
   return 0;
}
