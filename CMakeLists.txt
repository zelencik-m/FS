cmake_minimum_required(VERSION 3.10)
project(SDL2_Project)

# Find SDL2 package using CMake
find_package(SDL2 REQUIRED)

# Add source files
add_executable(sdl2_project src/main.cpp)

# Link SDL2
target_include_directories(sdl2_project PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(sdl2_project PRIVATE ${SDL2_LIBRARIES})
