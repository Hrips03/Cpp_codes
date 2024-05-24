#include <iostream>
#include <cassert>
#include "vector_implementation.hpp"

template <typename T>
Vector<T>::Vector(const Vector &other) : sizeOfVec(other.sizeOfVec), capOfVec(other.capOfVec)
{
    data = new T[capOfVec];

    for (size_t i = 0; i < sizeOfVec; i++)
        data[i] = other.data[i];
}

template <typename T>
Vector<T>::Vector(Vector &&other) : sizeOfVec(other.sizeOfVec), capOfVec(other.capOfVec), data(other.data)
{
    other.data = nullptr;
    other.sizeOfVec = 0;
    other.capOfVec = 0;
}

template <typename T>
Vector<T> &Vector<T>::operator=(const Vector<T> &v)
{
    if (this != &v)
    {
        delete[] data;

        sizeOfVec = v.sizeOfVec;
        capOfVec = v.capOfVec;

        data = new int[capOfVec];
        for (size_t i = 0; i < sizeOfVec; i++)
            data[i] = v.data[i];
    }

    return *this;
}

template <typename T>
Vector<T> &Vector<T>::operator=(Vector<T> &&other)
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        sizeOfVec = other.sizeOfVec;
        capOfVec = other.capOfVec;

        other.data = nullptr;
        other.sizeOfVec = 0;
        other.capOfVec = 0;
    }
    return *this;
}

template <typename T>
Vector<T>::~Vector()
{
    delete[] data;
    data = 0;
}

template <typename T>
size_t Vector<T>::size() const
{
    return sizeOfVec;
}

template <typename T>
size_t Vector<T>::capacity() const
{
    return capOfVec;
}

template <typename T>
void Vector<T>::print()
{
    for (int i = 0; i < sizeOfVec; i++)
        std::cout << data[i] << " ";
    std::cout << '\n';
}

template <typename T>
void Vector<T>::push_back(const T &data)
{
    int *temp;
    if (sizeOfVec == capOfVec)
    {
        temp = new int[capOfVec * 2];
        // temp = static_cast<int *>(alloca(capacity * 2 * sizeof(int)));

        for (int i = 0; i < capOfVec; i++)
            temp[i] = this->data[i];

        delete[] this->data;
        this->data = temp;
        capOfVec *= 2;
    }

    this->data[sizeOfVec] = data;
    sizeOfVec++;
}

template <typename T>
void Vector<T>::pop_back()
{
    if (sizeOfVec == 0)
        return;

    int *temp = new int[sizeOfVec - 1];
    for (int i = 0; i < sizeOfVec - 1; i++)
        temp[i] = data[i];

    delete[] data;
    data = temp;

    sizeOfVec--;
}

template <typename T>
bool Vector<T>::empty()
{
    if (sizeOfVec == 0)
        return true;

    return false;
}

template <typename T>
void Vector<T>::clear()
{
    delete[] data;
    sizeOfVec = 0;
    capOfVec = 0;
}

template <typename T>
const T &Vector<T>::operator[](size_t index)
{
    return data[index];
}

template <typename T>
const T &Vector<T>::at(size_t index)
{

    try
    {
        if (data[index])
            return data[index];
        else
            throw std::out_of_range("Error");
    }
    catch (const std::out_of_range &err)
    {
        std::cerr << "Out of Range error: " << err.what() << '\n';
        std::terminate;
    }
}

template <typename T>
T *Vector<T>::front()
{
    return *data[0];
}

template <typename T>
T &Vector<T>::back()
{
    return data[sizeOfVec - 1];
}

template <typename T>
void Vector<T>::resize(size_t newSize)
{
    size_t *temp = new size_t[newSize];
    for (int i = 0; i < sizeOfVec; i++)
        temp[i] = data[i];

    delete[] data;
    data = temp;
    sizeOfVec = newSize;

    if (newSize > capOfVec)
        capOfVec = newSize;
}

template <typename T>
void Vector<T>::assign(size_t count, const T &value)
{
    clear();
    for (int i = 0; i < count; i++)
        data[i] = value;

    sizeOfVec = count;
    capOfVec = 2 * sizeOfVec;
}

template <typename T>
void Vector<T>::insert(size_t position, const T &value)
{
    if (position == sizeOfVec)
        push_back(value);
    else if (sizeOfVec == capOfVec)
    {
        T *temp = new T[capOfVec * 2];

        for (int i = 0; i < capOfVec; i++)
            temp[i] = data[i];

        delete[] data;
        data = temp;
        capOfVec *= 2;
    }

    T *temp = new T[capOfVec];
    for (int i = 0; i < position; i++)
        temp[i] = data[i];

    temp[position] = value;

    for (int i = position; i < sizeOfVec; i++)
        temp[i + 1] = data[i];

    delete[] data;
    data = temp;
    sizeOfVec++;
}

template <typename T>
T &Vector<T>::Iterator::operator*() const
{
    return *curr;
}

template <typename T>
typename Vector<T>::Iterator &Vector<T>::Iterator::operator++()
{
    assert(curr);
    if (!curr)
        return *this;

    ++curr;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
    auto temp = *this;
    this->operator++();
    return temp;
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const Iterator &other) const
{
    return curr != other.curr;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin()
{
    return Iterator(data);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end()
{
    return Iterator(data + sizeOfVec);
}
