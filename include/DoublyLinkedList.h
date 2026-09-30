#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include "MPointer.h"

#include <cstddef>
#include <utility>
#include <vector>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        explicit Node(const T& value) : data(value) {
        }

        T data;
        Node* previous = nullptr;
        MPointer<Node> next;
    };

public:
    DoublyLinkedList() = default;
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    void append(const T& value) {
        MPointer<Node> node = MPointer<Node>::New(value);
        node->previous = tail_;

        if (tail_ == nullptr) {
            head_ = node;
        } else {
            tail_->next = node;
        }

        tail_ = node.get();
        ++size_;
    }

    void clear() noexcept {
        head_.reset();
        tail_ = nullptr;
        size_ = 0;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size_ == 0;
    }

    [[nodiscard]] std::size_t size() const noexcept {
        return size_;
    }

    [[nodiscard]] static std::size_t activeNodeAllocations() {
        return MPointerGC<Node>::instance().activeAllocations();
    }

    [[nodiscard]] std::vector<T> values() const {
        std::vector<T> result;
        result.reserve(size_);
        for (const Node* current = head_.get(); current != nullptr; current = current->next.get()) {
            result.push_back(current->data);
        }
        return result;
    }

    void bubbleSort() {
        if (size_ < 2) {
            return;
        }

        bool swapped;
        do {
            swapped = false;
            for (Node* current = head_.get(); current->next != nullptr; current = current->next.get()) {
                if (current->data > current->next->data) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
            }
        } while (swapped);
    }

    void insertionSort() {
        for (Node* current = head_ == nullptr ? nullptr : head_->next.get();
             current != nullptr;
             current = current->next.get()) {
            T key = current->data;
            Node* previous = current->previous;
            Node* destination = current;

            while (previous != nullptr && previous->data > key) {
                destination->data = previous->data;
                destination = previous;
                previous = previous->previous;
            }
            destination->data = std::move(key);
        }
    }

    void quickSort() {
        quickSort(head_.get(), tail_);
    }

private:
    MPointer<Node> head_;
    Node* tail_ = nullptr;
    std::size_t size_ = 0;

    static void swapData(Node* first, Node* second) {
        std::swap(first->data, second->data);
    }

    static Node* partition(Node* low, Node* high) {
        const T pivot = high->data;
        Node* boundary = low->previous;

        for (Node* current = low; current != high; current = current->next.get()) {
            if (current->data <= pivot) {
                boundary = boundary == nullptr ? low : boundary->next.get();
                swapData(boundary, current);
            }
        }

        boundary = boundary == nullptr ? low : boundary->next.get();
        swapData(boundary, high);
        return boundary;
    }

    static void quickSort(Node* low, Node* high) {
        if (low == nullptr || high == nullptr || low == high || low == high->next.get()) {
            return;
        }

        Node* pivot = partition(low, high);
        quickSort(low, pivot->previous);
        quickSort(pivot->next.get(), high);
    }
};

#endif
