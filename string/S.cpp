#include "S.h"

/* Class member functions and function operators */
char S::operator[] (int i) {		// Constructor
	if (i > l) {return '\0';}
	return *(s+i);
}
S::S() {				// Constructor
	l = 0; 
	s = (char *) malloc((l+1)*sizeof(char));
	*s = '\0';
}
S::S(char c) {				// Constructor
	l = 1;
	s = (char *) malloc((l+1)*sizeof(char));
	*s = c;
	*(s+l) = '\0';
};
S::S(const char *ss) {			// Constructor
	l = strlen(ss);
	s = (char *) malloc((l+1)*sizeof(char));
	strcpy(ss, s, l);
	*(s+l)='\0';
}
S::S(const S &ss) {			// Copy constructor
	s = ss.s; 
	l = ss.l;
}
S::~S() {				// Destructor				
	if (s) free(s);
}
const char *S::str() const {
	return (const char *)s;
}
int S::length() const {
	return l;
}
S &S::operator+= (const S &b) {
	int k = this->length(), l = b.length();
	int L = k+l;
	this->s = (char *) realloc(this->s, (L+1)*sizeof(char));
	int i = 0;
	for (i = 0; i < l; i++) 
		*(this->s+k+i) = *(b.s+i);
	*(this->s+L) = '\0';
	this->l = L;
	return *this;
}

// Non-member function operators
S operator+ (const S &a, const S &b) {
	int l = a.length() + b.length();
	char *cc = (char *) malloc((l+1)*sizeof(char));
	strcat(a.str(), b.str(), cc, l);
	S c(cc);
	free(cc);
	return c;
}
ostream &operator<< (ostream &stream, const S &a) {
	stream << a.str();
	return stream;
};



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


