#ifndef TemplateTools_hpp
#define TemplateTools_hpp

#include <iostream>
#include <sstream>
#include "IDExpressManager.hpp"

namespace gt {

template<typename T>
class NumericProvider;

template<typename T, int N = 1, typename... Providers>
class IndexProvider;

template<typename T>
class TemporaryProvider;

template<typename T>
class ValueObserverProvider;

class IDExpressProvider;

template<typename T, template<typename>class DataSource = NumericProvider, typename... Providers>
class GuardType;

template<typename T, int Demention = 1, typename... Providers>
class GuardArray;


//---------------------------------------------------------------------------
//                              gt::type_traits

template<typename T>
struct type_traits
{
    typedef T value_type;
};

template<typename T, template<typename>class DataSource, typename... Providers>
struct type_traits<GuardType<T, DataSource, Providers...> >
{
    typedef T value_type;
};

template<typename T>
using RawType = typename std::remove_cv<
typename std::remove_reference<
typename std::remove_pointer<T>::type>::type>::type;

template<typename T>
struct isOriginalType
{
    enum { value = std::is_same<typename type_traits<RawType<T> >::value_type, T>::value };
};

template<typename T>
struct isNumericProvider
{
    template<typename U>
    static int check(const NumericProvider<U>*) { return 1; };
    static char check(...) { return 0; }
    enum { value = sizeof(check((RawType<T>*)NULL))==sizeof(int) };
};

template<typename T>
struct isIndexProvider
{
    template<typename U, int N, typename... Providers>
    static int check(const IndexProvider<U, N, Providers...>*) { return 1; };
    static char check(...) { return 0; }
    enum { value = sizeof(check((RawType<T>*)NULL))==sizeof(int) };
};

template<typename T>
struct isTemporaryProvider
{
    template<typename U>
    static int check(const TemporaryProvider<U>*) { return 1; };
    static char check(...) { return 0; }
    enum { value = sizeof(check((RawType<T>*)NULL))==sizeof(int) };
};

template<typename T>
struct isValueObserverProvider
{
    template<typename U>
    static int check(const ValueObserverProvider<U>*) { return 1; };
    static char check(...) { return 0; }
    enum { value = sizeof(check((RawType<T>*)NULL))==sizeof(int) };
};

template<typename T>
struct isIDExpressProvider
{
    static int check(const IDExpressProvider*) { return 1; };
    static char check(...) { return 0; }
    enum { value = sizeof(check((RawType<T>*)NULL))==sizeof(int) };
};

//---------------------------------------------------------------------------
//                          if support operator

template<typename T>
struct isDereferencable
{
    template<typename U>
    static decltype(*(std::declval<U>()), std::true_type())
    check(U*)
    {
        return std::true_type();
    }
    
    static std::false_type check(...)
    {
        return std::false_type();
    }
    enum { value = std::is_same<decltype(check((RawType<T>*)NULL)), std::true_type>::value };
};

template<typename T>
struct isStringable
{
    template<typename U>
    static decltype(std::declval<std::ostream&>() << std::declval<U>(), std::true_type())
    check(U*)
    {
        return std::true_type();
    }
    
    static std::false_type check(...)
    {
        return std::false_type();
    }
    enum { value = std::is_same<decltype(check((RawType<T>*)NULL)), std::true_type>::value };
};

template<typename T, typename U>
struct isEqualable
{
    template<typename V=T, typename W=U>
    static decltype(std::declval<V>() == std::declval<W>(), std::true_type())
    check(void*)
    {
        return std::true_type();
    }
    
    static std::false_type check(...)
    {
        return std::false_type();
    }
    enum { value = std::is_same<decltype(check(NULL)), std::true_type>::value };
};

template<typename T, typename U>
struct isNEqualable
{
    template<typename V=T, typename W=U>
    static decltype(std::declval<V>() != std::declval<W>(), std::true_type())
    check(void*)
    {
        return std::true_type();
    }
    
    static std::false_type check(...)
    {
        return std::false_type();
    }
    enum { value = std::is_same<decltype(check(NULL)), std::true_type>::value };
};


template<typename T>
struct isExistArrayId
{
    template<typename U>
    static decltype(std::declval<U>().array->Id(), std::true_type())
    check(U*)
    {
        return std::true_type();
    }
    
    static std::false_type check(...)
    {
        return std::false_type();
    }
    enum { value = std::is_same<decltype(check((RawType<T>*)NULL)), std::true_type>::value };
};


//---------------------------------------------------------------------------
//                          isContailFirstType

template<int N, typename...Args>
struct TemplateParameterType;


template<int N, typename T, typename...Args>
struct TemplateParameterType<N, T, Args...>
{
    using FirstType = T;
};

template<>
struct TemplateParameterType<0>
{
    using FirstType = void;
};

template<typename T, int N, typename... Args>
struct ContainFirstType;

template<typename T, int N, typename U, typename... Args>
struct GetRestOfContailFirstType
{
    using type = ContainFirstType<T, N-1, Args...>;
};

template<typename T, int N, typename... Args>
struct ContainFirstType
{
    using FirstType = typename TemplateParameterType<sizeof...(Args), Args...>::FirstType;
    using NextCondition = typename GetRestOfContailFirstType<T, N, Args...>::type;
    enum { value = std::is_same<T, FirstType>::value ? true : NextCondition::value };
};

template<typename T, typename U>
struct ContainFirstType<T, 1, U>
{
    enum { value = std::is_same<T, U>::value };
};

template<typename T>
struct ContainFirstType<T, 0>
{
    enum { value = false };
};

template<typename T, typename... Args>
struct isContainFirstType
{
    enum { value = ContainFirstType<T, sizeof...(Args), Args...>::value };
};


//---------------------------------------------------------------------------
//                              Get type with pos

template<int N, typename T, typename...Types>
struct GetTypes;

template<typename T, typename...Types>
struct GetTypes<1, T, Types...>
{
    typedef T type;
};

template<int N, typename T, typename... Types>
struct GetTypes
{
    typedef std::conditional_t<N <= sizeof...(Types)+1, typename GetTypes<N-1, Types...>::type, void>  type;
};

template<int N, typename... Types>
using GetTypes_t = typename GetTypes<N, Types...>::type;

template<int N, typename TemplateClass>
struct GetTplArgs
{
    template<template<typename... U>class Packer, typename... Args>
    static GetTypes_t<N, Args...> Result(Packer<Args...>*);
    
    static void Result(...);
    
    typedef decltype(Result((TemplateClass*)nullptr)) type;
};

template<int N, typename TemplateClass>
using GetTplArgs_t = typename GetTplArgs<N, TemplateClass>::type;

//---------------------------------------------------------------------------
//                              MultiplyParameters

template<int n, int i, int ...left>
struct NMultiply
{
    enum { value = i * NMultiply<n-1, left...>::value };
};

template<int i>
struct NMultiply<1, i>
{
    enum { value = i };
};

template<int ...n>
struct MultiplyParameters
{
    enum { value = NMultiply<sizeof...(n), n...>::value };
};


//---------------------------------------------------------------------------
//                              TypeFilter


template<typename... ExpectTypes>
struct Include
{
};

template<typename... ExcludeTypes>
struct Exclude
{
};

template<template<typename> class Condition>
struct IncludeIf
{
};

template<template<typename> class Condition>
struct ExcludeIf
{
};

template<template<typename> class Condition1, template<typename> class Condition2>
struct ConditionAnd
{
    template<typename T>
    struct tpl {
        enum { value = Condition1<T>::value && Condition2<T>::value };
    };
};

template<template<typename> class Condition1, template<typename> class Condition2>
struct ConditionOr
{
    template<typename T>
    struct tpl {
        enum { value = Condition1<T>::value || Condition2<T>::value };
    };
};


template<typename Filter, typename T>
struct checkFilter
{
    template<typename U=T, typename... Args, typename = std::enable_if_t<isContainFirstType<U, Args...>::value> >
    static std::true_type check(Include<Args...>*);
    template<typename U=T, typename... Args, typename = std::enable_if_t<!isContainFirstType<U, Args...>::value> >
    static std::false_type check(Include<Args...>*);
    
    template<typename U=T, typename... Args, typename = std::enable_if_t<!isContainFirstType<U, Args...>::value> >
    static std::true_type check(Exclude<Args...>*);
    template<typename U=T, typename... Args, typename = std::enable_if_t<isContainFirstType<U, Args...>::value> >
    static std::false_type check(Exclude<Args...>*);
    
    template<typename U=T, template<typename> class condition, typename = std::enable_if_t<condition<U>::value> >
    static std::true_type check(IncludeIf<condition>*);
    template<typename U=T, template<typename> class condition, typename = std::enable_if_t<!condition<U>::value> >
    static std::false_type check(IncludeIf<condition>*);
    
    template<typename U=T, template<typename> class condition, typename = std::enable_if_t<!condition<U>::value> >
    static std::true_type check(ExcludeIf<condition>*);
    template<typename U=T, template<typename> class condition, typename = std::enable_if_t<condition<U>::value> >
    static std::false_type check(ExcludeIf<condition>*);
    
    enum { value = std::is_same<decltype(check<T>((Filter*)nullptr)), std::true_type>::value };
};

template<typename T=void, typename... Base>
struct TypesPacker : public Base...
{
    typedef T type;
    typedef GetTypes_t<1, Base...> base;
};

template<>
struct TypesPacker<void>
{
    typedef void type;
};

template<typename ResultPacker, typename Filter, typename...Types>
struct TypeFilterImpl
{
    typedef TypesPacker<void> types;
};

template<typename ResultPacker, typename Filter, typename T, typename...Types>
struct TypeFilterImpl<ResultPacker, Filter, T, Types...>
{
    typedef std::conditional_t<checkFilter<Filter, T>::value,
                                typename TypeFilterImpl<TypesPacker<T, ResultPacker>, Filter, Types...>::types,
                                typename TypeFilterImpl<ResultPacker, Filter, Types...>::types> types;
};

template<typename ResultPacker, typename Filter, typename T>
struct TypeFilterImpl<ResultPacker, Filter, T>
{
    typedef std::conditional_t<checkFilter<Filter, T>::value,
                                TypesPacker<T, ResultPacker>,
                                ResultPacker> types;
};

template<typename Filter, typename... Types>
struct TypeFilter
{
    typedef typename TypeFilterImpl<TypesPacker<void>, Filter, Types...>::types types;
};

template<typename Filter, typename... Types>
using TypeFilter_t = typename TypeFilter<Filter, Types...>::types;

template<template<typename...T>class tpl, typename Packer, typename... Types>
struct TemplatePacker
{
    typedef typename TemplatePacker<tpl, typename Packer::base, typename Packer::type, Types...>::type type;
};

template<template<typename...T>class tpl, typename... Types>
struct TemplatePacker<tpl, TypesPacker<void>, Types...>
{
    typedef tpl<Types...> type;
};

template<template<typename...T>class tpl, typename Packer, typename... Types>
using TemplatePacker_t = typename TemplatePacker<tpl, Packer, Types...>::type;


template<typename... Types>
struct TemplateTypes
{
};

template<typename Types, template<typename... T>class tpl>
struct TemplateTransferArgs
{
    template<template<typename... U>class Packer, typename... Args>
    static tpl<Args...> Result(Packer<Args...>*);
    typedef decltype(Result((Types*)nullptr)) type;
};


//---------------------------------------------------------------------------
//                              Get Parameter with pos

template<int N, int a, int...args>
struct GetVec;

template<int a, int...args>
struct GetVec<1, a, args...>
{
    enum { value = a };
};

template<int N, int a, int...args>
struct GetVec
{
    enum { value = GetVec<N-1, args...>::value };
};


//---------------------------------------------------------------------------
//                          Recursive pack template class N times

template<int N, template<typename>class tpl, typename T>
struct RecursivePack;

template<template<typename>class tpl, typename T>
struct RecursivePack<1, tpl, T>
{
    typedef tpl<T> type;
};

template<int N, template<typename>class tpl, typename T>
struct RecursivePack
{
    typedef tpl<typename RecursivePack<N-1, tpl, T>::type> type;
};

template<int N, template<typename>class tpl, typename T>
using RecursivePack_t = typename RecursivePack<N, tpl, T>::type;
}



namespace std {
//---------------------------------------------------------------------------
//                          R value translate

template<typename T, typename = typename T::isGuardType>
typename T::value_type&& move(T& data)
{
    return static_cast<typename T::value_type&&>(data.Data());
}

template<typename T, typename = typename T::isGuardType>
const typename T::value_type&& move(const T& data)
{
    return static_cast<const typename T::value_type&&>(data.Data());
}

template<typename T, typename = typename T::isGuardType>
typename T::value_type&& move(T&& data)
{
    return static_cast<typename T::value_type&&>(data.Data());
}

template<typename T, typename = typename T::isGuardType>
const typename T::value_type&& move(const T&& data)
{
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
