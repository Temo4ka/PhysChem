#include "config.h"
#include "vec.h"

myVec& myVec:: operator += (const myVec& other) {
	this -> x += other.x;
	this -> y += other.y;

	return *this;
}

myVec& myVec:: operator *= (const myVec& other) {
	this -> x *= other.x;
	this -> y *= other.y;

	return *this;
}

myVec& myVec:: operator -= (const myVec& other) {
	this -> x -= other.x;
	this -> y -= other.y;
	
	return *this;
}

myVec operator + (const myVec& a, const myVec& b) {
	myVec res = a;
	res += b;
	
	return res;
}

myVec operator - (const myVec& a, const myVec& b) {
	myVec res = a;
	res -= b;
	
	return res;
}

myVec operator * (const myVec& a, const myVec& b) {
	myVec res = a;
	res *= b;
	
	return res;
}

myVec operator ^ (const myVec& a, const double& angle) {
	myVec res = a;
	
	res.x = a.x * cos(angle) - a.y * sin(angle);
	res.y = a.x * sin(angle) + a.y * cos(angle);
	
	return res;
}

myVec operator && (const myVec& a, const myVec& b) {
	myVec *res = (myVec *)((size_t)(&a) & (size_t)(&b));
	
	return *res;
}

double operator , (const myVec& a, const myVec& b) {
	return a.x * b.x + a.y * b.y;
}

myVec myVec::operator - () {
	this -> x *= -1;
	this -> y *= -1;

	return *this;
}

void shoot(double bullet, myVec *victim);

myVec myVec::operator ~ () {
	int bullet = (rand() % 6);
	
	shoot(bullet, this);
	
	return *this;
}

void shoot(double bullet, myVec *victim) {
	if (bullet == 0) fprintf(stderr, "Headshot!!!\n");

	victim -> x /= bullet;
	victim -> y /= bullet;
	
	return;
}