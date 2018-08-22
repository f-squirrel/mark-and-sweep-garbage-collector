#pragma once

#include "ObjectStackWrapper.hpp"
#include "StackSet.hpp"

#include <unordered_set>


class MemoryManager {
public:
    MemoryManager() : _count(0u) {}
    MemoryManager(const MemoryManager&) = delete;
    MemoryManager(MemoryManager&&) = delete;
    MemoryManager& operator=(const MemoryManager&) = delete;
    MemoryManager&& operator=(MemoryManager&&) = delete;
    ~MemoryManager();
    ObjectStackWrapper create();
    uint64_t clean();
private:
    void reset_flags();
    void mark();
    uint64_t do_clean();
    void traverse(Object* object);
private:
    StackSet _stack;
    using Heap = std::unordered_set<Object*>;
    Heap _heap;
    uint64_t _count;
};
