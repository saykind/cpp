#include <iostream>
#define newline '\n'
using namespace std;

class dog {
	string name;
	int age;
	public:
	void setName 	(string newName) 	{name 	= newName;}
	void setAge 	(int newAge) 		{age 	= newAge;}
	int getAge 	(void) 	{return age;}
	string getName 	(void)	{return name;}
};


int main (int argc, char *argv[]) {
	dog Rex;
	string input;
	int n;
	cout << "Hello, I'm object - \'dog\' class member. Set name: ";
	cin >> input;
	Rex.setName(input);
	cout << "Now my name is " << Rex.getName() << endl;
	cout << "How old you want me to be? Set age: ";
	cin >> input;
	Rex.setAge(stoi(input));
	cout << "I'm " << Rex.getAge() << " years old now!" << newline; 
	return 0;
}
