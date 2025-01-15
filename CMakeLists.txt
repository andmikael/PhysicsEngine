cmake_minimum_required(VERSION 3.25)

project(physicsengine LANGUAGES CXX)

add_executable(game main.cpp circlesolver.cpp renderer.cpp)

find_package(SFML COMPONENTS system window graphics) 

target_link_libraries(game PRIVATE sfml-graphics sfml-system sfml-window)

target_compile_features(game PRIVATE cxx_std_23)