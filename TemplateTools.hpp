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
    struct isOriginalType {
        using RawType = typename std::remove_cv<typename std::remove_reference<typename std::remove_pointer<T>::type>::type>::type;
        
        enum { value = std::is_same<typename type_traits<RawType>::value_type, T>::value };
    };
    
    
    //---------------------------------------------------------------------------
    //                              GT::ResultType
    
    template<typename T>
    struct TypePriority {
        enum { N = 9999 };
    };
    
    template<int T>
    struct TypeFromPriority {
        typedef long double value_type;
    };
    
    template <typename T, typename U>
    struct ResultType {
        enum { P_T = TypePriority<T>::N};
        enum { P_U = TypePriority<U>::N};
        enum { P = (P_T > P_U ? P_T : P_U)};
        typedef typename TypeFromPriority<
        (P+1)/2*2 * ((P==31||P==32)?1:2)
        >::value_type type;
    };
    
    template<typename T, typename U>
    using ResultType_t = typename ResultType<T, U>::type;
    
    template <typename T, typename U>
    struct ResultTypeMultiply {
        enum { P_T = TypePriority<T>::N};
        enum { P_U = TypePriority<U>::N};
        enum { P = (P_T > P_U ? P_T : P_U)};
        typedef typename TypeFromPriority<
        (P+1)/2*2 * ((P==31||P==32)?1:2) - (P_T%2==1&&P_U%2==1)*(P<=32)
        >::value_type type;
    };
    
    template<typename T, typename U>
    using ResultTypeMultiply_t = typename ResultTypeMultiply<T, U>::type;
    
    
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
    struct TypeFromPriority<0> {            typedef bool value_type; };
    
    template<>
    struct TypeFromPriority<1> {            typedef unsigned short value_type; };
    
    template<>
    struct TypeFromPriority<2> {            typedef short value_type;};
    
    template<>
    struct TypeFromPriority<3> {            typedef unsigned short value_type; };
    
    template<>
    struct TypeFromPriority<4> {            typedef short value_type; };
    
    template<>
    struct TypeFromPriority<7> {            typedef unsigned int value_type; };
    
    template<>
    struct TypeFromPriority<8> {            typedef int value_type; };
    
    template<>
    struct TypeFromPriority<15> {           typedef unsigned long value_type; };
    
    template<>
    struct TypeFromPriority<16> {           typedef long value_type; };
    
    template<>
    struct TypeFromPriority<31> {           typedef unsigned long long value_type; };
    
    template<>
    struct TypeFromPriority<32> {           typedef long long value_type; };
    
    template<>
    struct TypeFromPriority<64> {           typedef float value_type; };
    
    template<>
    struct TypeFromPriority<128> {          typedef double value_type; };
    
    template<>
    struct TypeFromPriority<256> {          typedef long double value_type; };
    
    
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
        return data.IdIndex();
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
    //                              MultiplyParameters
    
    template<int n, int i, int ...left>
    struct NMultiply {
        enum { result = i * NMultiply<n-1, left...>::result };
    };
    
    template<int i>
    struct NMultiply<1, i> {
        enum { result = i };
    };
    
    template<int ...n>
    struct MultiplyParameters {
        enum { result = NMultiply<sizeof...(n), n...>::result };
    };
}

#endif /* TemplateTools_hpp */
