#pragma once

#include <unordered_map>
#include <forward_list>
#include <array>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Collision.h"
#include "Surfaces.h"
#include "Geometries.h"
#include "Random_Generator.h"
#include "Materials.h"
#include "Foundations.h"

class Cell
{
private:
	int id = -1;
	int fill = -1;
	double volume = 1;

	std::vector<double> surf_areas;
	std::vector<int> surf_ids;
	std::vector<bool> senses;


public:
	static std::unordered_map<int, Cell*> cells;
	std::forward_list<int> neighbors;
	Material material = Material();

	Cell() {}
	~Cell() = default;

	Cell(int id, Material material, const std::vector<int>& surf_ids, const std::vector<bool>& senses);
	Cell(int id, Material material, const std::vector<int>& surf_ids, const std::vector<bool>& senses, std::vector<double> surf_areas, double volume);
	Cell(int id, int fill, const std::vector<int>& surf_ids, const std::vector<bool>& senses);

	bool findFill(Collision& col) const;
	bool isInCell(const vector3<double>& pos) const;
	double DTS(const vector3<double>& pos, const vector3<double>& dir, Collision& col);
	double GetSurfaceArea(int surf_id);
};

