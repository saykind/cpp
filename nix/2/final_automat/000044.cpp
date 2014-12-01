#include <cstdlib>
#include <cstdio>
#include <iostream>
using namespace std;


template<class T_state, class T_alphabet, int rules_limit> 
// T_state - тип состояния автомата Если тип целый или перечисление, то нумерация начинается с нуля 
// T_alphabet - тип буквы, принимаемой автоматом Тип состояния и тип буквы могут отличаться. 
// rules_limit - максимальное количество правил 
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
}// создаёт автомат c 0 правил, текущее состояние устанавливает как startstate 
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
// возвращает, удалось ли добавить правило, false если лимит rules_limit исчерпан или правило уже существует
// state - текущее состояние
// alpha - текущяя буква
// new_state - новое состояние

size_t rules_lim() {return ruleslimit;}
// возвращает rules_limit 

size_t rules_size() {return count;}
// возвращает текущее количество правил 

void set_state(T_state newstate) {state = newstate;}
// устанавливает текущее состояние 

T_state get_state() const {return state;}
// возвращает текущее состояние 

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
// делает 1 шаг, пытается применить букву alpha (и меняет состояние автомата в соответствии с правилом) 
// возвращает номер применённого правила или -1 если правило не обнаружено 

const T_alphabet* run(const T_alphabet* str, int N) {
	int i = 0;
	for(i = 0; i < N; i++) {
		if (this->make_step(*(str+i)) == -1) 
			return (str+i);
	}
	return NULL;
}
// возвращает указатель на символ, для которого не нашлось правила, иначе NULL 
// запускает автомат на слове str 
// это слово состоит из N букв 
// буквы применяются по очереди 
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
