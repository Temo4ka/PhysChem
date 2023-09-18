#include <stdlib.h>
#include <cmath>
#include <cstdio>

struct Vect {
	double x;
	double y;

	Vect& operator  += (const Vect &other);
	Vect& operator  -= (const Vect &other);
	Vect& operator  *= (const Vect &other);
	
	Vect operator - ();
	Vect operator ~ (); // Russkaya ruletka

	Vect(double x, double y):
			  x (x),
					    y (y)
	{}
	
	Vect() {}
};

Vect  operator  +  (const Vect &a, const Vect &b);
Vect  operator  -  (const Vect &a, const Vect &b);
double operator  ,  (const Vect &a, const Vect &b);
Vect  operator  *  (const Vect &a, const Vect &b);
Vect  operator  ^  (const Vect &a, const double &angle);
Vect  operator  && (const Vect &a, const Vect &b);
