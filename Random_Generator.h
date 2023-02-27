#pragma once
#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>

#include "Geometries.h"
#include "Foundations.h"

class Random_generator
{
private:
	int seed = 0;
	std::mt19937 gen;

public:
	Random_generator() {
		this->seed = 0;
		gen = std::mt19937(seed);	// Mersenne-Twister generator
	}

	Random_generator(int seed) {
		this->seed = seed;
		gen = std::mt19937(seed);	// Mersenne-Twister generator
	}

	double Random() {				// Generate random number in between 0 and 1
		std::uniform_real_distribution<double> rand_real(0.0, 1.0);
		return rand_real(gen);
	}

	double Random(double min, double max) {				// Generate random number in between min and max
		std::uniform_real_distribution<double> rand_real(min, max);
		return rand_real(gen);
	}

	int ParticleNumber(double value) {
		std::uniform_real_distribution<double> rand_real(0.0, 1.0);
		return int(floor(rand_real(gen) + value));
	}

	double flightLength(double Xsection) {
		if (Xsection == 0.0) {
			return INF();
		}
		return -1 * std::log(1 - Random()) / Xsection;
	}

	double pdfPower(double power = 1) {
		return std::pow(Random(), (1 / (power + 1)));
	}

	Vector3 IsoScatter() {
		std::uniform_real_distribution<double> rand_real(0.0, 1.0);
		double xi_1 = rand_real(gen);
		double xi_2 = rand_real(gen);
		double u = 2 * xi_1 - 1;
		return Vector3(u, sqrt(1 - u * u) * cos(2 * PI() * xi_2), sqrt(1 - u * u) * sin(2 * PI() * xi_2));
	}
	int pdfDiscrete(const std::vector<double>& probabilities) {
		double random = Random();

		// Normalize the probabilities
		double totalProbability = 0.0;
		for (double probability : probabilities) {
			totalProbability += probability;
		}
		std::vector<double> normalizedProbabilities;
		for (double probability : probabilities) {
			normalizedProbabilities.push_back(probability / totalProbability);
		}

		// Sample an event based on the probabilities
		double cumulativeProbability = 0.0;
		for (int i = 0; i < normalizedProbabilities.size(); i++) {
			cumulativeProbability += normalizedProbabilities[i];
			if (random <= cumulativeProbability) {
				return i;
			}
		}
		return -1;  // should never happen
	}

	Vector3 Random3D(const Vector3& min, const Vector3& max) {
		std::uniform_real_distribution<double> rand_x(min.x, max.x);
		std::uniform_real_distribution<double> rand_y(min.y, max.y);
		std::uniform_real_distribution<double> rand_z(min.z, max.z);

		return Vector3(rand_x(gen), rand_y(gen), rand_z(gen));
	}
};

#endif