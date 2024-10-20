#pragma once

template <class T>
struct remove_extent { 
    using type = T;
};

template <class T, size_t N>
struct remove_extent<T[N]> {
    using type = T;
};

template <class T>
struct remove_extent<T[]> {
    using type = T;
};

template <class T>
using remove_extent_t = typename remove_extent<T>::type;


struct false_type{};
struct true_type{};

template<typename T>
struct is_array
{
    using value = false_type;
};
template<typename T>
struct is_array<T[]>
{
    using value = true_type;
};
template<typename T,size_t N>
struct is_array<T[N]>
{
    using value = true_type;
};

template<typename T>
using is_array_t=  typename  is_array<T>::value;


template<class B>
struct enable_if{};

template<>
struct enable_if<true_type>{
    using type = void;
};
template<class B>
using enable_if_t = typename enable_if<B>::type;



template<class T, class U>
struct is_same : false_type {};
 
template<class T>
struct is_same<T, T> : true_type {};

