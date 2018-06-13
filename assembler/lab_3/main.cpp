#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h> 
#include<conio.h> 
#include <windows.h>

extern "C" void __fastcall STEFF(int itersToDo, float initCond);
extern "C" float ROOT = 0; 

void main() {
	float initCond = 0.8; // 8 bytes in size
	int itersToDo = 4;

	/*printf("Enter amount of iterations to do: ");
	scanf("%d/n", &itersToDo);
	printf("Enter initial condition: ");
	scanf("%lf/n", &initCond);*/

	STEFF(itersToDo, initCond);

	printf("Founded root = %lf\n", ROOT);
	printf("Press any key to exit...");
	_getch();
}