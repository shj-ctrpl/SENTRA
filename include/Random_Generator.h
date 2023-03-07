#pragma once

#include <random>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>

#include "Geometries.h"
#include "Utilities.h"

enum ReactionType {
	FIS = 0,
	ABS = 1,
	SCT = 2
};

class Random_generator
{
private:
	int seed = 0;
	std::mt19937 gen;

public:
	Random_generator();
	Random_generator(int seed);

	double Random();
	double Random(double min, double max);
	int ParticleNumber(double value);
	double flightLength(double Xsection);
	double pdfPower(double power);

	vector3<double> IsoScatter();
	int pdfDiscrete(const std::vector<double>& probabilities);
	vector3<double> Random3D(const vector3<double>& min, const vector3<double>& max);
};
