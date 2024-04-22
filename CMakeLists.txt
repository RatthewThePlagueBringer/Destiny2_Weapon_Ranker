cmake_minimum_required(VERSION 3.27)
project(Destiny2_Weapon_Ranker)

set(CMAKE_CXX_STANDARD 14)

add_executable(Destiny2_Weapon_Ranker
        src/main.cpp
        src/Arsenal.h
        src/Weapon.h
        src/Arsenal.cpp
        src/Weapon.cpp
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include/SFML)
target_link_libraries(Destiny2_Weapon_Ranker sfml-system sfml-window sfml-graphics sfml-audio)