#include <iostream>
using namespace std;

template <class T, int S = 10>
class Vector {
public:
	static const int size = S;
	T data[S];
	Vector(void) {	for (int i; i < size; i++) data[i] = 0;}
	vector(int val = 10) {for (int i; i < size; i++) data[i] = val;}
};
//#include "vector.h"
int main(void) {
	Vector<int, 10> a;
	a.data[0] = 0;
	cout << a.data[0] << endl;
	return 0;
}
