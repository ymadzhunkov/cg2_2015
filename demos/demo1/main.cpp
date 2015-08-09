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
#include <float.h>
#include <math.h>
#include "randomgenerator.h"

class Surface2DInterface {
   public:
	virtual ~Surface2DInterface() {};
   // returns 0, if the pair (x, y) is inside the 2D surface
	virtual int isInside(const double x, const double y) const = 0;
   // returns a rectangler bounds of the problem
	virtual void getBounds(double &lowX, double &lowY, double &highX,
	                       double &highY) const = 0;
   // returns name of the surface ( for display purpose)
	virtual const char *getName() const = 0;
   // returns true, if the exact surface is known for this surface, 
   // This methods should also set the exact suface values to 'val'
   // and error  
   virtual bool getExact(double &val, double &error) { 
      val = 0.0; error = 0.0;
      return false; 
   }
};

class Mandelbrot : public Surface2DInterface {
   public:
	virtual ~Mandelbrot() {};
	virtual const char *getName() const override { return "Mandelbrot"; }
	virtual int isInside(const double x0, const double y0) const override {
		const size_t max_iteration = 1024;
		double x = 0.0, y = 0.0;
		size_t i = 0;
		for (i = 0; i < max_iteration && x * x + y * y < 4.0; i++) {
			double xtemp = x * x - y * y + x0;
			y = 2 * x * y + y0;
			x = xtemp;
		}
		return i == max_iteration ? 0 : i;
	}
	virtual void getBounds(double &lowX, double &lowY, double &highX,
	                       double &highY) const override {
		lowX = -2.0;
		highX = 1.0;
		lowY = -1.0;
		highY = 1.0;
	};
};
class Curcle : public Surface2DInterface {
   public:
	virtual ~Curcle() {};
	virtual const char *getName() const override { return "Curcle"; }
	virtual int isInside(const double x0, const double y0) const override {
		return x0 * x0 + y0 * y0 < 1.0 ? 0 : 1;
	}
	virtual void getBounds(double &lowX, double &lowY, double &highX,
	                       double &highY) const override {
		lowX  = 0.0;
		highX = 1.0;
		lowY  = 0.0;
		highY = 1.0;
	};
   virtual bool getExact(double& val, double &error) {
      val = M_PI * 0.25;
      error = val * DBL_EPSILON;
      return true;
   }
};

int main() {
	RandomGenerator<double> *rng = newRandomGeneratorD(GT_Ranmar, 1232);
	//   Surface2DInterface * surface = new Mandelbrot();
	Surface2DInterface *surface = new Curcle();
	size_t numTries = 1024 * 1024;
	numTries *= 1024 * 16;
	size_t numHits = 0;
	double lowX, lowY, highX, highY;
	surface->getBounds(lowX, lowY, highX, highY);
   double exact = 0.0, errExact = 0.0;
   bool hasKnowExact = surface->getExact(exact, errExact);
	for (size_t i = 0; i < numTries; i++) {
		double x0 = rng->getUniform(lowX, highX);
		double y0 = rng->getUniform(lowY, highY);
		if (surface->isInside(x0, y0) == 0) {
			numHits++;
		};
		if (((i & (1024 * 1024 * 2 - 1)) == 0) || (i == numTries - 1)) {
			double area = ((highY - lowY) * (highX - lowX) * numHits) / (i + 1);
			double prob = (1.0 * numHits) / (i + 1);
			double variance = prob - prob * prob;
			double sigma = sqrt(variance / (i + 1));
   		double confidence = 3 * sigma * area;
         char c = fabs((M_PI - area)/(sigma*area)) < 3.0 ? '3' : '1';
			printf(
			    "\r Comleated %.2f %% of samples. \033[1;3%cm error of %s so far = %.*e +/- "
			    "%.*e\033[0m",
			    (100.0 * i) / numTries, c, surface->getName(), DECIMAL_DIG, area - M_PI,
			    DECIMAL_DIG, confidence);
			fflush(stdout);  // Will now print everything in the stdout buffer
		}
	}
	printf("\n");
	delete surface;
	surface = NULL;
	delete rng;
	rng = NULL;
	return 0;
}
