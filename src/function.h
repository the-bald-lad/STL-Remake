//
// Created by samjb on 15/11/2025.
//

#pragma once

#include "function_internal.h"

#include "util.h"

namespace stl {

// TODO: Change to support binding values at creation
template <typename TReturnType, typename... TArgs>
class Function
{
public:
    explicit Function(TReturnType(*func)(TArgs...))
    {
        m_callable = new function::CallableFromPointer<TReturnType, TArgs...>(func);
    }

    template <typename TFunctor>
    explicit Function(TFunctor&& functor)
    {
        m_callable = new function::CallableFromFunctor<TReturnType, TArgs...>(util::forward<TFunctor>(functor));
    }

    Function(const Function& other) = delete;
    Function operator=(const Function& other) = delete;

    Function(Function&& other) noexcept
        : m_callable(util::move(other.m_callable))
    {
        delete other.m_callable;
        other.m_callable = nullptr;
    }

    Function& operator=(Function&& other) noexcept
    {
        if (this == &other)
        {
            return *this;
        }

        m_callable = other.m_callable;
        delete other.m_callable;
        other.m_callable = nullptr;
        return *this;
    }

    ~Function()
    {
        delete m_callable;
        m_callable = nullptr;
    }

    TReturnType operator()(TArgs&&... args)
    {
        return m_callable->Invoke(util::forward<TArgs>(args)...);
    }

private:
    function::CallableBase<TReturnType, TArgs...>* m_callable;
};

}