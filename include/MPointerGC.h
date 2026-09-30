#ifndef MPOINTER_GC_H
#define MPOINTER_GC_H

#include <cstddef>
#include <map>
#include <ostream>
#include <vector>

template <typename T>
class MPointerGC {
public:
    struct Allocation {
        std::size_t id;
        const T* address;
        std::size_t references;
    };

    static MPointerGC& instance() {
        static MPointerGC tracker;
        return tracker;
    }

    void registerAllocation(std::size_t id, const T* address, std::size_t references) {
        allocations_[id] = Allocation{id, address, references};
    }

    void updateReferences(std::size_t id, std::size_t references) {
        auto allocation = allocations_.find(id);
        if (allocation != allocations_.end()) {
            allocation->second.references = references;
        }
    }

    void unregisterAllocation(std::size_t id) {
        allocations_.erase(id);
    }

    [[nodiscard]] std::size_t activeAllocations() const {
        return allocations_.size();
    }

    [[nodiscard]] std::vector<Allocation> snapshot() const {
        std::vector<Allocation> result;
        result.reserve(allocations_.size());
        for (const auto& [id, allocation] : allocations_) {
            (void)id;
            result.push_back(allocation);
        }
        return result;
    }

    void debug(std::ostream& output) const {
        for (const Allocation& allocation : snapshot()) {
            output << "id=" << allocation.id
                   << " address=" << static_cast<const void*>(allocation.address)
                   << " references=" << allocation.references << '\n';
        }
    }

private:
    MPointerGC() = default;
    std::map<std::size_t, Allocation> allocations_;
};

#endif
