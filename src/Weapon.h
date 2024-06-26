#include <iostream>
#include <vector>
#include <string>
#include <cmath>

#ifndef DESTINY2_WEAPON_DPS_WEAPON_H
#define DESTINY2_WEAPON_DPS_WEAPON_H

using namespace std;

class Weapon {
private:
    // Stores weapon family
    string fam;
    
    // Stores weapon subfamily
    string subFam;

    // Stores weapon name
    string name;

    // Stores the damage value of a single round (assumes precision when applicable)
    int damage;

    // Stores the RPM (Rounds Per Minute)
    int rpm;

    // Stores time it takes to reload a magazine
    float reloadTime;

    // Stores the number of rounds in a single magazine
    int magSize;

    // Stores the total amount of rounds in magazine and reserves
    int totSize;

    // Stores the total damage of magazine and reserves
    int totDamage;

    // Stores the theoretical "burst" Damage Per Second
    int burstDPS;

    // Stores the theoretical "sustained" Damage Per Second
    int sustainedDPS;

public:
    // Constructors
    Weapon();
    Weapon(string fam, string subFam, string name, string damage, string rpm, string reloadTime, string magSize, string totSize);

    // Getters
    int getSusDPS();
    int getBurstDPS();
    int getTotDamage();
    string getName();
    string getFam();
    string getSubFam();

    // Operator Overloads
    bool operator==(Weapon const& obj) const;
};

#endif //DESTINY2_WEAPON_DPS_WEAPON_H
