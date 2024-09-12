#include <iostream>
#include "MPointer.h" // Incluir el archivo donde está implementado MPointer
#include "MPointerGC.h" // Incluir MPointerGC si no está incluido en MPointer.h

int main() {
    // Crear el primer MPointer y registrarlo en el GC
    MPointer<int> ptr1 = MPointer<int>::New();
    *ptr1 = 10; // Asignar un valor al MPointer
    std::cout << "Valor en ptr1: " << *ptr1 << std::endl;

    // Crear un segundo MPointer
    MPointer<int> ptr2 = MPointer<int>::New();
    *ptr2 = 20;
    std::cout << "Valor en ptr2: " << *ptr2 << std::endl;

    // Crear un tercer MPointer que apunte al segundo
    MPointer<int> ptr3 = ptr2; // Copia el puntero
    std::cout << "Valor en ptr3 (igual que ptr2): " << *ptr3 << std::endl;

    // Liberar un puntero (destructor se llama automáticamente al final del bloque)
    ptr2 = nullptr; // Debería disminuir el contador de referencias de ptr3

    // Mostrar el estado actual del Garbage Collector
    MPointerGC<int>::getInstance()->debug();

    // Salir del programa, los destructores de ptr1 y ptr3 deberían liberarse
    return 0;
}
