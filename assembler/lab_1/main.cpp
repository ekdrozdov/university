//#include "stdafx.h"
#include <stdio.h>
#include "FUNC.asm"

extern "C" int __fastcall FUNC(int A1, int A2, int A3); // используется 
extern "C" int VAL = 0;
void main() {
	int x = 10;
	FUNC(x, 20, 20 + 5);
	printf("VAL = %d\n", VAL);
}