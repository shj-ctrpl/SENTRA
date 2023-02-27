#pragma once

#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <sstream>

using namespace std;

enum ReactionType {
	TOT = 0,
	ABS = 1,
	CAP = 2,
	FIS = 3,
	SCT = 4
};


class Material {
private:
	string name;

	vector<double> XS_tot;
	vector<double> XS_trn;
	vector<double> XS_abs;
	vector<double> XS_cap;
	vector<double> XS_fis;
	vector<double> XS_sct_grouptotal;
	vector<double> Nu;
	vector<double> Chi;

	vector<vector<double>> XS_sct;

public:
	Material() {
		this->name = "VOID";
	}
	Material(const string& name, const vector<double>& XS_tot, const vector<double>& XS_trn, const vector<double>& XS_abs, const vector<double>& XS_cap,
		const vector<double>& XS_fis, const vector<double>& Nu, const vector<double>& Chi, const vector<vector<double>>& XS_sct) {
		this->name = name;
		this->XS_tot = XS_tot;
		this->XS_trn = XS_trn;
		this->XS_abs = XS_abs;
		this->XS_cap = XS_cap;
		this->XS_fis = XS_fis;
		this->Nu = Nu;
		this->Chi = Chi;
		this->XS_sct = XS_sct;

		this->XS_sct_grouptotal.clear();

		for (int i = 0; i < this->XS_sct.size(); i++) {
			this->XS_sct_grouptotal.push_back(accumulate(this->XS_sct[i].begin(), this->XS_sct[i].end(), 0.0));
		}
	}

	bool isVoid() const {
		if (this->name == "VOID") {
			return true;
		}
		else return false;
	}
	string getName() const {
		return name;
	}

	double GetXsTot(int group) const {
		if (group < XS_trn.size()) { return XS_trn[group]; }
		else return 0.0f;
	}

	double GetXsAbs(int group) const {
		if (group < XS_abs.size()) { return XS_abs[group]; }
		else return 0.0f;
	}

	double GetXsFis(int group) const {
		if (group < XS_fis.size()) { return XS_fis[group]; }
		else return 0.0f;
	}

	double GetNu(int group) const {
		if (group < Nu.size()) { return Nu[group]; }
		else return 0.0f;
	}

	double GetXsCap(int group) const {
		if (group < XS_cap.size()) { return XS_cap[group]; }
		else return 0.0f;
	}

	vector<double> GetChi() const {
		if (Chi.size() == 0) {
			return vector<double> {1.0f};
		}
		else return Chi;
	}

	vector<double> GetXsSct(int group) const {
		if (group < XS_sct.size()) { return XS_sct[group]; }
		else return vector<double> {1.0};
	}

	vector<double> GetXsAlltype(int group) const {
		if (group < XS_tot.size()) {
			return vector<double> {
				XS_fis[group], XS_cap[group], XS_sct_grouptotal[group]
			};
		}
		else return vector<double> {0.0, 0.0, 1.0};
		// FISS - CAPTURE - SCATTER - ETC

	}

	void CheckMaterial() const {
		cout << "Material name: " << name << "\n" << endl;

		cout << "Total cross section" << endl;
		for (auto i : XS_tot) {
			cout << scientific << i << "  ";
		}
		cout << "\n" << endl;

		cout << "Transport cross section" << endl;
		for (auto i : XS_trn) {
			cout << scientific << i << "  ";
		}
		cout << "\n" << endl;

		cout << "Absorption cross section" << endl;
		for (auto i : XS_abs) {
			cout << scientific << i << "  ";
		}
		cout << "\n" << endl;

		cout << "Fission cross section" << endl;
		for (auto i : XS_fis) {
			cout << scientific << i << "  ";
		}
		cout << "\n" << endl;

		cout << "Capture cross section" << endl;
		for (auto i : XS_cap) {
			cout << scientific << i << "  ";
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
};

class MaterialReader {
private:
	string filename;
public:
	MaterialReader(const string& fileName) {
		this->filename = fileName;
	}

	~MaterialReader() {
	}

	vector<Material> GetMaterials() {
		int energyGroup;
		int matNumber;
		double tmpdouble;
		string mName;
		string tmp;
		vector<double> tmpVF;

		vector<double> XS_tot;
		vector<double> XS_trn;
		vector<double> XS_abs;
		vector<double> XS_cap;
		vector<double> XS_fis;
		vector<double> Nu;
		vector<double> Chi;
		vector<vector<double>> XS_sct;

		vector<Material> materials;

		ifstream inputFile(filename);

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
};
