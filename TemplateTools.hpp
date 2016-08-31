#ifndef TemplateTools_hpp
#define TemplateTools_hpp

#include <iostream>
#include <sstream>
#include "Tools.hpp"

template<typename T>
class NumericProvider;

template<typename T, int N = 1>
class IndexProvider;

template<typename T, template<typename>class DataSource = NumericProvider>
class GuardType;

template<typename T, int Demention = 1>
class GuardArray;

//--------------------------------------------------------------------------
//                             GT template tools

template<typename T>
void AddId(const T& id) {
    GuardConfig::idArray.push(id);
}

template<typename T, typename ...U>
void AddId(const T& id, const U&...ids) {
    GuardConfig::idArray.push(id);
    AddId(ids...);
}

namespace GT {
    
    //---------------------------------------------------------------------------
    //                              GT::type_traits
    
    template<typename T>
    struct type_traits {
        typedef T value_type;
    };
    
    template<typename T, template<typename>class DataSource>
    struct type_traits<GuardType<T, DataSource> > {
        typedef T value_type;
    };
    
    template<typename T, int N>
    struct type_traits<IndexProvider<T, N> > {
        typedef T value_type;
    };
    
    template<typename T>
    struct type_traits<NumericProvider<T> > {
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
    
    
    //---------------------------------------------------------------------------
    //                              GT::ResultType
    
    
    #define CalcResultType(T, op, U)\
    typename std::conditional<\
        (GT::TypePriority<GT::RawType<T> >::N == -1 || GT::TypePriority<GT::RawType<U> >::N == -1)\
        , decltype(std::declval<T>() op std::declval<U>())\
        , GT::ResultType_t<GT::RawType<T>, GT::RawType<U> >\
    >::type
    
    #define CalcMultiplyResultType(T, op, U)\
    typename std::conditional<\
        (GT::TypePriority<GT::RawType<T> >::N == -1 || GT::TypePriority<GT::RawType<U> >::N == -1)\
        , decltype(std::declval<T>() op std::declval<U>())\
        , GT::ResultTypeMultiply_t<GT::RawType<T>, GT::RawType<U> >\
    >::type
    
    
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
    
    
    template<>
    struct TypePriority<bool> {             enum { N = 0 }; };
    
    template<>
    struct TypePriority<unsigned char> {    enum { N = 1 }; };
    
    template<>
    struct TypePriority<char> {             enum { N = 2 }; };
    
    template<>
    struct TypePriority<unsigned short> {   enum { N = 3 }; };
    
    template<>
    struct TypePriority<short> {            enum { N = 4 }; };
    
    template<>
    struct TypePriority<unsigned int> {     enum { N = 7 }; };
    
    template<>
    struct TypePriority<int> {              enum { N = 8 }; };
    
    template<>
    struct TypePriority<unsigned long> {    enum { N = 15 }; };
    
    template<>
    struct TypePriority<long> {             enum { N = 16 }; };
    
    template<>
    struct TypePriority<unsigned long long> { enum { N = 31 }; };
    
    template<>
    struct TypePriority<long long> {        enum { N = 32 }; };
    
    template<>
    struct TypePriority<float> {            enum { N = 64 }; };
    
    template<>
    struct TypePriority<double> {           enum { N = 128 }; };
    
    template<>
    struct TypePriority<long double> {      enum { N = 256 }; };
    
    
    
    template<>
    struct TypeFromPriority<0> {            typedef bool type; };
    
    template<>
    struct TypeFromPriority<1> {            typedef unsigned short type; };
    
    template<>
    struct TypeFromPriority<2> {            typedef short type;};
    
    template<>
    struct TypeFromPriority<3> {            typedef unsigned short type; };
    
    template<>
    struct TypeFromPriority<4> {            typedef short type; };
    
    template<>
    struct TypeFromPriority<7> {            typedef unsigned int type; };
    
    template<>
    struct TypeFromPriority<8> {            typedef int type; };
    
    template<>
    struct TypeFromPriority<15> {           typedef unsigned long type; };
    
    template<>
    struct TypeFromPriority<16> {           typedef long type; };
    
    template<>
    struct TypeFromPriority<31> {           typedef unsigned long long type; };
    
    template<>
    struct TypeFromPriority<32> {           typedef long long type; };
    
    template<>
    struct TypeFromPriority<64> {           typedef float type; };
    
    template<>
    struct TypeFromPriority<128> {          typedef double type; };
    
    template<>
    struct TypeFromPriority<256> {          typedef long double type; };
    
    
    //---------------------------------------------------------------------------
    //                              PackExpres
    // (data1) op (data2)
    
    template<typename T>
    const std::string NumericToString(const T& data) {
        std::ostringstream s;
        s << data;
        return s.str();
    }
    
    template<typename T, template<typename>class DataSource>
    const std::string NumericToString(const GuardType<T, DataSource>& data) {
        std::string idIndex = data.IdIndex();
        if(idIndex == "") {
            return NumericToString(static_cast<const T&>(data));
        } else {
            return idIndex;
        }
    }
    
    template<typename T>
    std::string CalcString(T data) {
        std::ostringstream s;
        s << data;
        return s.str();
    }
    
    template<typename T, template<typename>class DataSource>
    std::string CalcString(const GuardType<T, DataSource>& data) {
        return data.CalcString();
    }
    
    template<typename U, typename V>
    const std::string PackWithBracket(const U& data1,
                                      const std::string& opStr,
                                      const V& data2) {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        std::string calcExpress;
        std::string data1CalcString = CalcString(data1);
        std::string data2CalcString = CalcString(data2);
        if(MinCalcPriorityOf(data1CalcString) < PriorityOfSymbol(opStr))
            calcExpress = "("+data1CalcString+")" + opStr;
        else
            calcExpress = data1CalcString + opStr;
        
        if(PriorityOfSymbol(opStr) >= MinCalcPriorityOf(data2CalcString))
            calcExpress += "("+data2CalcString+")";
        else
            calcExpress += data2CalcString;
        return calcExpress;
    }
    
    
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
    //                              Output pack parameters
    
    template<typename T, typename ...Args>
    std::ostream& Output(std::ostream& so, const std::string& div, const T& a) {
        return so << a;
    }
    
    template<typename T, typename ...Args>
    std::ostream& Output(std::ostream& so, const std::string& div, const T& a, const Args&... args) {
        so << a << div;
        return Output(so, div, args...);
    }
    
    
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

#endif /* TemplateTools_hpp */
