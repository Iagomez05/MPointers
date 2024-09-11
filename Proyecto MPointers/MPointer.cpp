//
// Created by joelg on 10/9/2024.
//

#include <iostream>
#include <memory> // Para manejar punteros

template <typename T>

class MPointer {
    
public:
    // Constructor por defecto
    MPointer() : memory(nullptr), id(++global_id), refCount(new int(1)) {
        std::cout << "MPointer::New() called, id: " << id << std::endl;
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
                delete memory;
                delete refCount;
                std::cout << "MPointer::memory deleted, id: " << id << std::endl;
            }
        }
        memory = nullptr;
        refCount = new int(1);  // Reiniciamos el refCount para el nuevo objeto
        return *this;
    }

    // Operador de asignación
    MPointer& operator=(const MPointer& other) {
        std::cout << "MPointer::operator= called, id: " << other.id << std::endl;
        if (this == &other) return *this;  // Auto-asignación

        // Si había un puntero asignado, reducir el refCount
        if (memory) {
            (*refCount)--;
            if (*refCount == 0) {
                delete memory;
                delete refCount;
                std::cout << "MPointer::memory deleted, id: " << id << std::endl;
            }
        }

        // Asignamos los nuevos valores
        memory = other.memory;
        id = other.id;
        refCount = other.refCount;
        (*refCount)++;

        return *this;
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

    // Método estático para crear un nuevo MPointer
    static MPointer New() {
        MPointer ptr;
        ptr.memory = new T();
        std::cout << "MPointer::New() created object, id: " << ptr.id << std::endl;
        return ptr;
    }

private:
    T* memory;         // Puntero a la memoria gestionada
    int id;            // Identificador único de cada MPointer
    int* refCount;     // Contador de referencias

    static int global_id; // ID global para todos los MPointer
};

// Inicialización del ID global
template <typename T>
int MPointer<T>::global_id = 0;
