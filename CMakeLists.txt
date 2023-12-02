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
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")
endif()

add_executable(DayOneQ1 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayOne/DayOneQ1.cpp)
add_executable(DayOneQ2 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayOne/DayOneQ2.cpp)
add_executable(DayTwoQ1 ${CMAKE_CURRENT_SOURCE_DIR}/src/DayTwo/DayTwoQ1.cpp)
