#ifndef GUARDTYPEARRAY3D_H
#define GUARDTYPEARRAY3D_H
#include "GuardTypeArray2D.h"


//-----------------------------------------------------------------------------
//                            class GuardTypeArray3D

template<typename T>
class GuardTypeArray3D : protected GuardTypeArray2D<T> {
public :
    GuardTypeArray3D(const GuardTypeArray3D<T>& gt);
    GuardTypeArray3D(size_t n, size_t m, size_t k, const std::string& id="GT");
    typename GuardTypeArray2D<T>::Ptr2          operator [] (size_t n);
    const typename GuardTypeArray2D<T>::Ptr2    operator [] (size_t n) const;
    size_t          LengthX() const;
    size_t          LengthY() const;
    size_t          LengthZ() const;
    virtual size_t  D1()     const { return z; }
    virtual size_t  D2()     const { return y; }
    virtual size_t  D3()     const { return x; }

    friend std::istream& operator >> (
            std::istream &              si,
            GuardTypeArray3D<T>&        gt) {
        return ReadArray3DFromIO(si, gt);
    }
    friend std::ostream& operator << (
            std::ostream &              so,
            const GuardTypeArray3D<T>&  gt) {
        return WriteArray3DToIO(so, gt);
    }
    virtual void PrintArray() const { GuardConfig::so << *this; }
private :
    static std::istream& ReadArray3DFromIO(
            std::istream&               si,
            GuardTypeArray3D&           gt);
    static std::ostream& WriteArray3DToIO(
            std::ostream&               so,
            const GuardTypeArray3D&     gt);

private :
    size_t x, y, z;
};

#include "GuardTypeArray3D.cpp"
#endif // GUARDTYPEARRAY3D_H
