#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// Declaración adelantada de la clase MPointerGC
template <typename T>
class MPointer;

// Clase plantilla LinkedList
template <typename T>
class LinkedList {
public:
    // Estructura para representar un nodo
    struct Node {
        T* mpointer;  // Cambiamos el puntero a T en vez de depender de MPointer
        Node* next;
    };

    // Constructor
    LinkedList() : head(nullptr) {}

    // Destructor para liberar toda la memoria
    ~LinkedList() {
        clear();
    }

    // Añadir un elemento (un puntero de tipo T) a la lista
    void add(T* mpointer) {
        Node* newNode = new Node{mpointer, head};
        head = newNode;
    }

    // Eliminar un elemento de la lista
    void remove(T* mpointer) {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->mpointer == mpointer) {
                if (prev == nullptr) {  // Si es el primer nodo
                    head = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    // Liberar todos los elementos de la lista
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* toDelete = current;
            delete current->mpointer;
            current = current->next;
            delete toDelete;
        }
        head = nullptr;
    }

    // Devuelve la cabeza de la lista
    Node* getHead() const {
        return head;
    }

private:
    Node* head;  // Cabeza de la lista enlazada
};

#endif // LINKEDLIST_H