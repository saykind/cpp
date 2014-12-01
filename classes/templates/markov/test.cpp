//#include <iostream>
//using namespace std;
#include "markov.h"
#define TEST(exp) cout << (exp) << endl

int main(void){
	M<char> m('\0', 2);
	m.set_state("AAA");
	TEST( m.get_state() );
	TEST( m.add_rule("AAA", "B", true) );
	TEST( m.add_rule("", "A", false) );
	TEST( !m.add_rule("A", "C", true) );
	//m.show_rules();
	TEST( m.run(100));
	TEST( strcmp(m.get_state(), "B") == 0);

	M<int> m2(0, 10);
//	m2.set_state(5, 0);
//	TEST( m2.get_state()[0] );
//	TEST( m2.get_state()[1] );
//	TEST( m2.add_rule(false, 5, 0, 4, 4, 0) );
//	TEST( m2.add_rule(false, 4, 0, 3, 3, 0) );
//	TEST( m2.add_rule(false, 3, 0, 2, 2, 0) );
//	TEST( m2.add_rule(false, 2, 0, 1, 1, 0) );
//	TEST( m2.run(14) == -1 );
//	TEST( m2.run(14) == 1 );
//	TEST( m2.run() == 0 );
//	TEST( m2.get_state()[15] == 1 );
	return 0;
}
