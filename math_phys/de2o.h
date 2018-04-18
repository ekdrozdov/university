#pragma once

class DE2O {
public:
	double lambda;
	double gamma;
	virtual double f(double x, double y) = 0;
	virtual double teta(double x, double y) = 0;

	static const int nBounds = 6;
	int boundaryConditions[nBounds];
};