#include "Cells.h"

using namespace std;
using namespace World;

Cell::Cell(int id, int material, const vector<int>& surf_ids, const vector<bool>& senses) {
	this->fill == NULL;
	this->surf_ids = surf_ids;
	this->senses = senses;
	this->material = material;
	this->id = id;
	cells.insert({ this->id, this });
}

Cell::Cell(int id, int material, const vector<int>& surf_ids, const vector<bool>& senses, vector<double> surf_areas, double volume) {
	this->fill == NULL;
	this->surf_ids = surf_ids;
	this->senses = senses;
	this->material = material;
	this->id = id;
	this->surf_areas = surf_areas;
	this->volume = volume;
	cells.insert({ this->id, this });
}

Cell::Cell(int id, int fill, const vector<int>& surf_ids, const vector<bool>& senses) {
	this->surf_ids = surf_ids;
	this->senses = senses;
	this->fill = fill;
	this->id = id;
	cells.insert({ this->id, this });
}

bool Cell::findFill(Collision& col) const {
	if (fill == NULL) {
		return false;
	}
	else {
		return true;
	}
}

bool Cell::isInCell(const vector3<double>& pos) const {
	bool sense = true;
	int j = 0;
	for (int surfid : surf_ids) {
		bool tmpsense = surfaces[surfid]->Sense(pos);
		sense = sense && !(senses[j] ^ tmpsense);
		j++;
	}
	return sense;
}

double Cell::DTS(const vector3<double>& pos, const vector3<double>& dir, Collision& col) {
	double tmp = INF(), dts = INF();
	for (int surfId : surf_ids) {
		tmp = surfaces[surfId]->DTS(pos, dir);
		if (tmp < 0) { continue; }
		if (tmp < dts) {
			if ((abs(tmp - dts) / dts) >= EPS()) {
				dts = tmp;
				col.Set_Surf(surfId);
			}
			else {
				continue;
			}
		}
	}
	return dts;
}

double Cell::GetSurfaceArea(int surf_id) {
	return this->surf_areas[surf_id];
}