#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList {
public:
    // Estructura para representar un nodo
    struct Node {
        T* mpointer;
        Node* next;
    };

    // Constructor
    LinkedList() : head(nullptr) {}

    // Obtener la cabeza de la lista
    Node* getHead() const {
        return head;
    }

    // Establecer una nueva cabeza de la lista
    void setHead(Node* newHead) {
        head = newHead;
    }

    // Añadir un MPointer a la lista
    void add(T* mpointer) {
        Node* newNode = new Node{mpointer, head};
        head = newNode;
    }

    // Eliminar un MPointer de la lista
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

    // Liberar todos los MPointer
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

private:
    Node* head;  // Cabeza de la lista enlazada
};

#endif // LINKEDLIST_H
