#include <iostream>
using namespace std;
#include "class.h"

ostream &operator << (ostream &stream, vector<int> &a) {
	for (int i = 0; i < a.size_; i++) 
		stream << a.s[i] << ' ';
	cout << '\n';
	return stream;
}



int main(void) {
	vector<int> a (8);
//	for (int i = 0; i < a.size_; i++) {
//		cout << a.s[i] << endl;
//	}
	cout << a;
	return 0;
}




