#include <iostream>
#include <limits>

using namespace std;

int main() {
	cout << "\nbool" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<bool>::is_signed << '\t' 
		<< int(numeric_limits<bool>::min()) << "\t\t\t" 
		<< int(numeric_limits<bool>::max()) << "\t\t\t"
		<< numeric_limits<bool>::digits << '('
		<< sizeof(bool) << ')' << endl << endl;
	cout << "char" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<char>::is_signed << '\t' 
		<< int(numeric_limits<char>::min()) << "\t\t\t" 
		<< int(numeric_limits<char>::max()) << "\t\t\t"
		<< numeric_limits<char>::digits << '('
		<< sizeof(char) << ')' << endl << endl;
	cout << "short" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<short>::is_signed << '\t' 
		<< numeric_limits<short>::min() << "\t\t\t" 
		<< numeric_limits<short>::max() << "\t\t\t"
		<< numeric_limits<short>::digits << endl << endl;
	cout << "int" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<int>::is_signed << '\t' 
		<< numeric_limits<int>::min() << "\t\t" 
		<< numeric_limits<int>::max() << "\t\t"
		<< numeric_limits<int>::digits << '(' 
		<< sizeof(int) << ')' << endl << endl;
	cout << "unsigned" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<unsigned>::is_signed << '\t' 
		<< numeric_limits<unsigned>::min() << "\t\t\t" 
		<< numeric_limits<unsigned>::max() << "\t\t"
		<< numeric_limits<unsigned>::digits << '(' 
		<< sizeof(unsigned) << ')' <<endl << endl;
	cout << "long" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<long>::is_signed << '\t' 
		<< numeric_limits<long>::min() << "\t" 
		<< numeric_limits<long>::max() << "\t"
		<< numeric_limits<long>::digits << endl << endl;
	cout << "float" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<float>::is_signed << '\t' 
		<< numeric_limits<float>::min() << "\t\t" 
		<< numeric_limits<float>::max() << "\t\t"
		<< numeric_limits<float>::digits << endl << endl;
	cout << "double" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<double>::is_signed << '\t' 
		<< numeric_limits<double>::min() << "\t\t" 
		<< numeric_limits<double>::max() << "\t\t"
		<< numeric_limits<double>::digits << endl << endl;
	cout << "long double" << endl;
	cout << "sign\t" << "min\t\t\t" << "max\t\t\t" << "digits" << endl;
	cout << numeric_limits<long double>::is_signed << '\t' 
		<< numeric_limits<long double>::min() << "\t\t" 
		<< numeric_limits<long double>::max() << "\t\t"
		<< numeric_limits<long double>::digits << endl << endl;
	
	return 0;
}

//TODO do something;
