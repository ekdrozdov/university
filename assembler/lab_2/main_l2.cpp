#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h> 
#include<conio.h> 
#include <windows.h>

extern "C" void __fastcall REPSTR(int COUNT, char BASESTR[8], int STRLEN);
extern "C" char NEWSTR[32] = "THIS IS A STRING";

int strlen(char* str);

void main() {
	char baseStr[8] = "Hello! ";
	int len = strlen(baseStr);
	int count = 3;

	REPSTR(count, baseStr, len);

	printf("newStr = %s\n", NEWSTR);
	_getch();
}

int strlen(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	return i;
}