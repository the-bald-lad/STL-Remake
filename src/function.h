//
// Created by samjb on 15/11/2025.
//

#pragma once

#include "util.h"

namespace function {

template <typename TReturnType, typename... TArgs>
class CallableBase
{
public:
    virtual ~CallableBase() = default;
    virtual TReturnType Invoke(TArgs&&... args) = 0;
};

template <typename TReturnType, typename... TArgs>
class CallableFromPointer final : public CallableBase<TReturnType, TArgs...>
{
public:
    using Function = TReturnType(*)(TArgs...);

    explicit CallableFromPointer(const Function func) : m_func(func)
    { }

    TReturnType Invoke(TArgs&&... args) override
    {
        return m_func(util::forward<TArgs>(args)...);
    }

private:
    Function m_func;
};

template <typename TReturnType, typename... TArgs>
class CallableFromFunctor final : public CallableBase<TReturnType, TArgs...>
{
public:
    explicit CallableFromFunctor(auto&& functor)
    {
        m_callable = new FunctorWrapper<std::decay_t<decltype(functor)>>{ util::forward<decltype(functor)>(functor) };
    }

    TReturnType Invoke(TArgs&&... args) override
    {
        return (*m_callable)(util::forward<TArgs>(args)...);
    }

private:
    struct CallableWrapper;
    CallableWrapper* m_callable;

    struct CallableWrapper
    {
        virtual ~CallableWrapper() = default;
        virtual TReturnType operator()(TArgs... args) = 0;
    };

    template <typename Functor>
    class FunctorWrapper final : public CallableWrapper
    {
    public:
        explicit FunctorWrapper(Functor&& f)
            : m_functor(std::move(f))
        { }

        TReturnType operator()(TArgs... args) override
        {
            return m_functor(std::forward<TArgs>(args)...);
        }

    private:
        Functor m_functor;
    };
};

}

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