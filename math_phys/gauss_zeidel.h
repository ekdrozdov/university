typedef double type;
#include <conio.h> 
#include <stdio.h> 
#include <math.h> 
class GaussZeidel
{
public:
	void SetData(int n1, int m1, type* F1, type** A1);
	int IterStep();
	type* Resh();
	type CalcNorm(type* s);
private:
	type** A;
	int n;
	int m;
	int iter;
	int count;
	type* F;
	type* X;
	type* Xp;
	type W;
	type eps;
};