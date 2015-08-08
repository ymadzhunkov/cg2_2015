// =====================================================================================
//
//       Filename:  ranmar.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:   8.08.2015 11,22,52
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include "ranmar.h"
double Ranmar::twom24 = 1./16777216.;
int Ranmar::cd = 7654321;
int Ranmar::cm = 16777213;
void Ranmar::setState(int ixx, int jxx) {
	if( ixx <= 0 || ixx >= 31328) ixx = 1802;
	if( jxx <= 0 || jxx >= 30081) jxx = 9373;
	iseed1 = ixx; iseed2 = jxx;
	int i = (ixx/177)%177 + 2;
	int j = ixx%177 + 2;
	int k = (jxx/169)%178 + 1;
	int l = jxx%169;
	for(int ii=0; ii<97; ii++) {
   	int s = 0; int t = 8388608;
		for(int jj=0; jj<24; jj++) {
      	int m = (((i*j)%179)*k)%179;
       	i = j; j = k; k = m;
        	l = (53*l+1)%169; 
        	if( (l*m)%64 >= 32 ) s += t;
        	t /= 2;
    	}
		u[ii] = s;
	}
	c = 362436; ix = 96; jx = 32;
}
double Ranmar::getUniform() {
	register int r = u[ix] - u[jx--];
	if( r < 0 ) r += 16777216;
	u[ix--] = r;
	if(ix < 0) ix = 96;
	if(jx < 0) jx = 96;
	c -= cd; if( c < 0 ) c+=cm;
	r -= c; if( r < 0 ) r+=16777216;
	double res = twom24*r;
   	r = u[ix] - u[jx--];
      if( r < 0 ) r += 16777216;
      u[ix--] = r;
      if(ix < 0) ix = 96;
      if(jx < 0) jx = 96;
      c -= cd; if( c < 0 ) c+=cm;
      r -= c; if( r < 0 ) r+=16777216;
      res += twom24*twom24*r;
	return res;
}

void Ranmar::fillUniform(const unsigned int n, double * __restrict__ d) {
    for(unsigned int i = 0; i < n; i++) {
        register int r = u[ix] - u[jx--];
        if( r < 0 ) r += 16777216;
        u[ix--] = r;
        if(ix < 0) ix = 96;
        if(jx < 0) jx = 96;
        c -= cd; if( c < 0 ) c+=cm;
        r -= c; if( r < 0 ) r+=16777216;
        d[i] = twom24*r;
    }
        for(unsigned int i=0; i<n; i++) {
            register int r = u[ix] - u[jx--];
            if( r < 0 ) r += 16777216;
            u[ix--] = r;
            if(ix < 0) ix = 96;
            if(jx < 0) jx = 96;
            c -= cd; if( c < 0 ) c+=cm;
            r -= c; if( r < 0 ) r+=16777216;
            d[i] += twom24*twom24*r;
        }

}
