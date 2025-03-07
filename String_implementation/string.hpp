#pragma once
#include <iostream>

class String
{
    char* data = nullptr;
    size_t Length = 0, Capacity = 0;
    size_t calculate_length(const char* str);

    static const size_t SSO_BUFFER_SIZE = 16;
    char sso[SSO_BUFFER_SIZE];
    bool is_SSO();
    char* memAlloc_SSO();

    bool Cow = false;
    String* str;
    
public:
    static size_t counter;

    String() = default;

    String(const char* value);
    String &operator=(const char* value);

    String(const String &other);
    String &operator=(const String &other);

    String(String &&other);
    String &operator=(String &&other);

    ~String();

    friend std::ostream& operator<<(std::ostream& os, const String& str);

    size_t length() const;
    size_t capacity() const;
    
    void resize(size_t newSize);

    void push_back(const char &item);
    void pop_back();

    String& swap(String& str);

    String operator+(const String &str);

    void modify();
};

#include "string.inl"