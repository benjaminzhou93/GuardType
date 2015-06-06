#ifndef GT_H
#define GT_H

#include <cmath>
#include "GuardType.h"
#include "GuardTypeArray.h"
#include "GuardTypeArray2D.h"
#include "GuardTypeArray3D.h"

#define GT_TYPE(type, name)\
typedef GuardType<type>                         name;\
typedef GuardTypeArray<type>                    name##Arr;\
typedef GuardTypeArray2D<type>                  name##Arr2;\
typedef GuardTypeArray3D<type>                  name##Arr3;\
typedef typename GuardTypeArray<type>::Ptr      name##Ptr;\
typedef typename GuardTypeArray2D<type>::Ptr2   name##Ptr2;

GT_TYPE(bool,              Bool)
GT_TYPE(char,              Char)
GT_TYPE(unsigned char,     UChar)
GT_TYPE(short,             Short)
GT_TYPE(unsigned short,    UShort)
GT_TYPE(int,               Int)
GT_TYPE(unsigned int,      UInt)
GT_TYPE(float,             Float)
GT_TYPE(double,            Double)
GT_TYPE(long double,       LongDouble)
GT_TYPE(std::string,       String)


GuardConfig::AddNewName AddId(std::string id) {
    GuardConfig::idArray.push(id);
    return GuardConfig::AddNewName();
}

enum OnOrOff {OFF = 0, ON = 1};

void TurnTrace(OnOrOff s) {
    GuardConfig::TurnOutPutCalcTraceSwitch(s);
}

void TurnExpres(OnOrOff s) {
    GuardConfig::TurnOutPutCalcExpressSwitch(s);
}


template<typename... T>
int printf(const char * s, const T&... arg1) {
    return std::printf(s, static_cast<typename type_traits<T>::value_type>(arg1)...);
}



//--------------------------------------------------------------------------------
//                              C math library

#define C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, T)\
GuardType<typename LargerType<float, T>::value_type>\
Function(const T& x) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+")";\
return GuardType<typename LargerType<float, T>::value_type>\
(std::Function(x), Expres, false);\
}

#define C_MATH_FUNCTION_SINGLE_PARAMETER(Function)\
    template<typename T>\
    GuardType<typename LargerType<float, T>::value_type> Function(const GuardType<T>& x) {\
        std::string Expres = #Function;\
        Expres += "("+GuardType<T>::ToString(x)+")";\
        return GuardType<typename LargerType<float, T>::value_type>\
                (std::Function(static_cast<T>(x)), Expres, false);\
    }\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, unsigned short)\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, short)\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, unsigned int)\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, int)\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, unsigned long)\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, long)\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, float)\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, double)\
    C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, long double)

C_MATH_FUNCTION_SINGLE_PARAMETER(acos)
C_MATH_FUNCTION_SINGLE_PARAMETER(asin)
C_MATH_FUNCTION_SINGLE_PARAMETER(atan)
C_MATH_FUNCTION_SINGLE_PARAMETER(ceil)
C_MATH_FUNCTION_SINGLE_PARAMETER(cos)
C_MATH_FUNCTION_SINGLE_PARAMETER(cosh)
C_MATH_FUNCTION_SINGLE_PARAMETER(exp)
C_MATH_FUNCTION_SINGLE_PARAMETER(fabs)
C_MATH_FUNCTION_SINGLE_PARAMETER(floor)
C_MATH_FUNCTION_SINGLE_PARAMETER(log)
C_MATH_FUNCTION_SINGLE_PARAMETER(log10)
C_MATH_FUNCTION_SINGLE_PARAMETER(sin)
C_MATH_FUNCTION_SINGLE_PARAMETER(sinh)
C_MATH_FUNCTION_SINGLE_PARAMETER(sqrt)
C_MATH_FUNCTION_SINGLE_PARAMETER(tan)
C_MATH_FUNCTION_SINGLE_PARAMETER(tanh)
C_MATH_FUNCTION_SINGLE_PARAMETER(signbit)
C_MATH_FUNCTION_SINGLE_PARAMETER(fpclassify)


#define C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(Function)\
    template<typename T>\
    GuardType<bool> Function(const GuardType<T>& x) {\
        std::string Expres = #Function;\
        Expres += "("+GuardType<T>::ToString(x)+")";\
        return GuardType<bool>(std::Function(static_cast<T>(x)), Expres, false);\
    }

C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(isfinite)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(isinf)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(isnan)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(isnormal)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(ilogb)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(acos)


#define C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_LONG(Function)\
    template<typename T>\
    GuardType<long> Function(const GuardType<T>& x) {\
        std::string Expres = #Function;\
        Expres += "("+GuardType<T>::ToString(x)+")";\
        return GuardType<long>(std::Function(static_cast<T>(x)), Expres, false);\
    }

C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_LONG(lrint)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_LONG(lround)


#define C_MATH_FUNCTION_COUPLE_PARAMETER(Function)\
template<typename T, typename U>\
GuardType<typename LargerType<float,\
            typename LargerType<\
            typename type_traits<T>::value_type, \
            typename type_traits<U>::value_type>::value_type\
            >::value_type >\
Function(const T& x, const U& y) {\
    std::string Expres = #Function;\
    Expres += "("+GuardType<T>::ToString(x)+", "+GuardType<T>::ToString(y)+")";\
    return GuardType<typename LargerType<float,\
                                        typename LargerType<\
                                        typename type_traits<T>::value_type, \
                                        typename type_traits<U>::value_type>::value_type\
                                        >::value_type >\
    (std::Function(static_cast<typename type_traits<T>::value_type>(x),\
                   static_cast<typename type_traits<T>::value_type>(y)),\
     Expres, false);\
}

C_MATH_FUNCTION_COUPLE_PARAMETER(atan2f)
C_MATH_FUNCTION_COUPLE_PARAMETER(fmodf)
C_MATH_FUNCTION_COUPLE_PARAMETER(frexp)
C_MATH_FUNCTION_COUPLE_PARAMETER(ldexp)
C_MATH_FUNCTION_COUPLE_PARAMETER(modf)
C_MATH_FUNCTION_COUPLE_PARAMETER(pow)
C_MATH_FUNCTION_COUPLE_PARAMETER(acosh)
C_MATH_FUNCTION_COUPLE_PARAMETER(asinh)
C_MATH_FUNCTION_COUPLE_PARAMETER(atanh)
C_MATH_FUNCTION_COUPLE_PARAMETER(cbrt)
C_MATH_FUNCTION_COUPLE_PARAMETER(erf)
C_MATH_FUNCTION_COUPLE_PARAMETER(erfc)
C_MATH_FUNCTION_COUPLE_PARAMETER(exp2)
C_MATH_FUNCTION_COUPLE_PARAMETER(expm1)
C_MATH_FUNCTION_COUPLE_PARAMETER(fdim)
C_MATH_FUNCTION_COUPLE_PARAMETER(fmax)
C_MATH_FUNCTION_COUPLE_PARAMETER(fmin)
C_MATH_FUNCTION_COUPLE_PARAMETER(hypot)
C_MATH_FUNCTION_COUPLE_PARAMETER(lgamma)
C_MATH_FUNCTION_COUPLE_PARAMETER(llrint)
C_MATH_FUNCTION_COUPLE_PARAMETER(llround)
C_MATH_FUNCTION_COUPLE_PARAMETER(log1p)
C_MATH_FUNCTION_COUPLE_PARAMETER(log2)
C_MATH_FUNCTION_COUPLE_PARAMETER(logb)
C_MATH_FUNCTION_COUPLE_PARAMETER(nearbyint)
C_MATH_FUNCTION_COUPLE_PARAMETER(nextafter)
C_MATH_FUNCTION_COUPLE_PARAMETER(nexttoward)
C_MATH_FUNCTION_COUPLE_PARAMETER(remainder)
C_MATH_FUNCTION_COUPLE_PARAMETER(rint)
C_MATH_FUNCTION_COUPLE_PARAMETER(round)
C_MATH_FUNCTION_COUPLE_PARAMETER(scalbln)
C_MATH_FUNCTION_COUPLE_PARAMETER(scalbn)
C_MATH_FUNCTION_COUPLE_PARAMETER(tgamma)
C_MATH_FUNCTION_COUPLE_PARAMETER(trunc)


#define C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(Function)\
    template<typename T, typename U>\
    GuardType<bool> Function(const T& x, const U& y) {\
        std::string Expres = #Function;\
        Expres += "("+GuardType<T>::ToString(x)+", "+GuardType<T>::ToString(y)+")";\
        return GuardType<bool>\
        (std::Function(static_cast<typename type_traits<T>::value_type>(x),\
                       static_cast<typename type_traits<T>::value_type>(y)),\
         Expres, false);\
    }

C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(isgreater)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(isgreaterequal)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(isless)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(islessequal)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(islessgreater)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(isunordered)

#endif // GT_H
