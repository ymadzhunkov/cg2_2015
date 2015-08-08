// =====================================================================================
//
//       Filename:  rand48.h
//
//    Description:  
//
//        Version:  1.0
//        Created:   8.08.2015 10,23,39
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include <stddef.h>
#include "randomgenerator.h"
class Rand48 : public RandomGenerator<double> {
public:
	Rand48(const unsigned int someSeed) {
		setSeed(someSeed);
	}
	virtual ~Rand48() override {}
	virtual size_t getStateSize() const override {
      return sizeof(state);
   };
	virtual void setSeed(const unsigned int N) override;
	virtual void * getState() override { return state; }
	virtual double getUniform() override; // returns random number from in [0.0,1.0)
private:
   unsigned short state[3];
};
