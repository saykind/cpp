#include <iostream>
#include <vector>
#include <cstdarg>

using namespace std;

template<class T>
class M {
private:
	T end_symbol;
	int limit;
	int rules_count;
	vector<T> state;
	//int statesize;
	vector< vector <T> > srch;
	vector< vector <T> > rpls;
	vector< bool > istrm;

//Дополнительное требование: пустой конструктор, оператор присваивания, конструктор копирования должны быть запрещены
	M(){};
	M(const M &){};
	M& operator=(const M &){};

public:
	M(T , int = 100);
	~M();

	bool add_rule(const T* search, const T* replace, bool isterm);
	bool add_rule(bool isterm, ...);

	void set_state(const T* state);
	void set_state(T firstchar, ...);

	const T* get_state() const;

	int run(int = 1000000);
};

template<class T>
M<T>::~M()
{
	for (int i = 0; i < rules_count; i++)
	{
		srch[i].clear();
		rpls[i].clear();
	}
	srch.clear();
	rpls.clear();
	istrm.clear();
	state.clear();
}

template<class T>
M<T>::M(T endline, int ruleslimit)
{
	end_symbol = endline;
	limit = ruleslimit;
	rules_count = 0;
	state.push_back(endline);
}


template<class T>
bool M<T>::add_rule(const T* search, const T* replace, bool isterm)
{
	if (rules_count < limit)
	{
		rules_count++;
		istrm.push_back(isterm);

		vector<T> temp;
		const T* s = search;
		while (*s != end_symbol)
		{
			temp.push_back(*s);
			s++;
		}
		temp.push_back(end_symbol);

		srch.push_back(temp);
		
		vector<T> tempr;
		s = replace;
		while (*s != end_symbol)
		{
			tempr.push_back(*s);
			s++;
		}
		tempr.push_back(end_symbol);

		rpls.push_back(tempr);

		return true;
	}
	else
		return false;
}

template<class T>
bool M<T>::add_rule(bool isterm, ...)
{
	if (rules_count < limit)
	{
		rules_count++;
		istrm.push_back(isterm);

		vector<T> temps;

		////
		T val;

		va_list vl;
		va_start(vl, isterm);		 

		val=va_arg(vl, T);
		while (val != end_symbol)
		{
			temps.push_back(val);
			val=va_arg(vl, T);
		}
		temps.push_back(end_symbol);
		
		srch.push_back(temps);

		vector<T> tempr;
		val=va_arg(vl, T);
		while (val != end_symbol)
		{
			tempr.push_back(val);
			val=va_arg(vl, T);
		}
		tempr.push_back(end_symbol);

		rpls.push_back(tempr);
		va_end(vl);

		return true;
	}
	else
		return false;
}

template<class T>
void M<T>::set_state(const T* st)
{
	state.clear();

	int i = 0;
	while (st[i] != end_symbol)
	{
		state.push_back(st[i]);
		i++;
	}
	state.push_back(end_symbol);
}

template<class T>
void M<T>::set_state(T firstchar, ...)
{
	state.clear();

	T *st = &firstchar;
	while (*st != end_symbol)
	{
		state.push_back(*st);
		st++;
	}
	state.push_back(end_symbol);
}


template<class T>
const T* M<T>::get_state() const
{
	return &state[0];
}


template<class T>
int M<T>::run(int limit)
{
	int cur = 0;
	bool p = false;
	while (cur < limit)
	{
		int num = -1; //номер правила, которое будем применять
		int search = -1; //номер символа, начиная с которого удалять
		for (int i = 0; i < rules_count; i++)
		{
			bool q = true;
			int _len = state.size() - 1;
			int _lensr = srch[i].size() - 1;
			if (_len < _lensr)
				q = false;
			else
			{
				if (_lensr == 0)
				{
					search = 0;
					num = i;
					break;
				}

				for (int j = 0; j < _len - _lensr + 1; j++)
				{
					q = true;
					for (int t = 0; t < _lensr; t++)
						if (state[j + t] != srch[i][t])
						{
							q = false;
							break;
						}
					if (q)
					{
						search = j;
						num = i;
						break;
					}
				}
			}

			if (q)
				break;
		}

		if (num == -1)
		{
			p = true;
			break;
		}

		state.erase(state.begin() + search, state.begin() + search + srch[num].size() - 1);
		state.insert(state.begin() + search, rpls[num].begin(), rpls[num].end() - 1);
		
		cur++;
		
		if (istrm[num])
		{
			p = true;
			break;
		}
	}

	if (p)
		return cur;
	else
		return -1;
}


#if _DEBUG
	int main(void)
	{
		M<char> test('\0');
	
		{
		M<char> m('\0', 2);

		cout << m.add_rule("AAA", "B", true) << endl;
		m.add_rule("", "A", false);

		cout << !m.add_rule("A", "C", true) << endl;

		cout << m.run(100) << endl;

		if (strcmp(m.get_state(), "B") == 0)
			cout << "Right" << endl;

		cout << m.get_state() << endl;
		}
		cout << endl << endl;

		M<int> m2(0, 10);
		m2.set_state(5, 0);
		m2.add_rule(false, 5, 0, 4, 4, 0);

		m2.add_rule(false, 4, 0, 3, 3, 0);

		m2.add_rule(false, 3, 0, 2, 2, 0);

		m2.add_rule(false, 2, 0, 1, 1, 0);

		cout << "m2" << endl << m2.run(14) << endl;
		cout << m2.run(14)<< endl;
		cout << m2.run()<< endl;
		cout << "m2[15] = " <<  m2.get_state()[15] << endl;
		cout << endl << endl;

		M<char> m3('\0', 10);
		m3.add_rule("A" ,"", false);
		m3.add_rule("B", "A", false);
		m3.add_rule("", "FINISH", true);

		cout << "m3" << endl << "AAAABBB" << endl;
		m3.set_state("AAAABBB");
		cout << m3.run(3) << endl << m3.get_state() << endl;
		cout << m3.run() << endl << m3.get_state() << endl;


		M<int> m4(0, 10);
		m4.set_state(5, 1, 4, 4, 0);
		m4.add_rule(false, 5, 1, 4, 4, 0, 0);

		m4.add_rule(false, 4, 0, 3, 3, 0);

		m4.add_rule(false, 3, 0, 2, 2, 0);

		m4.add_rule(false, 2, 0, 1, 1, 0);

		cout << "m4" << endl << m4.run(1) << endl;
		cout << m4.run(14)<< endl;
		cout << m4.run()<< endl;
	
		system("pause");
		return 0;
	}
#endif




