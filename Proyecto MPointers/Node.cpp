//
// Created by joelg on 10/9/2024.
//

#ifndef NODE_H
#define NODE_H

// Clase básica para nodo en una lista enlazada simple
class Node {
public:
    int value;
    Node* next;

    // Constructor del nodo
    Node(int val) : value(val), next(nullptr) {}
};

#endif
