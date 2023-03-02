#include <iostream>

#include "Materials.h"

using namespace std;

void Material::CheckMaterial() const {
	cout << "Material name: " << name << "\n" << endl;

	cout << "Total cross section" << endl;
	for (auto i : XS_tot) {
		cout << std::scientific << i << "  ";
	}
	cout << "\n" << endl;

	cout << "Transport cross section" << endl;
	for (auto i : XS_trn) {
		cout << std::scientific << i << "  ";
	}
	cout << "\n" << endl;

	cout << "Absorption cross section" << endl;
	for (auto i : XS_abs) {
		cout << std::scientific << i << "  ";
	}
	cout << "\n" << endl;

	cout << "Fission cross section" << endl;
	for (auto i : XS_fis) {
		cout << std::scientific << i << "  ";
	}
	cout << "\n" << endl;

	cout << "Capture cross section" << endl;
	for (auto i : XS_cap) {
		cout << std::scientific << i << "  ";
	}
	cout << "\n" << endl;

	cout << "Nu" << endl;
	for (auto i : Nu) {
		cout << scientific << i << "  ";
	}
	cout << "\n" << endl;

	cout << "Chi" << endl;
	for (auto i : Chi) {
		cout << scientific << i << "  ";
	}
	cout << "\n" << endl;

	cout << "Scatter cross section (groupwise)" << endl;
	for (auto i : XS_sct_grouptotal) {
		cout << scientific << i << "  ";
	}
	cout << "\n" << endl;

	cout << "Scatter cross section (Total)" << endl;
	for (auto i : XS_sct) {
		for (auto j : i) {
			cout << scientific << j << "  ";
		}
		cout << "\n";
	}
	cout << "\n" << endl;
}

std::vector<Material> MaterialReader::GetMaterials() {
	int energyGroup;
	int matNumber;
	double tmpdouble;
	std::string mName;
	std::string tmp;
	std::vector<double> tmpVF;

	std::vector<double> XS_tot;
	std::vector<double> XS_trn;
	std::vector<double> XS_abs;
	std::vector<double> XS_cap;
	std::vector<double> XS_fis;
	std::vector<double> Nu;
	std::vector<double> Chi;
	std::vector<std::vector<double>> XS_sct;

	std::vector<Material> materials;

	std::ifstream inputFile(filename);

	inputFile >> energyGroup;
	inputFile >> matNumber;

	cout << "Energy Groups: " << energyGroup << " | Material Number: " << matNumber << endl;
	for (int i = 0; i < matNumber; i++) {
		mName = "";
		XS_tot.clear();
		XS_trn.clear();
		XS_abs.clear();
		XS_cap.clear();
		XS_fis.clear();
		Nu.clear();
		Chi.clear();
		XS_sct.clear();

		inputFile >> mName;

		for (int j = 0; j < energyGroup; j++) {
			inputFile >> tmpdouble;	XS_tot.push_back(tmpdouble);
			inputFile >> tmpdouble;	XS_trn.push_back(tmpdouble);
			inputFile >> tmpdouble;	XS_abs.push_back(tmpdouble);
			inputFile >> tmpdouble;	XS_cap.push_back(tmpdouble);
			inputFile >> tmpdouble;	XS_fis.push_back(tmpdouble);
			inputFile >> tmpdouble;	Nu.push_back(tmpdouble);
			inputFile >> tmpdouble;	Chi.push_back(tmpdouble);
		}

		for (int j = 0; j < energyGroup; j++) {
			tmpVF.clear();
			for (int k = 0; k < energyGroup; k++) {
				inputFile >> tmpdouble; tmpVF.push_back(tmpdouble);
			}
			XS_sct.push_back(tmpVF);
		}

		materials.push_back(Material(mName, XS_tot, XS_trn, XS_abs, XS_cap, XS_fis, Nu, Chi, XS_sct));
	}
	return materials;
}