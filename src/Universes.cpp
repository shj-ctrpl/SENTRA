#include "Universes.h"

using namespace std;
using namespace World;

// ================================
// Class Universe
// ================================

Universe::Universe(int id, vector<int> childs) {
	this->id = id;
	this->childs = childs;
	universes.insert({ id, this });
}

bool Universe::findCell(const vector3<double>& pos, Collision& col) {
	// Failed to find cells by neighbors search
	for (int c : childs) {
		if (cells[c]->isInCell(pos)) {
			col.Push_travel(this->id, c);
			return true;
		}
	}

	// Failed to find any cell in the Universe.		
	col.Pop_travel();
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
vector3<int> Lattice::LocalIndex(const vector3<double>& pos) {
	int idx_x = int(floor((pos.x - pos_start.x) / lat_size.x));
	if (idx_x < 0) { idx_x = 0; }
	if (idx_x >= lat_num.x) { idx_x = lat_num.x - 1; }

	int idx_y = int(floor((pos.y - pos_start.y) / lat_size.y));
	if (idx_y < 0) { idx_y = 0; }
	if (idx_y >= lat_num.y) { idx_y = lat_num.y - 1; }

	int idx_z = int(floor((pos.z - pos_start.z) / lat_size.z));
	if (idx_z < 0) { idx_z = 0; }
	if (idx_z >= lat_num.z) { idx_z = lat_num.z - 1; }

	return vector3(idx_x, idx_y, idx_z);
}

vector3<double> Lattice::LocalPos(const vector3<double>& pos) const {
	vector3<double> localPos = vector3<double>(
		fmod((pos.x - pos_start.x), lat_size.x) - lat_size.x / 2,
		fmod((pos.y - pos_start.y), lat_size.y) - lat_size.y / 2,
		pos.z);
	return localPos;
}

bool Lattice::findCell(const vector3<double>& pos, Collision& col) {
	if (pos >= pos_start && pos <= pos_end) {
		vector3<int> idx = LocalIndex(pos);
		vector3<double> localpos = LocalPos(pos);
		int univ = indices[idx.x][idx.y];

		col.Push_travel(this->id, idx, (localpos - pos));

		if (universes[univ]->findCell(localpos, col)) {
			return true;
		}
		else {
			col.Pop_travel();
			return false;
		}
	}
	col.Pop_travel();
	return false;
}