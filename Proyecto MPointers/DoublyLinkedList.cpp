//
// Created by joelg on 11/9/2024.
//

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

#include "DoublyNode.h"
#include <iostream>

class DoublyLinkedList {
private:
    DoublyNode* head;

public:
    // Constructor de la lista doblemente enlazada
    DoublyLinkedList() : head(nullptr) {}

    // Método para agregar un nodo al final de la lista
    void add(int value) {
        DoublyNode* newNode = new DoublyNode(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            DoublyNode* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    // Método para imprimir la lista desde el inicio
    void printList() const {
        DoublyNode* temp = head;
        while (temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Método para imprimir la lista desde el final
    void printListReverse() const {
        if (head == nullptr) return;
        DoublyNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        while (temp != nullptr) {
            std::cout << temp->value << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }
};

#endif
