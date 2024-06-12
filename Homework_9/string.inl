#include "string.hpp"
#include <string.h>

size_t String::counter = 0;

size_t String::calculate_length(const char *str)
{
    size_t len = 0;
    while (str[len] != '\0')
        ++len;

    return len;
}

bool String::is_SSO()
{
    return (Length < SSO_BUFFER_SIZE);
}

char *String::memAlloc_SSO()
{
    if (is_SSO())
    {
        std::cout << "Memory is allocated from stack.\n";
        return sso;
    }
    else
    {
        std::cout << "Memory is allocated from heap.\n";
        return new char[Capacity];
    }
}

String::String(const char *value)
{
    Length = calculate_length(value);
    Capacity = Length * 2;
    data = memAlloc_SSO();
    counter++;
    memcpy(data, value, Length);
    
    data[Length] = '\0';
}

String &String::operator=(const char *value)
{
    if(Cow)
        Cow = false;

    if (data && !is_SSO())
        delete[] data;

    Length = calculate_length(value);
    Capacity = Length * 2;
    data = memAlloc_SSO();
   
    memcpy(data, value, Length);

    return *this;
}

String::String(const String &other) : Length(other.Length), Capacity(other.Capacity)
{
    Cow = true;
    data = other.data;
    counter++;
}

String &String::operator=(const String &other)
{
    Cow = true;
    if (this != &other)
    {
        delete[] data;

        Length = other.Length;
        Capacity = other.Capacity;
        data = other.data;
    }
    counter++;
    return *this;
}

String::String(String &&other) : data(other.data), Length(other.Length), Capacity(other.Capacity), Cow(other.Cow)
{
    other.data = nullptr;
    other.Length = 0;
    other.Capacity = 0;
}

String &String::operator=(String &&other)
{
    if (this != &other)
    {
        delete[] data;
        data = other.data;
        Length = other.Length;
        Capacity = other.Capacity;

        Cow = other.Cow;
        other.data = nullptr;
        other.Length = 0;
        other.Capacity = 0;
    }
    return *this;
}

String::~String()
{
    if (!is_SSO() && !Cow)
    {
        std::cout << "NOT SSO\n";
        delete[] data;
    }
}

std::ostream &operator<<(std::ostream &os, const String &str)
{
    for (size_t i = 0; i < str.Length; ++i)
        os << str.data[i];

    return os;
}

size_t String::length() const
{
    return Length;
}

size_t String::capacity() const
{
    return Capacity;
}

void String::resize(size_t newSize)
{
    if(Cow)
        modify();

    Length = newSize;
    Capacity = newSize * 2;

    char *temp = new char[newSize];
    for (size_t i = 0; i < newSize; i++)
        temp[i] = data[i];

    data = temp;
}

void String::push_back(const char &item)
{   
    if(Cow)
        modify();
   
    if (Length == Capacity)
    {
        char *temp = memAlloc_SSO();
        for (size_t i = 0; i < Length; i++)
            temp[i] = data[i];

        delete[] data;
        data = temp;
        Capacity *= 2;
    }
    data[Length] = item;
    Length++;
}

void String::pop_back()
{   
    if(Cow)
        modify();
    
    if (Length == 0)
        return;

    char *temp = data;
    memcpy(data, temp, Length - 1);
    
    Length--;
}


String &String::swap(String &str)
{
    size_t tempSize = Length;
    Length = str.Length;
    str.Length = tempSize;

    size_t tempCap = Capacity;
    Capacity = str.Capacity;
    str.Capacity = tempCap;

    char *temp = data;
    data = str.data;
    str.data = temp;

    return *this;
}

String String::operator+(const String &str)
{
    size_t new_Length = str.Length + Length;
    size_t new_Capacity = new_Length * 2;
    char *temp = new char[new_Capacity];

    for (size_t i = 0; i < Length; i++)
        temp[i] = data[i];

    for (size_t i = 0; i < str.Length; i++)
        temp[Length + i] = str.data[i];

    return String(temp);
}

void String::modify()
{
    Cow = false;
    char *temp = data;
    data = memAlloc_SSO();
    memcpy(data, temp, Length);
    counter--;
}