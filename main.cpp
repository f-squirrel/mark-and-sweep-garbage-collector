#include "MemoryManager.hpp"


void test_exit_from_scope() {
    MemoryManager manager;
    {
        manager.create();
    }
    auto cnt = manager.clean();
    std::cout << "PASSED: " << std::boolalpha << ( cnt == 1 ) << "\n";
}

void test_several_references() {
    MemoryManager manager;
    {
        auto ref1 = manager.create();
        auto ref2 = manager.create();
        ref1.add_ref(ref2);
        ref2.add_ref(ref1);
    }
    auto cnt = manager.clean();
    std::cout << "PASSED: " << std::boolalpha << ( cnt == 2 ) << "\n";
}

void test_refernces_to_itself() {
    MemoryManager manager;
    {
        auto ref = manager.create();
        ref.add_ref(ref);
    }
    auto cnt = manager.clean();
    std::cout << "PASSED: " << std::boolalpha << ( cnt == 1 ) << "\n";
}

void test_pass_ref_out_of_the_scope() {
    MemoryManager manager;
    auto out_ref = manager.create();
    {
        auto ref = manager.create();
        out_ref.add_ref(ref);
    }
    auto cnt = manager.clean();
    std::cout << "PASSED: " << std::boolalpha << ( cnt == 0 ) << "\n";
}

void test_no_collection_of_objects_in_use() {
    MemoryManager manager;
    {
        auto ref = manager.create();
        auto cnt = manager.clean();
        std::cout << "PASSED: " << std::boolalpha << ( cnt == 0 ) << "\n";
    }
}

int main() {
    test_exit_from_scope();
    test_several_references();
    test_refernces_to_itself();
    test_pass_ref_out_of_the_scope();
    test_no_collection_of_objects_in_use();
    return 0;
}
