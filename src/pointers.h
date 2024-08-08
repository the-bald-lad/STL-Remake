//
// Created by samjb on 16/06/2024.
//

#pragma once

namespace dataStructures
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
        UniquePointer(const UniquePointer& other) noexcept
            : m_ptr(other.m_ptr)
        {
        }
        UniquePointer(UniquePointer&& other) noexcept
            : m_ptr(std::move(other.m_ptr))
        {
        }
        ~UniquePointer()
        {
            delete m_ptr;
        }

        [[nodiscard]] UniquePointer& operator=(UniquePointer&&) noexcept = default;
        [[nodiscard]] UniquePointer& operator=(const UniquePointer&) noexcept = default;

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

template<typename T, typename... Args>
inline dataStructures::UniquePointer<T> make_unique(Args&&... args)
{
    T* temp = static_cast<T*>(::operator new(sizeof(T)));
    *temp = std::move(std::forward<Args>(args)...);
    return dataStructures::UniquePointer<T>(temp);
}
