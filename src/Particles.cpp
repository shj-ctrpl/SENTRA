#include "Particles.h"

using namespace std;

int Particle::seed = 0;

//================================
// Class Particle
//================================


Particle::Particle(const vector3<double>& pos, const vector3<double>& dir, int grp) {
	this->pos = pos;
	this->dir = dir.normalized();
	this->grp = grp;
	this->rng = Random_generator(seed);
}

int Particle::fission(Material* mat) {
	int particleNum = rng.ParticleNumber(mat->GetNu(grp));
	return particleNum;
}
int Particle::Scatter(Material* mat) {
	grp = rng.pdfDiscrete(mat->GetXsSct(grp));
	dir = rng.IsoScatter();
	return 0;
}