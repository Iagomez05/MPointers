//
// Created by joelg on 10/9/2024.
//

#include <iostream>
#include <map> // Para almacenar los MPointer y su información

template <typename T>

class MPointerGC {

public:
    // Obtener la instancia única de MPointerGC (patrón Singleton)
    static MPointerGC* getInstance() {
        if (!instance) {
            instance = new MPointerGC();
        }
        return instance;
    }

    // Método para registrar un nuevo MPointer en el GC
    void registerPointer(int id, T* ptr, int* refCount) {
        registry[id] = {ptr, refCount};
        std::cout << "MPointerGC::registerPointer called, id: " << id << std::endl;
    }

    // Método para liberar todos los recursos (opcional)
    void releaseAllResources() {
        for (auto& entry : registry) {
            if (*entry.second.refCount == 0) {
                delete entry.second.ptr;
                delete entry.second.refCount;
                std::cout << "MPointerGC::releaseAllResources deleted memory, id: " << entry.first << std::endl;
            }
        }
        registry.clear();
    }

    // Método para mostrar el estado actual de los MPointer
    void debug() const {
        std::cout << "\nMPointerGC::debug() called\n";
        for (const auto& entry : registry) {
            std::cout << "|>Id:" << entry.first
                      << " RefCount:" << *entry.second.refCount
                      << " Address:" << entry.second.ptr
                      << "<|" << std::endl;
        }
    }

    // Destructor
    ~MPointerGC() {
        releaseAllResources();
        std::cout << "MPointerGC::Destructor called\n";
    }

private:
    // Constructor privado para patrón Singleton
    MPointerGC() = default;

    // Estructura para almacenar los MPointer y su contador de referencias
    struct MemoryRegistryEntry {
        T* ptr;
        int* refCount;
    };

    // Registro de todos los MPointer
    std::map<int, MemoryRegistryEntry> registry;

    // Instancia única del GC
    static MPointerGC* instance;
};

// Inicialización de la instancia del GC
template <typename T>
MPointerGC<T>* MPointerGC<T>::instance = nullptr;
