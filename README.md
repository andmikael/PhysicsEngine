# PhysicsEngine

https://github.com/user-attachments/assets/8ec3b764-5246-4193-ab32-dfd1415137ce

## About
C++ Physics simulation engine for collision detection. It uses SFML for window management and rendering and ImGui for settings menu. Verlet integration is used to calculate object motions.

## Compiling and running the program
To run the program in linux:

> [!NOTE]
> libsfml-dev version must be 2.6.1, since SFML ver. 3.0.0 changes function calls for window management which breaks this app
1. install SFML dev library
   ```
   sudo apt-get install libsfml-dev
   ```
2. build the project and run it
   ```
   cmake -B ./build
   cmake --build build
   ./build/bin/game
   ```

If using Qt creator

1. add SFML libraries to the project's .pro file
   ```
   LIBS += -lsfml-graphics
   LIBS += -lsfml-window
   LIBS += -lsfml-system
   ```
2. run the project

To run the program in windows:
1. download SFML source code
2. compile SFML library
3. In the .pro file, replace commented out paths with the paths from the compiled library:
   INCLUDE- and DEPENDPATH with SFML/include source code path.
   LIBS with the compild SFML libraries
   uncomment CONFIG lines in .pro file
5. Copy compiled .dll's from the compiled library to projects debug and release build directories
6. run the project
