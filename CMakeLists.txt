cmake_minimum_required(VERSION 3.12)
project(multi)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE
        Engine/MemoryStream.cpp
        Engine/RoboMath.cpp
        )

set(HEADER
        Engine/MemoryStream.h
        Engine/RoboMath.h
        )

set(TEST
        Tests/testRoboMath.cpp
        )

add_executable(multi main.cpp ${SOURCE} ${HEADER})
add_executable(tests ${TEST} ${SOURCE} ${HEADER})

target_link_libraries(tests gtest gtest_main)