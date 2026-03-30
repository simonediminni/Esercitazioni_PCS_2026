cmake_minimum_required(VERSION 3.20)
project(es3) 

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")

set(SOURCES es3.cpp)
add_executable(es3 ${SOURCES})
