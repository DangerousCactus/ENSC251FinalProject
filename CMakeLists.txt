cmake_minimum_required(VERSION 3.16.3)

set(This finalProject)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT ON)

enable_testing()

add_subdirectory(/usr/src/googletest/googletest googletest)

set(Headers
    student.hpp
    domesticStudent.hpp
    internationalStudent.hpp
    TOEFLScore.hpp
)

set(Sources
    student.cpp
    domesticStudent.cpp
    internationalStudent.cpp
    TOEFLScore.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)


