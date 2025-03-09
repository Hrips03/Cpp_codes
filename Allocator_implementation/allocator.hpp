#pragma once
#include <iostream>
#include <cstdlib> 

template <typename T>
class Allocator {
public:
    T* allocate(size_t size);
    void deallocate(T* ptr);
    void construct(T* ptr, const T& value);
    void destroy(T* ptr);
};

#include "allocator.inl"
