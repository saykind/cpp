#include "math.h"
#include "function.h"
#include "iostream"
using namespace std;

int main(void) {
	float x = 1.1, y = 2.1;
	float z = sum(x, y);
	cout << "sum(float 1.1, float 2.1) =\t" << z << endl;
	int a = 1, b = 2;
	int c = sum(a, b);
	cout << "sum(int 1, int 2) =\t\t" << c << endl;

	c = sum(x, y);
	cout << c << endl;
}
