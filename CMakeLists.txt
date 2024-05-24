cmake_minimum_required(VERSION 3.28)
project(DAACODING)

set(CMAKE_CXX_STANDARD 98)

add_executable(SHORTESTPATH "SHORTEST PATH/main.cpp")
add_executable(GRAPHMATRIX "GRAPH MATRIX/main.cpp"
        "MERGE SORT/linkedlist.h"
        "MERGE SORT/node.h")
add_executable(QUICKSORT "QUICK SORT/main.cpp")
add_executable(REDLACK "RED BLACK/main.cpp")
add_executable(HASHTABLE "HASHTABLE/main.cpp")
add_executable(SPLAYTREE "SPLAY TREE/main.cpp")
add_executable(MERGESORT "MERGE SORT/main.cpp")
