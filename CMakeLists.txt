cmake_minimum_required(VERSION 3.5)
project(determinant LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(COMMON_SOURCES
  matrix.hpp
  matrix.cpp
)

add_executable(determinant ${COMMON_SOURCES} main.cpp)
