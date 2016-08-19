#ifndef gt_h
#define gt_h

#include "GuardType.hpp"
#include "GuardArrayN.hpp"
#include "GuardArrayC.hpp"

//---------------------------------------------------------------------------
//                            Type Define

#define GT_TYPE(type, name)                             \
typedef GuardType<type>                     name;       \
typedef IndexProvider<type>                 name##Ptr;  \
typedef GuardArray<type>                    name##Arr;  \
typedef GuardArray<type, 2>                 name##Arr2D;\
typedef GuardArray<type, 3>                 name##Arr3D;
// ...

GT_TYPE(bool,              Bool)
GT_TYPE(char,              Char)
GT_TYPE(unsigned char,     UChar)
GT_TYPE(short,             Short)
GT_TYPE(unsigned short,    UShort)
GT_TYPE(int,               Int)
GT_TYPE(unsigned int,      UInt)
GT_TYPE(long,              Long)
GT_TYPE(unsigned long,     ULong)
GT_TYPE(unsigned long long, ULLong)
GT_TYPE(long long,         LLong)
GT_TYPE(float,             Float)
GT_TYPE(double,            Double)
GT_TYPE(long double,       LDouble)
GT_TYPE(std::string,       String)



#define BoolArray(...)      GuardArrayC<bool,           __VA_ARGS__>()
#define CharArray(...)      GuardArrayC<char,           __VA_ARGS__>()
#define UCharArray(...)     GuardArrayC<unsigned char,  __VA_ARGS__>()
#define ShortArray(...)     GuardArrayC<short,          __VA_ARGS__>()
#define UShortArray(...)    GuardArrayC<unsigned short, __VA_ARGS__>()
#define IntArray(...)       GuardArrayC<int,            __VA_ARGS__>()
#define UIntArray(...)      GuardArrayC<unsigned int,   __VA_ARGS__>()
#define LongArray(...)      GuardArrayC<long,           __VA_ARGS__>()
#define ULongArray(...)     GuardArrayC<unsigned long,  __VA_ARGS__>()
#define ULLongArray(...)    GuardArrayC<unsigned long long, __VA_ARGS__>()
#define LLongArray(...)     GuardArrayC<long long,      __VA_ARGS__>()
#define FloatArray(...)     GuardArrayC<float,          __VA_ARGS__>()
#define DoubleArray(...)    GuardArrayC<double,         __VA_ARGS__>()
#define LDoubleArray(...)   GuardArrayC<long double,    __VA_ARGS__>()
#define StringArray(...)    GuardArrayC<std::string,    __VA_ARGS__>()


#endif /* gt_h */
