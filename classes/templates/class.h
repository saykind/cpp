template <class type = float, int size = 5>
// default value for type is 'float'
// default value for size is '5'

class vector {
public:
	type s[size];
	static const int size_ = size;
	vector() {for(int i = 0; i < size; i++) s[i] = 0; }
	vector(type a) {for(int i = 0; i < size; i++) s[i] =a; }
	type add(type x) {
		for(int i = 0; i < size; i++) s[i]+=x;}
//	friend ostream &operator<< (ostream &stream, vector &a);
};



// Example of use:
// vector<int, 10> a;		// creates vector of 10 elementes with typei int; 
