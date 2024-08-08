//
// Created by samjb on 23/06/2024.
//

#pragma once

#include <ostream>

class String
{
public:
    String()
    {
    }
    String(const char* data) noexcept
        : m_string(data)
    {
    }
    String(const String& copy) noexcept
        : m_string(copy.m_string)
    {
    }
    String(String&& move) noexcept
        : m_string(move.m_string)
    {
    }

    [[nodiscard]] const char* get_raw() const
    {
        return m_string;
    }

private:
    const char* m_string = nullptr;
};

namespace std
{
    inline ostream& operator<<(ostream& out_stream, const String& str) { return out_stream << str.get_raw(); }
}