#ifndef TemplateTools_hpp
#define TemplateTools_hpp

#include <iostream>
#include <sstream>
#include "IDExpressManager.hpp"

template<typename T>
class NumericProvider;

template<typename T, int N = 1, typename... Providers>
class IndexProvider;

template<typename T>
class TemporaryProvider;

template<typename T, template<typename>class DataSource = NumericProvider, typename... Providers>
class GuardType;

template<typename T, int Demention = 1, typename... Providers>
class GuardArray;

//--------------------------------------------------------------------------
//                             GT template tools

namespace GT {
    
    //---------------------------------------------------------------------------
    //                              GT::type_traits
    
    template<typename T>
    struct type_traits {
        typedef T value_type;
    };
    
    template<typename T, template<typename>class DataSource, typename... Providers>
    struct type_traits<GuardType<T, DataSource, Providers...> > {
        typedef T value_type;
    };
    
    template<typename T>
    using RawType = typename std::remove_cv<
    typename std::remove_reference<
    typename std::remove_pointer<T>::type>::type>::type;
    
    template<typename T>
    struct isOriginalType {
        enum { value = std::is_same<typename type_traits<RawType<T> >::value_type, T>::value };
    };
    
    template<typename T>
    struct isNumericProvider {
        template<typename U>
        static int check(const NumericProvider<U>*) { return 1; };
        static char check(...) { return 0; }
        enum { value = sizeof(check((T*)NULL))==sizeof(int) };
    };
    
    template<typename T>
    struct isIndexProvider {
        template<typename U, int N, typename... Providers>
        static int check(const IndexProvider<U, N, Providers...>*) { return 1; };
        static char check(...) { return 0; }
        enum { value = sizeof(check((T*)NULL))==sizeof(int) };
    };
    
    template<typename T>
    struct isTemporaryProvider {
        template<typename U>
        static int check(const TemporaryProvider<U>*) { return 1; };
        static char check(...) { return 0; }
        enum { value = sizeof(check((T*)NULL))==sizeof(int) };
    };
    
    
    
#define PRE_VALUE_BE_READED_DO(data)\
    if(std::is_base_of<ThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ThreadSafetyProvider&)data).thread_lock();\
    }\
    else if(std::is_base_of<ArrayThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ArrayThreadSafetyProvider&)data).thread_lock(data);\
    }\
    if(std::is_base_of<ValueObserverProvider<typename GT::RawType<decltype(data)>::value_type>, GT::RawType<decltype(data)> >::value) {\
        ((ValueObserverProvider<typename GT::RawType<decltype(data)>::value_type>&)data).CallReadedCallback((data).Data());\
    }
    
#define END_VALUE_BE_READED_DO(data)\
    if(std::is_base_of<ThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ThreadSafetyProvider&)data).thread_unlock();\
    }\
    else if(std::is_base_of<ArrayThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ArrayThreadSafetyProvider&)data).thread_unlock(data);\
    }\
    if(std::is_base_of<IndexProvider<typename GT::RawType<decltype(data)>::value_type>, decltype(data)>::value) {\
        OUTPUT_TRACE_SWITCH__((data).OutputExpres());\
        OUTPUT_TRACE_SWITCH__((data).OutputArray());\
    }


#define PRE_OLD_TO_NEW_VALUE_DO(data)\
    if(std::is_base_of<ThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ThreadSafetyProvider&)data).thread_lock();\
    }\
    else if(std::is_base_of<ArrayThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ArrayThreadSafetyProvider&)data).thread_lock(data);\
    }\
    GT::RawType<decltype((data).Data())> oldValue;\
    if(std::is_base_of<ValueObserverProvider<typename GT::RawType<decltype(data)>::value_type>, GT::RawType<decltype(data)>>::value) {\
        oldValue = (data).Data();\
    }


#define END_OLD_TO_NEW_VALUE_DO(data)\
    if(std::is_base_of<ThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ThreadSafetyProvider&)data).thread_unlock();\
    }\
    else if(std::is_base_of<ArrayThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ArrayThreadSafetyProvider&)data).thread_unlock(data);\
    }\
    if(std::is_base_of<ValueObserverProvider<typename GT::RawType<decltype(data)>::value_type>, GT::RawType<decltype(data)>>::value) {\
        ((ValueObserverProvider<typename GT::RawType<decltype(data)>::value_type>&)data).CallWroteCallback((data).Data(), oldValue);\
    }
    
#define END_OLD_MAYBE_TO_NEW_VALUE_DO(data)\
    if(std::is_base_of<ThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ThreadSafetyProvider&)data).thread_unlock();\
    }\
    else if(std::is_base_of<ArrayThreadSafetyProvider, GT::RawType<decltype(data)> >::value) {\
        ((ArrayThreadSafetyProvider&)data).thread_unlock(data);\
    }\
    if(std::is_base_of<ValueObserverProvider<typename GT::RawType<decltype(data)>::value_type>, GT::RawType<decltype(data)> >::value) {\
        if(GT::optionalEqual(oldValue,(data).Data()))\
            ((ValueObserverProvider<typename GT::RawType<decltype(data)>::value_type>&)data).CallWroteCallback((data).Data(), oldValue);\
    }
    
    //---------------------------------------------------------------------------
    //                              GT::ResultType
    
#if !SAVE_EXPRES_SLOWER_SPEED
    #define GuardTypeResult(T) T
#else
    #define GuardTypeResult(T) GuardType<T, TP>
#endif
    
    
    
#if !SAVE_EXPRES_SLOWER_SPEED
    
#define CalcResultType(T, op, U)\
    typename std::conditional<\
        (GT::TypePriority<GT::RawType<T> >::N == -1 || GT::TypePriority<GT::RawType<U> >::N == -1)\
        , decltype(std::declval<T>() op std::declval<U>())\
        , GT::ResultType_t<GT::RawType<T>, GT::RawType<U> >\
    >::type
    
#define CalcOperatorResultType(T, op, U)\
    typename std::conditional<\
        (GT::TypePriority<GT::RawType<T> >::N == -1 || GT::TypePriority<GT::RawType<U> >::N == -1)\
        , decltype(std::declval<T>() op std::declval<U>())\
        , GT::ResultTypeMultiply_t<GT::RawType<T>, GT::RawType<U> >\
    >::type
    
#else
    
#define CalcResultType(T, op, U)\
    GuardType<typename std::conditional<\
        (GT::TypePriority<GT::RawType<T> >::N == -1 || GT::TypePriority<GT::RawType<U> >::N == -1)\
        , decltype(std::declval<T>() op std::declval<U>())\
        , GT::ResultType_t<GT::RawType<T>, GT::RawType<U> >\
    >::type, TP>
    
#define CalcOperatorResultType(T, op, U)\
    GuardType<typename std::conditional<\
        (GT::TypePriority<GT::RawType<T> >::N == -1 || GT::TypePriority<GT::RawType<U> >::N == -1)\
        , decltype(std::declval<T>() op std::declval<U>())\
        , GT::ResultTypeMultiply_t<GT::RawType<T>, GT::RawType<U> >\
    >::type, TP>
#endif
    
    template<typename T>
    struct TypePriority {
        enum { N = -1 };
    };
    
    template<int T>
    struct TypeFromPriority {
        typedef long double type;
    };
    
    template <typename T, typename U>
    struct ResultType {
        enum { P_T = TypePriority<T>::N};
        enum { P_U = TypePriority<U>::N};
        enum { P = (P_T > P_U ? P_T : P_U)};
        typedef typename TypeFromPriority<
        (P+1)/2*2 * ((P==31||P==32)?1:2)
        >::type type;
    };
    
    template<typename T, typename U>
    using ResultType_t = typename ResultType<RawType<T>, RawType<U> >::type;
    
    template <typename T, typename U>
    struct ResultTypeMultiply {
        enum { P_T = TypePriority<T>::N};
        enum { P_U = TypePriority<U>::N};
        enum { P = (P_T > P_U ? P_T : P_U)};
        typedef typename TypeFromPriority<
        (P+1)/2*2 * ((P==31||P==32)?1:2) - (P_T%2==1&&P_U%2==1)*(P<=32)
        >::type type;
    };
    
    template<typename T, typename U>
    using ResultTypeMultiply_t = typename ResultTypeMultiply<RawType<T>, RawType<U> >::type;
    
    
    template<> struct TypePriority<bool> {             enum { N = 0 }; };
    template<> struct TypePriority<unsigned char> {    enum { N = 1 }; };
    template<> struct TypePriority<char> {             enum { N = 2 }; };
    template<> struct TypePriority<unsigned short> {   enum { N = 3 }; };
    template<> struct TypePriority<short> {            enum { N = 4 }; };
    template<> struct TypePriority<unsigned int> {     enum { N = 7 }; };
    template<> struct TypePriority<int> {              enum { N = 8 }; };
    template<> struct TypePriority<unsigned long> {    enum { N = 15 }; };
    template<> struct TypePriority<long> {             enum { N = 16 }; };
    template<> struct TypePriority<unsigned long long> { enum { N = 31 }; };
    template<> struct TypePriority<long long> {        enum { N = 32 }; };
    template<> struct TypePriority<float> {            enum { N = 64 }; };
    template<> struct TypePriority<double> {           enum { N = 128 }; };
    template<> struct TypePriority<long double> {      enum { N = 256 }; };
    
    
    template<> struct TypeFromPriority<0> { typedef bool             type; };
    template<> struct TypeFromPriority<1> { typedef unsigned short   type; };
    template<> struct TypeFromPriority<2> { typedef short            type; };
    template<> struct TypeFromPriority<3> { typedef unsigned short   type; };
    template<> struct TypeFromPriority<4> { typedef short            type; };
    template<> struct TypeFromPriority<7> { typedef unsigned int     type; };
    template<> struct TypeFromPriority<8> { typedef int              type; };
    template<> struct TypeFromPriority<15> { typedef unsigned long   type; };
    template<> struct TypeFromPriority<16> { typedef long            type; };
    template<> struct TypeFromPriority<31> { typedef unsigned long long type; };
    template<> struct TypeFromPriority<32> { typedef long long       type; };
    template<> struct TypeFromPriority<64> { typedef float           type; };
    template<> struct TypeFromPriority<128> { typedef double         type; };
    template<> struct TypeFromPriority<256> { typedef long double    type; };
    
    
    //---------------------------------------------------------------------------
    //                          if support operator
    
    template<typename T>
    struct isDereferencable {
        template<typename U>
        static decltype(*(std::declval<U>()), std::true_type())
        check(U*) {
            return std::true_type();
        }
        static std::false_type check(...) {
            return std::false_type();
        }
        enum { value = std::is_same<decltype(check((T*)NULL)), std::true_type>::value };
    };
    
    template<typename T>
    struct isStringable {
        template<typename U>
        static decltype(std::declval<std::ostream&>() << std::declval<U>(), std::true_type())
        check(U*) {
            return std::true_type();
        }
        static std::false_type check(...) {
            return std::false_type();
        }
        enum { value = std::is_same<decltype(check((T*)NULL)), std::true_type>::value };
    };
    
    template<typename T, typename U>
    struct isEqualable {
        static decltype(std::declval<U>() == std::declval<U>(), std::true_type())
        check(U*) {
            return std::true_type();
        }
        static std::false_type check(...) {
            return std::false_type();
        }
        enum { value = std::is_same<decltype(check((T*)NULL)), std::true_type>::value };
    };
    
    template<typename T, typename U, typename = typename std::enable_if<isEqualable<T, U>::value>::type>
    bool optionalEqual(const T& data1, const U& data2) {
        return data1 == data2;
    }
    
    template<typename T, typename U, typename = typename std::enable_if<!isEqualable<T, U>::value>::type>
    bool optionalEqual(T&, const U&) {
        return false;
    }
    
    
    //---------------------------------------------------------------------------
    //                          isContailMultiFirstType
    
    template<int N, typename...Args>
    struct TemplateParameterType;
    
    
    template<typename T, typename...Args>
    struct TemplateParameterType<sizeof...(Args)+1, T, Args...> {
        using FirstType = T;
    };
    
    template<>
    struct TemplateParameterType<0> {
        using FirstType = void;
    };
    
    template<typename T, int N, typename... Args>
    struct ContainMultiFirstType;

    template<typename T, int N, typename U, typename... Args>
    struct GetRestOfContailMultiFirstType {
        using type = ContainMultiFirstType<T, N-1, Args...>;
    };
    
    template<typename T, int N, typename... Args>
    struct ContainMultiFirstType {
        using FirstType = typename TemplateParameterType<sizeof...(Args), Args...>::FirstType;
        using NextCondition = typename GetRestOfContailMultiFirstType<T, N, Args...>::type;
        enum { value = std::is_same<T, FirstType>::value ? true : NextCondition::value };
    };
    
    template<typename T, typename U>
    struct ContainMultiFirstType<T, 1, U> {
        enum { value = std::is_same<T, U>::value };
    };
    
    template<typename T>
    struct ContainMultiFirstType<T, 0> {
        enum { value = false };
    };
    
    template<typename T, typename... Args>
    struct isContainMultiFirstType {
        enum { value = ContainMultiFirstType<T, sizeof...(Args), Args...>::value };
    };
    
    
    //---------------------------------------------------------------------------
    //                              Get Parameter with pos
    
    template<int N, int a, int...args>
    struct GetVec;
    
    template<int a, int...args>
    struct GetVec<1, a, args...> {
        enum { value = a };
    };
    
    template<int N, int a, int...args>
    struct GetVec {
        enum { value = GetVec<N-1, args...>::value };
    };
    
    
    //---------------------------------------------------------------------------
    //                              MultiplyParameters
    
    template<int n, int i, int ...left>
    struct NMultiply {
        enum { value = i * NMultiply<n-1, left...>::value };
    };
    
    template<int i>
    struct NMultiply<1, i> {
        enum { value = i };
    };
    
    template<int ...n>
    struct MultiplyParameters {
        enum { value = NMultiply<sizeof...(n), n...>::value };
    };
    
    
    //---------------------------------------------------------------------------
    //                          Recursive pack template class N times
    
    template<int N, template<typename>class tmp, typename T>
    struct RecursivePack;
    
    template<template<typename>class tmp, typename T>
    struct RecursivePack<1, tmp, T> {
        typedef tmp<T> type;
    };
    
    template<int N, template<typename>class tmp, typename T>
    struct RecursivePack {
        typedef tmp<typename RecursivePack<N-1, tmp, T>::type> type;
    };
}



namespace std {
    //---------------------------------------------------------------------------
    //                          R value translate
    
    template<typename T, typename = typename T::isGuardType>
    typename T::value_type&& move(T& data) {
        return static_cast<typename T::value_type&&>(data.Data());
    }
    
    template<typename T, typename = typename T::isGuardType>
    const typename T::value_type&& move(const T& data) {
        return static_cast<const typename T::value_type&&>(data.Data());
    }
    
    template<typename T, typename = typename T::isGuardType>
    typename T::value_type&& move(T&& data) {
        return static_cast<typename T::value_type&&>(data.Data());
    }
    
    template<typename T, typename = typename T::isGuardType>
    const typename T::value_type&& move(const T&& data) {
        return static_cast<const typename T::value_type&&>(data.Data());
    }
    
    template<typename T>
    typename T::value_type&& forwards(typename std::remove_reference<typename T::isGuardType>::type& data)
    {
        return static_cast<typename T::value_type&&>(data.Data());
    }
    
    template<typename T>
    const typename T::value_type&& forwards(const typename std::remove_reference<typename T::isGuardType>::type& data)
    {
        return static_cast<const typename T::value_type&&>(data.Data());
    }
    
    template<typename T>
    typename T::value_type&& forwards(typename std::remove_reference<typename T::isGuardType>::type&& data)
    {
        return static_cast<typename T::value_type&&>(data.Data());
    }
    
    template<typename T>
    const typename T::value_type&& forwards(const typename std::remove_reference<typename T::isGuardType>::type&& data)
    {
        return static_cast<const typename T::value_type&&>(data.Data());
    }
}

#endif /* TemplateTools_hpp */
