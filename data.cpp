#include <iostream>

using namespace std;

class dimension {
	 private:
	char *parser(char *input);	
	 public:
	char 	*unit;
	int	*degree;
};
class data {
//	 private:					// That's not essential.
	double 	   val;
	string dim;
	 public:
	void print(void)  {cout << val;}
	void println(void){
		cout << val << '\n';
	} 
	data (double a) {val = a;}
	data (double a, string b) {val = a;}			// Constructor has no return type
};

int main (int argv, char *argc[]) {
	data a (1.1);
	a.println();
	
	enum month {Jan, Feb, Mar };
	month m = Feb;
	cout << m;
	return 0;
}
	
