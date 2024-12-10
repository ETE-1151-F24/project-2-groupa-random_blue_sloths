cmake_minimum_required(VERSION 3.31)

set(1stProject)

project(${Ths} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(googletest)

set(Headers 
    Inventory.hpp
)
set(Sources 
    Inventory.hpp
)
add_library(${This} STATIC ${Headers})

add_subdirectory(test)