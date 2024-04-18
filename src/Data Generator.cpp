// There are only around 300 unique weapon types in Destiny 2 which does not meet the requirement of 100,000 data points
// Our solution is using the parameters of the real weapons, we will randomly generate an extra 999,700 weapon variants

/*

#include <fstream>
#include <iostream>

using namespace std;

int main() {
    fstream file;
    file.open("weapons.csv", ios::out | ios::app);

    cout << "Generating random weapon data!" << endl;

    // 18 weapon subfamilies, 5,555 randomly generated weapons per subfamily
    // Auto Rifles
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", " // Ammo type
             << "AuRi," // Weapon type
             << "AutoRifle_" << i << "," // Weapon name
             << rand() % 4604 + 1436 << "," // Burst
             << rand() % 4823 + 1217 << "," // Sustained
             << "inf," // Total damage
             << rand() % 20706 + 8646 << "," // Mag damage
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
        file << "P" << ", " // Ammo type
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
        file << "S" << ", " // Ammo type
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
        file << "S" << ", " // Ammo type
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
        file << "S" << ", " // Ammo type
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
        file << "P" << ", " // Ammo type
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
        file << "H" << ", " // Ammo type
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
    // Heavy Machine Guns
    for (int i = 0; i < 5555; i++) {
        file << "H" << ", " // Ammo type
             << "HeMG," // Weapon type
             << "MachineGun_" << i << "," // Weapon name
             << rand() % 15060 + 3870 << "," // Burst
             << rand() % 11837 + 4147 << "," // Sustained
             << rand() % 779916 + 319464 << "," // Total damage
             << rand() % 145130 + 43120 << "," // Mag damage
             << rand() % 60 + 30 << "," // Mag size
             << rand() % 438 + 180 << "," // Total size
             << rand() % 360 + 540 << "," // Fire rate (rpm)
             << (rand() % 286 + 71)/100 << "," // Reload speed (s)
             << (rand() % 551 + 348)/10 << "," // Time to empty (s)
             << rand() % 968 + 822 << "," // Body damage
             << rand() % 1262 + 1248 << "," // Precision damage
             << "\n";
    }
    // Linear Fusion Rifles
    for (int i = 0; i < 5555; i++) {
        file << "H" << ", " // Ammo type
             << "LFRi," // Weapon type
             << "LinearFusionRifle_" << i << "," // Weapon name
             << rand() % 20453 + 1006 << "," // Burst
             << rand() % 18490 + 1376 << "," // Sustained
             << rand() % 500066 + 212122 << "," // Total damage
             << rand() % 152194 + 64559 << "," // Mag damage
             << rand() % 5 + 2 << "," // Mag size
             << rand() % 17 + 5 << "," // Total size
             << rand() % 42 + 14 << "," // Fire rate (rpm)
             << (rand() % 122 + 20)/100 << "," // Reload speed (s)
             << (rand() % 237 + 20)/10 << "," // Time to empty (s)
             << rand() % 6319 + 2681 << "," // Body damage
             << rand() % 21742 + 9223 << "," // Precision damage
             << "\n";
    }
    // Pulse Rifles
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", " // Ammo type
             << "PuRi," // Weapon type
             << "PulseRifle_" << i << "," // Weapon name
             << rand() % 4418 + 433 << "," // Burst
             << rand() % 3804 + 1403 << "," // Sustained
             << "inf," // Total damage
             << rand() % 25872 + 11824 << "," // Mag damage
             << rand() % 46 + 16 << "," // Mag size
             << "inf," // Total size
             << rand() % 340 + 200 << "," // Fire rate (rpm)
             << (rand() % 9 + 12)/10 << "," // Reload speed (s)
             << "inf," // Time to empty (s)
             << rand() % 325 + 171 << "," // Body damage
             << rand() % 539 + 249 // Precision damage
             << "\n";
    }
    // Rocket Launchers
    for (int i = 0; i < 5555; i++) {
        file << "H" << ", " // Ammo type
             << "RocL," // Weapon type
             << "RocketLauncher_" << i << "," // Weapon name
             << rand() % 39760 + 10987 << "," // Burst
             << rand() % 17485 + 1518 << "," // Sustained
             << rand() % 401913 + 91167 << "," // Total damage
             << rand() % 38567 + 6090 << "," // Mag damage
             << "1," // Mag size
             << rand() % 7 + 10 << "," // Total size
             << rand() % 62 + 68 << "," // Fire rate (rpm)
             << (rand() % 210 + 40)/100 << "," // Reload speed (s)
             << (rand() % 178 + 80)/10 << "," // Time to empty (s)
             << rand() % 38567 + 6090 << "," // Body damage
             << "N/A," // Precision damage
             << "\n";
    }
    // Scout Rifles
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", " // Ammo type
             << "ScRi," // Weapon type
             << "PulseRifle_" << i << "," // Weapon name
             << rand() % 4656 + 1337 << "," // Burst
             << rand() % 3449 + 1996 << "," // Sustained
             << "inf," // Total damage
             << rand() % 46560 + 18900 << "," // Mag damage
             << rand() % 12 + 6 << "," // Mag size
             << "inf," // Total size
             << rand() % 120 + 140 << "," // Fire rate (rpm)
             << (rand() % 4 + 13)/10 << "," // Reload speed (s)
             << "inf," // Time to empty (s)
             << rand() % 816 + 757 << "," // Body damage
             << rand() % 1383 + 945 // Precision damage
             << "\n";
    }
    // Sidearms
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", " // Ammo type
             << "Sdrm," // Weapon type
             << "Sidearm_" << i << "," // Weapon name
             << rand() % 7860 + 1224 << "," // Burst
             << rand() % 6973 + 745 << "," // Sustained
             << "inf," // Total damage
             << rand() % 24340 + 28896 << "," // Mag damage
             << rand() % 18 + 22 << "," // Mag size
             << "inf," // Total size
             << rand() % 260 + 231 << "," // Fire rate (rpm)
             << (rand() % 82 + 21)/100 << "," // Reload speed (s)
             << "inf," // Time to empty (s)
             << rand() % 695 + 694 << "," // Body damage
             << rand() % 1110 + 838 // Precision damage
             << "\n";
    }
    // Shotguns
    for (int i = 0; i < 5555; i++) {
        file << "S" << ", " // Ammo type
             << "Shgu," // Weapon type
             << "Shotgun_" << i << "," // Weapon name
             << rand() % 15708 + 3108 << "," // Burst
             << rand() % 12889 + 478 << "," // Sustained
             << rand() % 297065 + 101494 << "," // Total damage
             << rand() % 102816 + 28024 << "," // Mag damage
             << rand() % 5 + 3 << "," // Mag size
             << rand() % 17 + 4 << "," // Total size
             << rand() % 55 + 25 << "," // Fire rate (rpm)
             << (rand() % 5 + 5)/10 << "," // Reload speed (s)
             << (rand() % 202 + 77)/10 << "," // Time to empty (s)
             << rand() % 14112 + 3024 << "," // Body damage
             << rand() % 15635 + 3344 << "," // Precision damage
             << "\n";
    }
    // Sniper Rifles
    for (int i = 0; i < 5555; i++) {
        file << "S" << ", " // Ammo type
             << "SnRi," // Weapon type
             << "SniperRifle_" << i << "," // Weapon name
             << rand() % 19307 + 3933 << "," // Burst
             << rand() % 15140 + 1638 << "," // Sustained
             << rand() % 348600 + 37536 << "," // Total damage
             << rand() % 69720 + 22316 << "," // Mag damage
             << rand() % 4 + 3 << "," // Mag size
             << rand() % 22 + 13 << "," // Total size
             << rand() % 72 + 68 << "," // Fire rate (rpm)
             << (rand() % 158 + 40)/10 << "," // Reload speed (s)
             << (rand() % 192 + 40)/10 << "," // Time to empty (s)
             << rand() % 2895 + 1702 << "," // Body damage
             << rand() % 9960 + 6129 << "," // Precision damage
             << "\n";
    }
    // Sub Machine Guns
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", " // Ammo type
             << "SuMG," // Weapon type
             << "SubMachineGun_" << i << "," // Weapon name
             << rand() % 8180 + 1075 << "," // Burst
             << rand() % 6149 + 314 << "," // Sustained
             << "inf," // Total damage
             << rand() % 22581 + 4413 << "," // Mag damage
             << rand() % 27 + 10 << "," // Mag size
             << "inf," // Total size
             << rand() % 600 + 300 << "," // Fire rate (rpm)
             << (rand() % 119 + 21)/100 << "," // Reload speed (s)
             << "inf," // Time to empty (s)
             << rand() % 373 + 210 << "," // Body damage
             << rand() % 579 + 239 // Precision damage
             << "\n";
    }
    // Swords
    for (int i = 0; i < 5555; i++) {
        file << "S" << ", " // Ammo type
             << "SnRi," // Weapon type
             << "SniperRifle_" << i << "," // Weapon name
             << rand() % 20962 + 2029 << "," // Burst
             << rand() % 20962 + 2029 << "," // Sustained
             << rand() % 436262 + 266024 << "," // Total damage
             << "N/A," // Mag damage
             << "N/A," // Mag size
             << rand() % 44 + 26 << "," // Total size
             << rand() % 50 + 78 << "," // Fire rate (rpm)
             << (rand() % 166 + 86)/10 << "," // Reload speed (s)
             << (rand() % 191 + 109)/10 << "," // Time to empty (s)
             << rand() % 9254 + 4626 << "," // Body damage
             << rand() % 27760 + 13880 << "," // Heavy damage
             << "\n";
    }
    // Trace Rifles
    for (int i = 0; i < 5555; i++) {
        file << "S" << ", " // Ammo type
             << "TrRi," // Weapon type
             << "TraceRifle" << i << "," // Weapon name
             << rand() % 10170 + 933 << "," // Burst
             << rand() % 8489 + 1638 << "," // Sustained
             << rand() % 397308 + 37536 << "," // Total damage
             << rand() % 70512 + 22316 << "," // Mag damage
             << rand() % 104 + 20 << "," // Mag size
             << rand() % 586 + 100 << "," // Total size
             << "900," // Fire rate (rpm)
             << (rand() % 144 + 40)/10 << "," // Reload speed (s)
             << (rand() % 449 + 60)/10 << "," // Time to empty (s)
             << rand() % 505 + 122 << "," // Body damage
             << rand() % 678 + 326 << "," // Precision damage
             << "\n";
    }

    cout << "Data generated, closing file stream." << endl;

    file.close();
    return 0;
}

 */