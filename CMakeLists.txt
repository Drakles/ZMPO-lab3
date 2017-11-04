cmake_minimum_required(VERSION 3.8)
project(Lista3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CTree.cpp CTree.h CNode.cpp CNode.h)
add_executable(Lista3 ${SOURCE_FILES})