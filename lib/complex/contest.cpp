#include <iostream>
#define nl '\n'

using namespace std;

class C {
public:
	double	re;
	double	im;
	C() : re(.0), im(.0) {}
	C(double r) : re(r) {}
	C(double r, double i) : re(r), im(i) {}
	double	abs()	{return re*re+im*im;}
	friend C operator + (const C a, const C b);
	friend C operator - (const C a, const C b);
	friend C operator * (const C a, const C b);
	friend C operator / (const C a, const C b);
	bool operator== (const C c) const; 
	bool operator!= (const C c) const;
	friend ostream &operator<< (ostream &stream, const C c);
	friend istream &operator>> (istream &stream, C &c);
};

inline C operator + (const C a, const C b) {return C(a.re+b.re, a.im+b.im);}
inline C operator - (const C a, const C b) {return C(a.re-b.re, a.im-b.im);}
inline C operator * (const C a, const C b) {return C(a.re*b.re-a.im*b.im, a.re*b.im+a.im*b.re);}
inline C operator / (const C a, const C b) {
	return C((a.re*b.re+a.im*b.im)/(b.re*b.re+b.im*b.im), 
		(-a.re*b.im+a.im*b.re)/(b.re*b.re+b.im*b.im));}
inline bool C::operator== (const C c) const {return (re == c.re) && (im == c.im);}
inline bool C::operator!= (const C c) const {return (re != c.re) || (im != c.im);}
ostream &operator<< (ostream &stream, const C c) {
	stream << c.re << ' ' << c.im;
	return stream;
};
istream &operator>> (istream &stream, C &c) {
    double r,i;
    stream>>r>>i;
    if(stream.good()) {c.re = r; c.im = i;}
    return stream;
};


/*
int main(int argv, char *argc[]) {
	C a(-1, 1), b(-1, 1), i(0,1);
	double c = -1, d = 3;
	cout << "a  = " << a << nl;
	cout << "|a| = " << a.abs() << nl;
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
*/

#include <complex_main.h>
