#pragma once

struct Vect {
    double x;
    double y;

    Vect& operator  += (const Vect &other);
	Vect& operator  -= (const Vect &other);
	Vect& operator  *= (const Vect &other);

    Vect operator - ();
    Vect operator ~ ();                     //Russian roulet
    Vect operator ! ();

    Vect(double x, double y) : 
             x (x),    
                       y (y)  
    {}

     Vect() {}
    ~Vect() {}

};

 Vect  operator  +  (const Vect &a, const Vect &b);
 Vect  operator  -  (const Vect &a, const Vect &b);
 Vect  operator  *  (const Vect &a, const Vect &b);
 Vect  operator  && (const Vect &a, const Vect &b);
double operator  ,  (const Vect &a, const Vect &b);
 Vect  operator  *  (const Vect &a, const double scalar);

// Vect  operator  ^  (const Vect &a, const double &angle);