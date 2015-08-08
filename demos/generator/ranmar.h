// =====================================================================================
//
//       Filename:  ranmar.h
//
//    Description:  
//
//        Version:  1.0
//        Created:   8.08.2015 10,21,32
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#pragma once
#include <stddef.h>
#include "randomgenerator.h"
// implements Zaman & Marsaglia ranmar generator
class Ranmar : public RandomGenerator<double> {
public:
	Ranmar(const unsigned int someSeed = 1802) {
		setSeed(someSeed);
	}
	virtual ~Ranmar() override {};
	double getUniform() override; // returns random number from in [0.0,1.0)
	virtual size_t getStateSize() const override { 
      return 102 * sizeof(int);
   }
   virtual void * getState() override {
      return &iseed1;
   }

	void fillUniform(const unsigned int N, double * __restrict__ d);
	void setSeed(const unsigned int N) { setState(N, 9373);};
private:
	void setState(int ixx, int jxx);
   int        iseed1, iseed2;
   int        ix, jx, c;
   int        u[97];
   static     int cd, cm;
   static     double  twom24;
};
