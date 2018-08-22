#pragma once

class Object;
class StackSet;


class ObjectStackWrapper {
public:
    ObjectStackWrapper(StackSet&, Object*);
    ObjectStackWrapper(const ObjectStackWrapper&);
    ObjectStackWrapper& operator = (const ObjectStackWrapper&);
    ObjectStackWrapper(ObjectStackWrapper&&) = default;
    ObjectStackWrapper& operator = (ObjectStackWrapper&&);
    ~ObjectStackWrapper();

    void add_ref(const ObjectStackWrapper& owrapper);
    void rm_ref(const ObjectStackWrapper& owrapper);
private:
    StackSet&   _stack_set;
    Object*     _object;
};
