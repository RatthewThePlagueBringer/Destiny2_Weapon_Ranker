// There are only around 300 unique weapon types in Destiny 2 which does not meet the requirement of 100,000 data points
// Our solution is using the parameters of the real weapons, we will randomly generate an extra 999,700 weapon variants

#include <fstream>

using namespace std;

int main() {
    fstream file;
    file.open("weapons.csv", ios::out | ios::app);

    // file << stuff << ","

    // 18 weapon subfamilies, 5,555 randomly generated weapons per subfamily
    // Auto Rifles
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", "
                << "AuRi," // Weapon type
                << "AutoRifle_" << i << "," // Weapon name
                << rand() % 4604 + 5436 << "," // Burst
                << rand() % 4823 + 5217 << "," // Sustained
                << "inf," // Total damage
                << rand() % 20706 + 28646 << "," // Mag damage
                << rand() % 34 + 26 << "," // Mag size
                << "inf," // Total size
                << rand() % 360 + 360 << "," // Fire rate (rpm)
                << (rand() % 9 + 12)/10 << "," // Reload speed (s)
                << "inf," // Time to empty (s)
                << rand() % 346 + 278 << "," // Body damage
                << rand() % 518 + 479 // Precision damage
                << "\n";
    }
    // Bows
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", "
             << "Bows," // Weapon type
             << "Bow_" << i << "," // Weapon name
             << rand() % 3844 + 1195 << "," // Burst
             << rand() % 3844 + 1195 << "," // Sustained
             << "inf," // Total damage
             << rand() % 4913 + 149 << "," // Mag damage
             << "1," // Mag size
             << "inf," // Total size
             << rand() % 50 + 10 << "," // Fire rate (rpm)
             << (rand() % 6 + 8)/10 << "," // Reload speed (s)
             << "inf," // Time to empty (s)
             << rand() % 3075 + 300 << "," // Body damage
             << rand() % 4913 + 200 // Precision damage
             << "\n";
    }
    // Fusion Rifles
    for (int i = 0; i < 5555; i++) {
        file << "S" << ", "
             << "FuRi," // Weapon type
             << "FusionRifle_" << i << "," // Weapon name
             << rand() % 11331 + 3712 << "," // Burst
             << rand() % 14030 + 3696 << "," // Sustained
             << rand() % 334026 + 142989 << "," // Total damage
             << rand() % 121464 + 37912 << "," // Mag damage
             << rand() % 6 + 3 << "," // Mag size
             << rand() % 19 + 7 << "," // Total size
             << rand() % 40 + 13 << "," // Fire rate (rpm)
             << (rand() % 106 + 26)/100 << "," // Reload speed (s)
             << (rand() % 234 + 49)/10 << "," // Time to empty (s)
             << rand() % 15183 + 7532 << "," // Body damage
             << "N/A," // Precision damage
             << "\n";
    }
    // Glaives
    for (int i = 0; i < 5555; i++) {
        file << "S" << ", "
             << "Glai," // Weapon type
             << "Glaive_" << i << "," // Weapon name
             << rand() % 9907 + 200 << "," // Burst
             << rand() % 9907 + 200 << "," // Sustained
             << "inf," // Total damage
             << "N/A," // Mag damage
             << "N/A," // Mag size
             << "N/A," // Total size
             << rand() % 40 + 13 << "," // Fire rate (rpm)
             << "N/A," // Reload speed (s)
             << "N/A," // Time to empty (s)
             << rand() % 4403 + 200 << "," // Body damage
             << "N/A," // Precision damage
             << "\n";
    }
    // Special Grenade Launchers
    for (int i = 0; i < 5555; i++) {
        file << "S" << ", "
             << "GrLa," // Weapon type
             << "SpecialGrenade_" << i << "," // Weapon name
             << rand() % 6741 + 2165 << "," // Burst
             << rand() % 6741 + 2165 << "," // Sustained
             << rand() % 251160 + 80661 << "," // Total damage
             << rand() % 10920 + 3506 << "," // Mag damage
             << "1," // Mag size
             << "23," // Total size
             << rand() % 72 + 18 << "," // Fire rate (rpm)
             << "1.62," // Reload speed (s)
             << "37.3," // Time to empty (s)
             << rand() % 10920 + 3506 << "," // Body damage
             << "N/A," // Precision damage
             << "\n";
    }
    // Hand Cannons
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", "
             << "HaCa," // Weapon type
             << "HandCannon_" << i << "," // Weapon name
             << rand() % 4654 + 917 << "," // Burst
             << rand() % 3884 + 722 << "," // Sustained
             << "inf," // Total damage
             << rand() % 35283 + 29876 << "," // Mag damage
             << rand() % 6 + 6 << "," // Mag size
             << "inf," // Total size
             << rand() % 120 + 60 << "," // Fire rate (rpm)
             << (rand() % 14 + 6)/10 << "," // Reload speed (s)
             << "inf," // Time to empty (s)
             << rand() % 1238 + 1694 << "," // Body damage
             << rand() % 1857 + 1411 // Precision damage
             << "\n";
    }
    // Heavy Grenade Launchers
    for (int i = 0; i < 5555; i++) {
        file << "H" << ", "
             << "HeGL," // Weapon type
             << "HeavyGrenade_" << i << "," // Weapon name
             << rand() % 39980 + 340 << "," // Burst
             << rand() % 24933 + 3726 << "," // Sustained
             << rand() % 544320 + 17150 << "," // Total damage
             << rand() % 128336 + 31584 << "," // Mag damage
             << rand() % 6 + 2 << "," // Mag size
             << rand() % 27 + 8 << "," // Total size
             << rand() % 120 + 30 << "," // Fire rate (rpm)
             << (rand() % 192 + 24)/100 << "," // Reload speed (s)
             << (rand() % 182 + 18)/10 << "," // Time to empty (s)
             << rand() % 16042 + 4118 << "," // Body damage
             << "N/A," // Precision damage
             << "\n";
    }
    file.close();
    return 0;
}