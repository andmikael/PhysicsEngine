# PhysicsEngine
A small C++ program used to simulate rudamentary object physics and collision using SFML library in Qt Creator.


Currently to run PhysicsEngine you need to use Qt Creator in Linux or Windows 
The plan is to update this repository with a correct Makefile so it can be compiled without needing Qt Creator.

It uses verlet integration to calculate object motion.

To run the program in linux:
1. install SFML dev library
   ```
   sudo apt-get install libsfml-dev
   ```
2. clone the project to your preferred destination

3. add SFML libraries to the project's .pro file
   ```
   LIBS += -lsfml-audio
   LIBS += -lsfml-graphics
   LIBS += -lsfml-network
   LIBS += -lsfml-window
   LIBS += -lsfml-system
   ```
4. run the project

To run the program in windows:
1. download SFML source code
2. compile SFML library
3. In the .pro file, replace commented out paths with the paths from the compiled library:
   INCLUDE- and DEPENDPATH with SFML/include source code path.
   LIBS with the compild SFML libraries
   uncomment CONFIG lines in .pro file
5. Copy compiled .dll's from the compiled library to projects debug and release build directories // TODO: add picture or file names for the dll's
6. run the project
