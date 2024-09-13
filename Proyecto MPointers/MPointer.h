#ifndef MPOINTER_H
#define MPOINTER_H

#include <iostream>
#include <memory>
#include <utility>
#include "MPointerGC.h"  // Solo si no hay dependencias circulares

template <typename T>
class MPointer {
public:
    // Constructor por defecto
    MPointer() : memory(nullptr), id(++global_id), refCount(new int(1)) {
        std::cout << "MPointer::New() called, id: " << id << std::endl;
    }

    // Constructor que permite la inicialización con nullptr
    MPointer(std::nullptr_t) : memory(nullptr), id(++global_id), refCount(new int(1)) {
        std::cout << "MPointer initialized with nullptr, id: " << id << std::endl;
    }

    // Constructor de copia
    MPointer(const MPointer& other) : memory(other.memory), id(other.id), refCount(other.refCount) {
        (*refCount)++;
        std::cout << "MPointer::CopyConstructor called, id: " << id << std::endl;
    }

    // Operador de asignación para nullptr
    MPointer& operator=(std::nullptr_t nullValue) {
        std::cout << "MPointer::operator=(nullptr) called, id: " << id << std::endl;
        if (memory) {
            (*refCount)--;
            if (*refCount == 0) {
                MPointerGC<T>::getInstance()->releasePointer(id);
                std::cout << "MPointer::memory deletion requested, id: " << id << std::endl;
            }
        }
        memory = nullptr;
        refCount = new int(1);
        return *this;
    }

    // Sobrecarga del operador = para asignar valores a MPointer
    MPointer& operator=(T value) {
        if (!memory) {
            memory = new T();
        }
        *memory = value;
        return *this;
    }

    // Operador de asignación
    MPointer& operator=(const MPointer& other) {
        std::cout << "MPointer::operator= called, id: " << other.id << std::endl;
        if (this == &other) return *this;

        if (memory) {
            (*refCount)--;
            if (*refCount == 0) {
                delete memory;
                delete refCount;
                std::cout << "MPointer::memory deleted, id: " << id << std::endl;
            }
        }

        memory = other.memory;
        id = other.id;
        refCount = other.refCount;
        (*refCount)++;
        return *this;
    }

    // Operador de comparación con nullptr
    bool operator==(std::nullptr_t) const {
        return memory == nullptr;
    }

    bool operator!=(std::nullptr_t) const {
        return memory != nullptr;
    }

    // Operador ! para verificar si un MPointer está vacío
    bool operator!() const {
        return memory == nullptr;
    }

    // Destructor
    ~MPointer() {
        std::cout << "MPointer::Destructor called, id: " << id << std::endl;
        if (memory) {
            (*refCount)--;
            if (*refCount == 0) {
                delete memory;
                delete refCount;
                std::cout << "MPointer::memory deleted in destructor, id: " << id << std::endl;
            }
        }
    }

    // Sobrecarga del operador * para acceder al valor apuntado
    T& operator*() {
        return *memory;
    }

    // Sobrecarga del operador -> para acceder a los miembros de T
    T* operator->() {
        return memory;
    }

    // Sobrecarga del operador != para comparar dos MPointers
    bool operator!=(const MPointer<T>& other) const {
        return this->memory != other.memory;
    }


    // Método para obtener el ID del MPointer
    int getId() const {
        return id;
    }

    // Método estático para crear un nuevo MPointer
    static MPointer New() {
        MPointer ptr;
        ptr.memory = new T();
        std::cout << "MPointer::New() created object, id: " << ptr.id << std::endl;
        return ptr;
    }

private:
    T* memory;
    int id;
    int* refCount;

    static int global_id;
};

// Inicialización del ID global
template <typename T>
int MPointer<T>::global_id = 0;

#endif // MPOINTER_H
