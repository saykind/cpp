#include <iostream>
#include <cmath>
#define nl '\n'
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


int main(int argv, char *argc[]) {
	complex a(-1, 1), b(-1, 1), i(0,1);
	double c = -1, d = 3;
	cout << "a  = " << a << nl;
	cout << "-a = " << &a << nl;
	cout << "|a| = " << a.abs() << nl;
	cout << "|a| = " << sqrt(Re(a)*Re(a)+Im(a)*Im(a)) << nl;
	double absa = a;
	cout << "|a| = " << absa << nl;
	cout << "b  = " << b << nl;
	cout << "|b| = " << b.abs() << nl;
	cout << "c  = " << c << nl;
	cout << "d  = " << d << nl;
	cout << "a+b  = " << a+b << nl;
	cout << "a+c  = " << a+c << nl;
	cout << "a-b  = " << a-b << nl;
	cout << "a-c  = " << a-c << nl;
	cout << "a*b  = " << a*b << nl;
	cout << "a*d  = " << a*d << nl;
	cout << "a/b  = " << a/b << nl;
	cout << "a/d  = " << a/d << nl;
	cout << "(a==b) = " << boolalpha << (a==b) << nl;
	cout << "(a==c) = " << boolalpha << (a==c) << nl;
	cout << "(a!=b) = " << boolalpha << (a!=b) << nl;
	cout << "(a!=c) = " << boolalpha << (a!=c) << nl;
	return 0;
}

