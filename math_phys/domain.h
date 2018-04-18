#pragma once
#include <vector>

class Domain {
public:
	Domain(std::vector<double> x, std::vector<double> y) { ox = x; oy = y; };
	std::vector<double> ox;
	std::vector<double> oy;
};