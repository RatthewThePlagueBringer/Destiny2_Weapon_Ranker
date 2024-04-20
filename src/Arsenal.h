#include <vector>
#include <fstream>
#include <sstream>

#include "Weapon.h"

#ifndef DESTINY2_WEAPON_DPS_ARSENAL_H
#define DESTINY2_WEAPON_DPS_ARSENAL_H

using namespace std;

class Arsenal {
private:
    int size;

public:
    // Weapon Families
    vector<vector<Weapon>> priWeapons;
    vector<vector<Weapon>> secWeapons;
    vector<vector<Weapon>> powWeapons;

    // Weapon Subfamilies
    // Primary
    vector<Weapon> handCannons;
    vector<Weapon> autoRifles;
    vector<Weapon> pulseRifles;
    vector<Weapon> scoutRifles;
    vector<Weapon> sidearms;
    vector<Weapon> subMachineGuns;
    vector<Weapon> bows;
    vector<Weapon> pri_Uniques;
    // Secondary
    vector<Weapon> shotguns;
    vector<Weapon> sniperRifles;
    vector<Weapon> fusionRifles;
    vector<Weapon> glaives;
    vector<Weapon> traceRifles;
    vector<Weapon> sec_grenades;
    vector<Weapon> sec_Uniques;
    // Power
    vector<Weapon> pow_grenades;
    vector<Weapon> rockets;
    vector<Weapon> swords;
    vector<Weapon> heavyMachineGuns;
    vector<Weapon> linearFusions;
    vector<Weapon> pow_Uniques;

public:
    // Default constructor
    Arsenal();

    // Methods
    void updateMethods(bool method);
};


#endif //DESTINY2_WEAPON_DPS_ARSENAL_H
