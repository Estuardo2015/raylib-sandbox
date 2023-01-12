cmake_minimum_required(VERSION 3.24)

project(raylib-sandbox)

set(CMAKE_CXX_STANDARD 14)

include_directories(raylib-sandbox ./include ./src/)
add_executable(raylib-sandbox ./src/main.cpp)
target_link_libraries(raylib-sandbox $ENV{RAYLIB_PATH} opengl32 gdi32 winmm)