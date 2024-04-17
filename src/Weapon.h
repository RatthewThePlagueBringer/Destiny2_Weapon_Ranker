#include <iostream>
#include <vector>
#include <string>

#ifndef DESTINY2_WEAPON_DPS_WEAPON_H
#define DESTINY2_WEAPON_DPS_WEAPON_H

using namespace std;

class Weapon {
private:
    // Stores weapon name
    string name;
    // Stores the damage of a single magazine
    int magDamage;
    // Stores the total damage of magazine and reserves
    int totDamage;
    // Stores time it takes to empty a single magazine
    int magTime;
    // Stores the number of rounds in a single magazine
    int magSize;
    // Stores the total amount of rounds in magazine and reserves
    int totSize;

    // Stores the theoretical "burst" Damage Per Second
    int burstDPS;
    // Stores the theoretical "sustained" Damage Per Second
    int sustainedDPS;

public:
    // Constructor
    Weapon(string name, int magDamage, int totDamage, int magTime, int magSize, int totSize);

    // Methods
    int getSusDPS();
    int getBurstDPS();
    int getTotDamage();
};


#endif //DESTINY2_WEAPON_DPS_WEAPON_H
