//
// Created by joelg on 10/9/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <iostream>

class LinkedList {
private:
    Node* head;

public:
    // Constructor de la lista enlazada simple
    LinkedList() : head(nullptr) {}

    // Método para agregar un nodo al final de la lista
    void add(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Método para imprimir la lista enlazada simple
    void printList() const {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

#endif
