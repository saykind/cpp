#include <cstdio>
#include <iostream>
using namespace std;
#include "vector.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {return 0;}

	const int n = 9;
	vector<n>  freq ("Frequency", "Hz");
	vector<n>  volt ("Voltage", "V");
	
	FILE *fp = fopen(argv[1], 'r');
	char str[100];
	char c;
	while(fscanf(fp, "%c", &c)) {
		if (c == '#') {getline(str, 100, fp); continue;}
		else ungetc(c, fp);	
		for(int i = 0; i < n; i++) {
			fscanf(fp, "%lf", &freq[i]); 
			fscanf(fp, "%lf", &volt[i]);
		}
	}	
	
	cout << freq;
	cout << volt;
	return 0; 
}
