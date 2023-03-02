#include <vector>

#include "Collision.h"
#include "Geometries.h"

Collision::Collision() {
	univId = {};
	biases = {};
	bias = vector3<double>(0, 0, 0);
	lastuniv = -1;
	surfId = -1;
	cellId = -1;
}

void Collision::Initialize() {
	univId.clear();
	biases.clear();
	bias = vector3<double>(0, 0, 0);
	lastuniv = -1;
	surfId = -1;
	cellId = -1;
}

void Collision::AddBias(const vector3<double>& bias) {
	biases.push_back(bias);
	double x = 0, y = 0;
	for (vector3<double>& v : biases) {
		x += v.x;
		y += v.y;
	}
	this->bias = vector3<double>(x, y, 0);
}

void Collision::RemoveBias() {
	if (!biases.empty()) { biases.pop_back(); }
	double x = 0, y = 0;
	for (vector3<double>& v : biases) {
		x += v.x;
		y += v.y;
	}
	this->bias = vector3<double>(x, y, 0);
}