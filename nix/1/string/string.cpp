#include <cstdlib>
#include <iostream>
using namespace std;


/* String functions */
int strlen(const char *s) {
	int i = 0;
	while(*s) {i++; s++;}
	return i;
}
void strcpy(const char *from, char *to, int M) {
	if (M<=0) {return;}
	int i = 0;
	for (i = 0; (i < M) && *(from+i); i++)
		*(to+i) = *(from+i);
}
void strcat(const char *a, const char *b, char *c, int M) {
	int i = 0, j = 0;
	for (i = 0; M && *(a+i); i++, j++) {*(c+j) = *(a+i); M--;}
	for (i = 0; M && *(b+i); i++, j++) {*(c+j) = *(b+i); M--;}
}

/* Class String */
class S {
public:
	char *s;
	int l;
	S();
	S(char *ss);
	S(const char *ss);
	S(char c);
	S(const S &ss) : s(ss.s), l(ss.l) {};
	~S();
	const char *str() const {return (const char *)s;}
	int lenght() const {return l;}
	char operator[] (int i) {
		if (i > l) {return '\0';}
		return *(s+i);
	}
	S &operator+= (const S &b);
	friend ostream &operator<< (ostream &stream, const S &a);
private:
};
S::S() {
	l = 0; 
	s = (char *) malloc((l+1)*sizeof(char));
	*s = '\0';
}
S::S(char c) {
	l = 1;
	s = (char *) malloc((l+1)*sizeof(char));
	*s = c;
	*(s+l) = '\0';
};
S::S(char *ss) {
	l = strlen(ss);
	s = (char *) malloc((l+1)*sizeof(char));
	strcpy(ss, s, l);
	*(s+l)='\0';
}
S::S(const char *ss) {
	l = strlen(ss);
	s = (char *) malloc((l+1)*sizeof(char));
	strcpy(ss, s, l);
	*(s+l)='\0';
}
S::~S() {
	if (s) free(s);
}
S operator+ (const S &a, const S &b) {
	int l = a.lenght() + b.lenght();
	char *cc = (char *) malloc((l+1)*sizeof(char));
	strcat(a.str(), b.str(), cc, l);
	S c(cc);
	free(cc);
	return c;
}
S &S::operator+= (const S &b) {
	int k = this->lenght(), l = b.lenght();
	int L = k+l;
	this->s = (char *) realloc(this->s, (L+1)*sizeof(char));
	int i = 0;
	for (i = 0; i < l; i++) 
		*(this->s+k+i) = *(b.s+i);
	*(this->s+L) = '\0';
	this->l = L;
	return *this;
}
ostream &operator<< (ostream &stream, const S &a) {
	stream << a.str();
	return stream;
};


/*
int main(int argv, char *argc[]) {
	char C = 'c';
	char A[] = "abra-kadabra";
	const char B[] = "constanta";
	char D[20];
	strcat(A,B,D,20);
	cout << D << endl;
	S a(A);
	S b(B);
	S c(C);
	S d(b+a);
	d += a;
	a += b;
	cout << a << ' ' << a.lenght() << endl;
	cout << b << ' ' << b.lenght() << endl;
       	cout << c << ' ' << c.lenght() << endl;
        cout << d << ' ' << d.lenght() << endl;	
	cout << d[13] << endl;
	return 0;
}
*/
