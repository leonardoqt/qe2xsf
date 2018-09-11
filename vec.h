#include <iostream>
#include <cstring>
#include <fstream>
#ifndef MY_VEC
#define MY_VEC

class vec;

class vec
{
public:
	double x[3];
//friend atom;
//friend cell;
public:
	void import(double *);
	void clean();					// reset value to zero
	vec operator+(const vec&);
	vec operator-(const vec&);
	vec operator*(const double&);
	vec operator/(const double&);
	double operator*(const vec&);
	vec operator^(const vec&);		// for cross product
	vec & operator=(const vec&);
	vec & operator=(double*);		// can replace import
	friend std::istream& operator>>(std::istream&,vec&);
	friend std::ostream& operator<<(std::ostream&,vec);
	friend std::ofstream& operator<<(std::ofstream&,vec);
	double norm();

	//debug
	void print();
};

#endif
