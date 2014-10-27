#include <iostream>
class Point {
public:
	static int count; 
	int x;
	int y;

	//Constructor
	Point(int _x, int _y) : x(_x), y(_y) {count++;} 
//	Point(int _x, int _y) {
//	x = _x; y = _y;} 

	// Copy
	Point(Point &p) : x(p.x), y(p.y) {}

	// Operator=
/*	Point operator= (Point &p) {
		x = p.x;
		y = p.y;	
	}
*/
	//Destructor
	~Point() {count--;}

	static int x0;
	static int y0;
	void FlipX() {y = -y;}
	void FlipX0() const {y0 = -y0;}
	static int FlipY0() {x0 = -x0;}
//	int MDist() const;
};
int Point::x0 = 0;
int Point::y0 = 0;
int Point::count = 1;
//int Point::MDist() {
//	return abs(x-x0)+abs(y-y0);
//}


using namespace std;
int main(void) {
	Point p (1,1);
	Point q(p);
	
//	Point w;
//	w = p;
//	cout << p.x + p.y << '\n';
	cout << "There is " << p.count << " objects of class Point " << '\n';
	return 0;	
}

