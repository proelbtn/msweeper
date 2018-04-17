cmake_minimum_required(VERSION 3.10)
project(msweeper)

set(CMAKE_CXX_STANDARD 11)

set(SRCS
        main.cpp
        src/msweeper.cpp)

include_directories(./include)

add_executable(msweeper ${SRCS})