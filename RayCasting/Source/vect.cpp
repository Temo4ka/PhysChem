#include "../headers/Config.h"
#include "../headers/Vect.h"
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

Vect3& Vect3:: operator += (const Vect3& other) {
    this -> x += other.x;
    this -> y += other.y;
    this -> z += other.z;

	return *this;
}

Vect3& Vect3:: operator *= (const Vect3& other) {
    this -> x *= other.x;
    this -> y *= other.y;
    this -> z *= other.z;

	return *this;
}

Vect3& Vect3:: operator -= (const Vect3& other) {
    this -> x -= other.x;
    this -> y -= other.y;
    this -> z -= other.z;
	
    return *this;
}

Vect3 operator + (const Vect3& a, const Vect3& b) {
    Vect3 res = a;
    res += b;
	
    return res;
}

Vect3 operator - (const Vect3& a, const Vect3& b) {
    Vect3 res = a;
    res -= b;
	
    return res;
}

Vect3 operator * (const Vect3& a, const Vect3& b) {
    Vect3 res = a;
    res *= b;
	
    return res;
}

Vect3 operator * (const Vect3 &a, const double scalar) {
    Vect3 res(a.x * scalar, a.y * scalar, a.z * scalar);

    return res;
}

Vect3 operator ^ (const Vect3& a, const double& angle) {
	Vect3 res = a;
	
	res.x = a.x * cos(angle) - a.y * sin(angle);
	res.y = a.x * sin(angle) + a.y * cos(angle);
	
	return res;
}

Vect3 operator && (const Vect3& a, const Vect3& b) {
    Vect3 *res = (Vect3 *)((size_t)(&a) & (size_t)(&b));
	
    return *res;
}

double operator , (const Vect3& a, const Vect3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vect3 Vect3::operator - () {
    this -> x *= -1;
    this -> y *= -1;
    this -> z *= -1;

    return *this;
}

//----------------------------------------------------------------

void shoot(double bullet, Vect3 *victim);

Vect3 Vect3::operator ~ () {
    int bullet = (rand() % 6);
	
    shoot(bullet, this);
	
    return *this;
}


void shoot(double bullet, Vect3 *victim) {
    if (bullet == 0) fprintf(stderr, "Headshot!!!\n");

    victim -> x /= bullet;
    victim -> y /= bullet;
    victim -> z /= bullet;
	
    return;
}

//----------------------------------------------------------------

Vect3 Vect3::operator ! () {
    double length = sqrt(sqr(this -> x) + sqr(this -> y) + sqr(this -> z));

    this -> x /= length;
    this -> y /= length;
    this -> z /= length;

    return *this;
}
