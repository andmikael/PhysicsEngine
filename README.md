# PhysicsEngine
## DEMO

https://github.com/user-attachments/assets/2e741d0e-d676-4f0c-af3d-8a60bfd41cc9

C++ Physics simulation engine for collision detection. It uses SFML for window management and and rendering.

Objects use verlet integration to calculate object motions

To run the program in linux:
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
