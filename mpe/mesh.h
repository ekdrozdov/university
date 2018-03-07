#pragma once
#include <cstddef>
#include <vector>
#include "node.h"

class Mesh {
public:
	Mesh();
	~Mesh();

	void buildMesh(std::vector ox, std::vector oy);

private:
	Node** nodes;
	int step;
	int height;
	int width;
};
