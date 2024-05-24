#pragma once
#include <cstddef>

template <typename T>
class Vector
{
    size_t sizeOfVec = 0, capOfVec = 0;
    T *data = nullptr;

public:

    class Iterator
    {
        T *curr = nullptr;

    public:
        Iterator(T *ptr) : curr(ptr) {}

        T &operator*() const;
        Iterator &operator++();
        Iterator operator++(int);
        bool operator!=(const Iterator& other) const;
    };


    Vector() = default;
    Vector(const Vector &other);
    Vector(Vector &&other);
    Vector &operator=(const Vector &other);
    Vector &operator=(Vector &&other);
    ~Vector();

    size_t size() const;
    size_t capacity() const;
    void print();

    void push_back(const T &data);
    void pop_back();

    bool empty();
    void clear();

    const T &operator[](size_t index);
    const T &at(size_t index);

    T* front();
    T &back();

    void resize(size_t newSize);
    void assign(size_t count, const T &value);
    void insert(size_t position, const T &value);

    Iterator begin();
    Iterator end();
};

#include "vector_implementation.inl"