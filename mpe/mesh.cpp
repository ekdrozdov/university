#include "mesh.h"

Mesh::Mesh() {
	this->height = height;
	this->width = width;
	nodes = NULL;
}

Mesh::~Mesh() {
	height = 0;
	width = 0;
	if (nodes != NULL) {
		for (int i = 0; i < height; ++i) {
			delete[] nodes[i];
		}
		delete[] nodes;
	}
}

void Mesh::buildMesh(int height, int width, int step) {
	nodes = new Node*[height];
	this->step = step;
	for (int i = 0; i < height; ++i) {
		nodes[i] = new Node[width];
	}
	
}
