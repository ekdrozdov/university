#include "mesh.h"

Mesh::Mesh() {

}

Mesh::~Mesh() {

}

void Mesh::buildSLAE(std::vector<double> ox, std::vector<double> oy) {
	int height = oy.size();
	int width = ox.size();

	int nLayoutPoints = 5;

	int nodesTotal = ox.size() * oy.size();
	A = new double*[nodesTotal];
	for (int i = 0; i < height; ++i) {
		A[i] = new double[nLayoutPoints];
		for (int j = 0; j < nLayoutPoints; ++j) {
			A[i][j] = 0.0;
		}
	}
	/*
	double deltaY = oy[1] - oy[0];
	double deltaX = ox[1] - ox[0];
	for (int i = 0; i < nodesTotal; ++i) {
		
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			A[i][j] = ...;
		}
	}*/
}
