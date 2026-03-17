cmake_minimum_required(VERSION 3.20)
project(es1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(SOURCES Es1.cpp)

add_executable(es1 ${SOURCES})
