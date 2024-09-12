cmake_minimum_required(VERSION 3.28)
project(Proyecto_MPointers)

set(CMAKE_CXX_STANDARD 23)

add_executable(Proyecto_MPointers main.cpp
        MPointer.h
        MPointerGC.h
        LinkedList.h
)
