#include "deque.hpp"

template <class T, class Allocator>
Deque<T, Allocator>::Deque(size_t count) : m_size(count), m_block_size(16) {
    Allocator alloc;
    m_map_size = (count + m_block_size - 1) / m_block_size; 
    m_map = new T*[m_map_size]; 

    for (size_t i = 0; i < m_map_size; ++i) {
        m_map[i] = alloc.allocate(m_block_size); 
    }

    m_front_index = 0;
    m_back_index = count - 1;
}
