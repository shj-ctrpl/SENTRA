#pragma once
#include <vector>
#include <memory>
#include <unordered_map>

#include "Collision.h"
#include "Universes.h"
#include "Eigenvalue.h"
#include "Cells.h"
#include "Surfaces.h"
#include "Geometries.h"
#include "Random_Generator.h"
#include "Materials.h"

class Particle
{
private:
	vector3<double> pos, dir;
	int grp = 0;
	double weight = 1.0, flightlength = 0.0;
	double dts = 0, dtc = INF();
public:
	static int seed;
	static Collision col;
	Random_generator rng;

	Particle(const vector3<double>& pos, const vector3<double>& dir, int eGroup) {
		this->pos = pos;
		this->dir = dir.normalized();
		this->grp = eGroup;
		this->rng = Random_generator(seed);
	}

	void SetSeed(const int& seed);

	void Transport(int world, std::vector<Particle>& sParticles, Eigenvalue& E);
	void SurfaceEscape(Eigenvalue& E);
	void ReflectiveEscape(Eigenvalue& E);

	void Scatter(const Material& mat);
	void Capture(const Material& mat);
	void Fission(const Material& mat, std::vector<Particle>& sParticles);

	void ShowDebug();
};