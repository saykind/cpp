#include "complex.h"
complex operator + (const complex a, const complex b) {return complex(a.re+b.re, a.im+b.im);}
complex operator + (const double a, const complex b) {return complex(a+b.re, b.im);}
complex operator + (const complex a, const double b) {return complex(a.re+b, a.im);}
complex operator - (const complex a, const complex b) {return complex(a.re-b.re, a.im-b.im);}
complex operator - (const double a, const complex b) {return complex(a-b.re, -b.im);}
complex operator - (const complex a, const double b) {return complex(a.re-b, a.im);}
complex operator * (const complex a, const complex b) {return complex(a.re*b.re-a.im*b.im, a.re*b.im+a.im*b.re);}
complex operator * (const double a, const complex b) {return complex(a*b.re, a*b.im);}
complex operator * (const complex a, const double b) {return complex(a.re*b,a.im*b);}
complex operator / (const complex a, const complex b) {
	return complex((a.re*b.re+a.im*b.im)/(b.re*b.re+b.im*b.im),(-a.re*b.im+a.im*b.re)/(b.re*b.re+b.im*b.im));}
complex operator / (const double a, const complex b) {return complex(a*b.re/(b.re*b.re+b.im*b.im), (-a*b.im)/(b.re*b.re+b.im*b.im));}
complex operator / (const complex a, const double b) {return complex(a.re/b, a.im/b);}
bool complex::operator== (const complex z) const {return (re == z.re) && (im == z.im);}
bool complex::operator!= (const complex z) const {return (re != z.re) || (im != z.im);}
bool complex::operator== (const double x) const {return (re == x) && (im == 0);}
bool complex::operator!= (const double x) const {return (re != x) || (im != 0);}
ostream &operator<< (ostream &stream, const complex z) {
	stream << z.re << ' ' << z.im;
	return stream;
};
istream &operator>> (istream &stream, complex &z) {
    double re,im;
    stream >> re >> im;
    if(stream.good()) {z.re = re; z.im = im;}
    return stream;
};
double Re(complex z) {return z.re;}
double Im(complex z) {return z.im;}


