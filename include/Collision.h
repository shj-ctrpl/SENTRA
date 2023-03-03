#pragma once

#include <variant>

#include "Geometries.h"

// int: Universe / lattice Id
// std::variant<int, vector3<int>: cell Id / Lattice inner index
typedef std::pair<int, std::variant<int, vector3<int>>> travel_info_t;

class Collision {
private:
	// Travel histories: first = universe/lattice, second = fill/indices
	std::vector<travel_info_t> travel_history;

	// Biases, due to position change in the lattice
	std::vector<vector3<double>> biases;
	
	int cellId;	// Cell Id where collision is happened
	int surfId; // Surface Id where collision is happened

public:
	vector3<double> bias;

	Collision();
	~Collision() = default;
	void Initialize();
	
	//================================
	// Setters
	//================================
	
	// Set surface Id
	void Set_Surf(int surfId) { this->surfId = surfId; }

	// For universes: not adding any biases
	void Add_travel(int univId, int fill);

	// For lattices: adding indices and biases
	void Add_travel(int univId, const vector3<int>& lattice_indice, const vector3<double>& lattice_bias);

	// Pop last travel info
	void Pop_travel();

	
	//================================
	// Getters
	//================================
	
	// Return the index of the collided surface
	// If no surface found, int& surf will not change.
	bool get_Surf(int& surf) const noexcept;
	int get_Surf() const noexcept { return surfId; }

	// Return the index of the last cell
	// If no cell found, int& cell will not change.
	bool get_Cell(int& cell) const noexcept;
	int get_Cell() const noexcept { return cellId; }

	// Return the index of the last universe
	// If no universe found, int& univ will not change.
	bool get_Univ(int& univ) const noexcept;
	int get_Univ() const noexcept { return travel_history.back().first; }

	std::vector<travel_info_t> Return_History() const noexcept {
		return travel_history;
	}
};