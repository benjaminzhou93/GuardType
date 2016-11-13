//==========================================================================//
//                                                                          //
//                https://github.com/benjaminzhou93/GuardType               //
//                                                                          //
//==========================================================================//


#ifndef gt_h
#define gt_h

#include "GuardType.hpp"
#include "GuardArray.hpp"


#define GTRule GuardConfig::rule

template<typename... T>
int printf(const char * s, const T&... arg1) {
    return std::printf(s, static_cast<typename GT::type_traits<T>::value_type>(arg1)...);
}

template<typename T>
void AddId(const T& id) {
    IDExpressManager::idArray.push(id);
}

template<typename T, typename ...U>
void AddId(const T& id, const U&...ids) {
    IDExpressManager::idArray.push(id);
    AddId(ids...);
}

//---------------------------------------------------------------------------
//                            Type Define

#if !ENSURE_MULTITHREAD_SAFETY && !(VALUE_BE_READED_DO || OLD_TO_NEW_VALUE_DO)
#define GT_TYPE(type, name) \
typedef GuardType<type, NumericProvider> name;\
typedef IndexProvider<type> name##Ptr;\
typedef GuardArray<type, 1> name##Arr;  \
typedef GuardArray<type, 2> name##Arr2D;\
typedef GuardArray<type, 3> name##Arr3D;
// ...
#endif


#if ENSURE_MULTITHREAD_SAFETY && !(VALUE_BE_READED_DO || OLD_TO_NEW_VALUE_DO)
#define GT_TYPE(type, name) \
typedef GuardType<type, NumericProvider, ThreadSafetyProvider> name;\
typedef IndexProvider<type, 1, ArrayThreadSafetyProvider> name##Ptr;\
typedef GuardArray<type, 1, ArrayThreadSafetyProvider> name##Arr;  \
typedef GuardArray<type, 2, ArrayThreadSafetyProvider> name##Arr2D;\
typedef GuardArray<type, 3, ArrayThreadSafetyProvider> name##Arr3D;
// ...
#endif


#if !ENSURE_MULTITHREAD_SAFETY && (VALUE_BE_READED_DO || OLD_TO_NEW_VALUE_DO)
#define GT_TYPE(type, name) \
typedef GuardType<type, NumericProvider, ValueObserverProvider<type> > name;\
typedef IndexProvider<type, 1, ValueObserverProvider<type> > name##Ptr;\
typedef GuardArray<type, 1, ValueObserverProvider<type> > name##Arr;  \
typedef GuardArray<type, 2, ValueObserverProvider<type> > name##Arr2D;\
typedef GuardArray<type, 3, ValueObserverProvider<type> > name##Arr3D;
// ...
#endif


#if ENSURE_MULTITHREAD_SAFETY && (VALUE_BE_READED_DO || OLD_TO_NEW_VALUE_DO)
#define GT_TYPE(type, name) \
typedef GuardType<type, NumericProvider, ThreadSafetyProvider, ValueObserverProvider<type> > name;\
typedef IndexProvider<type, 1, ArrayThreadSafetyProvider, ValueObserverProvider<type> > name##Ptr;\
typedef GuardArray<type, 1, ArrayThreadSafetyProvider, ValueObserverProvider<type> > name##Arr;  \
typedef GuardArray<type, 2, ArrayThreadSafetyProvider, ValueObserverProvider<type> > name##Arr2D;\
typedef GuardArray<type, 3, ArrayThreadSafetyProvider, ValueObserverProvider<type> > name##Arr3D;
// ...
#endif

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



#define BoolArray(...)      GTArray<bool,           __VA_ARGS__>
#define CharArray(...)      GTArray<char,           __VA_ARGS__>
#define UCharArray(...)     GTArray<unsigned char,  __VA_ARGS__>
#define ShortArray(...)     GTArray<short,          __VA_ARGS__>
#define UShortArray(...)    GTArray<unsigned short, __VA_ARGS__>
#define IntArray(...)       GTArray<int,            __VA_ARGS__>
#define UIntArray(...)      GTArray<unsigned int,   __VA_ARGS__>
#define LongArray(...)      GTArray<long,           __VA_ARGS__>
#define ULongArray(...)     GTArray<unsigned long,  __VA_ARGS__>
#define ULLongArray(...)    GTArray<unsigned long long, __VA_ARGS__>
#define LLongArray(...)     GTArray<long long,      __VA_ARGS__>
#define FloatArray(...)     GTArray<float,          __VA_ARGS__>
#define DoubleArray(...)    GTArray<double,         __VA_ARGS__>
#define LDoubleArray(...)   GTArray<long double,    __VA_ARGS__>
#define StringArray(...)    GTArray<std::string,    __VA_ARGS__>


#endif /* gt_h */
