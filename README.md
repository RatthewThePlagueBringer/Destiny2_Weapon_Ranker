# Destiny2_Weapon_DPS
This is a program that was designed for COP 3530 at the University of Florida with the goal of using the Destiny API to find the best weapons for sustained or burst DPS in the current Destiny 2 meta.

## SFML INSTRUCTIONS
at [https://www.sfml-dev.org/tutorials/2.6/](https://www.sfml-dev.org/tutorials/2.6/).
  
Select the correct "Getting Started" link for your system.
  
Using SFML Version 2.5.1.

### ADDITIONAL DEPENDENCIES
for Debug:
    
      sfml-graphics-s-d.lib	
      sfml-window-s-d.lib
      sfml-system-s-d.lib
      opengl32.lib
      freetype.lib
      opengl32.lib
      winmm.lib
      gdi32.lib
      winmm.lib
      
for Release:

      sfml-graphics-s.lib	
      sfml-window-s.lib
      sfml-system-s.lib
      opengl32.lib
      freetype.lib
      opengl32.lib
      winmm.lib
      gdi32.lib
      winmm.lib

## DATA GENERATOR INSTRUCTIONS
Due to the smaller sample size of our weapons.csv, we included a data generator to test the program's capabilities with larger datasets.
Run DataGenerator.cpp on weapons.csv before running main.cpp.
Since DataGenerator.cpp has main function, we suggest:
- Generating data in a separate folder from main.cpp and moving weapons.csv into the folder with main after finishing the data generation.
- Commenting out main.cpp and running DataGenerator.cpp, then commenting out DataGenerator.cpp and uncommenting main.cpp.
