#include <stdio.h>
#define SUM(A,B) \
A+B	

#define STR(x) #x
#define PRINT(x) printf(#x)
//#define PRINT_(x) putchar(#@x)

#define PRINTVAR(n) printf("Var" #n " - %d\n", var##n)

int main(int argv, char *argc[]) {
	SUM(2,3);
	char date[] = __DATE__;
	char file[] = __FILE__;
//#line 100 "define.c"
	char line[] = STR(__LINE__);
	char time[] = __TIME__;
	printf("%s\n""%s\n%s\n%s\n", date, time, file, line);
	PRINT(text);
	PRINT(\n);
	PRINT("text");


	int var1 = 1;
	int var2 = 2;
	PRINTVAR(1);
	return 0;
}
