#pragma once 
#include <iostream>

template <typename T>
class Allocator{
    public:
        T* allocate(size_t size);
        void deallocate(T* ptr, size_t size);
        void construct(T* ptr, T value);
        void destroy(T* ptr);
};

#include "allocator.inl"