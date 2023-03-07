#include "Transport.h"

using namespace std;
using namespace World;

Transport::Transport(int seed) {
	this->seed = seed;
}

void Transport::Transport_Particle(int world, vector<Particle>& particles, std::vector<Particle>& secondary_particles,
	Eigenvalue& k, std::vector<Tally>& tallies) {
	bool foundCell = false;
	int reactionType = 2;

	for (Particle& p : particles) {
		DTS = 0.0;
		DTC = INF();
		univ = world;

		col.Initialize();
		universes[univ]->findCell(p.pos + col.bias, col);
		cell = col.get_Cell();

		while (reactionType == 2) {
			while (DTS < DTC) {
				while (true) {
					// Try to find fill. If no fill found, break the loop.
					// If material is void, a particle dies.
					if (!cells[cell]->findFill(col)) {
						mat = materials[cells[cell]->material];
						if (mat->isVoid()) return;
						break;
					}

					// Try to get universe.
					// If universe list is empty, a particle dies.
					if (!col.get_Univ(univ)) {
						return;
					}

					// Try to find cell.
					// If failed to find cell, do surface escape and retry.
					if (universes[univ]->findCell(p.pos + col.bias, col)) {
						cell = col.get_Cell();
					}
					else {
						p.SurfaceEscape();
						if (universes[univ]->findCell(p.pos + col.bias, col)) {
							cell = col.get_Cell();
						}
						else {
							return;
						}
					}
				}

				// DTS, DTC calculation
				DTS = cells[cell]->DTS(p.pos + col.bias, p.dir, col);
				DTC = rng.flightLength(mat->GetXsTot(p.grp));

				if (surfaces[col.get_Surf()]->IsReflective()) {
					p.ReflectiveEscape();
				}
				else {
					p.SurfaceEscape();
				}
			}

			// DTS > DTC; Reaction occurs
			p.pos = p.pos * p.dir;
			k.Upadate_Pathlength(mat->GetNuSigmaF(p.grp) * DTC);
			reactionType = rng.pdfDiscrete(mat->GetXsAlltype(p.grp));

			switch (reactionType) {
			case 0:	// Fission
				int fissionNumber = p.fission(mat);
				for (int i = 0; i < fissionNumber; ++i) {
					int pGrp = rng.pdfDiscrete(mat->GetChi());
					secondary_particles.push_back(Particle(p.pos, rng.IsoScatter(), pGrp));
				}
				break;

			case 1:	// Capture
				break;

			case 2: // Scatter
				p.Scatter(mat);
				break;

			default:
				break;
			}
		}
	}
}