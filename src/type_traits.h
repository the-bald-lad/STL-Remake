//
// Created by samjb on 16/11/2025.
//

#pragma once

namespace traits {

    template <typename T_> constexpr bool is_const = false;
    template <typename T_> constexpr bool is_const<const T_> = true;

    template <typename T_> constexpr bool is_reference = false;
    template <typename T_> constexpr bool is_reference<T_&> = true;
    template <typename T_> constexpr bool is_reference<T_&&> = true;

    template <class> constexpr bool is_array = false;
    template <class T_, sizet TSize> constexpr bool is_array<T_[TSize]> = true;
    template <class T_> constexpr bool is_array<T_[]> = true;

    template <typename T_> constexpr bool is_lvalue = false;
    template <typename T_> constexpr bool is_lvalue<T_&> = true;
    template <typename T_> constexpr bool is_lvalue<T_&&> = false;

    template <typename T_>
    constexpr bool is_function = !is_const<const T_> && !is_reference<T_>;

    template <bool>
    struct select
    {
        template <typename T_, typename>
        using _Apply = T_;
    };

    template <>
    struct select<false>
    {
        template <typename, typename T_>
        using _Apply = T_;
    };

    template <typename T_>
    struct remove_reference
    { using type = T_; };

    template <typename T_>
    struct remove_reference<T_&>
    { using type = T_; };

    template <typename T_>
    struct remove_reference<T_&&>
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
    struct remove_array_extent
    { using type = T_; };

    template <typename T_, sizet TSize>
    struct remove_array_extent<T_[TSize]>
    { using type = T_; };

    template <typename T_>
    struct remove_array_extent<T_[]>
    { using type = T_; };

    template <typename T_>
    struct array_to_pointer
    { using type = T_; };

    template <typename T_, sizet TSize>
    struct array_to_pointer<T_[TSize]>
    { using type = T_*; };

    template <typename T_>
    struct array_to_pointer<T_[]>
    { using type = T_*; };

    template <typename T_>
    struct decay
    {
        using _1 = remove_reference<T_>;
        using _2 = select<is_function<T_>>::template _Apply<array_to_pointer<T_>, remove_cv<T_>>;
        using type = select<is_array<T_>>::template _Apply<array_to_pointer<remove_array_extent<T_>>, _2>::type;
    };

    template <typename T_>
    using decay_t = decay<T_>::type;

}