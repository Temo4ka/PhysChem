#include <stdlib.h>
#include <cmath>
#include <cstdio>

struct myVec {
	double x;
	double y;

	myVec& operator  += (const myVec &other);
	myVec& operator  -= (const myVec &other);
	myVec& operator  *= (const myVec &other);
	
	myVec operator - ();
	myVec operator ~ (); // Russkaya ruletka

	myVec(double x, double y):
			  x (x),
					    y (y)
	{}
};

myVec  operator  +  (const myVec &a, const myVec &b);
myVec  operator  -  (const myVec &a, const myVec &b);
double operator  ,  (const myVec &a, const myVec &b);
myVec  operator  *  (const myVec &a, const myVec &b);
myVec  operator  ^  (const myVec &a, const double &angle);
myVec  operator  && (const myVec &a, const myVec &b);
