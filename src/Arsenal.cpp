#include "Arsenal.h"
#include <fstream>

Arsenal::Arsenal() {
    size = 0;

    fstream file;
    file.open("weapons.csv", ios::in);
}
