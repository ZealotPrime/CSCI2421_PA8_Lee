cmake_minimum_required(VERSION 3.3)
project(CSCI2421_PA8_Lee)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp User.h User.cpp)
add_executable(CSCI2421_PA8_Lee ${SOURCE_FILES})