# PhysicsEngine
A small C++ program used to simulate rudamentary object physics and collision using SFML library in Qt Creator.

It uses verlet integration to calculate object motion.

To run the program in linux:
1. install SFML dev library
   ```
   sudo apt-get install libsfml-dev
   ```
2. build the project and run it
   ```
   cmake -B ./build
   cmake --build build
   ./build/game
   ```

4. add SFML libraries to the project's .pro file
   ```
   LIBS += -lsfml-audio
   LIBS += -lsfml-graphics
   LIBS += -lsfml-network
   LIBS += -lsfml-window
   LIBS += -lsfml-system
   ```
5. run the project

To run the program in windows:
1. download SFML source code
2. compile SFML library
3. In the .pro file, replace commented out paths with the paths from the compiled library:
   INCLUDE- and DEPENDPATH with SFML/include source code path.
   LIBS with the compild SFML libraries
   uncomment CONFIG lines in .pro file
5. Copy compiled .dll's from the compiled library to projects debug and release build directories
6. run the project
