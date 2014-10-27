#include <iostream>
#define nl '\n'
using namespace std;
class Point {
	int x;
	int y;
	public:
	Point(int x, int y) {this->x = x; this->y = y;}
	Point operator+ (const Point &p) const {
		return Point(x+p.x,y+p.y);
	}
	Point& operator<< (int n) {this->x<<=n; this->y<<=n; return *this;}
        friend ostream &operator<< (ostream &stream, const Point p);
        friend istream &operator>> (istream &stream, Point &p);
};
ostream &operator<< (ostream &stream, const Point p) {
        stream << p.x << ' ' << p.y;
        return stream;
};
istream &operator>> (istream &stream, Point &p) {
    int x, y;
    stream>>x>>y;
    if(stream.good()) {p.x = x; p.y = y;}
    return stream;
};

int main(void) {
	Point p(1,2);
	cout << p << nl;
	cout << (p<<4) << nl;
	return 0;
}
