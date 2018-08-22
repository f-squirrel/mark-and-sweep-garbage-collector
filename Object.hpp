#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>


class MemoryManager;


class Object {
public:
    using References = std::vector<Object*>;

    Object(const std::string& name) :
        _name(name),
        _visited(false)
    {}

    ~Object() {
        std::cerr << "\nDeleted:" << _name;
    }

    void add_ref(const Object* object) {
        _references.push_back(const_cast<Object*>(object));
    }

    void rm_ref(const Object* object) {
        if(!object) return;
        auto iter = std::find(std::cbegin(_references),
                                std::cend(_references), object);
        _references.erase(iter);
    }

    References refs() const { return _references; }

    Object(const Object&) = delete;
    Object& operator = (const Object&) = delete;
private:
    friend class MemoryManager;
    References  _references;
    std::string _name;
    bool        _visited;
};
