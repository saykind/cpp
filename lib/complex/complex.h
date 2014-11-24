#include <iostream>
#include <cmath>
using namespace std;

class complex {
private:
	double	re;
	double	im;
public:
	complex() : re(.0), im(.0) {}
	complex(double r) : re(r) {}
	complex(double re, double im) : re(re), im(im) {}
	double	abs()	{return sqrt(re*re+im*im);}
	friend double Re(complex z);
	friend double Im(complex z);
	friend complex operator + (const complex a, const complex b);
	friend complex operator + (const double a, const complex b);
	friend complex operator + (const complex a, const double b);
	friend complex operator - (const complex a, const complex b);
	friend complex operator - (const double a, const complex b);
	friend complex operator - (const complex a, const double b);
	friend complex operator * (const complex a, const complex b);
	friend complex operator * (const double a, const complex b);
	friend complex operator * (const complex a, const double b);
	friend complex operator / (const complex a, const complex b);
	friend complex operator / (const double a, const complex b);
	friend complex operator / (const complex a, const double b);
	complex operator & () {return complex(re,-im);}
	bool operator== (const complex z) const; 
	bool operator!= (const complex z) const;
	bool operator== (const double x) const;
	bool operator!= (const double x) const;
	operator double() {return sqrt(re*re+im*im);}
	friend ostream &operator<< (ostream &stream, const complex z);
	friend istream &operator>> (istream &stream, complex &z);
};
