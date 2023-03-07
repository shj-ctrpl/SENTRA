#include "Surfaces.h"

using namespace std;
using namespace World;

// ================================
// Class Plane
// ================================
Plane::Plane(int id, const vector3<double>& normal, double distance) {
	this->normal = normal;
	this->distance = distance;
	surfaces.insert({ id, this });
}

bool Plane::Sense(const vector3<double>& pos) const {
	if (normal.dot(pos) - distance >= 0) return true;
	else return false;
}

double Plane::DTS(const vector3<double>& pos, const vector3<double>& dir) const {
	if (normal == dir) { return INF(); }
	return (distance - normal.dot(pos) / normal.dot(dir));
}

void Plane::Reflect(const vector3<double>& pos, vector3<double>& dir) const {
	vector3<double> reflected = dir - 2.0 * normal.dot(normal * dir / normal * normal);
	dir = reflected;
}

// ================================
// Class Cylinder
// ================================
Cylinder::Cylinder(int id, const vector3<double>& normal, const vector3<double>& offset, double radius) {
	this->normal = normal;
	this->offset = offset;
	this->radius = radius;
	surfaces.insert({ id, this });
}

bool Cylinder::Sense(const vector3<double>& pos) const {
	if (((pos - offset) * (pos - offset)).dot(normal) <= radius * radius) {
		return false;
	}
	else {
		return true;
	}
}

double Cylinder::DTS(const vector3<double>& pos, const vector3<double>& dir) const {
	double a = normal.dot(dir * dir);
	if (a == 0) { return INF(); }
	double k = normal.dot(dir * (pos - offset));
	double c = ((pos - offset) * (pos - offset)).dot(normal) - (radius * radius);

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

void Cylinder::Reflect(const vector3<double>& pos, vector3<double>& dir) const {
	double grad = normal.dot(dir * (pos - offset)) / (radius * radius);
	dir = dir - ((pos - offset) * 2 * grad);
}

// ================================
// Class Sphere
// ================================

Sphere::Sphere(int id, const vector3<double>& offset, double radius) {
	this->offset = offset;
	this->radius = radius;
	surfaces.insert({ id, this });
}

bool Sphere::Sense(const vector3<double>& pos) const {
	if ((pos - offset).dot(pos - offset) >= (radius * radius)) return true;
	else return false;
}

double Sphere::DTS(const vector3<double>& pos, const vector3<double>& dir) const {
	double k = (pos - offset).dot(dir);
	double c = (pos - offset).dot(pos - offset) - radius * radius;
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

void Sphere::Reflect(const vector3<double>& pos, vector3<double>& dir) const {
	double grad = dir.dot(pos - offset) / (radius * radius);
	dir = dir - ((pos - offset) * 2 * grad);
}

// ================================
// Class RPP
// ================================

RPP::RPP(int id, const vector3<double>& pos_start, const vector3<double>& pos_end) {
	this->id = id;
	this->pos_start = pos_start;
	this->pos_end = pos_end;
	surfaces.insert({ this->id, this });
}

bool RPP::Sense(const vector3<double>& pos) const {
	if (pos >= pos_start && pos <= pos_end) {
		return false;
	}
	else {
		return true;
	}
}

double RPP::DTS(const vector3<double>& pos, const vector3<double>& dir) const {
	double dts = INF();
	vector3<double> tangentPoint = vector3<double>(0, 0, 0);

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

void RPP::Reflect(const vector3<double>& pos, vector3<double>& dir) const {
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