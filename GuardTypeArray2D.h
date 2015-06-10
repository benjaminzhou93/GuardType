#ifndef GUARDTYPEARRAY2D_H
#define GUARDTYPEARRAY2D_H
#include "GuardTypeArray.h"


//-----------------------------------------------------------------------------
//                            class GuardTypeArray2D

template<typename T>
class GuardTypeArray2D : protected GuardTypeArray<T> {
public :
    using typename GuardType<T>::ArrayIndex;
    using typename GuardTypeArray<T>::Ptr2;

// class GuardTypeArray2D
public :
    template<size_t M, size_t N>
    GuardTypeArray2D(const T (&pArr)[M][N], const std::string& id = "GT");
    template<size_t M, size_t N>
    GuardTypeArray2D(const T (&pArr)[M][N], bool isReferenceFromArray);
    GuardTypeArray2D(const GuardTypeArray2D<T>& gt);
    GuardTypeArray2D(size_t m, size_t n, const std::string& id = "GT");
                                            operator const Ptr2();
    template<typename U>
    Ptr2                                    operator + (U n);
    typename GuardTypeArray<T>::Ptr         operator [] (size_t n);
    const typename GuardTypeArray<T>::Ptr   operator [] (size_t n) const;
    size_t          LengthX() const;
    size_t          LengthY() const;
    virtual size_t  D1()     const { return y; }
    virtual size_t  D2()     const { return x; }
    virtual size_t  D3()     const { return 0; }

    friend std::istream& operator >> (
            std::istream &              si,
            GuardTypeArray2D<T>&        gt) {
        return ReadArray2DFromIO(si, gt);
    }
    friend std::ostream& operator << (
            std::ostream &              so,
            const GuardTypeArray2D<T>&  gt) {
        return WriteArray2DToIO(so, gt);
    }
    virtual void PrintArray() const { GuardConfig::so << *this; }
private :
    static std::istream& ReadArray2DFromIO(
            std::istream&               si,
            GuardTypeArray2D&           gt);
    static std::ostream& WriteArray2DToIO(
            std::ostream&               so,
            const GuardTypeArray2D&     gt);

private :
    size_t x, y;
};

#include "GuardTypeArray2D.cpp"
#endif // GUARDTYPEARRAY2D_H
