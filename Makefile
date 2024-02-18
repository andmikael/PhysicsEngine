CXX = g++
CXXFLAGS = -Wall -std=c++20 -I. -Isfml/include

LDLIBS = -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-network

# Explicitly list all source files:
SRCS = main.cpp circlesolver.cpp renderer.cpp

# Object files (built implicitly, no need for separate rules):
OBJS = $(SRCS:.cpp=.o)

# Executable file:
MAIN = main

# Build rule for the executable:
$(MAIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

# Object file dependency rules:

circlesolver.o: circlesolver.cpp
	$(CXX) -c $<

renderer.o: renderer.cpp circlesolver.h
	$(CXX) -c $<

main.o: main.cpp circlesolver.h renderer.h
	$(CXX) -c $<

# Clean rule:
clean:
	rm -f $(OBJS) $(MAIN)