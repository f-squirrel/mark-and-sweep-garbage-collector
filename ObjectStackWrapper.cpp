#include "ObjectStackWrapper.hpp"

#include "StackSet.hpp"
#include "Object.hpp"


ObjectStackWrapper::ObjectStackWrapper(StackSet& stack_set,
                                        Object* object):
    _stack_set(stack_set),
    _object(object)
{
    _stack_set.add(_object);
}

ObjectStackWrapper::ObjectStackWrapper(const ObjectStackWrapper& owrapper) :
    _stack_set(owrapper._stack_set),
    _object(owrapper._object)
{
    _stack_set.add(owrapper._object);
}

ObjectStackWrapper& ObjectStackWrapper::operator = (const ObjectStackWrapper& owrapper) {
    if(this == &owrapper) {
        return *this;
    }
    _stack_set.remove(_object);
    _object = owrapper._object;
    _stack_set.add(_object);

    return *this;
}

ObjectStackWrapper& ObjectStackWrapper::operator = (ObjectStackWrapper&& owrapper) {
    if(this == &owrapper) {
        return *this;
    }
    _stack_set.remove(_object);
    _object = owrapper._object;
    owrapper._object = nullptr;
    return *this;
}

ObjectStackWrapper::~ObjectStackWrapper() {
    _stack_set.remove(_object);
}

void ObjectStackWrapper::add_ref(const ObjectStackWrapper& owrapper) {
    _object->add_ref(owrapper._object);
}

void ObjectStackWrapper::rm_ref(const ObjectStackWrapper& owrapper) {
    _object->rm_ref(owrapper._object);
}
