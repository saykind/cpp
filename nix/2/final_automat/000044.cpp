#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;


template<class T_state, class T_alphabet, int rules_limit> 
// T_state - ��� ��������� �������� ���� ��� ����� ��� ������������, �� ��������� ���������� � ���� 
// T_alphabet - ��� �����, ����������� ��������� ��� ��������� � ��� ����� ����� ����������. 
// rules_limit - ������������ ���������� ������ 
class FA{ 
public: 
	int ruleslimit;
	int count;
	T_state state;
	T_state* ruless;
	T_state* rulesn;
	T_alphabet* rulesa;
FA(T_state startstate) : ruleslimit(rules_limit), state(startstate) {
		ruless = (T_state*) malloc(ruleslimit*sizeof(T_state));
		rulesn = (T_state*) malloc(ruleslimit*sizeof(T_state));
		rulesa = (T_alphabet*) malloc(ruleslimit*sizeof(T_alphabet));
		//for (int i = 0; i < ruleslimit; i++) {
		//	(ruless+i) = NULL;
		//	(rulesn+i) = NULL;
		///	(rulesa+i) = NULL;
		//}
		count = 0;
}// ������ ������� c 0 ������, ������� ��������� ������������� ��� startstate 
~FA() {
		free(ruless);
		free(rulesn);
		free(rulesa);
}
bool add_rule(const T_state &state, const T_alphabet &alpha, const T_state &new_state) {
	if (count >= ruleslimit) {return false;}
		int found = 0;
	int i = 0;
	for (i = 0; i < count; i++) {
		if (*(ruless+i)==state) {
			if (*(rulesa+i)==alpha) {
				found = 1;
				break;
			}
		}
	}
	if (found) {return false;}

	*(ruless+count) = state;
	*(rulesn+count) = new_state;
	*(rulesa+count) = alpha;
	count++;
	return true;
}
// ����������, ������� �� �������� �������, false ���� ����� rules_limit �������� ��� ������� ��� ����������
// state - ������� ���������
// alpha - ������� �����
// new_state - ����� ���������

size_t rules_lim() {return ruleslimit;}
// ���������� rules_limit 

size_t rules_size() {return count;}
// ���������� ������� ���������� ������ 

void set_state(T_state newstate) {state = newstate;}
// ������������� ������� ��������� 

T_state get_state() const {return state;}
// ���������� ������� ��������� 

int make_step(const T_alphabet &alpha) {
	int found = 0;
	int i = 0;
	for (i = 0; i < count; i++) {
		if (*(ruless+i)==state) {
			if (*(rulesa+i)==alpha) {
				found = 1;
				break;
			}
		}
	}
	if (!found) {return -1;}
	state = *(rulesn+i);
	return i;
}
// ������ 1 ���, �������� ��������� ����� alpha (� ������ ��������� �������� � ������������ � ��������) 
// ���������� ����� ����������� ������� ��� -1 ���� ������� �� ���������� 

const T_alphabet* run(const T_alphabet* str, int N) {
	int i = 0;
	for(i = 0; i < N; i++) {
		if (this->make_step(*(str+i)) == -1) 
			return (str+i);
	}
	return NULL;
}
// ���������� ��������� �� ������, ��� �������� �� ������� �������, ����� NULL 
// ��������� ������� �� ����� str 
// ��� ����� ������� �� N ���� 
// ����� ����������� �� ������� 
}; 







//int main(void) {
//	cout << "Hi" << endl;

//	FA<int, char, 10> a(2);
//	a.set_state(1);
//	cout << "rules_size = "<< a.rules_size() << endl;

//	a.add_rule(1,'a',2);

//	cout << "state = " << a.get_state() << endl;
//	a.make_step('a');
///	cout << "state = " << a.get_state() << endl;

//	getchar();
//	return 0;
//}
