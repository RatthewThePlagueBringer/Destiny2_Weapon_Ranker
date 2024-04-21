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
    // All Weapons
    vector<vector<vector<Weapon>>> allWeapons;

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
    // Temporary Subfamily
    vector<Weapon> tempVec;

public:
    // Default constructor
    Arsenal();

    // Getters
    Weapon searchItem(vector<Weapon> vec, string itemName);
    Weapon searchIndex(vector<Weapon> vec, int index);
    vector<Weapon> searchSub(vector<vector<vector<Weapon>>> vec, string itemName);
    vector<vector<Weapon>> searchFam(vector<vector<vector<Weapon>>> vec, string itemName);
    int getIndex(vector<Weapon> vec, Weapon item);

    // Sorters for Subfamilies
    void swap(vector<Weapon>& subFam, int a, int b);
    int partition(vector<Weapon>& subFam, int low, int high, bool isSust, bool isFwd);
    void quickSort(vector<Weapon>& subFam, int low, int high, bool isSust, bool isFwd);
    void insertionSort(vector<Weapon>& subFam, int gap, int n, bool isSust, bool isFwd);
    void shellSort (vector<Weapon>& subFam, bool isSust, bool isFwd);
    
    // Methods
    vector<Weapon> createFam(vector<vector<vector<Weapon>>> vec, string itemName);
    vector<Weapon> createAll(vector<vector<vector<Weapon>>> vec);
};


#endif //DESTINY2_WEAPON_DPS_ARSENAL_H
