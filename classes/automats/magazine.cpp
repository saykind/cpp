// Property of Saykin David
#include <iostream>
using namespace std;
#define max 40002

long n;
void push(char *lifo, char c) {
	lifo[n++] = c;
}
char pop(char *lifo) {
	if (n > 0)
		return lifo[--n];
	else
		return 0;
}

int main(void) {
	n = 0;
	char *lifo = new char [max];
	char *s = new char [max];
	cin >> s;
	char c = *(s++);
	while (c != 0) {
		switch (c) {
			case '(':
				push(lifo, c);
				break;
			case '[':
				push(lifo, c);
				break;
			case '{':
				push(lifo, c);
				break;
			case ')':
				if (pop(lifo) != '(') {
					cout << "NO";
					return 0;
				}
				break;
			case ']':
				if (pop(lifo) != '[') {
					cout << "NO";
					return 0;
				}
				break;
			case '}':
				if (pop(lifo) != '{') {
					cout << "NO";
					return 0;
				}
				break;
			default:
				//cout << "NO";
				//return 0;
				break;
		}
		c = *(s++);
	}
	if (n == 0)
		cout << "YES";
	else 
		cout << "NO";
	return 0;
}
