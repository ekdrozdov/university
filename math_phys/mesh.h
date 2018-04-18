#pragma once
#include <cstddef>
#include <vector>

class Mesh {
public:
	Mesh();
	~Mesh();

	void buildSLAE(std::vector<double> ox, std::vector<double> oy);

private:
	double** A;
	double x;
	double b;
	double gamma;
	double lambda;
};
