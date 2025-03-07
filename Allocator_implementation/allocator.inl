#include "allocator.hpp"
#include <memory>

template <typename T>
T* Allocator<T>::allocate(size_t size){
    T* ptr =  static_cast<T*>(malloc(size * sizeof(T)));
    if(!ptr){
        std::cerr << "terminate called after throwing an instance of 'std::bad_array_new_length'\nwhat():  std::bad_array_new_length\nAborted" << std::endl;
        std::terminate;
    }
    return ptr;
}

template <typename T>
void Allocator<T>::deallocate(T* ptr, size_t size){
    std::free(ptr);
}

template <typename T>
void Allocator<T>::construct(T* ptr, T value){
    *ptr = value;
}

template <typename T>
void Allocator<T>::destroy(T* ptr){
    ptr = nullptr;
}
