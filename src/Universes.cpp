#include "Universes.h"

using namespace std;

unordered_map<int, Universe*> Universe::universes = {};

// ================================
// Class Universe
// ================================

Universe::Universe(int id, vector<int> childs) {
	this->id = id;
	this->childs = childs;
	universes.insert({ id, this });
}

bool Universe::findCell(const vector3<double>& pos, Collision& col) {
	auto i = neighbors.find(col.cellId);

	// Try neighbor search
	if (i != neighbors.end()) {
		for (int c : i->second) {
			if (Cell::cells[c]->isInCell(pos)) {
				col.cellId = c;
				return true;
			}
		}
	}
	else {
		// No key found, add key to neighbors
		neighbors.insert(make_pair(col.cellId, forward_list<int> {}));
	}

	// Failed to find cells by neighbors search
	for (int c : childs) {
		if (Cell::cells[c]->isInCell(pos)) {
			col.cellId = c;
			if (col.cellId != c) {
				neighbors[col.cellId].push_front(c);
			}
			return true;
		}
	}

	// Failed to find any cell in the Universe.		
	col.lastuniv = col.univId.back();
	col.univId.pop_back();
	col.RemoveBias();
	return false;
}

// ================================
// Class Lattice
// ================================

Lattice::Lattice(int id, const vector3<double>& pos_start, const vector3<double>& lat_size, const vector3<int>& lat_num, const vector<vector<int>>& indices) {
	this->id = id;
	this->pos_start = pos_start;
	this->pos_end = pos_start + lat_num * (vector3<double>)lat_size;
	this->lat_size = lat_size;
	this->lat_num = lat_num;
	this->indices = indices;
	universes.insert({ this->id, this });
}
int Lattice::atUniv(const vector3<double>& pos) {
	lat_at_x = int(floor((pos.x - pos_start.x) / lat_size.x));
	if (lat_at_x < 0) { lat_at_x = 0; }
	if (lat_at_x >= lat_num.x) { lat_at_x = lat_num.x - 1; }

	lat_at_y = int(floor((pos.y - pos_start.y) / lat_size.y));
	if (lat_at_y < 0) { lat_at_y = 0; }
	if (lat_at_y >= lat_num.y) { lat_at_y = lat_num.y - 1; }
	return indices[lat_at_y][lat_at_x];
}

vector3<double> Lattice::local(const vector3<double>& pos) const {
	vector3<double> localPos = vector3<double>(
		fmod((pos.x - pos_start.x), lat_size.x) - lat_size.x / 2,
		fmod((pos.y - pos_start.y), lat_size.y) - lat_size.y / 2,
		pos.z);
	return localPos;
}

bool Lattice::findCell(const vector3<double>& pos, Collision& col) {
	bool found = false;

	if (pos >= pos_start && pos <= pos_end) {
		found = universes[atUniv(pos)]->findCell(local(pos), col);
		if (found) {
			col.univId.push_back(atUniv(pos));
			col.AddBias(local(pos) - pos);
			return true;
		}
		else {
			col.lastuniv = col.univId.back();
			col.univId.pop_back();
			return false;
		}
	}
	else {
		col.univId.pop_back();
		return false;
	}
}