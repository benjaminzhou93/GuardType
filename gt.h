//==========================================================================//
//                                                                          //
//                https://github.com/benjaminzhou93/GuardType               //
//                                                                          //
//==========================================================================//


#ifndef gt_h
#define gt_h

#include "GuardType.hpp"
#include "GuardArray.hpp"


//---------------------------------------------------------------------------
//                            Type Define

#define MACRO_COMMA() ,

#define GT_PROVIDERS_RES(type)\
ENSURE_THREAD_SAFETY_(MACRO_COMMA() gt::ThreadSafetyProvider)\
TRACE_STRING_SAVE____(MACRO_COMMA() gt::IDExpressProvider)

#define GENERATE_GT_TYPE(type, name, ...)\
typedef gt::GuardType<type, gt::NumericProvider VALUE_OBSERVER_______(MACRO_COMMA() gt::ValueObserverProvider<type>) __VA_ARGS__> name;\
typedef gt::GuardArray<type, 1 __VA_ARGS__> name##Arr;  \
typedef gt::IndexProvider<type, 2 __VA_ARGS__> name##Ptr2;\
typedef gt::GuardArray<type, 2 ENSURE_NOT_THREAD_SAFETY_(MACRO_COMMA() name##Ptr2) __VA_ARGS__> name##Arr2D;\
typedef gt::IndexProvider<type, 3 __VA_ARGS__> name##Ptr3;\
typedef gt::GuardArray<type, 3 ENSURE_NOT_THREAD_SAFETY_(MACRO_COMMA() name##Ptr3) __VA_ARGS__> name##Arr3D;\
/* ... */\
template<int... Dementions>\
using name##Array = gt::GTArray<type, Dementions...>;

#define GT_TYPE(type, name) GENERATE_GT_TYPE(type, name, GT_PROVIDERS_RES(type))



GT_TYPE(bool,              Bool)
GT_TYPE(char,              Char)
GT_TYPE(unsigned char,     UChar)
GT_TYPE(short,             Short)
GT_TYPE(unsigned short,    UShort)
GT_TYPE(int,               Int)
GT_TYPE(unsigned int,      UInt)
GT_TYPE(long,              Long)
GT_TYPE(unsigned long,     ULong)
GT_TYPE(long long,         LLong)
GT_TYPE(unsigned long long, ULLong)
GT_TYPE(float,             Float)
GT_TYPE(double,            Double)
GT_TYPE(long double,       LDouble)
GT_TYPE(std::string,       String)


#endif /* gt_h */
