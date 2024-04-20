#include "Arsenal.h"


using namespace std;

// Helper method for splitting input string into a vector of strings
vector<string> split(const string& s, char delimiter) {
    vector<string> items;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delimiter)) {
        items.push_back(item);
    }
    return items;
}

// Default constructor
Arsenal::Arsenal() {
    size = 0;

    cout << "Opening file stream" << endl;

    fstream file;
    file.open("weapons.csv", ios::in);

    vector<string> row;
    string line;

    cout << "File stream opened, loading data onto stack" << endl;

    while (getline(file, line)) {

        row = split(line, ',');

        string temp;

        if (row[8] == "N/A") {
            temp = row[7];
        }
        else {
            temp = row[8];
        }

        Weapon gun(row[1], row[2], temp, row[5], row[6], row[3], row[4]);

        if (row[1] == "AuRi") {
            autoRifles.push_back(gun);
        }
        else if (row[1] == "Bows") {
            bows.push_back(gun);
        }
        else if (row[1] == "FuRi") {
            fusionRifles.push_back(gun);
        }
        else if (row[1] == "Glai") {
            glaives.push_back(gun);
        }
        else if (row[1] == "GrLa") {
            sec_grenades.push_back(gun);
        }
        else if (row[1] == "HaCa") {
            handCannons.push_back(gun);
        }
        else if (row[1] == "HeGL") {
            pow_grenades.push_back(gun);
        }
        else if (row[1] == "HeMG") {
            heavyMachineGuns.push_back(gun);
        }
        else if (row[1] == "LFRi") {
            linearFusions.push_back(gun);
        }
        else if (row[1] == "PuRi") {
            pulseRifles.push_back(gun);
        }
        else if (row[1] == "RocL") {
            rockets.push_back(gun);
        }
        else if (row[1] == "ScRi") {
            scoutRifles.push_back(gun);
        }
        else if (row[1] == "Sdrm") {
            sidearms.push_back(gun);
        }
        else if (row[1] == "Shgu") {
            shotguns.push_back(gun);
        }
        else if (row[1] == "SnRi") {
            sniperRifles.push_back(gun);
        }
        else if (row[1] == "SuMG") {
            subMachineGuns.push_back(gun);
        }
        else if (row[1] == "Swrd") {
            swords.push_back(gun);
        }
        else if (row[1] == "TrRi") {
            traceRifles.push_back(gun);
        }

    }

    cout << "Data loaded." << endl;

    priWeapons.push_back(autoRifles);
    priWeapons.push_back(pulseRifles);
    priWeapons.push_back(scoutRifles);
    priWeapons.push_back(handCannons);
    priWeapons.push_back(subMachineGuns);
    priWeapons.push_back(bows);
    priWeapons.push_back(sidearms);

    secWeapons.push_back(shotguns);
    secWeapons.push_back(sniperRifles);
    secWeapons.push_back(fusionRifles);
    secWeapons.push_back(glaives);
    secWeapons.push_back(traceRifles);
    secWeapons.push_back(sec_grenades);

    powWeapons.push_back(rockets);
    powWeapons.push_back(pow_grenades);
    powWeapons.push_back(swords);
    powWeapons.push_back(linearFusions);
    powWeapons.push_back(heavyMachineGuns);

    allWeapons.push_back(priWeapons);
    allWeapons.push_back(secWeapons);
    allWeapons.push_back(powWeapons);

    cout << "Primary weapon sizes: " << endl;
    for (auto const& i : priWeapons) {
        cout << i.size() << endl;
    }

    cout << "Special weapon sizes: " << endl;
    for (auto const& i : secWeapons) {
        cout << i.size() << endl;
    }

    cout << "Power weapon sizes: " << endl;
    for (auto const& i : powWeapons) {
        cout << i.size() << endl;
    }

}

void Arsenal::setDPS(bool burst) {
    if (burst) {
        for (vector<Weapon> i : priWeapons) {
            for (Weapon j : i) {
                cout << j.getName() << endl;
                j.setActive(j.getBurstDPS());
            }
        }
        for (vector<Weapon> i : secWeapons) {
            for (Weapon j : i) {
                cout << j.getName() << endl;
                j.setActive(j.getBurstDPS());
            }
        }
        for (vector<Weapon> i : powWeapons) {
            for (Weapon j : i) {
                cout << j.getName() << endl;
                j.setActive(j.getBurstDPS());
            }
        }
    }
    else {
        for (vector<Weapon> i : priWeapons) {
            for (Weapon j : i) {
                cout << j.getName() << endl;
                j.setActive(j.getSusDPS());
            }
        }
        for (vector<Weapon> i : secWeapons) {
            for (Weapon j : i) {
                cout << j.getName() << endl;
                j.setActive(j.getSusDPS());
            }
        }
        for (vector<Weapon> i : powWeapons) {
            for (Weapon j : i) {
                cout << j.getName() << endl;
                j.setActive(j.getSusDPS());
            }
        }
    }
}

// Used the COP3530 Module 8 Lecture & Discussion Slides
void Arsenal::swap(vector<Weapon>& v, int a, int b) {
    Weapon temp = v[a];
    v[a] = v[b];
    v[b] = temp;
}

int Arsenal::partition(vector<Weapon>& vec, int low, int high, bool isSust, bool isFwd) {

    int pivot = (isSust ? vec[low].getSusDPS() : vec[low].getBurstDPS());
    int up = low, down = high;

    while (up < down) {

        for (int j = up; j < high; j++) {

            if ((isFwd && (isSust ? vec[up].getSusDPS() < pivot : vec[up].getBurstDPS() < pivot)) ||
                (!isFwd && (isSust ? vec[up].getSusDPS() > pivot : vec[up].getBurstDPS() > pivot))) {
                break;
            }

            up++;
        }
        for (int j = down; j > low; j--) {

            if ((isFwd && (isSust ? vec[down].getSusDPS() > pivot : vec[down].getBurstDPS() > pivot)) ||
                (!isFwd && (isSust ? vec[down].getSusDPS() < pivot : vec[down].getBurstDPS() < pivot))) {
                break;
            }

            down--;
        }

        if (up < down) {
            swap(vec, up, down);
        }
    }

    swap(vec, low, down);
    return down;
}

void Arsenal::quickSort(vector<Weapon>& vec, int low, int high, bool isSust, bool isFwd) {

    if (low < high) {
        int pivot = partition(vec, low, high, isSust, isFwd);
        quickSort(vec, low, pivot - 1, isSust, isFwd);
        quickSort(vec, pivot + 1, high, isSust, isFwd);
    }
}

void Arsenal::insertionSort(vector<Weapon>& vec, int gap, int n, bool isSust, bool isFwd) {

    for (int i = gap; i < n; i++) {

        int key = (isSust ? vec[i].getSusDPS() : vec[i].getBurstDPS());
        int j = i;

        while (j >= gap && ((isFwd && (isSust ? key > vec[j - gap].getSusDPS() : key > vec[j - gap].getBurstDPS())) ||
            (!isFwd && (isSust ? key < vec[j - gap].getSusDPS() : key < vec[j - gap].getBurstDPS())))) {
            swap(vec, j, j - gap);
            j -= gap;
        }
    }
}

void Arsenal::shellSort(vector<Weapon>& vec, bool isSust, bool isFwd) {

    int n = vec.size();
    int gap = n / 2;

    while (gap > 0) {

        insertionSort(vec, gap, n, isSust, isFwd);

        if (gap == 2) {
            gap = 1;
        }

        else {
            gap /= 2;
        }
    }
}

Weapon Arsenal::searchItem(vector<vector<vector<Weapon>>> vec, string itemName) {

    Weapon ret;

    for (int i = 0; i < vec.size(); i++) {

        for (int j = 0; j < vec[i].size(); j++) {

            if (vec[i][j].size() == itemName.size()) {

                for (int k = 0; k < itemName.size(); k++) {

                    if (vec[i][j][k].getName() == itemName) {
                        return vec[i][j][k];
                    }
                }
            }
        }
    }

    return ret;
}

Weapon Arsenal::searchIndex(vector<Weapon> vec, int index) {

	Weapon ret;

    if (index >= 0 && index < vec.size()) {
        return vec[index];
    }

    return ret;
}

vector<Weapon> Arsenal::searchSub(vector<vector<vector<Weapon>>> vec, string itemName) {

    vector<Weapon> ret;

    for (int i = 0; i < itemName.size(); i++) {
        itemName[i] = tolower(itemName[i]);
    }

    if (itemName == "autorifles") {
		return autoRifles;
	}
	else if (itemName == "bows") {
		return bows;
	}
	else if (itemName == "fusionrifles") {
		return fusionRifles;
	}
	else if (itemName == "glaives") {
		return glaives;
	}
	else if (itemName == "sec_grenades") {
		return sec_grenades;
	}
	else if (itemName == "handcannons") {
		return handCannons;
	}
	else if (itemName == "pow_grenades") {
		return pow_grenades;
	}
	else if (itemName == "heavymachineguns") {
		return heavyMachineGuns;
	}
	else if (itemName == "linearfusions") {
		return linearFusions;
	}
	else if (itemName == "pulserifles") {
		return pulseRifles;
	}
	else if (itemName == "rockets") {
		return rockets;
	}
	else if (itemName == "scoutrifles") {
		return scoutRifles;
	}
	else if (itemName == "sidearms") {
		return sidearms;
	}
	else if (itemName == "shotguns") {
		return shotguns;
	}
	else if (itemName == "sniperrifles") {
		return sniperRifles;
	}
	else if (itemName == "submachineguns") {
		return subMachineGuns;
	}
	else if (itemName == "swords") {
		return swords;
	}
	else if (itemName == "tracerifles") {
		return traceRifles;
	}

    return ret;
}

vector<vector<Weapon>> Arsenal::searchFam(vector<vector<vector<Weapon>>> vec, string itemName) {

    vector<vector<Weapon>> ret;

    for (int i = 0; i < itemName.size(); i++) {
        itemName[i] = tolower(itemName[i]);
    }

    if (itemName == "priweapons") {
        return priWeapons;
    }
	else if (itemName == "secweapons") {
		return secWeapons;
	}
	else if (itemName == "powweapons") {
		return powWeapons;
	}

    return ret;
}

int Arsenal::getIndex(vector<vector<vector<Weapon>>> vec, Weapon item) {

    int foundIndex = -1;

    for (int i = 0; i < vec.size(); i++) {

        for (int j = 0; j < vec[i].size(); j++) {

			for (int k = 0; k < vec[i][j].size(); k++) {

				if (vec[i][j][k] == item) {
					return foundIndex;
				}
			}
		}
    }

    return -1;
}
