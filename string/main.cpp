#include "S.h"

int main(int argv, char *argc[]) {
	char C = 'c';
	char A[] = "abra-kadabra";
	const char B[] = "constanta";
	char D[20];
	strcat(A,B,D,20);
	cout << D << nl;
	S a(A);
	S b(B);
	S c(C);
	S d(b+a);
	d += a;
	a += b;
	cout << a << ' ' << a.length() << nl;
	cout << b << ' ' << b.length() << nl;
       	cout << c << ' ' << c.length() << nl;
        cout << d << ' ' << d.length() << nl;	
	cout << d[13] << nl;
	return 0;
}
