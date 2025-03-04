Developers: Benjamin Levy (belevy@wpi.edu) and Sam Randa (swranda@wpi.edu)

Platform: Windows

Files: All files for Crate Craze can be found in the source directory. All engine files can be found in the "dragonfly" folder.

Code Structure: game.cpp starts and stops the game. The "dragonfly" folder contains the header and source files for the engine, and are referred to in the game code using nested pathways (e.g. #include "dragonfly/GameManager.h").

How to Compile: Open the project solution in Visual Studio and build the game. Run the game from Visual Studio (game.cpp will run the "main" function that loads the game).