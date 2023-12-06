cmake_minimum_required(VERSION 3.21.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(AOC2023)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING
      "Choose the type of build, options are: Debug Release."
      FORCE)
endif(NOT CMAKE_BUILD_TYPE)

set(BUILD_STATIC FALSE CACHE STRING "Set this to link external libraries statically")

if(CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -g")
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

add_executable(DayOneQ1 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayOne/DayOneQ1.cpp)
add_executable(DayOneQ2 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayOne/DayOneQ2.cpp)
add_executable(DayTwoQ1 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayTwo/DayTwoQ1.cpp)
add_executable(DayTwoQ2 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayTwo/DayTwoQ2.cpp)
add_executable(DayThreeQ1 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayThree/DayThreeQ1.cpp)
add_executable(DayThreeQ2 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayThree/DayThreeQ2.cpp)
add_executable(DayFourQ1 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayFour/DayFourQ1.cpp)
add_executable(DayFourQ2 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayFour/DayFourQ2.cpp)
add_executable(DayFiveQ1 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayFive/DayFiveQ1.cpp)
add_executable(DayFiveQ2 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayFive/DayFiveQ2.cpp)
add_executable(DaySixQ1 ${CMAKE_CURRENT_SOURCE_DIR}/src/DaySix/DaySixQ1.cpp)
add_executable(DaySixQ2 ${CMAKE_CURRENT_SOURCE_DIR}/src/DaySix/DaySixQ2.cpp)
