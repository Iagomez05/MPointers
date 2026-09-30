#include "DoublyLinkedList.h"
#include "MPointer.h"
#include "MPointerGC.h"

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
int failures = 0;

void expect(bool condition, const std::string& message) {
    if (!condition) {
        ++failures;
        std::cerr << "FAIL: " << message << '\n';
    }
}

void testReferenceTracking() {
    auto& tracker = MPointerGC<int>::instance();
    const std::size_t baseline = tracker.activeAllocations();

    {
        MPointer<int> first = MPointer<int>::New(42);
        expect(tracker.activeAllocations() == baseline + 1, "allocation is registered");
        expect(first.useCount() == 1, "new pointer starts with one reference");

        MPointer<int> second = first;
        expect(first.useCount() == 2 && second.useCount() == 2, "copy increments reference count");
        expect(first.id() == second.id(), "copies share an allocation id");
        const auto tracked = tracker.snapshot();
        expect(!tracked.empty() && tracked.back().references == 2,
               "tracking registry observes the shared reference count");

        second.reset();
        expect(first.useCount() == 1, "reset decrements reference count");
        expect(*first == 42, "remaining reference keeps the value alive");
    }

    expect(tracker.activeAllocations() == baseline, "last reference releases the allocation");
}

void testNullAndValueAssignment() {
    MPointer<int> pointer;
    expect(pointer == nullptr, "default pointer is empty");
    expect(pointer.useCount() == 0, "empty pointer has no control block");

    bool threw = false;
    try {
        (void)*pointer;
    } catch (const std::logic_error&) {
        threw = true;
    }
    expect(threw, "empty dereference is rejected");

    pointer = 17;
    expect(pointer != nullptr && *pointer == 17, "value assignment allocates storage");
    pointer = nullptr;
    expect(pointer == nullptr, "nullptr assignment releases storage");
}

void testLinkedListOperations() {
    const std::size_t baseline = DoublyLinkedList<int>::activeNodeAllocations();
    DoublyLinkedList<int> list;
    expect(list.empty(), "new list is empty");

    list.append(3);
    list.append(1);
    list.append(2);
    expect(list.size() == 3, "append updates list size");
    expect(list.values() == std::vector<int>({3, 1, 2}), "append preserves insertion order");
    expect(DoublyLinkedList<int>::activeNodeAllocations() == baseline + 3,
           "each list node is tracked");

    list.clear();
    expect(list.empty() && list.values().empty(), "clear releases the owning chain");
    expect(DoublyLinkedList<int>::activeNodeAllocations() == baseline,
           "clear releases every tracked node");
}

void testSortingAlgorithms() {
    const std::vector<int> expected{1, 2, 3, 4, 5};

    DoublyLinkedList<int> bubble;
    DoublyLinkedList<int> insertion;
    DoublyLinkedList<int> quick;
    for (int value : {4, 2, 5, 1, 3}) {
        bubble.append(value);
        insertion.append(value);
        quick.append(value);
    }

    bubble.bubbleSort();
    insertion.insertionSort();
    quick.quickSort();

    expect(bubble.values() == expected, "Bubble Sort orders the list");
    expect(insertion.values() == expected, "Insertion Sort orders the list");
    expect(quick.values() == expected, "Quick Sort orders the list");

    DoublyLinkedList<int> empty;
    empty.bubbleSort();
    empty.insertionSort();
    empty.quickSort();
    expect(empty.empty(), "sorting an empty list is safe");
}
}

int main() {
    testReferenceTracking();
    testNullAndValueAssignment();
    testLinkedListOperations();
    testSortingAlgorithms();

    if (failures == 0) {
        std::cout << "All MPointers tests passed.\n";
        return 0;
    }

    std::cerr << failures << " test assertion(s) failed.\n";
    return 1;
}
