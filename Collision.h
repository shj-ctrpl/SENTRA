#pragma once

#include <vector>

#include "Geometries.h"

using namespace std;

class Collision {

public:
	vector<int> univId;
	vector<Vector3> biases;
	Vector3 bias;
	int lastuniv;
	int surfId;
	int cellId;

	Collision() {
		univId = {};
		biases = {};
		bias = Vector3(0, 0, 0);
		lastuniv = -1;
		surfId = -1;
		cellId = -1;
	}

	void Initialize() {
		univId.clear();
		biases.clear();
		bias = Vector3(0, 0, 0);
		lastuniv = -1;
		surfId = -1;
		cellId = -1;
	}

	void AddBias(const Vector3& bias) {
		biases.push_back(bias);
		double x = 0, y = 0;
		for (Vector3& v : biases) {
			x += v.x;
			y += v.y;
		}
		this->bias = Vector3(x, y, 0);
	}

	void RemoveBias() {
		if (!biases.empty()) { biases.pop_back(); }
		double x = 0, y = 0;
		for (Vector3& v : biases) {
			x += v.x;
			y += v.y;
		}
		this->bias = Vector3(x, y, 0);
	}
};