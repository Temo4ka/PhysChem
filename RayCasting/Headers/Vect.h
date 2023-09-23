struct Vect3 {
    double x;
    double y;
    double z;

    Vect3& operator  += (const Vect3 &other);
	Vect3& operator  -= (const Vect3 &other);
	Vect3& operator  *= (const Vect3 &other);

    Vect3 operator - ();
    Vect3 operator ~ ();                     //Russian roulet
    Vect3 operator ! ();

    Vect3(double x, double y, double z) : 
             x (x),    
                       y (y),     
                                 z (z)
    {}
};

 Vect3  operator  +  (const Vect3 &a, const Vect3 &b);
 Vect3  operator  -  (const Vect3 &a, const Vect3 &b);
 Vect3  operator  *  (const Vect3 &a, const Vect3 &b);
 Vect3  operator  && (const Vect3 &a, const Vect3 &b);
double operator  ,  (const Vect3 &a, const Vect3 &b);
 Vect3  operator  *  (const Vect3 &a, const double scalar);
 Vect3  operator  ^  (const Vect3 &a, const double &angle);