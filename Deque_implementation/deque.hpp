#pragma once
#include <memory>
#include <cassert>

template <class T, class Allocator = std::allocator<T>>
class Deque
{
public:
    class Iterator
    {
    private:
        T **map; 
        size_t blockSize;
        size_t blockIdx;
        size_t elemIdx;

    public:
        Iterator(T **map, size_t blockSize, size_t blockIdx, size_t elemIdx)
            : map(map), blockSize(blockSize), blockIdx(blockIdx), elemIdx(elemIdx) {}

        T &operator*() const;
        Iterator &operator++();
        Iterator operator++(int);
        Iterator operator==(const Iterator& other);
        bool operator!=(const Iterator &other) const;
    };

    Deque() = default;
    Deque(size_t count);
    Deque(size_t count, const T &value);
    Deque(const Deque<T, Allocator> &other);
    Deque(Deque<T, Allocator> &&other) noexcept;
    Deque<T, Allocator> &operator=(const Deque<T, Allocator> &other);
    Deque<T, Allocator> &operator=(Deque<T, Allocator> &&other) noexcept;

    size_t size();
    const T &operator[](size_t pos) const;
    void printMatrix() const;
    void print() const;
    void push_back(const T &value);
    void push_back(T &&value);
    void pop_back();
    void push_front(const T &value);
    void push_front(T &&value);
    void pop_front();

    Iterator begin();
    Iterator end();

private:
    T **m_map;
    size_t m_map_size = 0;
    size_t m_size = 0;
    size_t m_block_size = 4;

    size_t m_front_index = 0;
    size_t m_back_index = 0;
};

#include "deque.inl"