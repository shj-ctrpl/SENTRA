#pragma once
#include <vector>
#include <memory>
#include <unordered_map>

#include "Materials.h"
#include "Random_Generator.h"

class Particle
{
public:
	static int seed;

	vector3<double> pos;
	vector3<double> dir;
	double wgt = 0;
	int grp = 0;

	Random_generator rng;

	Particle(const vector3<double>& pos, const vector3<double>& dir, int grp);
	virtual ~Particle() = default;

	void SurfaceEscape() { pos = pos + (dir * MSD()); }
	void ReflectiveEscape() { pos = pos - (dir * MSD()); }

	int fission(Material* mat);
	int Scatter(Material* mat);
};
