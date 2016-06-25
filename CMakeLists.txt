###########################################################
## CMAKE SETUP
###########################################################

cmake_minimum_required(VERSION 3.2)
project(bitset)

###########################################################
## DEPENDENCIES
###########################################################

add_subdirectory(vector)

###########################################################
## LIBRARY
###########################################################

add_library(bitset SHARED bitset.c)
add_library(bitset-static STATIC bitset.c)

target_link_libraries(bitset vector)
target_link_libraries(bitset-static vector-static)

###########################################################
## EXECUTABLES
###########################################################

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(bitset-test ${CMAKE_CURRENT_SOURCE_DIR}/test/test.c)
add_executable(bitset-example ${CMAKE_CURRENT_SOURCE_DIR}/test/example.c)

target_link_libraries(bitset-test bitset)
target_link_libraries(bitset-example bitset)

###########################################################
## COMPILER FLAGS
###########################################################

target_compile_options(bitset PUBLIC -O3 -Os -std=c99 -g)
