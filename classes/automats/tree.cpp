// Property of Saykin David
// FIXME -0
#include <cstdio>
#include <iostream>
using namespace std;

#define max 20002

int len(int i) {
	int l = 1;
	if (i == 0) {return l;} 
	if (i < 0) {
		l++;
		i = -i;
	}
	while (i/10) {
		l++;
		i = i/10;
	}
	return l;
}

int main(void) {
	int d, i;
	double a = 0, p = 1;
	long n = 0;
	char c;
	while (scanf("%c", &c) && c != '\n' && c != EOF) {
		if (c == '\n')
			break;
		if (c == ' ')
			continue;
		if (c == '(' || c == ')') {
			if (c == '(') {
				n++;
				p /= 2;
			} else {
				n--;
				p *= 2;
				if (n < 0) {
					printf("Wrong brakets. Last symbol = '%c'", c);
					return 0;
				}
			}
		} else {
			ungetc(c, stdin);
			scanf("%d", &i);
			//printf("<%d>\n", i);
			a += p*i;
		}
	}
	if (n != 0)
		cout << "Wrong brackets\n";
	printf("%.2f", a);
	return 0;
}
