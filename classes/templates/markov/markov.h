#include<cstdarg>
#include<cstring>
#include<cstdlib>
#include<iostream>
using namespace std;
#define maxstate 1000
#define maxstring 500

template<class T>
class M{
public:
	bool terminated;	// после обработки завершающего правило = true
	T endsymbol;		// символ конца "строки"
	int rules;		// кол-во установленых правил
	int rulesend;		// кол-во правил до (включая) терминирующего
	int rulesmax;		// максимально возможное кол-во правил
	T **from;		// массив содержащий rules элементов - указатели на "строки"
	T **to;			// ---||---
	T *state;		// "строка" подлежащая обработке
	
	M(T endline, int ruleslimit = 100) : endsymbol(endline), rulesmax(ruleslimit) {
		terminated = false;
		from = (T**) malloc(sizeof(T*)*rulesmax);
		to   = (T**) malloc(sizeof(T*)*rulesmax);
		int i = 0;
		for (i = 0; i < rulesmax; i++) {
			*(from + i) = NULL;
			*(to   + i) = NULL;
		}
		state = (T*) malloc(sizeof(T)*maxstate);
		for (i = 0; i < maxstate; i++)
			*(state + i) = endsymbol; 
		rules = 0;
		rulesend = 0;
	}// endline - символ конца строки,
	 // ruleslimit - максимальное количество правил для автомата
	 // начальное состояние алгорифма - пустая строка
	
	~M() {
		for (int i = 0; i < rulesmax; i++) {
			if (*(from+i)) 
				free(*(from+i));
			if (*(to+i)) 
				free(*(to+i));
		}
		free(from);
		free(to);
		free(state);
	}

	bool add_rule(const T* search, const T* replace, bool isterm) {
		if (rules >= rulesmax) {return false;}
		if (terminated) {rulesend = rules;}
		  int i = 0;
	      	  *(from+rules) = (T*) malloc(sizeof(T)*maxstring);
		  for (i = 0; (i < maxstring) && (*(search+i) != endsymbol); i++)
		  	*(*(from+rules)+i) = *(search+i);
		  for (; i < maxstring; i++)
		  	*(*(from+rules)+i) = endsymbol;
		  *(to+rules) = (T*) malloc(sizeof(T)*maxstring);
		  for (i = 0; (i < maxstring) && (*(replace+i) != endsymbol); i++)
		  	*(*(to+rules)+i) = *(replace+i);
		  for (; i < maxstring; i++)
		  	*(*(to+rules)+i) = endsymbol;
		if (isterm) {terminated = true;}
		rules++;
		return true;
	}// возвращает, удалось ли добавить правило, false если лимит исчерпан
	 // search - строка, которую ищут
	 // replace - строка, на которую заменяют
	 // isterm - является ли правило терминальным, true если является

	bool add_rule(bool isterm, ...) {
		va_list ap;
		va_start(ap, isterm);
		if (rules >= rulesmax) {return false;}
		if (terminated) {rulesend = rules;}
		
		if (isterm) {terminated = true;}
		rules++;
		va_end(ap);
		return true;
	}// isterm - является ли правило терминальным, true если является
	// … через запятую записаны элементы строк, сначала search потом replace обе
	// заканчиваются символами конца строки

	void set_state(const T* newstate) {
		int i = 0;
		for (i = 0; (i < maxstate) && (*(newstate+i) != endsymbol); i++)
			*(state+i) = *(newstate+i);
	}// устанавливает текущую строку

	void set_state(T firstchar, ...) {
		va_list ap;
		va_start(ap, firstchar);
		T val = firstchar;
		*state = val;
		int i = 1;
		while((val = va_arg(ap,T)) != endsymbol) {
			*(state+i) = val;
			i++;
		}
		va_end(ap);
		for(;i < maxstate; i++)
			*(state+i) = endsymbol;
	}// устанавливает текущую "строку"

	const T* get_state() const {
		return state;
	}
	// возвращает состояние алгорифма

	void show_rules() const {
		//cout << "rules = " << rules << endl;
		int i = 0, j = 0;
		for (i = 0; (i < rules) && (*(from+i)) && (*(to+i)); i++) {
			for (j = 0; (*(*(from+i)+j)!=endsymbol) && (j < maxstring); j++)
				cout << *(*(from+i)+j);
			cout << " --> ";
			for (j = 0; (*(*(to+i)+j)!=endsymbol) && (j < maxstring); j++)
				cout << *(*(to+i)+j);
			cout << endl;
		}
	}
	// печатает все (даже после терминирующего) добавленные правила

	int run(int limit = 1000000) {
		int step = 0, find = 0, found = -1, len = 0, i = 0, j = 0;
		for(step = 0; step < rulesend; step++) {
			if (step >= limit) {return -1;}
			found = -1;
			len = 0;
			for (find = 0; (find<maxstring) && (*(state+find)!=endsymbol); find++) {
				if (*(state+find)==*(*(from+step))) {
					found = find;
					for(i = 0; *(*(from+step)+i) != endsymbol; i++) {
						if (*(state+find+i) == *(*(from+step)+i)) {
							len++;
							continue;
						} else
							found  = -1;
					}
					if (found != -1)
						break;
				}
			}
			if (found == -1) {
				return step;
				continue;//
			}
			T* buffer = (T*) malloc(maxstring*sizeof(T));
			for (i = 0; i < maxstring; i++) 
				*(buffer+i) = *(state+i);
			for (i = find, j = 0; *(*(to+step)+j) != endsymbol; i++, j++) 
				*(state+i) = *(*(to+step)+j);
			for (; i < maxstring-len+1; i++)
				*(state+i) = *(buffer+len-1+i);
			free(buffer);
		} 
		return (step+1);
	}// запускает автомат, автомат должен сделать не более limit шагов
	 // если на каком-то шаге не удалось применить какое-то правило, то автомат останавливается
	 // функция должна возвращять номер шага, на котором остановится автомат
	 // если автомат не остановился за limit шагов, то вернуть -1 (т.е. если было сделано limit замен, и
	 // последнее из применённых limit правил было терминальным – возвращаем limit, иначе -1).
};
