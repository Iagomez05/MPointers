#ifndef MPOINTER_H
#define MPOINTER_H

#include "MPointerGC.h"

#include <atomic>
#include <cstddef>
#include <stdexcept>
#include <utility>

template <typename T>
class MPointer {
public:
    MPointer() noexcept = default;
    MPointer(std::nullptr_t) noexcept {
    }

    MPointer(const MPointer& other) noexcept : control_(other.control_) {
        retain();
    }

    MPointer(MPointer&& other) noexcept : control_(std::exchange(other.control_, nullptr)) {
    }

    ~MPointer() {
        release();
    }

    MPointer& operator=(const MPointer& other) noexcept {
        if (this != &other) {
            release();
            control_ = other.control_;
            retain();
        }
        return *this;
    }

    MPointer& operator=(MPointer&& other) noexcept {
        if (this != &other) {
            release();
            control_ = std::exchange(other.control_, nullptr);
        }
        return *this;
    }

    MPointer& operator=(std::nullptr_t) noexcept {
        reset();
        return *this;
    }

    MPointer& operator=(const T& value) {
        ensureAllocated();
        *control_->value = value;
        return *this;
    }

    MPointer& operator=(T&& value) {
        ensureAllocated();
        *control_->value = std::move(value);
        return *this;
    }

    template <typename... Args>
    static MPointer New(Args&&... args) {
        MPointer pointer;
        pointer.control_ = new ControlBlock{
                new T(std::forward<Args>(args)...),
                1,
                nextId_.fetch_add(1, std::memory_order_relaxed) + 1
        };
        try {
            tracker().registerAllocation(pointer.id(), pointer.get(), pointer.useCount());
        } catch (...) {
            delete pointer.control_->value;
            delete pointer.control_;
            pointer.control_ = nullptr;
            throw;
        }
        return pointer;
    }

    void reset() noexcept {
        release();
    }

    [[nodiscard]] T* get() noexcept {
        return control_ == nullptr ? nullptr : control_->value;
    }

    [[nodiscard]] const T* get() const noexcept {
        return control_ == nullptr ? nullptr : control_->value;
    }

    [[nodiscard]] std::size_t id() const noexcept {
        return control_ == nullptr ? 0 : control_->id;
    }

    [[nodiscard]] std::size_t getId() const noexcept {
        return id();
    }

    [[nodiscard]] std::size_t useCount() const noexcept {
        return control_ == nullptr ? 0 : control_->references;
    }

    explicit operator bool() const noexcept {
        return get() != nullptr;
    }

    bool operator==(std::nullptr_t) const noexcept {
        return get() == nullptr;
    }

    bool operator!=(std::nullptr_t) const noexcept {
        return get() != nullptr;
    }

    bool operator==(const MPointer& other) const noexcept {
        return get() == other.get();
    }

    bool operator!=(const MPointer& other) const noexcept {
        return !(*this == other);
    }

    T& operator*() {
        ensureDereferenceable();
        return *control_->value;
    }

    const T& operator*() const {
        ensureDereferenceable();
        return *control_->value;
    }

    T* operator->() {
        ensureDereferenceable();
        return control_->value;
    }

    const T* operator->() const {
        ensureDereferenceable();
        return control_->value;
    }

private:
    struct ControlBlock {
        T* value;
        std::size_t references;
        std::size_t id;
    };

    ControlBlock* control_ = nullptr;
    inline static std::atomic_size_t nextId_{0};

    static MPointerGC<T>& tracker() {
        return MPointerGC<T>::instance();
    }

    void ensureAllocated() {
        if (control_ == nullptr) {
            *this = New();
        }
    }

    void ensureDereferenceable() const {
        if (control_ == nullptr || control_->value == nullptr) {
            throw std::logic_error("Cannot dereference an empty MPointer");
        }
    }

    void retain() noexcept {
        if (control_ != nullptr) {
            ++control_->references;
            tracker().updateReferences(control_->id, control_->references);
        }
    }

    void release() noexcept {
        if (control_ == nullptr) {
            return;
        }

        ControlBlock* released = std::exchange(control_, nullptr);
        --released->references;
        if (released->references == 0) {
            tracker().unregisterAllocation(released->id);
            delete released->value;
            delete released;
        } else {
            tracker().updateReferences(released->id, released->references);
        }
    }
};

#endif
