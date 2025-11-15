//
// Created by samjb on 15/11/2024.
//

#pragma once

#include "util.h"

namespace stl
{
    template <typename T>
    class UniquePointer
    {
    public:
        UniquePointer() noexcept
            : m_ptr(nullptr)
        { }
        explicit UniquePointer(T* p) noexcept
            : m_ptr(p)
        { }
        UniquePointer(const UniquePointer& other) = delete;

        UniquePointer(UniquePointer&& other) noexcept
            : m_ptr(util::move(other.m_ptr))
        { }
        ~UniquePointer()
        {
            delete m_ptr;
            m_ptr = nullptr;
        }

        UniquePointer& operator=(UniquePointer&& other) noexcept
        {
            if (this != &other)
            {
                delete m_ptr;
                m_ptr = other.m_ptr;
                other.m_ptr = nullptr;
            }
            return *this;
        }

        T& operator*()
        {
            return *m_ptr;
        }

        T* operator->()
        {
            return m_ptr;
        }
    private:
        T* m_ptr;
    };
}

template <typename T, typename... Args>
stl::UniquePointer<T> make_unique(Args&&... args)
{
    return stl::UniquePointer<T>(new T(util::forward<Args>(args)...));
}
