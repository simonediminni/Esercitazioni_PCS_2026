cmake_minimum_required(VERSION 3.20)
project(esercitazione5)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")
# Creo il target per l'eseguibile principale del mio progetto software
set(SRC_test_sorts timecounter.cpp measure_sorts.cpp)
add_executable(measure_sorts ${SRC_test_sorts})

##Creo i target per gli eseguibili che effettueranno i test unitari
add_executable(test_mergesort test_mergesort.cpp)

add_executable(test_quicksort test_quicksort.cpp)

enable_testing()
add_test(NAME mergesort COMMAND test_mergesort)
add_test(NAME quicksort COMMAND test_quicksort)



