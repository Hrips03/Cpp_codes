#include "deque.hpp"
#include <iostream>

template <class T, class Allocator>
Deque<T, Allocator>::Deque(size_t count) : m_size(count)
{
    Allocator alloc;
    m_map_size = (count + m_block_size - 1) / m_block_size;
    m_map = new T *[m_map_size];

    for (size_t i = 0; i < m_map_size; ++i)
    {
        m_map[i] = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
    }

    m_front_index = 0;
    m_back_index = count - 1;
}

template <class T, class Allocator>
Deque<T, Allocator>::Deque(size_t count, const T &value) : m_size(count)
{
    Allocator alloc;
    m_map_size = (count + m_block_size - 1) / m_block_size;
    m_map = new T *[m_map_size];
    int counter = 0;
    for (size_t i = 0; i < m_map_size; ++i)
    {
        m_map[i] = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
        for (size_t j = 0; j < m_block_size; ++j)
        {
            if (counter == count)
                break;
            std::allocator_traits<Allocator>::construct(alloc, &m_map[i][j], value);
            counter++;
        }
    }

    m_front_index = 0;
    m_back_index = count % m_block_size - 1;
}

template <class T, class Allocator>
Deque<T, Allocator>::Deque(const Deque<T, Allocator> &other)
    : m_size(other.m_size),
      m_block_size(other.m_block_size),
      m_front_index(other.m_front_index),
      m_back_index(other.m_back_index),
      m_map_size(other.m_map_size)
{

    Allocator alloc;
    m_map = new T *[m_map_size];

    for (size_t i = 0; i < m_map_size; ++i)
    {
        m_map[i] = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
        for (size_t j = 0; j < m_block_size; ++j)
            std::allocator_traits<Allocator>::construct(alloc, &m_map[i][j], other.m_map[i][j]);
    }
}

template <class T, class Allocator>
Deque<T, Allocator> &Deque<T, Allocator>::operator=(const Deque<T, Allocator> &other)
{
    if (this == &other)
    {
        return *this;
    }

    Allocator alloc;
    m_map_size = other.m_map_size;
    m_map = new T *[m_map_size];

    for (size_t i = 0; i < m_map_size; ++i)
    {
        m_map[i] = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
        for (size_t j = 0; j < m_block_size; ++j)
            std::allocator_traits<Allocator>::construct(alloc, &m_map[i][j], other.m_map[i][j]);
    }

    m_size = other.m_size;
    m_block_size = other.m_block_size;
    m_front_index = other.m_front_index;
    m_back_index = other.m_back_index;

    return *this;
}

template <class T, class Allocator>
Deque<T, Allocator>::Deque(Deque<T, Allocator> &&other) noexcept
    : m_map(other.m_map), m_size(other.m_size), m_block_size(other.m_block_size),
      m_front_index(other.m_front_index), m_back_index(other.m_back_index), m_map_size(other.m_map_size)
{
    if (this != &other)
    {
        other.m_map = nullptr;
        other.m_size = 0;
        other.m_block_size = 0;
        other.m_front_index = 0;
        other.m_back_index = 0;
        other.m_map_size = 0;
    }
}

template <class T, class Allocator>
Deque<T, Allocator> &Deque<T, Allocator>::operator=(Deque<T, Allocator> &&other) noexcept
{
    if (this != &other)
    {
        delete[] m_map;
        m_map = other.m_map;
        m_size = other.m_size;
        m_block_size = other.m_block_size;
        m_front_index = other.m_front_index;
        m_back_index = other.m_back_index;
        m_map_size = other.m_map_size;

        other.m_map = nullptr;
        other.m_size = 0;
        other.m_block_size = 0;
        other.m_front_index = 0;
        other.m_back_index = 0;
        other.m_map_size = 0;
    }
    return *this;
}

template <class T, class Allocator>
const T &Deque<T, Allocator>::operator[](size_t pos) const
{
    // size_t block_index = pos / m_block_size;
    // size_t index = pos % m_block_size;
    // return m_map[block_index][index];

    size_t flatIdx = m_front_index + pos;
    return m_map[flatIdx / m_block_size][flatIdx % m_block_size];
}

template <class T, class Allocator>
void Deque<T, Allocator>::printMatrix() const
{
    std::cout << "m_map_size = " << m_map_size << std::endl;
    std::cout << "m_front_index = " << m_front_index << std::endl;
    std::cout << "m_back_index = " << m_back_index << std::endl;
    std::cout << "m_size = " << m_size << std::endl;
    for (size_t i = 0; i < m_map_size; ++i)
    {
        for (size_t j = 0; j < m_block_size; ++j)
        {
            std::cout << m_map[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <class T, class Allocator>
void Deque<T, Allocator>::print() const
{
    for (size_t i = 0; i < m_size; i++)
        std::cout << (*this)[i] << " "; 
    std::cout << std::endl;
}

template <class T, class Allocator>
size_t Deque<T, Allocator>::size()
{
    return m_size;
}

template <class T, class Allocator>
void Deque<T, Allocator>::push_back(T &&value)
{
    Allocator alloc;
    if (m_back_index < m_block_size - 1)
    {
        std::allocator_traits<Allocator>::construct(alloc, &m_map[m_map_size - 1][m_back_index + 1], value);
        m_back_index++;
    }
    else
    {
        T *new_block = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
        std::allocator_traits<Allocator>::construct(alloc, &new_block[0], value);
        m_map[m_map_size] = new_block;
        m_map_size++;
        m_back_index = 0;
    }
    m_size++;
}

template <class T, class Allocator>
void Deque<T, Allocator>::push_back(const T &value)
{
    Allocator alloc;
    if (m_back_index < m_block_size - 1)
    {
        std::allocator_traits<Allocator>::construct(alloc, &m_map[m_map_size - 1][m_back_index + 1], value);
        m_back_index++;
    }
    else
    {
        T *new_block = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
        std::allocator_traits<Allocator>::construct(alloc, &new_block[0], value);
        m_map[m_map_size] = new_block;
        m_map_size++;
        m_back_index = 0;
    }
    m_size++;
}

template <class T, class Allocator>
void Deque<T, Allocator>::pop_back()
{
    if (m_size == 0)
        return;

    Allocator alloc;
    std::allocator_traits<Allocator>::destroy(alloc, &m_map[m_map_size - 1][m_back_index]);

    if (m_back_index == 0)
    {
        std::allocator_traits<Allocator>::deallocate(alloc, m_map[m_map_size - 1], m_block_size);
        m_map[m_map_size - 1] = nullptr;
        m_map_size--;
        m_back_index = m_block_size - 1;
    }
    else
    {
        m_map[m_map_size - 1][m_back_index] = 0;
        m_back_index--;
    }
    m_size--;
}

template <class T, class Allocator>
void Deque<T, Allocator>::push_front(T &&value)
{
    Allocator alloc;
    if (m_front_index > 0)
    {
        m_front_index--;
        std::allocator_traits<Allocator>::construct(alloc, &m_map[0][m_front_index], value);
    }
    else
    {
        T *new_block = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
        std::allocator_traits<Allocator>::construct(alloc, &new_block[m_block_size - 1], value);

        for (size_t i = 0; i < m_block_size - 1; i++)
            std::allocator_traits<Allocator>::construct(alloc, &new_block[i], 0);

        for (size_t i = m_map_size; i > 0; --i)
            m_map[i] = m_map[i - 1];

        m_map[0] = new_block;
        m_map_size++;

        m_front_index = m_block_size - 1;
    }

    m_size++;
}

template <class T, class Allocator>
void Deque<T, Allocator>::push_front(const T &value)
{
    Allocator alloc;
    if (m_front_index > 0)
    {
        m_front_index--;
        std::allocator_traits<Allocator>::construct(alloc, &m_map[0][m_front_index], value);
    }
    else
    {
        T *new_block = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
        std::allocator_traits<Allocator>::construct(alloc, &new_block[m_block_size - 1], value);

        for (size_t i = 0; i < m_block_size - 1; i++)
            std::allocator_traits<Allocator>::construct(alloc, &new_block[i], 0);

        for (size_t i = m_map_size; i > 0; --i)
            m_map[i] = m_map[i - 1];

        m_map[0] = new_block;
        m_map_size++;

        m_front_index = m_block_size - 1;
    }

    m_size++;
}

template <class T, class Allocator>
void Deque<T, Allocator>::pop_front()
{
    if (m_size == 0)
        return;

    Allocator alloc;
    std::allocator_traits<Allocator>::destroy(alloc, &m_map[0][m_front_index]);

    if (m_front_index == m_block_size - 1)
    {
        std::allocator_traits<Allocator>::deallocate(alloc, m_map[0], m_block_size);
        m_map[0] = nullptr;

        for (size_t i = 0; i < m_map_size - 1; i++)
        {
            m_map[i] = m_map[i + 1];
        }
        m_map[m_map_size - 1] = nullptr;
        m_map_size--;
        m_front_index = 0;
    }
    else
    {
        m_front_index++;
    }

    m_size--;
}

template <class T, class Allocator>
T &Deque<T, Allocator>::Iterator::operator*() const
{
    return map[blockIdx][elemIdx];
}

template <class T, class Allocator>
typename Deque<T, Allocator>::Iterator &Deque<T, Allocator>::Iterator::operator++()
{
    if (++elemIdx == blockSize) { 
        elemIdx = 0;
        blockIdx++;
    }
    return *this;
}

template <class T, class Allocator>
typename Deque<T, Allocator>::Iterator Deque<T, Allocator>::Iterator::operator++(int)
{
    auto temp = *this;
    this->operator++();
    return temp;
}

template <class T, class Allocator>
typename Deque<T, Allocator>::Iterator Deque<T, Allocator>::Iterator::operator==(const Iterator& other)
{
    return !(*this != other);
}

template <class T, class Allocator>
bool Deque<T, Allocator>::Iterator::operator!=(const Iterator &other) const
{
    return blockIdx != other.blockIdx || elemIdx != other.elemIdx;
}

template <class T, class Allocator>
typename Deque<T, Allocator>::Iterator Deque<T, Allocator>::begin()
{
    return Iterator(m_map, m_block_size, 0, m_front_index);
}

template <class T, class Allocator>
typename Deque<T, Allocator>::Iterator Deque<T, Allocator>::end()
{
    return Iterator(m_map, m_block_size, m_map_size - 1, m_back_index + 1);
}
