#include "Weapon.h"

// Constructors
Weapon::Weapon() {
    type = "N/A";
	name = "DNE";
	damage = 0;
	rpm = 0;
	reloadTime = 0;
	magSize = 0;
	totSize = 0;
	totDamage = 0;
	sustainedDPS = 0;
	burstDPS = 0;
}

Weapon::Weapon(string type, string name, string damage, string rpm, string reloadTime, string magSize, string totSize) {

    this->type = type;
    this->name = name;
    this->damage = stoi(damage);

    if (rpm == "inf" || rpm == "N/A") {
        this->rpm = 0;
    }
    else {
        this->rpm = stoi(rpm);
    }

    if (reloadTime == "inf" || reloadTime == "N/A") {
        this->reloadTime = 0;
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

    // Calculating Total Damage
    this->totDamage = this->damage * this->totSize;

    // Calculating Burst DPS
    burstDPS = (this->damage * (this->rpm / 4) - this->damage * (this->rpm / 60) * this->reloadTime) / 15;


    // Calculating Sustained DPS
    float timeToEmpty;
    if (this->totSize == -1) {
        // Over time, damage will converge to this value given infinite ammunition
        sustainedDPS = (this->damage * this->rpm) / 60;
    }
    else {
        // Exact sustained DPS can be more accurately calculated when total amount of ammunition is known
        timeToEmpty = this->totSize / (this->rpm * 0.02) + this->reloadTime * floor(this->totSize / this->magSize);
        sustainedDPS = (this->damage * this->totSize) / timeToEmpty;
    }

}

// Getters
string Weapon::getName() {
    return name;
}

string Weapon::getType() {
    return type;
}

int Weapon::getSusDPS() {
    return sustainedDPS;
}

int Weapon::getBurstDPS() {
    return burstDPS;
}

int Weapon::getTotDamage() {
    return totDamage;
}

// Overloaded Operators
bool Weapon::operator==(const Weapon& obj) const {
    // Compare based on the name
    if (this->type == obj.type && this->name == obj.name) {
        return  true;
    }
    else {
        return false;
    }
}
