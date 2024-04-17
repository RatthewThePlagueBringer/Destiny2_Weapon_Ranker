#include "Weapon.h"

// Constructor
Weapon::Weapon(string name, int magDamage, int totDamage, int magTime, int magSize, int totSize) {
    this->name = name;
    this->magDamage = magDamage;
    this->totDamage = totDamage;
    this->magTime = magTime;
    this->magSize = magSize;
    this->totSize = totSize;
    this->burstDPS = 0;
    this->sustainedDPS = 0;
}

// Getters
int Weapon::getSusDPS() {
    return sustainedDPS;
}

int Weapon::getBurstDPS() {
    return burstDPS;
}

int Weapon::getTotDamage() {
    return totDamage;
}
