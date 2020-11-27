cmake_minimum_required(VERSION 2.8.8)

set(This finalProject)

#project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT ON)

enable_testing()

add_subdirectory(googletest googletest)

set(Headers
    student.hpp
    domesticStudent.hpp
    internationalStudent.hpp
    TOEFLScore.hpp
    StudentList.hpp
    StringHelper.hpp
)

set(Sources
    student.cpp
    domesticStudent.cpp
    internationalStudent.cpp
    TOEFLScore.cpp
    StudentList.cpp
    StringHelper.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)


