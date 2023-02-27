#pragma once

#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>

class Vector3
{
public:
	double x;
	double y;
	double z;

	Vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3(double _x, double _y, double _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	friend Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		double Vx = a.x + b.x;
		double Vy = a.y + b.y;
		double Vz = a.z + b.z;

		return Vector3(Vx, Vy, Vz);
	}

	friend Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		double Vx = a.x - b.x;
		double Vy = a.y - b.y;
		double Vz = a.z - b.z;

		return Vector3(Vx, Vy, Vz);
	}

	friend double operator*(const Vector3& a, const Vector3& b)
	{
		double Vx = a.x * b.x;
		double Vy = a.y * b.y;
		double Vz = a.z * b.z;

		return Vx + Vy + Vz;
	}

	friend Vector3 operator*(const Vector3& a, const double& b)
	{
		Vector3 scalarProduct;
		scalarProduct.x = a.x * b;
		scalarProduct.y = a.y * b;
		scalarProduct.z = a.z * b;

		return scalarProduct;
	}

	friend Vector3 operator^(const Vector3& v1, const Vector3& v2) {
		Vector3 cross;
		cross.x = v1.y * v2.z - v1.z * v2.y;
		cross.y = v1.z * v2.x - v1.x - v2.z;
		cross.z = v1.x * v2.y - v1.y * v2.x;
		return cross;
	}

	friend bool operator<(const Vector3& v1, const Vector3& v2) {
		return (v1.x < v2.x) && (v1.y < v2.y) && (v1.z < v2.z);
	}

	friend bool operator>(const Vector3& v1, const Vector3& v2) {
		return (v1.x > v2.x) && (v1.y > v2.y) && (v1.z > v2.z);
	}

	friend bool operator<=(const Vector3& v1, const Vector3& v2) {
		return (v1.x <= v2.x) && (v1.y <= v2.y) && (v1.z <= v2.z);
	}

	friend bool operator>=(const Vector3& v1, const Vector3& v2) {
		return (v1.x >= v2.x) && (v1.y >= v2.y) && (v1.z >= v2.z);
	}

	friend bool operator==(const Vector3& v1, const Vector3& v2) {
		return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
	}

	bool operator==(Vector3 a)
	{
		if (x == a.x && y == a.y && z == a.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static double InnerCos(Vector3 v1, Vector3 v2)
	{
		double Cos = (v1 * v2) / ((v1.Magnitude() * v2.Magnitude()));

		return Cos;
	}

	Vector3 Normalized() const
	{
		Vector3 normalized;
		double magnitude = this->Magnitude();
		normalized.x = x / magnitude;
		normalized.y = y / magnitude;
		normalized.z = z / magnitude;

		return normalized;
	}

	Vector3 Inversed() const {
		Vector3 inversed;
		return Vector3(-x, -y, -z);
	}

	double Magnitude() const
	{
		double magnitude = sqrt(x * x + y * y + z * z);
		return magnitude;
	}

	static double Theta(double cos)
	{
		return acos(cos) * (180 / 3.14f);
	}

	static Vector3 Projection(Vector3 v1, Vector3 v2)
	{
		Vector3 result;

		result.x = ((v1 * v2) / (v2 * v2)) * v2.x;
		result.y = ((v1 * v2) / (v2 * v2)) * v2.y;
		result.z = ((v1 * v2) / (v2 * v2)) * v2.z;

		return result;
	}

	static Vector3 Orthogonal_Projection(Vector3 v1, Vector3 proj)
	{
		Vector3 ortho;
		ortho = v1 - proj;
		return ortho;
	}

	static Vector3 CrossProduct(Vector3 v1, Vector3 v2)
	{
		Vector3 cross;
		cross.x = v1.y * v2.z - v1.z * v2.y;
		cross.y = v1.z * v2.x - v1.x - v2.z;
		cross.z = v1.x * v2.y - v1.y * v2.x;

		return cross;
	}

	static Vector3 ElementProduct(Vector3 v1, Vector3 v2)
	{
		Vector3 elpr;
		elpr.x = v1.x * v2.x;
		elpr.y = v1.y * v2.y;
		elpr.z = v1.z * v2.z;

		return elpr;
	}
	static Vector3 Reflect(Vector3 in, Vector3 n) {
		return in - (n * 2) * (in * n);
	}
};

