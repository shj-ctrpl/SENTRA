#include "Random_Generator.h"

using namespace std;

Random_generator::Random_generator() {
	this->seed = 0;
	gen = mt19937(seed);	// Mersenne-Twister generator
}

Random_generator::Random_generator(int seed) {
	this->seed = seed;
	gen = mt19937(seed);	// Mersenne-Twister generator
}

double Random_generator::Random() {				// Generate random number in between 0 and 1
	uniform_real_distribution<double> rand_real(0.0, 1.0);
	return rand_real(gen);
}

double Random_generator::Random(double min, double max) {				// Generate random number in between min and max
	uniform_real_distribution<double> rand_real(min, max);
	return rand_real(gen);
}

int Random_generator::ParticleNumber(double value) {
	uniform_real_distribution<double> rand_real(0.0, 1.0);
	return int(floor(rand_real(gen) + value));
}

double Random_generator::flightLength(double Xsection) {
	if (Xsection == 0.0) {
		return INF();
	}
	return -1 * log(1 - Random()) / Xsection;
}

double Random_generator::pdfPower(double power = 1) {
	return pow(Random(), (1 / (power + 1)));
}

vector3<double> Random_generator::IsoScatter() {
	uniform_real_distribution<double> rand_real(0.0, 1.0);
	double xi_1 = rand_real(gen);
	double xi_2 = rand_real(gen);
	double u = 2 * xi_1 - 1;
	return vector3<double>(u, sqrt(1 - u * u) * cos(2 * PI() * xi_2), sqrt(1 - u * u) * sin(2 * PI() * xi_2));
}
int Random_generator::pdfDiscrete(const vector<double>& probabilities) {
	double random = Random();

	// Normalize the probabilities
	double totalProbability = 0.0;
	for (double probability : probabilities) {
		totalProbability += probability;
	}
	vector<double> normalizedProbabilities;
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

vector3<double> Random_generator::Random3D(const vector3<double>& min, const vector3<double>& max) {
	uniform_real_distribution<double> rand_x(min.x, max.x);
	uniform_real_distribution<double> rand_y(min.y, max.y);
	uniform_real_distribution<double> rand_z(min.z, max.z);

	return vector3<double>(rand_x(gen), rand_y(gen), rand_z(gen));
}