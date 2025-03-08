#pragma once
#include <memory>

template <class T, class Allocator = std::allocator<T>>
class Deque
{
    T **m_map;           // Pointer to an array of block pointers (the "map")
    size_t m_map_size = 0;   // Number of allocated block pointers
    size_t m_size = 0;       // Current number of elements
    size_t m_block_size; // Fixed number of elements per block

    size_t m_front_index = 0; // Index of the first element in the first block
    size_t m_back_index = 0;  // Index of the last element in the last block

public:
    Deque() = default;
    Deque(size_t count);
    // Deque(size_t count, const T& value);
    // Deque(const T& Deque);
    // Deque(const T&& Deque) noexcept;
    // Deque& operator=(const T& Deque);
    // Deque& operator=(const T&& Deque) noexcept;
};


#include "deque.inl"