cmake_minimum_required(VERSION 3.20)
project(esercitazione8)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")
# Creo il target per l'eseguibile principale del mio progetto software
set(SRC_test test.cpp)
add_executable(test_eseguibile ${SRC_test})


enable_testing()
add_test(NAME graph COMMAND test_eseguibile)




