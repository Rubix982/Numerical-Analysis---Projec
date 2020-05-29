cmake_minimum_required(VERSION 3.15)

project(NC)
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_compile_options(-O2 -Wall -Wextra)
add_link_options(-lpthread)

add_executable(NC src/newtonCentral.cpp)