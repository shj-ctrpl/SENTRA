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



class Cell
{
private:
	int id = -1;
	int fill = -1;
	double volume = 1;

	vector<double> surf_areas;
	vector<int> surf_ids;
	vector<bool> senses;


public:
	static unordered_map<int, Cell*> cells;
	forward_list<int> neighbors;
	Material material = Material();

	Cell() {
	}

	Cell(int id, Material material, const vector<int>& surf_ids, const vector<bool>& senses) {
		this->surf_ids = surf_ids;
		this->senses = senses;
		this->material = material;
		this->id = id;
		cells.insert({ this->id, this });
	}

	Cell(int id, Material material, const vector<int>& surf_ids, const vector<bool>& senses, vector<double> surf_areas, double volume) {
		this->surf_ids = surf_ids;
		this->senses = senses;
		this->material = material;
		this->id = id;
		this->surf_areas = surf_areas;
		this->volume = volume;
		cells.insert({ this->id, this });
	}

	Cell(int id, int fill, const vector<int>& surf_ids, const vector<bool>& senses) {
		this->surf_ids = surf_ids;
		this->senses = senses;
		this->fill = fill;
		this->id = id;
		cells.insert({ this->id, this });
	}

	bool findFill(Collision& col) const {
		if (fill == -1) {
			return false;
		}
		else {
			col.univId.push_back(fill);
			return true;
		}
	}

	bool isInCell(const Vector3& pos) const {
		bool sense = true;
		int j = 0;
		for (int surfid : surf_ids) {
			bool tmpsense = Surface::surfaces[surfid]->Sense(pos);
			sense = sense && !(senses[j] ^ tmpsense);
			j++;
		}
		return sense;
	}

	double DTS(const Vector3& pos, const Vector3& dir, Collision& col) {
		double tmp = INF(), dts = INF();
		for (int surfId : surf_ids) {
			tmp = Surface::surfaces[surfId]->DTS(pos, dir);
			if (tmp < 0) { continue; }
			if (tmp < dts) {
				if ((abs(tmp - dts) / dts) >= EPS()) {
					dts = tmp;
					col.surfId = surfId;
				}
				else {
					continue;
				}
			}
		}
		return dts;
	}

	double GetSurfaceArea(int surf_id) {
		return this->surf_areas[surf_id];
	}
};

unordered_map<int, Cell*> Cell::cells = {};