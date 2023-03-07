#pragma once

#include <iostream>

class Eigenvalue {
private:
	double wgt = 1.0f;
	double k_pth = 0.0f;
	double k_col = 0.0f;
	double k_abs = 0.0f;
	double k_avg = 0.0f;

public:
	Eigenvalue() {
		k_pth = 0.0f;
		k_col = 0.0f;
		k_abs = 0.0f;
		k_avg = 0.0f;
	}
	~Eigenvalue() = default;

	void Set_Weight(const double wgt) {
		this->wgt = wgt;
	}

	inline void Upadate_Pathlength(const double p) noexcept {
		k_pth += p;
	}

	inline void Update_Absorption(const double a) noexcept {
		k_abs += a;
	}

	inline void Update_Collision(const double c) noexcept {
		k_col += c;
	}

	double Print_Eigenvalue() noexcept {
		std::cout << "Pathlength estimator: " << k_pth / divid << "\n";
		std::cout << "Collision  estimator: " << k_col / divid << "\n";
		std::cout << "Absorption estimator: " << k_abs / divid << "\n";

		k_avg = (k_pth + k_col + k_abs) / 3;
		std::cout << "Eigenvalue estimator: " << k_avg / divid << "\n";

		return k_avg / divid;
	}
};