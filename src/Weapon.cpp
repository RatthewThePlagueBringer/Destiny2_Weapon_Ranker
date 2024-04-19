#include "Weapon.h"

// Constructor
Weapon::Weapon(string type, string name, string damage, string rpm, string reloadTime, string magSize, string totSize) {

    this->type = type;
    this->name = name;

    if (damage == "inf" || damage == "N/A") {
        this->damage = -1;
    }
    else {
        this->damage = stoi(damage);
    }

    if (rpm == "inf" || rpm == "N/A") {
        this->rpm = -1;
    }
    else {
        this->rpm = stoi(rpm);
    }

    if (reloadTime == "inf" || reloadTime == "N/A") {
        this->reloadTime = -1;
    }
    else {
        this->reloadTime = stof(reloadTime);
    }

    if (magSize == "inf" || magSize == "N/A") {
        this->magSize = -1;
    }
    else {
        this->magSize = stoi(magSize);
    }

    if (totSize == "inf" || totSize == "N/A") {
        this->totSize = -1;
    }
    else {
        this->totSize = stoi(totSize);
    }

    this->totDamage = this->damage * this->totSize;

    this->burstDPS = 0;

    float timeToEmpty;
    if (this->totSize != -1) {
        timeToEmpty = this->totSize / (this->rpm * 0.02) + this->reloadTime * floor(this->totSize / this->magSize);
        this->sustainedDPS = (this->damage * this->totSize) / timeToEmpty;
    }
    else {
        this->sustainedDPS = 0;
    }

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
