#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <iostream>
#include "LinkedList.h"

// Declaración adelantada de la clase MPointer
template <typename T>
class MPointer;

template <typename T>
// Esta clase "MPointerGC" utiliza la clase LinkedList para gestiona los punteros de MPointer
class MPointerGC {

public:
    // Obtener la instancia única de MPointerGC (patrón Singleton)
    static MPointerGC* getInstance() {
        if (!instance) {
            instance = new MPointerGC();
        }
        return instance;
    }

    // Registrar un MPointer en el GC
    void registerPointer(MPointer<T>* ptr) {
        pointers.add(ptr);
        std::cout << "MPointerGC::registerPointer - MPointer registrado\n";
    }

    // Eliminar un MPointer del GC
    void unregisterPointer(MPointer<T>* ptr) {
        pointers.remove(ptr);
        std::cout << "MPointerGC::unregisterPointer - MPointer eliminado\n";
    }

    // Liberar todos los recursos
    void releaseAllResources() {
        pointers.clear();
        std::cout << "MPointerGC::releaseAllResources - Todos los recursos liberados\n";
    }

    // Mostrar el estado actual de los MPointer
    void debug() const {
        std::cout << "\nMPointerGC::debug() - Estado actual del Garbage Collector\n";

        // Usa typename para acceder a Node dentro de la plantilla LinkedList
        typename LinkedList<MPointer<T>>::Node* current = pointers.getHead();

        while (current != nullptr) {
            std::cout << "|> MPointer en dirección: " << current->mpointer << std::endl;
            current = current->next;
        }
    }

private:
    MPointerGC() = default;

    LinkedList<MPointer<T>> pointers;  // Lista enlazada de MPointer

    static MPointerGC* instance;
};

// Inicialización de la instancia única del GC
template <typename T>
MPointerGC<T>* MPointerGC<T>::instance = nullptr;

#endif // MPOINTERGC_H