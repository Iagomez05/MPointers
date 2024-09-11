cmake_minimum_required(VERSION 3.28)
project(Proyecto_MPointers)

set(CMAKE_CXX_STANDARD 23)

add_executable(Proyecto_MPointers main.cpp
        MPointer.cpp
        MPointer.h
        MPointerGC.cpp
        MPointerGC.h
        Node.cpp
        Node.h
        LinkedList.cpp
        LinkedList.h
        DoublyLinkedList.cpp
        DoublyLinkedList.h
        DoublyNode.cpp
        DoublyNode.h)
