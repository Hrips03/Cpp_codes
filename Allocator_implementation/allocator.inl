#include "allocator.hpp"
#include <memory>
#include "allocator.hpp"

template <typename T>
T *Allocator<T>::allocate(size_t size)
{
    T *ptr = static_cast<T *>(malloc(size * sizeof(T)));
    if (!ptr)
    {
        std::cerr << "Memory allocation failed: std::bad_alloc" << std::endl;
        std::terminate();
    }
    return ptr;
}

template <typename T>
void Allocator<T>::deallocate(T *ptr)
{
    std::free(ptr);
}

template <typename T>
void Allocator<T>::construct(T *ptr, const T &value)
{
    ::new (ptr) T(value); // Placement new
}

template <typename T>
void Allocator<T>::destroy(T *ptr)
{
    ptr->~T();
}
