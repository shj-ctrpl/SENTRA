// ================================================================
// SENTRA: Small Experimental Neutron Transport & Reactor Analysis
// ================================================================
#pragma once

#include <iostream>
#include <cstdio>
#include <mutex>
#include <thread>

#include "Utilities.h"
#include "Particles.h"
#include "Eigenvalue.h"
#include "Cells.h"
#include "Surfaces.h"
#include "Geometries.h"
#include "Universes.h"
#include "Random_Generator.h"
#include "Materials.h"

int main(void) {

	int seed = 10;

	Random_generator rng = Random_generator(seed);
	Eigenvalue E;
	MaterialReader materialReader = MaterialReader("materials.txt");

	std::vector<Material> materials = materialReader.GetMaterials();
	
	std::vector<Particle> particles;
	std::vector<Particle> sParticles;
	std::vector<double> egs;

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

	Cell* c1 = new Cell(1, materials[0], std::vector<int> {1, 2}, std::vector<bool> {false, false});
	Cell* c2 = new Cell(2, materials[0], std::vector<int> {1, 2}, std::vector<bool> {true, false});
	Universe* pin = new Universe(10, std::vector<int> {1, 2});

	Lattice* latt = new Lattice(11, vector3<double>(-8.5, -8.5, 0.0), vector3<double>(1.0, 1.0, 20.0), vector3<int>(17, 17, 1),
		std::vector<std::vector<int>> {
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

	Cell* L1 = new Cell(3, 11, std::vector<int> {11}, std::vector<bool> {false});
	Cell* Lp = new Cell(4, materials[0], std::vector<int> {11, 12}, std::vector<bool> {true, false});

	Universe* world = new Universe(12, std::vector<int> {3, 4});

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