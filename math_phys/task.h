#pragma once
#include "de2o.h"

class Task : public DE2O {
public:
	Task(double lambda, double gamma) { this->lambda = lambda; this->gamma = gamma; };
	double f(double x, double y);
	double teta(double x, double y);
};