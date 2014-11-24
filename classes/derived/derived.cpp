#include <iostream>
using namespace std;

class base{
public:
	unsigned int x;
	unsigned int y;
	unsigned int sum() {return x+y;}
	unsigned int mult() {return x*y;}
	virtual unsigned int div() {if (y==0) {return -1;} return x/y;}
};

class derived: public base {
public:
	unsigned int a;
	unsigned int b;
	unsigned int sum() {return a+b;}
};

int main(void) {
	base b;
	derived d;
	cout << "base:\t" << &b << endl;	// table of virtual functions
	cout << "base.x:\t" << &b.x << endl;
	cout << "base.y:\t" << &b.y << endl;
	cout << "derv:\t" << &d << endl;
	d.x = 2;
	d.y = 3;
	d.a = 20;
	d.b = 30;
	cout << "d.sum:\t" << d.sum() << endl;
	cout << "d.mult:\t" << d.mult() << endl;
	return 0;
}
