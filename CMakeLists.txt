cmake_minimum_required(VERSION 3.27)
project(Destiny2_Weapon_DPS)

set(CMAKE_CXX_STANDARD 14)

add_executable(Destiny2_Weapon_DPS
        src/main.cpp
        src/Arsenal.h
        src/Weapon.h
        src/Arsenal.cpp
        src/Weapon.cpp
        src/Sort.cpp
        "src/Data Generator.cpp")
