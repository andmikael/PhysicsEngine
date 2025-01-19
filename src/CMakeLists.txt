cmake_minimum_required(VERSION 3.25)

#compile program to build/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

#FetchContent_Declare(SFML
#    GIT_REPOSITORY https://github.com/SFML/SFML.git
#    GIT_TAG 2.6.1
#    GIT_SHALLOW ON
#    EXCLUDE_FROM_ALL
#    SYSTEM)
#FetchContent_MakeAvailable(SFML)

find_package(SFML COMPONENTS system window graphics audio network) 

FetchContent_Declare(ImGui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG v1.91.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui)
FetchContent_GetProperties(ImGui SOURCE_DIR IMGUI_DIR)

set(IMGUI_SFML_FIND_SFML OFF)
FetchContent_Declare(ImGui-SFML
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG v2.6.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(ImGui-SFML)

add_executable(game main.cpp circlesolver.cpp renderer.cpp circlecollider.cpp segment.cpp)
target_link_libraries(game PRIVATE sfml-graphics sfml-system sfml-window sfml-audio sfml-network ImGui-SFML::ImGui-SFML)
target_compile_features(game PRIVATE cxx_std_23)