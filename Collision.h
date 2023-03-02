#pragma once
#include "Geometries.h"

class Collision {
public:
	std::vector<int> lattice_pos;
	std::vector<int> univId;
	std::vector<vector3<double>> biases;
	vector3<double> bias;

	int lastuniv;
	int surfId;
	int cellId;

	Collision();
	~Collision() = default;

	void Initialize();
	void AddBias(const vector3<double>& bias);
	void RemoveBias();
};