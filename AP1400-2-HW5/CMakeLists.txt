cmake_minimum_required(VERSION 3.13)
project(AP)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)
find_package(Curses REQUIRED)

include_directories(include/ ${CURSES_INCLUDE_DIR})

add_executable(main
        src/main.cpp
        src/unit_test.cpp
        src/espresso_based.cpp
        src/cappuccino.cpp
        src/mocha.cpp
)
target_link_libraries(main
        GTest::GTest
        GTest::Main
        ${CURSES_LIBRARIES}
)