#include <vector>
#include <numeric>

#include "Collision.h"
#include "Geometries.h"

using namespace std;

Collision::Collision() {
	travel_history = {};
	biases = {};
	bias = vector3<double>(0, 0, 0);
	surfId = -1;
	cellId = -1;
}

void Collision::Initialize() {
	travel_history.clear();
	biases.clear();
	bias = vector3<double>(0, 0, 0);
	surfId = -1;
	cellId = -1;
}

void Collision::Add_travel(int univId, int fill) {
	travel_history.push_back(pair(univId, fill));
}

void Collision::Add_travel(int univId, const vector3<int>& lattice_index, const vector3<double>& lattice_bias) {
	travel_history.push_back(pair(univId, lattice_index));
	biases.push_back(lattice_bias);

	bias = std::accumulate(biases.begin(), biases.end(), vector3<double>(0, 0, 0));
}

void Collision::Pop_travel() {
	travel_history.pop_back();
	// If the last travel info has vector3<int>, it means the last universe is a lattice
	if (holds_alternative<vector3<int>> (travel_history.back().second)) {
		biases.pop_back();
		bias = std::accumulate(biases.begin(), biases.end(), vector3<double>(0, 0, 0));
	}
}

bool Collision::get_Surf(int& surf) const noexcept {
	if (surfId == -1) {
		return false;
	}
	else {
		surf = surfId;
		return true;
	}
}

bool Collision::get_Cell(int& cell) const noexcept {
	if (cellId == -1) {
		return false;
	}
	else {
		cell = cellId;
		return true;
	}
}

bool Collision::get_Univ(int& univ) const noexcept {
	if (!travel_history.empty()) {
		univ = travel_history.back().first;
		return true;
	}
	else return false;
}