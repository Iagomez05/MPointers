#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "MPointer.h"

template <typename T>
class DoublyLinkedList {
public:
    struct Node {
        T data;  // Cambiado para almacenar T directamente, no MPointer<T>
        MPointer<Node> prev;
        MPointer<Node> next;
    };

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Añadir un nodo al final de la lista
    void append(const T& value) {
        MPointer<Node> newNode = MPointer<Node>::New();
        newNode->data = value;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }

        tail = newNode;
    }

    // Imprimir los elementos de la lista
    void printList() const {
        MPointer<Node> current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";  // Accede a los datos directamente
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Algoritmo BubbleSort
    void bubbleSort() {
        if (!head) return;  // Si la lista está vacía, no hacemos nada

        bool swapped;
        do {
            swapped = false;
            MPointer<Node> current = head;

            while (current->next != nullptr) {
                if (current->data > current->next->data) {  // Comparar datos directamente
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    // Algoritmo InsertionSort
    void insertionSort() {
        if (!head) return;  // Si la lista está vacía, no hacemos nada

        MPointer<Node> current = head->next;

        while (current != nullptr) {
            T key = current->data;
            MPointer<Node> prev = current->prev;

            while (prev != nullptr && prev->data > key) {
                prev->next->data = prev->data;
                prev = prev->prev;
            }

            if (prev == nullptr) {
                head->data = key;
            } else {
                prev->next->data = key;
            }

            current = current->next;
        }
    }

    // Función auxiliar para hacer el intercambio de datos entre dos nodos
    void swapData(MPointer<Node> a, MPointer<Node> b) {
        T temp = a->data;
        a->data = b->data;
        b->data = temp;
    }

    // Función para particionar la lista en QuickSort
    MPointer<Node> partition(MPointer<Node> low, MPointer<Node> high) {
        T pivot = high->data;
        MPointer<Node> i = low->prev;

        for (MPointer<Node> j = low; j != high; j = j->next) {
            if (j->data <= pivot) {
                i = (i == nullptr) ? low : i->next;
                swapData(i, j);
            }
        }

        i = (i == nullptr) ? low : i->next;
        swapData(i, high);
        return i;
    }

    // Función recursiva para aplicar QuickSort
    void quickSort(MPointer<Node> low, MPointer<Node> high) {
        if (high != nullptr && low != high && low != high->next) {
            MPointer<Node> p = partition(low, high);
            quickSort(low, p->prev);
            quickSort(p->next, high);
        }
    }

    // Función principal de QuickSort
    void quickSort() {
        MPointer<Node> high = tail;
        quickSort(head, high);
    }

private:
    MPointer<Node> head;
    MPointer<Node> tail;
};

#endif
