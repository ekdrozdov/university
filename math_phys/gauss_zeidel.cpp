#include "gauss_zeidel.h" 

void GaussZeidel::SetData(int n1, int m1, type* F1, type** A1)
{
	int i, j;
	n = n1;
	m = m1;
	X = new type[n];
	Xp = new type[n];
	F = new type[n];
	A = new type*[n];
	iter = 10000;
	W = 1.4;
	eps = 1E-15;
	for (i = 0; i < n; i++)
		A[i] = new type[5];
	for (i = 0; i < n; i++)
	{
		F[i] = F1[i];
		Xp[i] = 0.0;
		for (j = 0; j < 5; j++)
			A[i][j] = A1[i][j];
	}
}

type GaussZeidel::CalcNorm(type* sum)
{
	type norm = 0;
	for (int i = 0; i < n; i++)
	{
		norm += sum[i] * sum[i];
	}
	norm = sqrt(norm);
	return norm;
}

int GaussZeidel::IterStep()
{
	int i, j, indj, indx, x;
	indx = 0;
	indj = 2;
	type* N;
	type F1, F2;
	type sum, sum1;
	N = new type[n];
	for (i = 0; i < n; i++, indx++)
	{
		if (i == 1 || i == 2 + m)
		{
			indx = 0;
			indj--;
		}
		j = indj;
		x = indx;
		sum = F[i];
		sum1 = F[i];
		if (j < 1)
		{
			sum -= A[i][j] * Xp[x];
			sum1 -= A[i][j] * X[x];
			x += m + 1;
			j++;
			sum -= A[i][j] * Xp[x];
			sum1 -= A[i][j] * X[x];
			x++;
			j++;
		}
		else if (j == 1)
		{
			sum -= A[i][j] * Xp[x];
			sum1 -= A[i][j] * X[x];
			x++;
			j++;
		}
		while (j < 4 && x < n)
		{
			sum -= A[i][j] * Xp[x];
			sum1 -= A[i][j] * Xp[x];
			x++;
			j++;
		}
		if (x + m < n)
		{
			x += m;
			sum -= A[i][j] * Xp[x];
			sum1 -= A[i][j] * Xp[x];
		}
		N[i] = sum;
		X[i] = Xp[i] + W / A[i][2] * sum1;
	}
	F1 = CalcNorm(N);
	F2 = CalcNorm(F);
	if (F1 / F2 < eps)
		return 1;
	else return 0;
}

type* GaussZeidel::Resh()
{
	count = 0;
	int i, j, quit = 0;
	for (i = 0; i < iter && quit != 1; i++)
	{
		quit = IterStep();
		for (j = 0; j < n; j++)
			Xp[j] = X[j];
		count++;
	}
	return X;
}