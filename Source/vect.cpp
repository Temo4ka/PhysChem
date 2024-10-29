#include "../Headers/Config.h"
#include "../Headers/Vect.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

Vect& Vect:: operator += (const Vect& other) {
    this -> x += other.x;
    this -> y += other.y;

	return *this;
}

Vect& Vect:: operator *= (const Vect& other) {
    this -> x *= other.x;
    this -> y *= other.y;

	return *this;
}

Vect& Vect:: operator -= (const Vect& other) {
    this -> x -= other.x;
    this -> y -= other.y;
	
    return *this;
}

Vect operator + (const Vect& a, const Vect& b) {
    Vect res = a;
    res += b;
	
    return res;
}

Vect operator - (const Vect& a, const Vect& b) {
    Vect res = a;
    res -= b;
	
    return res;
}

Vect operator * (const Vect& a, const Vect& b) {
    Vect res = a;
    res *= b;
	
    return res;
}

Vect operator * (const Vect &a, const double scalar) {
    Vect res(a.x * scalar, a.y * scalar);

    return res;
}

// Vect operator ^ (const Vect& a, const double& angle) {
// 	Vect res = a;
	
// 	res.x = a.x * cos(angle) - a.y * sin(angle);
// 	res.y = a.x * sin(angle) + a.y * cos(angle);
	
// 	return res;
// }

Vect operator && (const Vect& a, const Vect& b) {
    Vect *res = (Vect *)((size_t)(&a) & (size_t)(&b));
	
    return *res;
}

double operator , (const Vect& a, const Vect& b) {
    return a.x * b.x + a.y * b.y;
}

Vect Vect::operator - () {
    this -> x *= -1;
    this -> y *= -1;

    return *this;
}

//----------------------------------------------------------------

void shoot(double bullet, Vect *victim);

Vect Vect::operator ~ () {
    int bullet = (rand() % 6);
	
    shoot(bullet, this);
	
    return *this;
}


void shoot(double bullet, Vect *victim) {
    if (bullet == 0) fprintf(stderr, "Headshot!!!\n");

    victim -> x /= bullet;
    victim -> y /= bullet;
	
    return;
}

//----------------------------------------------------------------

Vect Vect::operator ! () {
    double length = sqrt(SQR(this -> x) + SQR(this -> y));

    this -> x /= length;
    this -> y /= length;

    return *this;
}
