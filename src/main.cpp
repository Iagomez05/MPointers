#include "DoublyLinkedList.h"
#include "MPointer.h"

#include <iostream>
#include <string>

template <typename T>
void printValues(const DoublyLinkedList<T>& list) {
    bool first = true;
    for (const T& value : list.values()) {
        std::cout << (first ? "" : " ") << value;
        first = false;
    }
    std::cout << '\n';
}

int main() {
    MPointer<std::string> message = MPointer<std::string>::New("reference tracked");
    MPointer<std::string> shared = message;

    std::cout << "MPointer value: " << *shared
              << " | allocation id: " << shared.id()
              << " | references: " << shared.useCount() << "\n\n";

    DoublyLinkedList<int> values;
    for (int value : {4, 2, 5, 1, 3}) {
        values.append(value);
    }

    std::cout << "Original list: ";
    printValues(values);
    values.quickSort();
    std::cout << "Quick sorted:  ";
    printValues(values);

    return 0;
}
