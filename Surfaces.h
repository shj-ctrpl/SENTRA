#pragma once

#include <unordered_map>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Geometries.h"
#include "Collision.h"
#include "Foundations.h"


class Surface {
private:

protected:
	bool isReflective = false;

public:
	static std::unordered_map<int, Surface*> surfaces;
	Surface() {	}
	~Surface() = default;

	void MakeReflective() {	this->isReflective = true; }
	bool IsReflective() { return isReflective; }

	virtual bool Sense(const vector3<double>& pos) const = 0;
	virtual double DTS(const vector3<double>& pos, const vector3<double>& dir) const = 0;
	virtual void Reflect(const vector3<double>& pos, vector3<double>& dir) const = 0;
};

// Ax + By + Cz = D
class Plane : public Surface {
private:
	vector3<double> normal;
	double distance;

	Plane(int id, const vector3<double>& normal, double distance);
public:
	static Plane PX(int id, double distance) {
		return { id, vector3<double>(1, 0, 0), distance };
	}
	static Plane PY(int id, double distance) {
		return { id, vector3<double>(0, 1, 0), distance };
	}
	static Plane PZ(int id, double distance) {
		return { id, vector3<double>(0, 0, 1), distance };
	}
	static Plane PXYZ(int id, const vector3<double>& normal, double distance) {
		return { id, normal, distance };
	}

	virtual bool Sense(const vector3<double>& pos) const;
	virtual double DTS(const vector3<double>& pos, const vector3<double>& dir) const;
	virtual void Reflect(const vector3<double>& pos, vector3<double>& dir) const;
};

class Cylinder : public Surface {

private:
	vector3<double> normal;
	vector3<double> offset;
	double radius;

	Cylinder(int id, const vector3<double>& normal, const vector3<double>& offset, double radius);
public:
	static Cylinder CylX(int id, double offset_y, double offset_z, double radius) {
		return { id, vector3<double>(0, 1, 1), vector3<double>(0, offset_y, offset_z), radius };
	}
	static Cylinder CylY(int id, double offset_x, double offset_z, double radius) {
		return { id, vector3<double>(1, 0, 1), vector3<double>(offset_x, 0, offset_z), radius };
	}
	static Cylinder CylZ(int id, double offset_x, double offset_y, double radius) {
		return { id, vector3<double>(1, 1, 0), vector3<double>(offset_x, offset_y, 0), radius };
	}

	virtual bool Sense(const vector3<double>& pos) const;
	virtual double DTS(const vector3<double>& pos, const vector3<double>& dir) const;
	virtual void Reflect(const vector3<double>& pos, vector3<double>& dir) const;
};

class Sphere : public Surface {

private:
	vector3<double> offset;
	double radius;

	Sphere(int id, const vector3<double>& offset, double radius);

public:
	static Sphere SO(int id, double radius) {
		return { id, vector3<double>(0, 0, 0), radius };
	}
	static Sphere Sph(int id, const vector3<double>& offset, double radius) {
		return { id, offset, radius };
	}

	virtual bool Sense(const vector3<double>& pos) const;
	virtual double DTS(const vector3<double>& pos, const vector3<double>& dir) const;
	virtual void Reflect(const vector3<double>& pos, vector3<double>& dir) const;
};

class Cone : public Surface {

private:

public:
	virtual bool Sense(const vector3<double>& pos) const;
	virtual double DTS(const vector3<double>& pos, const vector3<double>& dir) const;
	virtual void Reflect(const vector3<double>& pos, vector3<double>& dir) const;
};

class Quadric : public Surface {
private:

public:
	virtual bool Sense(const vector3<double>& pos) const;
	virtual double DTS(const vector3<double>& pos, const vector3<double>& dir) const;
	virtual void Reflect(const vector3<double>& pos, vector3<double>& dir) const;
};

class Torus : public Surface {

private:

public:
	virtual bool Sense(const vector3<double>& pos) const;
	virtual double DTS(const vector3<double>& pos, const vector3<double>& dir) const;
	virtual void Reflect(const vector3<double>& pos, vector3<double>& dir) const;
};

class RPP : public Surface {
private:
	int id = -1;
	vector3<double> pos_start, pos_end;

public:
	RPP(int id, const vector3<double>& pos_start, const vector3<double>& pos_end);

	virtual bool Sense(const vector3<double>& pos) const;
	virtual double DTS(const vector3<double>& pos, const vector3<double>& dir) const;
	virtual void Reflect(const vector3<double>& pos, vector3<double>& dir) const;
};