/*!  \file  RandomGeneraor.h
 *	  \brief  
 * 
 *   \details   details
 *   \author    Yordan Madzhunkov German Research School for Simulation Sciences GmbH
 *   \version   1.0
 *   \date      05/12/2013 10:09:52 AM
 *   \copyright GNU Public License.
 */
#pragma once
#include "macros.h"
#pragma clang diagnostic ignored "-Wundefined-inline"
template <typename F>
class RandomGenerator {
public:
///////////////////////////////////////
//            Lifecycle
///////////////////////////////////////
	RandomGenerator(): the_x(0), have_x(false){};
	virtual ~RandomGenerator(){};
///////////////////////////////////////
// Random Generator state control
///////////////////////////////////////
	
	virtual void setSeed(const unsigned int N) = 0;
	virtual size_t getStateSize() const = 0;
   virtual void * getState() = 0;

	void setSeed(const void * stateDataPtr);
///////////////////////////////////////
// pure virtuals 
///////////////////////////////////////
	virtual F getUniform() = 0; // returns random number from in [0.0,1.0)

///////////////////////////////////////
// sampling different distributions
///////////////////////////////////////
	virtual void fillUniform(const size_t n, F * __restrict__ d);
	inline F getUniform (const F a, const F b) { return a + getUniform() * (b - a);}
   inline F getGaussian();
   inline F getGaussian(const F mean, const F sigma); 
   inline void getAzimuth(F & cphi, F & sphi);
private:
   inline F preSampleGaussian();
protected:
	DISALLOW_COPY_AND_ASSIGN(RandomGenerator);
	F the_x;
	bool have_x;
};

enum RandomGeneratorType {
   GT_Ranmar, 
   GT_Rand48, 
};
RandomGenerator<double>* newRandomGeneratorD(const int type, const unsigned int someSeed=1234);
RandomGenerator<float>*  newRandomGeneratorF(const int type, const unsigned int someSeed=1234);
