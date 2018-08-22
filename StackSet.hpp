#pragma once
#include "ObjectStackWrapper.hpp"
#include "Object.hpp"

#include <unordered_map>


class StackSet {
public:
    using ReferencesInUse = std::unordered_map<Object*, uint64_t>;
    StackSet() = default;
    void add(Object* o) {
        auto iter = _stack_set.find(o);
        if(iter == _stack_set.end()) {
           _stack_set.emplace(o, 0u);
        } else {
            iter->second++;
        }
    }
    void remove(Object* o) {
        auto iter = _stack_set.find(o);
        if(iter == _stack_set.end()) {
            return;
        }
        if(iter->second == 0u) {
            _stack_set.erase(iter);
        } else {
            iter->second--;
        }
    }
    ReferencesInUse objects_in_use() const {
        return _stack_set;
    }
    StackSet(const StackSet&) = delete;
    StackSet& operator = (const StackSet&) = delete;
private:
    ReferencesInUse _stack_set;
};
