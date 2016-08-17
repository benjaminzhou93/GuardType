#ifndef gt_h
#define gt_h

#include "GuardType.hpp"
#include "GuardArrayN.hpp"

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

#endif /* gt_h */
