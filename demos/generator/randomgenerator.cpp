/*!  \file  RandomGeneraor.cpp
 *	  \brief  
 * 
 *   \details   details
 *   \author    Yordan Madzhunkov German Research School for Simulation Sciences GmbH
 *   \version   1.0
 *   \date      05/12/2013 06:09:56 PM
 *   \copyright GNU Public License.
 */
#include <assert.h>
#include <math.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include "randomgenerator.h"
// drand48 family of generators
#include "rand48.h"
#include "ranmar.h"
using namespace std;
template<>
void RandomGenerator<double>::getAzimuth(double & cphi, double & sphi) {
   const double phi = 2 * M_PI * this->getUniform();
   sincos(phi, &sphi, &cphi);
};
template<>
void RandomGenerator<float>::getAzimuth(float & cphi, float & sphi) {
   const float phi = 2 * M_PI * this->getUniform();
   sincosf(phi, &sphi, &cphi);
};
template<>
double RandomGenerator<double>::preSampleGaussian() {
   return sqrt(-2.0*log(1.0-this->getUniform()));
}
template<>
float RandomGenerator<float>::preSampleGaussian() {
   return sqrtf(-2.0f*logf(1.0f-this->getUniform()));
}
template <typename F>
void RandomGenerator<F>::setSeed(const void * stateDataPtr) {
	void * res = memcpy(getState(), stateDataPtr, getStateSize());
	assert(res == getState());
}
template<typename F>
F RandomGenerator<F>::getGaussian(const F mean, const F sigma) {
   return mean + getGaussian() * sigma;
}
template<typename F>
F RandomGenerator<F>::getGaussian() {
   if( have_x ) { 
      have_x = false; 
      return the_x; 
   } else {
      F r = preSampleGaussian();
      F cphi = 0.0;
      F sphi = 0.0;
      getAzimuth(cphi,sphi);
      have_x = true; 
      the_x = r*sphi; 
      return r*cphi;
   }
};

template<typename F>
void RandomGenerator<F>::fillUniform(const size_t n, F * __restrict__ d) {
	for (size_t i = 0; i < n; i++)
		d[i] = getUniform();
}
template class RandomGenerator<float>;
template class RandomGenerator<double>;
RandomGenerator<double>* newRandomGeneratorD(const int type, const unsigned int someSeed) {
   switch (type) {
      case GT_Ranmar: return new Ranmar(someSeed);
      case GT_Rand48: return new Rand48(someSeed); 
      default:
         return NULL;
   }
}
RandomGenerator<float>*  newRandomGeneratorF(const int type, const unsigned int someSeed) {
   return NULL;
}

#if !defined(NDEBUG) && defined(COMPILE_UNIT_TESTS)
#include "UnitTester.h"
#include <algorithm>
UNITTEST(RandomGeneratorTest);
RandomGeneratorTest::RandomGeneratorTest() {
	setName 				("Test Random Generator");
	setDescription  	("Tests if random generator behaives correctly");
	setTestAuthor		("Yordan Madzhunkov");
	setDeveloperAuthor("Yordan Madzhunkov");
	setCompileTime(__DATE__, __TIME__); // each class that inherits this one should also have this line.
};
#define SQR(x) (x*x)
	double pks(double z) {
		assert(z >= 0.);
		if (z == 0.) return 0.;
		if (z < 1.18) {
			double y = exp(-1.23370055013616983/SQR(z));
			return 2.25675833419102515*sqrt(-log(y))
				*(y + pow(y,9) + pow(y,25) + pow(y,49));
		} else {
			double x = exp(-2.*SQR(z));
			return 1. - 2.*(x - pow(x,4) + pow(x,9));
		}
	}

	double qks(double z) {
		assert(z >= 0.);
		if (z == 0.) return 1.;
		if (z < 1.18) return 1.-pks(z);
		double x = exp(-2.*SQR(z));
		return 2.*(x - pow(x,4) + pow(x,9));
	}

// Small values of prob show that the cumulative distribution function of data
// is significantly different from func.
double KolmogorovSmirnovUniform(const unsigned int N, double * data) {
	int j = 0, n = N;
	double dt,en,ff,fn,fo=0.0;
	sort(data, data + N);
	en=n;
	double d = 0.0;
	for (j=0;j<n;j++) {
		fn=(j+1)/en;
		ff= data[j];
		dt=fmax(fabs(fo-ff),fabs(fn-ff));
		if (dt > d) d=dt;
		fo=fn;
	}
	en=sqrt(en);
	return qks((en+0.12+0.11/en)*d); 
}
bool RandomGeneratorTest::test() const {
	RandomGenerator * rng = RandomGenerator::defaultGenerator(1312);
	const unsigned int N = 12624;
	double * data = new double[N]; if (!data) return false;
	rng->fillUniform(N, data);
	double p = KolmogorovSmirnovUniform(N, data); // Kolmogorov-Smirnov Test
/* 
	cout << endl << p << " for N = " << N << endl;
	unsigned int nBins = 11;
	unsigned int count[nBins]; 
	memset(count, 0, sizeof(count));
	unsigned int bin = 0;
	for (unsigned int i = 0; i < N; i++)
		if (data[i] < (bin+1) * 1.0/ nBins) {
			count[bin] += 1;			
		} else {
			while (data[i] >= (bin+1) * 1.0/ nBins) bin++;
			count[bin] += 1;			
		}	
	assert(bin < nBins);
	for (unsigned int i = 0; i < nBins; i ++)
		cout << count[i] << " ";	
	cout << endl;
*/
	if (data) delete [] data; data = 0;
	delete rng;
	return p > 0.95;
}
RandomGeneratorTest randomGeneratorTest;
#endif
