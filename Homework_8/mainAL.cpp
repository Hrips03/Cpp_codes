#include "allocator.hpp"

int main() {
    Allocator<int> alloc;
    int* p = alloc.allocate(1);
    alloc.construct(p, 42); 
    
    std::cout << "Constructed value: " << *p << std::endl;

    alloc.destroy(p); 
    alloc.deallocate(p, 1); 
    


    Allocator<char> allocChar;
    char* ptr = allocChar.allocate(1); 
    allocChar.construct(ptr, 'a'); 
    
    std::cout << "Constructed value: " << *ptr << std::endl;

    allocChar.destroy(ptr); 
    allocChar.deallocate(ptr, 1);
    return 0;
}