#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
using namespace std;
//	V - входной алфавит
//	Q - алфавит состояний
//	F - множество конечных состояний
//	P - функция переходов
template<class Vtype, class Qtype>
class FiniteAutomat {
public:
	typedef map<Qtype, bool>	Ftype;
	typedef pair<Qtype, Vtype>	PKtype;
	typedef map<PKtype, Qtype>	Ptype;
	vector<Vtype>	V;
	vector<Qtype>	Q;
	Qtype q;	// Current state
	Ftype F;
	Ptype P;
	
	FiniteAutomat(vector<Vtype> V, vector<Qtype> Q,
		Qtype q0, Ftype F, Ptype P) :
		V(V), Q(Q), F(F), P(P), q(q0) {};
	Qtype getState() {return Q;};
	
	bool step(Vtype v) {
		map<PKtype, Qtype>::iterator it = P.find(PKtype(q,v));
		if (it == P.end()) {return false;}
		q = (*it).second;
		return true;
	};
	bool isFinal() {
		Ftype::const_iterator it = F.find(Q);
		return (it != F.end());
	}
	Vtype run(Vtype *input) {
		for (; *input && !isFinal(); input++) {
			cout << q << " (" << *input << ") -> ";
			step(*input);
			cout << q << endl;
		}
		return *input;
	}
};

int main(void) {
	typedef char Vtype;
	typedef char Qtype;
	typedef FiniteAutomat<Vtype, Qtype> Automat;

	vector<Vtype> V(2);
	V[0] = 'U';
	V[1] = 'D';

	vector<Qtype> Q(5);
	Q[0] = 'B';
	Q[1] = 'R';
	Q[2] = 'Y';
	Q[3] = 'G';
	Q[4] = 'E';
	
	Qtype Q0 = Q[2];

	Automat::Ftype F;
	F[Q[0]] = true;
	F[Q[4]] = true;

	Automat::Ptype P;
	P[Automat::PKtype(Q[1],V[0])] = Q[0];
	P[Automat::PKtype(Q[2],V[0])] = Q[1];
	P[Automat::PKtype(Q[3],V[0])] = Q[3];
	P[Automat::PKtype(Q[1],V[1])] = Q[2];
	P[Automat::PKtype(Q[2],V[1])] = Q[3];
	P[Automat::PKtype(Q[3],V[1])] = Q[4];

	Automat myAutomat(V, Q, Q0, F, P);
	Vtype* input = "DDUDUUDU";
	myAutomat.run(input);
		
	return 0;
}
