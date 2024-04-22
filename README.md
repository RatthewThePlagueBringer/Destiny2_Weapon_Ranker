# Destiny2_Weapon_DPS
This is a program that was designed for COP 3530 at the University of Florida with the goal of using the Destiny API to find the best weapons for sustained or burst DPS in the current Destiny 2 meta.

## SFML INSTRUCTIONS
**THIS PROGRAM REQUIRES SFML TO RUN**

Using [SFML Version 2.5.1](https://www.sfml-dev.org/download/sfml/2.5.1/).

Install instructions can be found at [https://www.sfml-dev.org/tutorials/2.5/](https://www.sfml-dev.org/tutorials/2.5/).
  
Select the correct "Getting Started" link for your system.

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
Due to the smaller sample size of our weapons.csv, we included a data generator to test the program's capabilities with larger datasets. It is not necessary to generate data for the program to run. DataGenerator.cpp only increases the size of the dataset.
Run DataGenerator.cpp on weapons.csv before running main.cpp.
Since DataGenerator.cpp has a main function, we suggest:
- Generating data in a separate folder from main.cpp and moving weapons.csv into the folder with main after finishing the data generation.
- Commenting out main.cpp and running DataGenerator.cpp, then commenting out DataGenerator.cpp and uncommenting main.cpp.

## CREDITS
Weapon Statistics: [https://bungie-net.github.io/](https://bungie-net.github.io/)

Weapon Damage & Reload Speed: [https://www.reddit.com/r/DestinyTheGame/comments/12yswaf/destiny_2_quantum_damageics_new_dps_spreadsheet/](https://www.reddit.com/r/DestinyTheGame/comments/12yswaf/destiny_2_quantum_damageics_new_dps_spreadsheet/)

Font: [https://www.1001fonts.com/roboto-condensed-font.html](https://www.1001fonts.com/roboto-condensed-font.html) *(Roboto Condensed Light)*

Search Bar: [https://www.vecteezy.com/png/11888174-shadow-rectangle-neumorphic-rectangle](https://www.vecteezy.com/png/11888174-shadow-rectangle-neumorphic-rectangle)
