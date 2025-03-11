#pragma once
#include <memory>

template <class T, class Allocator = std::allocator<T>>
class Deque
{
    T **m_map;           // Pointer to an array of block pointers (the "map")
    size_t m_map_size = 0;   // Number of allocated block pointers
    size_t m_size = 0;       // Current number of elements
    size_t m_block_size = 4; // Fixed number of elements per block

    size_t m_front_index = 0; // Index of the first element in the first block
    size_t m_back_index = 0;  // Index of the last element in the last block

public:
    Deque() = default;
    Deque(size_t count);
    Deque(size_t count, const T& value);
    Deque(const Deque<T, Allocator>& other);
    Deque(Deque<T, Allocator>&& other) noexcept;
    Deque<T, Allocator>& operator=(const Deque<T, Allocator>& other);
    Deque<T, Allocator>& operator=(Deque<T, Allocator>&& other) noexcept;

    size_t size();
    const T& operator[]( size_t pos) const;
    void printMatrix() const;
    void print() const;
    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    void push_front(const T& value);
    void push_front(T&& value);
    void pop_front();
};


#include "deque.inl"