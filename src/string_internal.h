//
// Created by samjb on 27/09/2024.
//

#pragma once

#include "iterator.h"
#include "stlint.h"

#include <exception>

template<typename T>
class string_internal
{
public:
    using ValueType = T;
    using Iterator = Iterating::Iterator<string_internal>;

    // Default
    string_internal() = default;

    // Actual constructors
    string_internal(const T* data)
    {
        if (data == nullptr)
            throw std::exception();

        while (data[m_size] != '\0') {
            ++m_size;
        }

        if (m_size < 15 && !m_is_heap_alloc)
            stack_alloc(data);
        else
            heap_alloc(data);
    }
    string_internal(const T& fill, const sizet size)
    {
        heap_alloc(fill, size);
    }

    // Copy and move constructors
    string_internal(const string_internal& other) noexcept
        : m_contents(nullptr), m_size(other.m_size), m_is_heap_alloc(other.m_is_heap_alloc)
    {
        if (m_is_heap_alloc) {
            heap_alloc(other.m_contents, m_size);
        } else {
            stack_alloc(other.m_contents);
        }
    }
    string_internal(string_internal&& other) noexcept
        : m_contents(nullptr), m_size(other.m_size), m_is_heap_alloc(other.m_is_heap_alloc)
    {
        other.m_contents = nullptr;
        other.m_size = 0;
        other.m_is_heap_alloc = false;
    }

    // Equals overloads
    string_internal& operator=(const T* data)
    {
        if (data == m_contents)
            return *this;

        sizet data_size = 0;
        for (int i = 0; data[i] != '\0'; i++)
            data_size++;

        if (data_size < 15 && !m_is_heap_alloc)
            stack_alloc(data, data_size);
        else
            heap_alloc(data, data_size);

        return *this;
    }
    constexpr string_internal& operator=(const string_internal& other)
    {
        if (this == &other)
            return *this;

        if (m_is_heap_alloc)
            delete[] m_contents;

        m_size = other.m_size;
        m_is_heap_alloc = other.m_is_heap_alloc;

        if (m_is_heap_alloc) {
            heap_alloc(other.m_contents, m_size);
        } else {
            stack_alloc(other.m_contents);
        }

        return *this;
    }
    string_internal& operator=(string_internal&& other) noexcept
    {
        if (this == &other)
            return *this;

        if (m_is_heap_alloc) {
            delete[] m_contents;
        }

        m_contents = other.m_contents;
        m_size = other.m_size;
        m_is_heap_alloc = other.m_is_heap_alloc;

        other.m_contents = nullptr;
        other.m_size = 0;
        other.m_is_heap_alloc = false;

        return *this;
    }

    // Indexing
    // Index so that chars can be changed
    T& operator[](const sizet& index)
    {
        if (index >= m_size)
            throw std::exception();

        return m_contents[index];
    }

    // Destructors
    ~string_internal()
    {
        if (m_is_heap_alloc)
        {
            delete[] m_contents;
            m_contents = nullptr;
        }
    }

    // Iterators
    [[nodiscard]] Iterator begin() { return Iterator(m_contents); }
    [[nodiscard]] Iterator end() { return Iterator(m_contents + m_size); }
    [[nodiscard]] Iterator begin() const { return Iterator(m_contents); }
    [[nodiscard]] Iterator end() const { return Iterator(m_contents + m_size); }

    [[nodiscard]] const T* get_raw() const
    {
        return m_contents;
    }

private:
    // Stack based allocations
    void stack_alloc(const T* data)
    {
        if (m_is_heap_alloc)
            heap_alloc(data);

        m_contents = const_cast<T*>(data);
    }
    void stack_alloc(const T* data, const sizet& size)
    {
        if (m_is_heap_alloc)
            heap_alloc(data, size);

        m_contents = const_cast<T*>(data);

        //m_contents = data;
        m_size = size;
    }

    // Heap based allocations
    void heap_alloc(const T* data)
    {
        m_is_heap_alloc = true;

        m_contents = new T[m_size + 1];
        std::copy(data, data + m_size, m_contents);
        m_contents[m_size] = '\0';
    }
    void heap_alloc(const T* data, const sizet& size)
    {
        m_is_heap_alloc = true;

        m_contents = new T[m_size + 1]; // +1 for null terminator
        std::copy(data, data + m_size, m_contents);
        m_contents[m_size] = '\0';

        m_size = size;
    }
    void heap_alloc(const T& fill, const sizet& size)
    {
        m_is_heap_alloc = true;

        auto* temp_contents = static_cast<T*>(::operator new(sizeof(T) * size));
        for (int i = 0; i < size; i++)
            temp_contents[i] = fill;

        m_contents = temp_contents;
        m_size = size;
    }

    // Holds string pointer
    T* m_contents = nullptr;

    // Size of string
    sizet m_size = 0;

    // If heaped, don't then stack alloc
    bool m_is_heap_alloc = false;
};