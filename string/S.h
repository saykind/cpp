#include <iostream>
#include <cstdlib>
#define nl '\n'

using namespace std;

/* Class String */
class S {
public:
	S();			// Constructor
	S(const char *ss);	// Constructor
	S(char c);		// Constructor
	S(const S &ss);		// Copy constructor
	~S();			// Destructor
	const char *str() const;	// Method
	int length() const;		// Method
	char operator[] (int i);	// Operator overloading
	S &operator+= (const S &b);	// Operator overloading
	friend ostream &operator<< (ostream &stream, const S &a);
private:
	char *s;
	int l;
};

/* Non-member function operators */
S operator+ (const S &a, const S &b);
ostream &operator<< (ostream &stream, const S &a);

/* String functions */
int strlen(const char *s);
void strcpy(const char *from, char *to, int M);
void strcat(const char *a, const char *b, char *c, int M);


