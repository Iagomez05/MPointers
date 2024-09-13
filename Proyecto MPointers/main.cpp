#include <iostream>
#include "MPointer.h" // Incluir el archivo donde está implementado MPointer
#include "DoublyLinkedList.h"

int main() {
    // Crear una lista de enteros
    DoublyLinkedList<int> list;

    // Crear MPointers de valores
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 4;
    MPointer<int> ptr2 = MPointer<int>::New();
    *ptr2 = 2;
    MPointer<int> ptr3 = MPointer<int>::New();
    *ptr3 = 5;
    MPointer<int> ptr4 = MPointer<int>::New();
    *ptr4 = 1;
    MPointer<int> ptr5 = MPointer<int>::New();
    *ptr5 = 3;

    // Agregar los MPointers a la lista
    list.append(*ptr1);
    list.append(*ptr2);
    list.append(*ptr3);
    list.append(*ptr4);
    list.append(*ptr5);

    std::cout << "Lista antes de ordenar: ";
    list.printList();

    // Prueba de BubbleSort
    std::cout << "\nOrdenando con BubbleSort..." << std::endl;
    list.bubbleSort();
    std::cout << "Lista después de BubbleSort: ";
    list.printList();

    // Reinicializar la lista para otra prueba
    DoublyLinkedList<int> list2;
    list2.append(*ptr1);
    list2.append(*ptr2);
    list2.append(*ptr3);
    list2.append(*ptr4);
    list2.append(*ptr5);

    // Prueba de InsertionSort
    std::cout << "\nOrdenando con InsertionSort..." << std::endl;
    list2.insertionSort();
    std::cout << "Lista después de InsertionSort: ";
    list2.printList();

    // Reinicializar la lista para otra prueba
    DoublyLinkedList<int> list3;
    list3.append(*ptr1);
    list3.append(*ptr2);
    list3.append(*ptr3);
    list3.append(*ptr4);
    list3.append(*ptr5);

    // Prueba de QuickSort
    std::cout << "\nOrdenando con QuickSort..." << std::endl;
    list3.quickSort();
    std::cout << "Lista después de QuickSort: ";
    list3.printList();

    return 0;
}
