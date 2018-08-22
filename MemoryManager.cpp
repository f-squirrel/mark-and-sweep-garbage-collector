#include "MemoryManager.hpp"
#include "Object.hpp"

#include <iostream>


MemoryManager::~MemoryManager() {
    std::cout << "\nMemoryManager is going to be destroyed, cleaning the stack:";
    for(auto iter : _heap) {
        delete iter;
    }
    std::cout << "\nMemoryManager is destroyed\n\n";
}

ObjectStackWrapper MemoryManager::create() {
    std::string name = std::to_string( _count );
    _count++;
    Object* object = new Object(name);
    _heap.insert(object);
    const auto& wrapper = ObjectStackWrapper(_stack, object);
    return wrapper;
}

uint64_t MemoryManager::clean() {
    std::cout << "\nStarted garbage collection";
    std::cout << "\nList of objects in use:";
    for(auto o : _stack.objects_in_use()) {
        std::cout << '\n' << o.first->_name;
    }
    mark();
    uint64_t deleted_count = do_clean();
    reset_flags();
    std::cout << "\nFinished garbage collection, deleted: " << deleted_count << "\n";
    return deleted_count;
}

void MemoryManager::reset_flags() {
    for(auto iter : _heap) {
        iter->_visited = false;
    }
}

void MemoryManager::mark() {
    std::cout << "\nStarted building reference graph";
    for(auto ref : _stack.objects_in_use()) {
        traverse(ref.first);
    }
    std::cout << "\nFinished building reference graph";
}

uint64_t MemoryManager::do_clean() {
    std::cout << "\nStarted deleting objects";
    uint64_t deleted_count = 0;
    Heap::iterator it = _heap.begin();
    while(it != _heap.end()) {
        if(!((*it)->_visited)) {
            delete (*it);
            it = _heap.erase(it);
            ++deleted_count;
        } else {
            ++it;
        }
    }
    std::cout << "\nFinised deleting objects";
    return deleted_count;
}

void MemoryManager::traverse(Object* object) {
    if(!object) { return; }
    if(object->_visited) { return; }

    std::cout << "\nvisiting: " << object->_name;
    object->_visited = true;
    for(auto ref : object->refs()) {
        traverse(ref);
    }
}
