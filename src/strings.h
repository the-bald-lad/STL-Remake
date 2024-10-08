//
// Created by samjb on 23/06/2024.
//

#pragma once

#include "move.h"

#include <ostream>
#include "stlint.h"

#include <string.h>

class String
{
public:
    using ValueType = const char;
    using Iterator = Iterating::Iterator<String>;
    String()
    {
    }

    String(char* data) noexcept
        : m_string(data)
    {
        setSize();
    }
    String(const sizet& size, const char fill)
        : m_size(size)
    {
        m_string = static_cast<char*>(::operator new(size+1 * sizeof(char)));

        {
            sizet i = 0;
            for (; i < size; i++)
                m_string[i] = fill;
            m_string[++i] = '\0';
        }

        m_size = size;
    }

    String(const String& copy) noexcept
        : m_string(copy.m_string)
    {
        setSize();
    }
    String(String&& move) noexcept
        : m_string(move.m_string)
    {
        setSize();
    }

    constexpr String& operator=(const String& other)
    {
        if (this == &other)
            return *this;

        delete[] m_string;

        m_string = new char[strlen(other.m_string) + 1];
        strcpy(m_string, other.m_string);

        setSize();

        return *this;
    }

    constexpr char& operator[](const sizet& index) { return m_string[index]; }
    constexpr const char& operator[](const sizet& index) const { return m_string[index]; }

    // Iterators
    Iterator begin()
    {
        return Iterator(m_string);
    }

    Iterator end()
    {
        return Iterator(m_string + m_size);
    }

    // Iterators
    [[nodiscard]] Iterator begin() const
    {
        return Iterator(m_string);
    }

    [[nodiscard]] Iterator end() const
    {
        return Iterator(m_string + m_size - 1);
    }

    [[nodiscard]] const char* get_raw() const
    {
        return m_string;
    }

private:
    void setSize()
    {
        for (int i = 0; m_string[i] != '\0'; i++)
            m_size++;
    }

    char* m_string = nullptr;
    uint32t m_size = 0;
};

namespace std
{
    inline ostream& operator<<(ostream& out_stream, const String& str) { return out_stream << str.get_raw(); }
}