#ifndef LARGERTYPE_H
#define LARGERTYPE_H

template<typename T>
struct TypePriority {
    enum { N = 9999 };
};

template<typename T, typename U>
struct PriorityIsLarger {
    enum { result = TypePriority<T>::N > TypePriority<U>::N};
};

template <int IsLarger, typename T, typename U>
struct GetLargerType {
};

template <typename T, typename U>
struct GetLargerType<1, T, U> {
    typedef T value_type;
};

template <typename T, typename U>
struct GetLargerType<0, T, U> {
    typedef U value_type;
};

template <typename T, typename U>
struct LargerType {
    typedef typename GetLargerType<PriorityIsLarger<T, U>::result , T, U>::value_type value_type;
};




template<>
struct TypePriority<bool> {
    enum { N = 0 };
};

template<>
struct TypePriority<unsigned char> {
    enum { N = 1 };
};

template<>
struct TypePriority<char> {
    enum { N = 2 };
};

template<>
struct TypePriority<unsigned short> {
    enum { N = 3 };
};

template<>
struct TypePriority<short> {
    enum { N = 4 };
};

template<>
struct TypePriority<unsigned int> {
    enum { N = 5 };
};

template<>
struct TypePriority<int> {
    enum { N = 6 };
};

template<>
struct TypePriority<unsigned long> {
    enum { N = 7 };
};

template<>
struct TypePriority<long> {
    enum { N = 8 };
};

template<>
struct TypePriority<float> {
    enum { N = 9 };
};

template<>
struct TypePriority<double> {
    enum { N = 10 };
};

template<>
struct TypePriority<long double> {
    enum { N = 11 };
};

#endif // LARGERTYPE_H