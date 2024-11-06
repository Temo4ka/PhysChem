#pragma once

#include <cmath>

struct Vect {
    double x;
    double y;

    double len() const { return sqrt(x*x + y*y); }

    Vect& operator  += (const Vect &other);
	Vect& operator  -= (const Vect &other);
	Vect& operator  *= (const Vect &other);
    Vect& operator  *= (const double scalar);
    Vect& operator  /= (const double scalar);

    Vect& operator - ();
    Vect& operator ~ ();                     //Russian roulet
    Vect& operator ! ();

    Vect(double x, double y) : 
             x (x),
                       y (y)
    {}

    Vect() {}
   ~Vect() {}

    static Vect rand_unit_vect();
};

Vect   operator  +  (const Vect &a, const Vect &b);
Vect   operator  -  (const Vect &a, const Vect &b);
Vect   operator  *  (const Vect &a, const Vect &b);
Vect   operator  && (const Vect &a, const Vect &b);
double operator  ,  (const Vect &a, const Vect &b);
Vect   operator  *  (const double scalar, const Vect &a);
Vect   operator  *  (const Vect &a, const double scalar);
Vect   operator  /  (const Vect &a, const double scalar);

// Vect  operator  ^  (const Vect &a, const double &angle);