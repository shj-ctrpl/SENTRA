#pragma once

#include <forward_list>
#include <unordered_map>
#include <array>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Geometries.h"
#include "Cells.h"
#include "Collision.h"
#include "Surfaces.h"
#include "Random_Generator.h"
#include "Materials.h"

class Universe;

namespace World {
	extern std::unordered_map<int, Universe*> universes;
}

class Universe {
private:
	int id = -1;
	std::vector<int> childs;

public:
	std::unordered_map<int, std::forward_list<int>> neighbors;

	Universe() {}
	Universe(int id, std::vector<int> childs);
	~Universe() = default;

	virtual bool findCell(const vector3<double>& pos, Collision& col);
};

class Lattice : public Universe {
private:
	int id = 0;
	vector3<double> pos_start, pos_end, lat_size;
	vector3<int> lat_num;
	std::vector<std::vector<int>> indices;

	// Returns indices of the lattice.
	vector3<int> LocalIndex(const vector3<double>& pos);

	// Returns local position of the lattice.
	vector3<double> LocalPos(const vector3<double>& pos) const;

public:
	Lattice(int id, const vector3<double>& pos_start, const vector3<double>& lat_size, 
		const vector3<int>& lat_num, const std::vector<std::vector<int>>& indices);
	~Lattice() = default;

	virtual bool findCell(const vector3<double>& pos, Collision& col) override;
};

