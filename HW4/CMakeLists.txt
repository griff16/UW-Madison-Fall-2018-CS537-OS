cmake_minimum_required(VERSION 3.12)
project(HW4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HW4
        advanced_testcase4.c
        537malloc.c
        537malloc.h
        AVLTree.c
        AVLTree.h
        tuple.c
        tuple.h)
