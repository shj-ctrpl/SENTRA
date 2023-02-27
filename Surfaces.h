#pragma once

#include <unordered_map>
#include <array>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Geometries.h"
#include "Random_Generator.h"
#include "Materials.h"

using namespace std;

class Surface {
private:

protected:
	bool isReflective = false;

public:
	static unordered_map<int, Surface*> surfaces;
	Surface() {	}
	~Surface() = default;

	void MakeReflective() {
		this->isReflective = true;
	}

	bool IsReflective() {
		return isReflective;
	}

	virtual bool Sense(const Vector3& pos) const = 0;
	virtual double DTS(const Vector3& pos, const Vector3& dir) const = 0;

	virtual void Reflect(const Vector3& pos, Vector3& dir) const = 0;
};

// Ax + By + Cz = D
class Plane : public Surface {
private:
	Vector3 normal;
	double distance;

	Plane(int id, const Vector3& normal, double distance) {
		this->normal = normal;
		this->distance = distance;
		surfaces.insert({ id, this });
	}

public:

	static Plane PX(int id, double distance) {
		return { id, Vector3(1, 0, 0), distance };
	}

	static Plane PY(int id, double distance) {
		return { id, Vector3(0, 1, 0), distance };
	}

	static Plane PZ(int id, double distance) {
		return { id, Vector3(0, 0, 1), distance };
	}

	static Plane PXYZ(int id, const Vector3& normal, double distance) {
		return { id, normal, distance };
	}

	virtual bool Sense(const Vector3& pos) const {
		if ((normal * pos) - distance >= 0) return true;
		else return false;
	}

	virtual double DTS(const Vector3& pos, const Vector3& dir) const {
		if (normal == dir) { return INF(); }
		return (distance - (normal * pos)) / (normal * dir);
	}

	virtual void Reflect(const Vector3& pos, Vector3& dir) const {
		Vector3 reflected = dir - normal * 2 * ((normal * dir) / (normal * normal));
		dir = reflected;
	}
};

class Cylinder : public Surface {

private:
	Vector3 normal;
	Vector3 offset;
	double radius;

	Cylinder(int id, const Vector3& normal, const Vector3& offset, double radius) {
		this->normal = normal;
		this->offset = offset;
		this->radius = radius;
		surfaces.insert({ id, this });
	}
public:

	static Cylinder CylX(int id, double offset_y, double offset_z, double radius) {
		return { id, Vector3(0, 1, 1), Vector3(0, offset_y, offset_z), radius };
	}

	static Cylinder CylY(int id, double offset_x, double offset_z, double radius) {
		return { id, Vector3(1, 0, 1), Vector3(offset_x, 0, offset_z), radius };
	}

	static Cylinder CylZ(int id, double offset_x, double offset_y, double radius) {
		return { id, Vector3(1, 1, 0), Vector3(offset_x, offset_y, 0), radius };
	}

	virtual bool Sense(const Vector3& pos) const {
		if (normal * Vector3::ElementProduct((pos - offset), (pos - offset)) <= radius * radius) {
			return false;
		}
		else {
			return true;
		}
	}

	virtual double DTS(const Vector3& pos, const Vector3& dir) const {
		double a = normal * Vector3::ElementProduct(dir, dir);
		if (a == 0) { return INF(); }
		double k = normal * Vector3::ElementProduct(dir, (pos - offset));
		double c = normal * Vector3::ElementProduct((pos - offset), (pos - offset)) - (radius * radius);

		if ((k * k - a * c) < 0) { return INF(); }
		if (c < 0) {
			return (-k + sqrt(k * k - a * c)) / a;
		}
		else {
			double d = (-k - sqrt(k * k - a * c)) / a;
			if (d > 0) return d;
			else return INF();
		}
	}

	virtual void Reflect(const Vector3& pos, Vector3& dir) const {
		double grad = Vector3::ElementProduct(normal, dir) * (pos - offset) / (radius * radius);
		dir = dir - ((pos - offset) * 2 * grad);
	}
};

class Sphere : public Surface {

private:
	Vector3 offset;
	double radius;

	Sphere(int id, const Vector3& offset, double radius) {
		this->offset = offset;
		this->radius = radius;
		surfaces.insert({ id, this });
	}

public:
	static Sphere SO(int id, double radius) {
		return { id, Vector3(0, 0, 0), radius };
	}

	static Sphere Sph(int id, const Vector3& offset, double radius) {
		return { id, offset, radius };
	}

	virtual bool Sense(const Vector3& pos) const {
		if ((pos - offset) * (pos - offset) >= (radius * radius)) return true;
		else return false;
	}

	virtual double DTS(const Vector3& pos, const Vector3& dir) const {
		double k = (pos - offset) * dir;
		double c = (pos - offset) * (pos - offset) - radius * radius;
		double d = k * k - c;
		if (d >= 0) {
			if (c < 0) {
				return (-k) + sqrt(d);
			}
			else {
				double u = (-k) - sqrt(d);
				if (u > 0) return u;
				else return INF();
			}
		}
		else {
			return INF();
		}
	}

	virtual void Reflect(const Vector3& pos, Vector3& dir) const {
		double grad = dir * (pos - offset) / (radius * radius);
		dir = dir - ((pos - offset) * 2 * grad);
	}
};

class Cone : public Surface {

private:

public:
	virtual bool Sense(const Vector3& pos) const {

	}

	virtual double DTS(const Vector3& pos, const Vector3& dir) const {

	}

	virtual void Reflect(const Vector3& pos, Vector3& dir) const {

	}
};

class Quadric : public Surface {
private:

public:
	virtual bool Sense(const Vector3& pos) const {

	}

	virtual double DTS(const Vector3& pos, const Vector3& dir) const {

	}

	virtual void Reflect(const Vector3& pos, Vector3& dir) const {

	}
};

class Torus : public Surface {

private:

public:
	virtual bool Sense(const Vector3& pos) const {

	}

	virtual double DTS(const Vector3& pos, const Vector3& dir) const {

	}

	virtual void Reflect(const Vector3& pos, Vector3& dir) const {

	}
};

class RPP : public Surface {
private:
	int id = -1;
	Vector3 pos_start, pos_end;

public:
	RPP(int id, const Vector3& pos_start, const Vector3& pos_end) {
		this->id = id;
		this->pos_start = pos_start;
		this->pos_end = pos_end;
		surfaces.insert({ this->id, this });
	}

	virtual bool Sense(const Vector3& pos) const {
		if (pos >= pos_start && pos <= pos_end) {
			return false;
		}
		else {
			return true;
		}
	}

	virtual double DTS(const Vector3& pos, const Vector3& dir) const override {
		double dts = INF();
		Vector3 tangentPoint = Vector3(0, 0, 0);

		array<double, 6> dists = { INF() };
		dists[0] = (pos.x - pos_start.x) / -dir.x;
		dists[1] = (pos.x - pos_end.x) / -dir.x;
		dists[2] = (pos.y - pos_start.y) / -dir.y;
		dists[3] = (pos.y - pos_end.y) / -dir.y;
		dists[4] = (pos.z - pos_start.z) / -dir.z;
		dists[5] = (pos.z - pos_end.z) / -dir.z;

		for (auto d : dists) {
			if (d <= 0) { continue; }
			if (d < dts) {
				dts = d;
			}
		}

		return dts;
	}

	virtual void Reflect(const Vector3& pos, Vector3& dir) const {
		int side = 0;
		double tmp = INF();

		array<double, 6> dists = { INF() };
		dists[0] = (pos.x - pos_start.x) / -dir.x;
		dists[1] = (pos.x - pos_end.x) / -dir.x;
		dists[2] = (pos.y - pos_start.y) / -dir.y;
		dists[3] = (pos.y - pos_end.y) / -dir.y;
		dists[4] = (pos.z - pos_start.z) / -dir.z;
		dists[5] = (pos.z - pos_end.z) / -dir.z;

		for (int i = 0; i < 6; i++) {
			if (dists[i] < 0) { continue; }
			if (dists[i] < tmp) {
				tmp = dists[i];
				side = i;
			}
		}

		switch (side) {
		case 0:
			dir.x = -dir.x;
			break;
		case 1:
			dir.x = -dir.x;
			break;
		case 2:
			dir.y = -dir.y;
			break;
		case 3:
			dir.y = -dir.y;
			break;
		case 4:
			dir.z = -dir.z;
			break;
		case 5:
			dir.z = -dir.z;
			break;
		}
	}
};

unordered_map<int, Surface*> Surface::surfaces = { {} };
