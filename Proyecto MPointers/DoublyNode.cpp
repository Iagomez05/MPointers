//
// Created by joelg on 11/9/2024.
//

#ifndef DOUBLYNODE_H
#define DOUBLYNODE_H

// Clase básica para nodo en una lista doblemente enlazada
class DoublyNode {
public:
    int value;
    DoublyNode* next;
    DoublyNode* prev;

    // Constructor del nodo
    DoublyNode(int val) : value(val), next(nullptr), prev(nullptr) {}
};

#endif
