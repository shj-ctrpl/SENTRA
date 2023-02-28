#include <iostream>
#include <cstdio>
#include <mutex>
#include <thread>

#include "Particles.h"
#include "Eigenvalue.h"
#include "Cells.h"
#include "Surfaces.h"
#include "Geometries.h"
#include "Universes.h"
#include "Random_Generator.h"
#include "Materials.h"

// SENTRA: Small Experimental Neutron Transport & Reactor Analysis

using namespace std;

void Checker(int world, const vector3<double>& min, const vector3<double>& max, const vector3<double>& step)
{
	Collision col;
	for (double z = min.z; z <= max.z; z += step.z) {
		cout << "Z = " << z << endl;

		cout << "   X";
		for (double x = min.x; x <= max.x; x += step.x) {
			cout.width(3);
			cout << std::right << int(x);
		}

		cout << "\n Y\n";
		for (double y = min.y; y <= max.y; y += step.y) {
			cout.width(3);
			cout << std::left << int(y);
			for (double x = min.x; x <= max.x; x += step.x) {
				cout.width(3);
				col.Initialize();
				col.univId.push_back(world);
				while (true) {
					while (true) {
						if (col.univId.empty()) { return; }
						if (Universe::universes[col.univId.back()]->findCell(vector3<double>(x, y, z) + col.bias, col)) break;
					}

					if (!Cell::cells[col.cellId]->findFill(col)) {
						break;
					}
				}
				cout << col.cellId;
			}
			cout << "\n";
		}
		cout << "\n" << endl;
	}
}

int main(void) {

	int seed = 10;

	Random_generator rng = Random_generator(seed);

	MaterialReader materialReader = MaterialReader("m1.txt");
	vector<Material> materials = materialReader.GetMaterials();
	Eigenvalue E;
	vector<Particle> particles;
	vector<Particle> sParticles;
	vector<double> egs;

	const vector3<double> sPos(-8.5, -8.5, 0.0);
	const vector3<double> ePos(8.5, 8.5, 20);

	double egssum = 0;
	double mean = 0;
	double accum = 0;

	/*
	Plane s1 = Plane::PX(1, -1); s1.MakeReflective();
	Plane s2 = Plane::PX(2, 1);  s2.MakeReflective();
	Plane s3 = Plane::PY(3, -1); s3.MakeReflective();
	Plane s4 = Plane::PY(4, 1);  s4.MakeReflective();
	Plane s5 = Plane::PZ(5, -1); s5.MakeReflective();
	Plane s6 = Plane::PZ(6, 1);  s6.MakeReflective();

	Cell* c = new Cell(1, materials[0], vector<int> {1, 2, 3, 4, 5, 6}, vector<bool> {true, false, true, false, true, false});
	Universe* u = new Universe(1, vector<int> {1});
	*/

	Cylinder s1 = Cylinder::CylZ(1, 0, 0, 0.45);
	RPP s2(2, vector3<double>(-0.5, -0.5, 0.0), vector3<double>(0.5, 0.5, 20));
	RPP pad1(11, vector3<double>(-8.5, -8.5, 0.0), vector3<double>(8.5, 8.5, 20));
	RPP pad2(12, vector3<double>(-9.0, -9.0, -1.0), vector3<double>(9.0, 9.0, 21));
	pad2.MakeReflective();

	Cell* c1 = new Cell(1, materials[0], vector<int> {1, 2}, vector<bool> {false, false});
	Cell* c2 = new Cell(2, materials[0], vector<int> {1, 2}, vector<bool> {true, false});
	Universe* pin = new Universe(10, vector<int> {1, 2});

	Lattice* latt = new Lattice(11, vector3<double>(-8.5, -8.5, 0.0), vector3<double>(1.0, 1.0, 20.0), vector3<double>(17, 17, 1),
		vector<vector<int>> {
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 }
	});

	Cell* L1 = new Cell(3, 11, vector<int> {11}, vector<bool> {false});
	Cell* Lp = new Cell(4, materials[0], vector<int> {11, 12}, vector<bool> {true, false});

	Universe* world = new Universe(12, vector<int> {3, 4});
	/*
	Cylinder s1 = Cylinder::CylZ(1, 0, 0, 0.54);
	RPP s2(2, vector3<double>(-0.63, -0.63, 0.0), vector3<double>(0.63, 0.63, 385.56));
	RPP pad(11, vector3<double>(-64.26, -64.26, -21.42), vector3<double>(64.26, 64.26, 406.98));

	Cell* c1 = new Cell(1, materials[0], vector<int> {1, 2}, vector<bool> {false, false}); // UO2
	Cell* c2 = new Cell(2, materials[1], vector<int> {1, 2}, vector<bool> {false, false}); // MOX43
	Cell* c3 = new Cell(3, materials[2], vector<int> {1, 2}, vector<bool> {false, false}); // MOX70
	Cell* c4 = new Cell(4, materials[3], vector<int> {1, 2}, vector<bool> {false, false}); // MOX87
	Cell* c5 = new Cell(5, materials[4], vector<int> {1, 2}, vector<bool> {false, false}); // Fission chamber
	Cell* c6 = new Cell(6, materials[5], vector<int> {1, 2}, vector<bool> {false, false}); // Instrument tube
	Cell* c7 = new Cell(7, materials[6], vector<int> {1, 2}, vector<bool> {true, false});  // Moderator only

	Universe* UO2 = new Universe(10, vector<int> {1, 7});
	Universe* MOX43 = new Universe(11, vector<int> {2, 7});
	Universe* MOX70 = new Universe(12, vector<int> {3, 7});
	Universe* MOX87 = new Universe(13, vector<int> {4, 7});
	Universe* CHAM = new Universe(14, vector<int> {5, 7});
	Universe* TUBE = new Universe(15, vector<int> {6, 7});

	Lattice* LatType1 = new Lattice(100, vector3<double>(-10.71, -10.71, 0.0), vector3<double>(1.26, 1.26, 385.56), vector3<double>(17, 17, 1),
		vector<vector<int>> {
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 15, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 15, 10, 10, 15, 10, 10, 14, 10, 10, 15, 10, 10, 15, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 15, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 }
	});

	Lattice* LatType2 = new Lattice(200, vector3<double>(-10.71, -10.71, 0), vector3<double>(1.26, 1.26, 385.56), vector3<double>(17, 17, 1),
		vector<vector<int>> {
			{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 },
			{ 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11 },
			{ 11, 12, 12, 12, 12, 15, 12, 12, 15, 12, 12, 15, 12, 12, 12, 12, 11 },
			{ 11, 12, 12, 15, 12, 13, 13, 13, 13, 13, 13, 13, 12, 15, 12, 12, 11 },
			{ 11, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 11 },
			{ 11, 12, 15, 13, 13, 15, 13, 13, 15, 13, 13, 15, 13, 13, 15, 12, 11 },
			{ 11, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 11 },
			{ 11, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 11 },
			{ 11, 12, 15, 13, 13, 15, 13, 13, 14, 13, 13, 15, 13, 13, 15, 12, 11 },
			{ 11, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 11 },
			{ 11, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 11 },
			{ 11, 12, 15, 13, 13, 15, 13, 13, 15, 13, 13, 15, 13, 13, 15, 12, 11 },
			{ 11, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 11 },
			{ 11, 12, 12, 15, 12, 13, 13, 13, 13, 13, 13, 13, 12, 15, 12, 12, 11 },
			{ 11, 12, 12, 12, 12, 15, 12, 12, 15, 12, 12, 15, 12, 12, 12, 12, 11 },
			{ 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11 },
			{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 }
	});

	RPP ls(100, vector3<double>(-10.71, -10.71, 0), vector3<double>(10.71, 10.71, 385.56));
	Cell* L1 = new Cell(100, 100, vector<int> {100}, vector<bool> {false});
	Cell* L2 = new Cell(200, 200, vector<int> {100}, vector<bool> {false});

	Universe* uu1 = new Universe(101, vector<int> {100});
	Universe* uu2 = new Universe(201, vector<int> {200});

	Lattice* L = new Lattice(300, vector3<double>(-42.84, -42.84, 0.0), vector3<double>(21.42, 21.42, 385.56), vector3<double>(4, 4, 1),
		vector<vector<int>> {
			{ 101, 201, 201, 101 },
			{ 201, 101, 101, 201 },
			{ 201, 101, 101, 201 },
			{ 101, 201, 201, 101 }});

	RPP ls2(300, vector3<double>(-42.84, -42.84, 0.0), vector3<double>(42.84, 42.84, 385.56));
	Cell* L3 = new Cell(300, 300, vector<int> {300}, vector<bool> {false});

	Cell* Padding = new Cell(8, materials[6], vector<int> {11, 300},
		vector<bool> {false, true});

	Universe* world = new Universe(16, vector<int> {8, 300});

	Checker(16, vector3<double>(0.63, 0.63, 100), vector3<double>(50, 50, 100), vector3<double>(1.26, 1.26, 100));
	system("pause");

	*/


	const int particle_num = 10000;
	int analogs = 0;
	for (int i = 0; i < particle_num; i++) {
		vector3<double> pos = rng.Random3D(sPos, ePos);
		particles.push_back(Particle(pos, rng.IsoScatter(), 0));
		Particle::seed++;
	}

	for (int itr = 1; itr <= 550; itr++) {
		cout << "======== Iteration: " << itr << " ========" << endl;
		E.initialize(particle_num);

		for (Particle& p : particles) {
			p.Transport(12, sParticles, E);
		}

		cout << "Primary particles: " << particles.size() << "\n";
		cout << "Secondary particles: " << sParticles.size() << "\n";
		cout << "Analog eigenvalue: " << double(sParticles.size()) / double(particles.size()) << "\n";

		E.setDivision(particles.size());

		if (itr > 50) {
			analogs += sParticles.size();
			egs.push_back(E.print_Eigenvalue());
			egssum += egs.back();
			mean = egssum / egs.size();
			accum = 0;
			std::for_each(std::begin(egs), std::end(egs), [&](const double d) {accum += (d - mean) * (d - mean); });

			double stdev = sqrt(accum / (egs.size() - 1));
			cout << "Eigenvalue mean: " << mean << "  Eigenvalue Stdev: " << stdev << "\n";
			cout << "Analog Ev mean: " << analogs / ((itr - 20) * particle_num) << "\n";
		}
		else {
			E.print_Eigenvalue();
		}

		cout << endl;
		particles.clear();

		if (sParticles.size() > particle_num) {
			std::copy(sParticles.begin(), sParticles.begin() + particle_num, std::back_inserter(particles));
		}
		else {
			particles = sParticles;
		}

		sParticles.clear();
	}

	for (auto& p : egs) {
		cout << p << endl;
	}
}


/*
	//Benchmark
	Cylinder s1 = Cylinder::CylZ(1, 0, 0, 0.54);
	RPP s2(2, vector3<double>(-0.63, -0.63, 0.0), vector3<double>(0.63, 0.63, 385.56));
	RPP pad(11, vector3<double>(-64.26, -64.26, -21.42), vector3<double>(64.26, 64.26, 406.98));

	Cell* c1 = new Cell(1, materials[0], vector<int> {1, 2}, vector<bool> {false, false}); // UO2
	Cell* c2 = new Cell(2, materials[1], vector<int> {1, 2}, vector<bool> {false, false}); // MOX43
	Cell* c3 = new Cell(3, materials[2], vector<int> {1, 2}, vector<bool> {false, false}); // MOX70
	Cell* c4 = new Cell(4, materials[3], vector<int> {1, 2}, vector<bool> {false, false}); // MOX87
	Cell* c5 = new Cell(5, materials[4], vector<int> {1, 2}, vector<bool> {false, false}); // Fission chamber
	Cell* c6 = new Cell(6, materials[5], vector<int> {1, 2}, vector<bool> {false, false}); // Instrument tube
	Cell* c7 = new Cell(7, materials[6], vector<int> {1, 2}, vector<bool> {true, false});  // Moderator only

	Universe* UO2 = new Universe(10, vector<int> {1, 7});
	Universe* MOX43 = new Universe(11, vector<int> {2, 7});
	Universe* MOX70 = new Universe(12, vector<int> {3, 7});
	Universe* MOX87 = new Universe(13, vector<int> {4, 7});
	Universe* CHAM = new Universe(14, vector<int> {5, 7});
	Universe* TUBE = new Universe(15, vector<int> {6, 7});

	Lattice* LatType1 = new Lattice(100, vector3<double>(-10.71, -10.71, 0.0), vector3<double>(1.26, 1.26, 385.56), vector3<double>(17, 17, 1),
		vector<vector<int>> {
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 15, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 15, 10, 10, 15, 10, 10, 14, 10, 10, 15, 10, 10, 15, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 15, 10, 10, 10, 10, 10, 10, 10, 10, 10, 15, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 15, 10, 10, 15, 10, 10, 15, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
			{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 }
	});

	Lattice* LatType2 = new Lattice(200, vector3<double>(-10.71, -10.71, 0), vector3<double>(1.26, 1.26, 385.56), vector3<double>(17, 17, 1),
		vector<vector<int>> {
			{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 },
			{ 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11 },
			{ 11, 12, 12, 12, 12, 15, 12, 12, 15, 12, 12, 15, 12, 12, 12, 12, 11 },
			{ 11, 12, 12, 15, 12, 13, 13, 13, 13, 13, 13, 13, 12, 15, 12, 12, 11 },
			{ 11, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 11 },
			{ 11, 12, 15, 13, 13, 15, 13, 13, 15, 13, 13, 15, 13, 13, 15, 12, 11 },
			{ 11, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 11 },
			{ 11, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 11 },
			{ 11, 12, 15, 13, 13, 15, 13, 13, 14, 13, 13, 15, 13, 13, 15, 12, 11 },
			{ 11, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 11 },
			{ 11, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 11 },
			{ 11, 12, 15, 13, 13, 15, 13, 13, 15, 13, 13, 15, 13, 13, 15, 12, 11 },
			{ 11, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 11 },
			{ 11, 12, 12, 15, 12, 13, 13, 13, 13, 13, 13, 13, 12, 15, 12, 12, 11 },
			{ 11, 12, 12, 12, 12, 15, 12, 12, 15, 12, 12, 15, 12, 12, 12, 12, 11 },
			{ 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 11 },
			{ 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11 }
	});

	RPP ls(100, vector3<double>(-10.71, -10.71, 0), vector3<double>(10.71, 10.71, 385.56));
	Cell* L1 = new Cell(100, 100, vector<int> {100}, vector<bool> {false});
	Cell* L2 = new Cell(200, 200, vector<int> {100}, vector<bool> {false});

	Universe* uu1 = new Universe(101, vector<int> {100});
	Universe* uu2 = new Universe(201, vector<int> {200});

	Lattice* L = new Lattice(300, vector3<double>(-42.84, -42.84, 0.0), vector3<double>(21.42, 21.42, 385.56), vector3<double>(4, 4, 1),
		vector<vector<int>> {
			{ 101, 201, 201, 101 },
			{ 201, 101, 101, 201 },
			{ 201, 101, 101, 201 },
			{ 101, 201, 201, 101 }});

	RPP ls2(300, vector3<double>(-42.84, -42.84, 0.0), vector3<double>(42.84, 42.84, 385.56));
	Cell* L3 = new Cell(300, 300, vector<int> {300}, vector<bool> {false});

	Cell* Padding = new Cell(8, materials[6], vector<int> {11, 300},
		vector<bool> {false, true});

	Universe* world = new Universe(16, vector<int> {8, 300});

	*/