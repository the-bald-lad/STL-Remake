//
// Created by samjb on 15/11/2024.
//

#pragma once

#include "util.h"

template <typename T>
struct UsageCount
{
    using RefType = T;

    sizet strong_usages = 0;
    sizet weak_usages = 0;
};

template <typename T>
struct MemBlock
{
    using Type = T;

    T* data;
    UsageCount<T>* references;
};

namespace stl
{
    template <typename T>
    class SharedPointer
    {
    public:
        using public_type = T;
        using mem_block_type = MemBlock<T>;

        SharedPointer() = default;

        explicit SharedPointer(mem_block_type* p) noexcept
                : m_data(p)
        {
            incrementStrongCount();
        }
        SharedPointer(const SharedPointer& other) noexcept
            : m_data(other.m_data)
        {
            incrementStrongCount();
        }
        SharedPointer(SharedPointer&& other) noexcept
            : m_data(util::move(other.m_data))
        {
        }

        ~SharedPointer()
        {
            if (m_data->references == nullptr)
                return;

            auto& count_ref = m_data->references;

            --count_ref;

            // If pointer data still in use
            if (count_ref->strong_usages > 0)
                return;

            delete m_data->data;
            m_data->data = nullptr;

            // If weak usages are present
            if (count_ref->weak_usages > 0)
                return;

            delete m_data->references;
            m_data->references = nullptr;
        }

        SharedPointer& operator=(const SharedPointer& other) noexcept
        {
            if (this == &other)
                return *this;

            m_data = other.m_data;

            incrementStrongCount();
            return *this;
        }

        T& operator*()
        {
            return *m_data->data;
        }

        T* operator->()
        {
            return m_data->data;
        }
    private:
        void incrementStrongCount() { ++m_data->references->strong_usages; }

        mem_block_type* m_data;
    };
}

template <typename T, typename... Args>
stl::SharedPointer<T> make_shared(Args&&... args)
{
    constexpr auto c_type_size = sizeof(T);
    constexpr auto c_ref_size = sizeof(UsageCount<T>);
    constexpr auto c_mem_size = sizeof(MemBlock<T>);

    constexpr sizet total_size = c_type_size + c_ref_size + c_mem_size;

    void* raw_memory = ::operator new(total_size);

    auto* base = static_cast<util::byte*>(raw_memory);
    util::byte* temp_memory = base;
    util::byte* temp_count_memory = base + c_type_size;
    util::byte* shared_memory = base + c_type_size + c_ref_size;

    T* temp = new(temp_memory) T(util::move(util::forward<Args>(args)...));

    auto* temp_count = new(temp_count_memory) UsageCount<T>();

    auto* shared = new(shared_memory) MemBlock<T>();
    shared->data = temp;
    shared->references = temp_count;

    if (shared == nullptr || temp == nullptr || temp_count == nullptr)
        exit(EXIT_FAILURE);

    return stl::SharedPointer<T>(shared);
}