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
    string line, word, temp;

    cout << "File stream opened, loading data onto stack" << endl;


    while (getline(file, line)) {

        row = split(line, ',');

        Weapon gun(row[1], row[2], row[13], row[9], row[10], row[7], row[8]);

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


