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
   virtual bool getExact(double &val, double &error) const { 
      val = 0.0; error = 0.0;
      return false; 
   }
};


class Mandelbrot : public Surface2DInterface {
   public:
	virtual ~Mandelbrot() {};
	virtual const char *getName() const override { return "Mandelbrot"; }
	virtual int isInside(const double x0, const double y0) const override {
		const size_t max_iteration = 64 * 16 * 8;
		double x = 0.0, y = 0.0;
		size_t i = 0;
      //bool escape = false;
      //bool inside = false;
		for (i = 0; i < max_iteration; i++) {
            // compute next point 
			   double xtemp = this->add(x * x, - y * y, x0);
			   y = 2 * x * y + y0;
			   x = xtemp;

         if (x * x + y * y >= 4.0) {
            return i;
         }
		   if (isInCircle(x, y) || isInCardioid(x, y))
           return 0;
		}
		return 0;

/*    printf("x0=%f y0=%f ", x0, y0);
		for (i = 0; i < 6; i++) {
			double xtemp = this->add(x * x, - y * y, x0);
			y = 2 * x * y + y0;
			x = xtemp;
         printf("x=%f y=%f ", x, y);
      }
      printf("\n");
*/
	}
   bool isInCircle(const double x0, const double y0) const {
      // Circle  test
      return (x0 + 1) * (x0 + 1) + y0 + y0 <  0.0625 * (1 - 4 * DBL_EPSILON);
   }
   bool isInCardioid(const double x0, const double y0) const {
      // cardioide  test
      double q = (x0 - 0.25) * (x0 - 0.25) + y0 * y0;
      double t = q * (q + (x0 - 0.25)) - 0.25 * y0 * y0;
      return t < 0;
   }

	virtual void getBounds(double &lowX, double &lowY, double &highX,
	                       double &highY) const override {
		lowX = -2.0;
		highX = 1.0;
		lowY = -1.0;
		highY = 1.0;
	};
   virtual double add(const double a, const double b, const double c) const {
      return a + b + c;
   }
};
class Mandelbrot2 : public Mandelbrot {
   public:
	virtual ~Mandelbrot2() {};
	virtual const char *getName() const override { return "Mandelbrot2"; }
	virtual double add(const double a, const double b,
	                        const double c)  const override {
		// assumes  a >= 0
		// assumes  b <= 0
		const double abs_c = fabs(c);
		const double d_ab = fabs(a + b);
		const double d_ac = fabs(a - abs_c);
		const double d_bc = fabs(fabs(abs_c) + b);
		if (d_ab <= d_ac && d_ab <= d_bc) {
			const double ab = a + b;
			return ab + c;
		} else if (d_ac < d_bc) {
			const double ac = a + c;
			return ac + b;
		} else {
			const double bc = b + c;
			return bc + a;
		}
	}
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
   virtual bool getExact(double& val, double &error) const {
      val = M_PI * 0.25;
      error = val * DBL_EPSILON;
      return true;
   }
};

/*void testAdd() {
   const double a = 1e10;
   const double b = -0.1;
   const double c = -1e10;
   printf("add      %.*e\n", DECIMAL_DIG, add(a, b, c) );
   printf("add_safe %.*e\n", DECIMAL_DIG, add_safe(a, b, c) );

}
*/

class Accumulator {
public:
   Accumulator(): numHits(0), totalSamples(0) {};

   void reset() { *this = Accumulator(); };
 
   void accumulate(const bool isItHit) {
      totalSamples++;
      if (isItHit)
         numHits++;
   }
   double getProb() const {
      return (numHits * 1.0) / totalSamples;
   }
   double getSigma() const {
      double prob = getProb();
		double variance = prob * (1.0 - prob);
		double sigma = sqrt(variance / (totalSamples - 1));
      return sigma;
   }
   size_t getTotalSamples() const { return totalSamples; }

private:
	size_t numHits;
   size_t totalSamples;
};

class Progress {
public:
   Progress(Surface2DInterface &surface, Accumulator &acc,const size_t total)
	 : surface(surface), acc(acc), total(total) {}
   void report() const {
	      double lowX, lowY, highX, highY;
         double exact = 0.0, errExact = 0.0;
         bool hasKnowExact = surface.getExact(exact, errExact);
      	surface.getBounds(lowX, lowY, highX, highY);
         const double totalArea = (highY - lowY) * (highX - lowX);
			double area       =     acc.getProb () * totalArea;
   		double confidence = 3 * acc.getSigma() * totalArea;

         char c = '2';
         if (hasKnowExact) {
            c = fabs((exact - area)) < confidence ? '3' : '1';
         }
         int prec = ceil(log(confidence)/log(10)); 
			printf("\rComputing %s (%.2f %% of samples)", surface.getName(), (100.0 * acc.getTotalSamples()) / total);
				printf(
				    " \033[1;3%cm area = %.*f +/- "
				    "%.*f\033[0m       ",
				    c, prec, area, prec, confidence);

			if (hasKnowExact) {
				printf(
				    " \033[1;3%cm error = %.*e +/- "
				    "%.*e\033[0m       ",
				    c, prec, area - exact, prec, confidence);
			} else {
			}
			fflush(stdout);  // Will now print everything in the stdout buffer

   }
private:
   Surface2DInterface & surface;
   Accumulator & acc;
   size_t total;
};

int testMangelbrod() {
	RandomGenerator<double> *rng = newRandomGeneratorD(GT_Ranmar, 21232);
	Surface2DInterface * m1 = new Mandelbrot ();
	Surface2DInterface * m2 = new Mandelbrot2();
   // Define input domain
	double lowX, lowY, highX, highY;
	m1->getBounds(lowX, lowY, highX, highY);

   for (size_t i = 0; i < 10000000; i++) {
   	double x0 = rng->getUniform(lowX, highX);
	   double y0 = rng->getUniform(lowY, highY);
      int c1 = m1->isInside(x0, y0);
      int c2 = m2->isInside(x0, y0);

      if (c1 != c2) {
         printf ("%f %f %d %d\n", x0, y0, c1, c2);
      }
   }
   
   
   delete m1; m1 = NULL;
   delete m2; m2 = NULL;
   delete rng; rng = NULL;
   return 0;
}
int main() {
//   testMangelbrod();
 //  testAdd(); 
	RandomGenerator<double> *rng = newRandomGeneratorD(GT_Ranmar, 1232);
	Surface2DInterface * surface = new Mandelbrot2();
//	Surface2DInterface *surface = new Curcle();
	size_t numTries = 1024 * 1024;
	numTries *= 1024 * 16;

   Accumulator acc;
   Progress progress(*surface, acc, numTries);

   // Define input domain
	double lowX, lowY, highX, highY;
	surface->getBounds(lowX, lowY, highX, highY);
	for (size_t i = 0; i < numTries; i++) {
      // sampling
		double x0 = rng->getUniform(lowX, highX);
		double y0 = rng->getUniform(lowY, highY);
      // computation
      const int res = surface->isInside(x0, y0);
      const bool isItHit = res == 0;
      // accumulation
      acc.accumulate(isItHit);

		if (((i & (1024 * 8 * 2 - 1)) == 0) || (i == numTries - 1)) {
         progress.report();
		}
	}
	printf("\n");
	delete surface;
	surface = NULL;
	delete rng;
	rng = NULL;
	return 0;
}
