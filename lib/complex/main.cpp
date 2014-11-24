#include "complex.h"
#define nl '\n'

int main(int argv, char *argc[]) {
	complex a(-1, 1), b(-1, 1), i(0,1);
	double c = -1, d = 3;
	cout << "a  = " << a << nl;
	cout << "-a = " << &a << nl;
	cout << "|a| = " << a.abs() << nl;
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
