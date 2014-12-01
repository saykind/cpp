// Property of Saykin David
#include <iostream>
using namespace std;

#define max 20002
int main(void) {
	long n = 0;
	char *s = new char [max];
	cin >> s;
	char c = *(s++);
	while (c != 0) {
		if (c != '(' && c != ')') {cout << "NO"; return 0;}
		if (c == '(')
			n++;
		else {
			n--;
			if (n < 0) {
				cout << "NO";
				return 0;
			}
		}
		c = *(s++);
	}
	if (n == 0)
		cout << "YES";
	else 
		cout << "NO";
	return 0;
}
