cmake_minimum_required(VERSION 2.8.8)

set(This tests)

set(Sources
    studentTest.cpp
    studentListTest.cpp
)

add_executable(${This} ${Sources})
target_link_libraries(${This} PUBLIC
    gtest_main
    finalProject
)

add_test(
    NAME ${This}
    COMMAND ${This}
)