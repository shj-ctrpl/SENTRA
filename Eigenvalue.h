#pragma once

#include <iostream>

using namespace std;

class Eigenvalue {
private:
	double divid = 1.0f;
	double k_pth = 0.0f;
	double k_col = 0.0f;
	double k_abs = 0.0f;
	double k_avg = 0.0f;
public:
	Eigenvalue() {

	}

	~Eigenvalue() = default;

	void initialize(double divider) {
		divid = divider;
		k_pth = 0.0f;
		k_col = 0.0f;
		k_abs = 0.0f;
		k_avg = 0.0f;
	}

	void setDivision(double divider) {
		divid = divider;
	}

	inline void add_Pathlength(double p) noexcept {
		k_pth += p;
	}

	inline void add_Collision(double c) noexcept {
		k_col += c;
	}

	inline void add_Absorption(double a) noexcept {
		k_abs += a;
	}

	double print_Eigenvalue() noexcept {
		cout << "Pathlength estimator: " << k_pth / divid << "\n";
		cout << "Collision  estimator: " << k_col / divid << "\n";
		cout << "Absorption estimator: " << k_abs / divid << "\n";

		k_avg = (k_pth + k_col + k_abs) / 3;
		cout << "Eigenvalue estimator: " << k_avg / divid << "\n";

		return k_avg / divid;
	}
};