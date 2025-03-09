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

    for (size_t i = 0; i < m_map_size; ++i)
    {
        m_map[i] = std::allocator_traits<Allocator>::allocate(alloc, m_block_size);
        for (size_t j = 0; j < m_block_size; ++j)
        {
            if (j > count)
                break;
            std::allocator_traits<Allocator>::construct(alloc, &m_map[i][j], value);
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
    size_t block_index = pos / m_block_size;
    size_t index = pos % m_block_size;
    return m_map[block_index][index];
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
        std::allocator_traits<Allocator>::construct(alloc, &new_block[m_front_index], value);

        for (size_t i = m_map_size; i > 0; --i)
        {
            m_map[i] = m_map[i - 1];
        }

        m_map[0] = new_block;
        m_map_size++;

        m_front_index = 0;
    }

    m_size++;

    std::cout << "m_map_size = " << m_map_size << std::endl;
    std::cout << "m_front_index = " << m_front_index << std::endl;
    std::cout << "m_back_index = " << m_back_index << std::endl;
    std::cout << "m_size = " << m_size << std::endl;
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
        std::allocator_traits<Allocator>::construct(alloc, &new_block[m_front_index], value);

        for (size_t i = m_map_size; i > 0; --i)
        {
            m_map[i] = m_map[i - 1];
        }

        m_map[0] = new_block;
        m_map_size++;

        m_front_index = 0;
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
    m_front_index++;

    if (m_front_index == m_block_size - 1)
    {
        std::allocator_traits<Allocator>::deallocate(alloc, m_map[0], m_block_size);
        m_map[0] = nullptr;
        m_map_size--;
        m_front_index = 0;
    }
   
    m_size--;

    std::cout << "m_map_size = " << m_map_size << std::endl;
    std::cout << "m_front_index = " << m_front_index << std::endl;
    std::cout << "m_back_index = " << m_back_index << std::endl;
    std::cout << "m_size = " << m_size << std::endl;
}