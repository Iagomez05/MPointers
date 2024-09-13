#ifndef MPOINTERGC_H
#define MPOINTERGC_H

#include <iostream>
#include "LinkedList.h"

// Declaración adelantada de la clase MPointer
template <typename T>
class MPointer;

template <typename T>
// Esta clase "MPointerGC" utiliza la clase LinkedList para gestionar los punteros de MPointer
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

    // Eliminar un MPointer del GC usando el id
    void releasePointer(int id) {
        typename LinkedList<MPointer<T>>::Node* current = pointers.getHead();
        typename LinkedList<MPointer<T>>::Node* prev = nullptr;

        while (current != nullptr) {
            if (current->mpointer->getId() == id) {  // Asegúrate de que MPointer tenga el método getId()
                if (prev == nullptr) {  // Si es el primer nodo
                    pointers.setHead(current->next);
                } else {
                    prev->next = current->next;
                }
                delete current;
                std::cout << "MPointerGC::releasePointer - MPointer con id: " << id << " liberado\n";
                return;
            }
            prev = current;
            current = current->next;
        }
        std::cout << "MPointerGC::releasePointer - No se encontró el MPointer con id: " << id << "\n";
    }

    // Liberar todos los recursos
    void releaseAllResources() {
        pointers.clear();
        std::cout << "MPointerGC::releaseAllResources - Todos los recursos liberados\n";
    }

    // Mostrar el estado actual de los MPointer
    void debug() const {
        std::cout << "\nMPointerGC::debug() - Estado actual del Garbage Collector\n";

        typename LinkedList<MPointer<T>>::Node* current = pointers.getHead();

        while (current != nullptr) {
            std::cout << "|> MPointer en dirección: " << current->mpointer << " con id: " << current->mpointer->getId() << std::endl;
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
