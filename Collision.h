#pragma once

#include <vector>

#include "Geometries.h"

using namespace std;

class Collision {

public:
	vector<int> lattice_pos;
	vector<int> univId;
	vector<vector3<double>> biases;
	vector3<double> bias;

	int lastuniv;
	int surfId;
	int cellId;

	Collision() {
		univId = {};
		biases = {};
		bias = vector3<double>(0, 0, 0);
		lastuniv = -1;
		surfId = -1;
		cellId = -1;
	}

	void Initialize() {
		univId.clear();
		biases.clear();
		bias = vector3<double>(0, 0, 0);
		lastuniv = -1;
		surfId = -1;
		cellId = -1;
	}

	void AddBias(const vector3<double>& bias) {
		biases.push_back(bias);
		double x = 0, y = 0;
		for (vector3<double>& v : biases) {
			x += v.x;
			y += v.y;
		}
		this->bias = vector3<double>(x, y, 0);
	}

	void RemoveBias() {
		if (!biases.empty()) { biases.pop_back(); }
		double x = 0, y = 0;
		for (vector3<double>& v : biases) {
			x += v.x;
			y += v.y;
		}
		this->bias = vector3<double>(x, y, 0);
	}
};