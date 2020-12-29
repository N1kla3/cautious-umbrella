cmake_minimum_required(VERSION 3.17)
project(multi)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(SOURCE
        Engine/MemoryStream.cpp
        Engine/RoboMath.cpp
        Engine/GameObject.cpp)

set(HEADER
        Engine/MemoryStream.h
        Engine/RoboMath.h
        Engine/LinkingContext.hpp
        Engine/GameObject.h Engine/ObjectCreationRegistry.hpp)

set(TEST
        Tests/testRoboMath.cpp
        Tests/testMemoryStream.cpp
        Tests/testLinkingContext.cpp
        Tests/testCreationRegistry.cpp)

add_executable(multi main.cpp ${SOURCE} ${HEADER})
add_executable(tests ${TEST} ${SOURCE} ${HEADER})

target_link_libraries(tests gtest gtest_main)