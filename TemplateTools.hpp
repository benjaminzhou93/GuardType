#ifndef TemplateTools_hpp
#define TemplateTools_hpp

#include <iostream>
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

#define EXPAND_NUMERIC_MACRO(MACRO)\
MACRO(bool)             \
MACRO(char)             \
MACRO(unsigned char)    \
MACRO(short)            \
MACRO(unsigned short)   \
MACRO(int)              \
MACRO(unsigned int)     \
MACRO(long)             \
MACRO(unsigned long)    \
MACRO(unsigned long long)\
MACRO(long long)        \
MACRO(float)            \
MACRO(double)           \
MACRO(long double)      \
MACRO(std::string)


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
    
    template<typename T, typename U>
    struct type_equals {
        enum { value = 0 };
    };
    
    template<typename T>
    struct type_equals<T, T> {
        enum { value = 1 };
    };
    
    template<typename... T>
    int printf(const char * s, const T&... arg1) {
        return std::printf(s, static_cast<typename type_traits<T>::value_type>(arg1)...);
    }
    
    
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
        >::value_type value_type;
    };
    
    template <typename T, typename U>
    struct ResultTypeMultiply {
        enum { P_T = TypePriority<T>::N};
        enum { P_U = TypePriority<U>::N};
        enum { P = (P_T > P_U ? P_T : P_U)};
        typedef typename TypeFromPriority<
        (P+1)/2*2 * ((P==31||P==32)?1:2) - (P_T%2==1&&P_U%2==1)*(P<=32)
        >::value_type value_type;
    };
    
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
        std::string num = std::to_string(const_cast<T&>(data));
        if((GT::type_equals<T, float>::value
            || GT::type_equals<T, double>::value
            || GT::type_equals<T, long double>::value)) {
            while (num.back() == '0') {
                num.pop_back();
            }
            if(num.back() == '.') {
                num.push_back('0');
            }
        }
        return num;
    }
    
    template<typename T, template<typename>class DataSource>
    const std::string NumericToString(const GuardType<T, DataSource>& data) {
        return data.Id();
    }
    
    template<typename T, template<typename>class DataSource>
    std::string CalcString(const GuardType<T, DataSource>& data) {
        return data.CalcString();
    }
    
    template<typename T>
    std::string CalcString(T data) {
        return NumericToString(data);
    }
    
    template<typename U, typename V>
    const std::string PackWithBracket(const U& data1,
                                      const std::string& opStr,
                                      const V& data2) {
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
    //                              InitWithCArray
    
    template<int D>
    struct InitWithCArray {
        template<typename T, int Demention, typename U, int N>
        static void Init(const GuardArray<T, Demention>& gt, const U (&arr)[N]) {
            const_cast<size_t&>(gt.dementions[D]) = N;
            InitWithCArray<D-1>::Init(gt, arr[0]);
        }
    };
    
    template<>
    struct InitWithCArray<1> {
        template<typename T, int Demention, typename U, int N>
        static void Init(const GuardArray<T, Demention>& gt, const U (&arr)[N]) {
            const_cast<size_t&>(gt.dementions[0]) = 1;
            const_cast<size_t&>(gt.dementions[1]) = N;
            const_cast<GuardArray<T, Demention>&>(gt).array = const_cast<int*>(&arr[0]);
            const_cast<GuardArray<T, Demention>&>(gt).InitDementions();
        }
    };
    
}

#endif /* TemplateTools_hpp */
