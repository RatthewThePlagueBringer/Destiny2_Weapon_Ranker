// There are only around 300 unique weapon types in Destiny 2 which does not meet the requirement of 100,000 data points
// Our solution is using the parameters of the real weapons, we will randomly generate an extra 999,700 weapon variants

#include <fstream>

using namespace std;

void generateData() {
    fstream file;
    file.open("weapons.csv", ios::out | ios::app);

    // file << stuff << ","

    // 18 weapon subfamilies, 5,555 randomly generated weapons per subfamily
    // Auto Rifles
    for (int i = 0; i < 5555; i++) {
        file << "P" << ", "
                << "AuRi," // Weapon types
                << "N/A," // Lucent stacks
                << "AutoRifle_" << i << "," // Weapon name
                << rand() % 4604 + 5436 << "," // Burst
                << rand() % 4823 + 5217 << "," // Sustained
                << "inf," // Total damage
                << rand() % 20706 + 28646 << "," // Mag damage
                << rand() % 34 + 26 << "," // Mag size
                << "inf," // Total size
                << "<360-720>," // Fire rate (rpm)
                << "<0.9-1.2>" // Reload speed (s)
                << "inf," // Time to empty (s)
                << "<346-624>," // Body damage
                << "<518-997>," // Precision damage
                << "\n"
    }
}