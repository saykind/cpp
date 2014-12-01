#define LEN 10
#include <iostream>
using namespace std;
#include <cstring>
template <int Size = 0, class Type = double>
class vector {
private:
	char *name;
	char *dim;
	static const int size = Size;
	Type data[Size];
public:
	vector(void) {for (int i = 0; i < size; i++) data[i] = (Type) 0; name = NULL; dim = NULL;}
	vector(char const *Dim) : 
		dim(new char[strlen(Dim)+1]) 
		{strcpy(dim, Dim);}
	vector(char const *Name, char const *Dim) : 
		name(new char[strlen(Name)+1]),
		dim(new char[strlen(Dim)+1])
		{strcpy(name, Name); strcpy(dim, Dim);}
	~vector() {if (dim) delete[] dim; if (name) delete[] name;}

	Type &operator[] (int i) {/*if ((i < 0)||(i >= size)) return 0;*/ return data[i];} 
	friend ostream &operator<< (ostream &stream, const vector &v) {
	stream << v.name << '[' << v.dim << ']' << endl;
		for (int  i = 0; i < size; i++)
			stream << '[' << i+1 << ']' << ' ' << v.data[i] << endl;
		stream << endl;
		return stream;
	}
	friend istream &operator>> (istream &stream, vector &v) {
		Type val;
		for (int i = 0; i < size; i++) {
			stream >> val;
			if (stream.good()) v.data[i] = val;
		}
		return stream;
	}

	friend plot(const vector &x, const vector &y);
	
};
