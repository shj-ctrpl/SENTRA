#include "Particles.h"

using namespace std;

int Particle::seed = 0;
Collision Particle::col;

void Particle::SetSeed(const int& seed) {
	this->rng = Random_generator(seed);
}

void Particle::Transport(int world, vector<Particle>& sParticles, Eigenvalue& E) {
	bool stuck = false;
	bool hasfill = true;
	col.Initialize();
	col.univId.push_back(world);
	// cout << "Go" << endl;
	while (true) {
		while (hasfill) {
			while (true) {
				if (col.univId.empty()) {
					return;
				}
				if (Universe::universes[col.univId.back()]->findCell(pos + col.bias, col)) {
					break;
				}
				else {
					SurfaceEscape(E);
				}
			}

			hasfill = Cell::cells[col.cellId]->findFill(col);

			if (col.cellId == -1) {
				cout << "DEAD" << endl;
				return;
			}
		}
		hasfill = true;
	determineDTS:
		dts = Cell::cells[col.cellId]->DTS(pos + col.bias, dir, col) + EPS();
		dtc = rng.flightLength(Cell::cells[col.cellId]->material.GetXsTot(grp));


		// ShowDebug();

		if (dts > dtc) {
			pos = pos + dir * dtc;
			E.add_Pathlength(Cell::cells[col.cellId]->material.GetNu(grp) * Cell::cells[col.cellId]->material.GetXsFis(grp) * dtc);
			break;
		}
		else {
			if (Surface::surfaces[col.surfId]->IsReflective()) {
				if (dts < MSD()) { ReflectiveEscape(E); }
				pos = pos + dir * (dts - 2 * EPS());
				Surface::surfaces[col.surfId]->Reflect(pos, dir);
			}
			else {
				if (dts < MSD()) { SurfaceEscape(E); }
				pos = pos + dir * dts;
			}
			E.add_Pathlength(Cell::cells[col.cellId]->material.GetNu(grp) * Cell::cells[col.cellId]->material.GetXsFis(grp) * dts);
		}

	}
	E.add_Collision(Cell::cells[col.cellId]->material.GetNu(grp)
		* Cell::cells[col.cellId]->material.GetXsFis(grp) / Cell::cells[col.cellId]->material.GetXsTot(grp));

	switch (rng.pdfDiscrete(Cell::cells[col.cellId]->material.GetXsAlltype(grp))) {
	case 0:
		Fission(Cell::cells[col.cellId]->material, sParticles);
		E.add_Absorption(Cell::cells[col.cellId]->material.GetNu(grp)
			* Cell::cells[col.cellId]->material.GetXsFis(grp) / Cell::cells[col.cellId]->material.GetXsAbs(grp));
		break;
	case 1:
		Capture(Cell::cells[col.cellId]->material);
		E.add_Absorption(Cell::cells[col.cellId]->material.GetNu(grp)
			* Cell::cells[col.cellId]->material.GetXsFis(grp) / Cell::cells[col.cellId]->material.GetXsAbs(grp));
		break;
	case 2:
		Scatter(Cell::cells[col.cellId]->material);
		goto determineDTS;
		break;
	default:
		break;
	}
}

void Particle::SurfaceEscape(Eigenvalue& E) {
	pos = pos + (dir * MSD());
	E.add_Pathlength(Cell::cells[col.cellId]->material.GetNu(grp) * Cell::cells[col.cellId]->material.GetXsFis(grp) * MSD());
}

void Particle::ReflectiveEscape(Eigenvalue& E) {
	pos = pos - (dir * MSD());
	E.add_Pathlength(Cell::cells[col.cellId]->material.GetNu(grp) * Cell::cells[col.cellId]->material.GetXsFis(grp) * MSD());
}

void Particle::Scatter(const Material& mat) {
	grp = rng.pdfDiscrete(mat.GetXsSct(grp));
	dir = rng.IsoScatter();
}

void Particle::Capture(const Material& mat) {
	return;
}

void Particle::Fission(const Material& mat, vector<Particle>& sParticles) {
	int particleNum = rng.ParticleNumber(mat.GetNu(grp));
	int particleGrp = rng.pdfDiscrete(mat.GetChi());
	for (int i = 0; i < particleNum; i++) {
		sParticles.push_back(Particle(pos, rng.IsoScatter(), particleGrp));
		seed++;
	}
}

void Particle::ShowDebug() {
	cout << pos.x << " " << pos.y << " " << pos.z << " ";
	//cout << dir.x << " " << dir.y << " " << dir.z << " ";
	cout << dts << " " << dtc << "\n";
}