#pragma once

#include <vector>
#include <string>
#include <numeric>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Material;

namespace World {
	extern std::unordered_map<int, Material*> materials;
}

class Material {
private:
	std::string name;
	std::vector<double> XS_tot;
	std::vector<double> XS_trn;
	std::vector<double> XS_abs;
	std::vector<double> XS_cap;
	std::vector<double> XS_fis;
	std::vector<double> XS_sct_grouptotal;
	std::vector<double> Nu;
	std::vector<double> Chi;

	std::vector<std::vector<double>> XS_sct;

public:
	Material() {
		this->name = "VOID";
	}
	Material(const std::string& name,
		const std::vector<double>& XS_tot, const std::vector<double>& XS_trn,
		const std::vector<double>& XS_abs, const std::vector<double>& XS_cap,
		const std::vector<double>& XS_fis, const std::vector<double>& Nu,
		const std::vector<double>& Chi, const std::vector<std::vector<double>>& XS_sct) {
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
	std::string getName() const {
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

	double GetNuSigmaF(int group) const {
		if (group < Nu.size()) { return Nu[group] * XS_fis[group]; }
		else return 0.0f;
	}

	double GetXsCap(int group) const {
		if (group < XS_cap.size()) { return XS_cap[group]; }
		else return 0.0f;
	}

	std::vector<double> GetChi() const {
		if (Chi.size() == 0) {
			return std::vector<double> {1.0f};
		}
		else return Chi;
	}

	std::vector<double> GetXsSct(int group) const {
		if (group < XS_sct.size()) { return XS_sct[group]; }
		else return std::vector<double> {1.0};
	}

	// FISS - CAPTURE - SCATTER - ETC
	std::vector<double> GetXsAlltype(int group) const {
		if (group < XS_tot.size()) {
			return std::vector<double> {
				XS_fis[group], XS_cap[group], XS_sct_grouptotal[group]
			};
		}
		else return std::vector<double> {0.0, 0.0, 1.0};


	}
	void CheckMaterial() const;
};

class MaterialReader {
private:
	std::string filename;
public:
	MaterialReader(const std::string& fileName) {
		this->filename = fileName;
	}

	~MaterialReader() {
	}

	std::vector<Material> GetMaterials();
};
