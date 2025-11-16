//
// Created by samjb on 16/11/2025.
//

#pragma once

namespace traits {

    template <typename T_>
    struct remove_ref
    { using type = T_; };

    template <typename T_>
    struct remove_ref<T_&>
    { using type = T_; };

    template <typename T_>
    struct remove_ref<T_&&>
    { using type = T_; };

    template <typename T_>
    struct remove_const
    { using type = T_; };

    template <typename T_>
    struct remove_const<const T_>
    { using type = T_; };

    template <typename T_>
    struct remove_volatile
    { using type = T_; };

    template <typename T_>
    struct remove_volatile<volatile T_>
    { using type = T_; };

    template <typename T_>
    struct remove_cv
    { using type = remove_const<typename remove_volatile<T_>::type>::type; };

    template <typename T_>
    using remove_cv_t = remove_cv<T_>::type;

    template <typename T_>
    struct decay
    { using type = remove_cv<typename remove_ref<T_>::type>::type; };

    template <typename T_, std::size_t TSize>
    struct decay<T_[TSize]>
    { using type = T_*; };

    template <typename TReturnType, typename... TArgs>
    struct decay<TReturnType(TArgs...)>
    { using type = TReturnType(*)(TArgs...); };

    template <typename T_>
    using decay_t = decay<T_>::type;

    template <typename T_> constexpr bool is_lvalue(T_&)  { return true; }
    template <typename T_> constexpr bool is_lvalue(T_&&) { return false; }

}