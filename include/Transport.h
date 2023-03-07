#include <vector>

#include "Cells.h"
#include "Tallies.h"
#include "Particles.h"
#include "Materials.h"
#include "Universes.h"
#include "Collision.h"
#include "Eigenvalue.h"

class Transport;

class Transport {
private:
	int seed;
	float DTS, DTC;
	Collision col;
	Random_generator rng;

	int cell, univ;
	Material* mat;
public:
	// User must set seed before using Trasnport class
	Transport(int seed);
	~Transport() = default;


	void Transport_Particle(int world, std::vector<Particle>& p, std::vector<Particle>& secondary_particles,
		Eigenvalue& k, std::vector<Tally>& tallies);
};