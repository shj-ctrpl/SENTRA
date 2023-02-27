#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "Collision.h"
#include "Geometries.h"
#include "Cells.h"
#include "Universes.h"

class Tally {
public:
	virtual ~Tally() = default;
	virtual void AddScore(Collision& col) noexcept = 0;
	virtual double GetScore() const noexcept = 0;

};

class SurfaceCurrentTally : public Tally {
private:
	int tally_id;
	int surface_id;
	double current = 0.0;

public:
	SurfaceCurrentTally(int tally_id, int surface_id, int cell_id) {
		this->tally_id = tally_id;
		this->surface_id = surface_id;
	}

	~SurfaceCurrentTally() = default;

	virtual void AddScore(Collision& col) noexcept override {
		current += 1;//고쳐야함
	}

	virtual double GetScore() const noexcept override {
		return current;
	}
};

class SurfaceFluxTally : public Tally {
private:
	int tally_id;
	double current = 0.0;
	double area = 1.0;

public:
	SurfaceFluxTally(int tally_id, int surface_id, int cell_id) {
		this->tally_id = tally_id;
		this->area = Cell::cells[cell_id]->GetSurfaceArea(surface_id);
	}

	~SurfaceFluxTally() = default;

	virtual void AddScore(Collision& col) noexcept override {
		current += 1;
	}

	virtual double GetScore() const noexcept override {
		return (current/area);
	}
};


class CellFluxTally : public Tally {
private:
	int tally_id;
	int surface_id;
	int cell_id;
	double current = 0.0;
	double volume = 1.0;

public:
	CellFluxTally(int tally_id, int surface_id, int cell_id) {
		this->tally_id = tally_id;
		this->volume = Cell::cells[cell_id]->GetSurfaceArea(surface_id);
	}

	~CellFluxTally() = default;

	virtual void AddScore(Collision& col) noexcept override {
		current += 1;
	}

	virtual double GetScore() const noexcept override {
		return (current / volume);
	}
};
