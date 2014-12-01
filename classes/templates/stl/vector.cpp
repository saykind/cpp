#include <vector>
#include <iostream>
using namespace std;


int main() {
	vector<int> a(5); //10 initialized with zeroes
	a.reserve(10);
	cout << "initialized/memory allocated for: " << a.capacity() << '/' << a.size() << endl;
	a.resize(3);
	cout << "initialized/memory allocated for: " << a.capacity() << '/' << a.size() << endl;

	for (int i = 0; i < 10; i++)
		cout << a[i] << ' ';
	cout << endl;

	for (int i = 0; i < 10; i++)
		a.push_back(i);
	for (int i = 0; i < 10;)
		cout << a[++i] << ' ';
	cout << endl;

	return 0;
}

