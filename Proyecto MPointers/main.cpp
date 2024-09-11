#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include <iostream>

int main() {

    // Prueba para la lista enlazada simple
    LinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);
    std::cout << "Lista enlazada simple: ";
    list.printList(); // Output: 10 20 30

    // Prueba para la lista doblemente enlazada
    DoublyLinkedList dList;
    dList.add(10);
    dList.add(20);
    dList.add(30);
    std::cout << "Lista doblemente enlazada: ";
    dList.printList(); // Output: 10 20 30

    std::cout << "Lista doblemente enlazada (reversa): ";
    dList.printListReverse(); // Output: 30 20 10

    return 0;
}
