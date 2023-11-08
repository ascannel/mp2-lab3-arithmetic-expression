cmake_minimum_required(VERSION 2.8)

project(mp2-lab3-arithmetic-expression)

include_directories(include)

add_executable(mp2-lab3-arithmetic-expression src/main.cpp src/expressions.cpp include/expressions.hpp)
