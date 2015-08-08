// =====================================================================================
//
//       Filename:  rand48.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:   8.08.2015 11,34,19
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include "rand48.h"
#include <stdlib.h>
void Rand48::setSeed(const unsigned int N) {
   state[0] = N % (256 * 256);
   state[1] = (N / 256) % (256 * 256);
   state[2] = (N / (256 * 256)) % (256 * 256);
}
double Rand48::getUniform(){
	unsigned int res = nrand48(state);
	const double rm = 1.0 / ( 256 * 256 * 256) * (1.0/ 128);
	return rm * res;
};
