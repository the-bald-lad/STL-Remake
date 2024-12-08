//
// Created by samjb on 15/11/2024.
//

#pragma once


namespace stl
{
    template <typename T>
    class UniquePointer
    {
    public:
        UniquePointer() noexcept
            : m_ptr(nullptr)
        {
        }
        explicit UniquePointer(T* p) noexcept
            : m_ptr(p)
        {
        }
        // Delete the copy constructor
        UniquePointer(const UniquePointer& other) = delete;

        UniquePointer(UniquePointer&& other) noexcept
            : m_ptr(util::move(other.m_ptr))
        {
        }
        ~UniquePointer()
        {
            delete m_ptr;
            m_ptr = nullptr;
        }

        //[[nodiscard]] UniquePointer& operator=(const UniquePointer&) noexcept = default;
        UniquePointer& operator=(UniquePointer&& other) noexcept
        {
            if (this != &other)
            {
                delete m_ptr;  // Delete existing resource
                m_ptr = other.m_ptr;  // Steal the pointer
                other.m_ptr = nullptr;  // Null out the source pointer
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
    return stl::UniquePointer<T>(new T(std::forward<Args>(args)...));
}
