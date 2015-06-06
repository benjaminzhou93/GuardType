#ifndef GUARDTYPEARRAY3D_CPP
#define GUARDTYPEARRAY3D_CPP
#include "GuardTypeArray3D.h"

//------------------------------------GuardTypeArray3D---------------------------------
//                          The members of GuardTypeArray3D

template<typename T>
GuardTypeArray3D<T>::GuardTypeArray3D(const GuardTypeArray3D<T>& gt)
    : GuardTypeArray2D<T>(gt.x*gt.y, gt.z, gt.GetNewNameByIncreaseId(gt.id))
{
    this->x = gt.x;
    this->y = gt.y;
    this->z = gt.z;
    T* pDestination = this->arr.get();
    T* pSource = gt.arr.get();
    for (size_t i=0; i<x*y*z; i++) {
        *(pDestination + i) = *(pSource + i);
    }
}

template<typename T>
GuardTypeArray3D<T>::GuardTypeArray3D(
        size_t n, size_t m, size_t k, const std::string& id)
    : GuardTypeArray2D<T>(n*m, k, id), x(n), y(m), z(k)
{
    assert( x>0 && y>0 && z>0);
}

template<typename T>
size_t GuardTypeArray3D<T>::LengthX() const {
    return this->x;
}

template<typename T>
size_t GuardTypeArray3D<T>::LengthY() const {
    return this->y;
}

template<typename T>
size_t GuardTypeArray3D<T>::LengthZ() const {
    return this->z;
}

template<typename T>
typename GuardTypeArray2D<T>::Ptr2
GuardTypeArray3D<T>::operator [] (size_t n) {
    ASSERT(0 <= n && n < x, "TRACE: out of range "+this->MaxIndex()+" used: "+
           this->id+"["+NumToString::Transform(n)+"]"+"[0][0]");
    T* p = this->arr.get() + y*z*n;
    typename GuardTypeArray2D<T>::Ptr2
            ptr2(typename GuardType<T>::ArrayIndex(n, 0, 0), p, this);
    return ptr2;
}

template<typename T>
const typename GuardTypeArray2D<T>::Ptr2
GuardTypeArray3D<T>::operator [] (size_t n) const {
    ASSERT(0 <= n && n < x, "TRACE: out of range "+this->MaxIndex()+" used: "+
           this->id+"["+NumToString::Transform(n)+"]"+"[0][0]");
    T* p = this->arr.get() + y*z*n;
    typename GuardTypeArray2D<T>::Ptr2
            ptr2(typename GuardType<T>::ArrayIndex(n, 0, 0), p, *this);
    return ptr2;
}

template<typename T>
std::istream& GuardTypeArray3D<T>::ReadArray3DFromIO(
        std::istream &si,
        GuardTypeArray3D<T>& gt)
{
    T data;
    if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
        if(typeid(si) == typeid(std::cin)) {
            std::cout<< "Please input ";
            std::cout<< "["<<(gt.D2()==0?1:gt.D2())*gt.D1()<< "] Datas "
                      << gt.id << ": " << std::endl;
        }
    }
    for (size_t i=0; i<gt.x; i++) {
        for (size_t j=0; j<gt.y; j++) {
            for (size_t k=0; k<gt.z; k++) {
                si >> data;
                gt[i][j][k] = data;
            }
        }
    }
    return si;
}

template<typename T>
std::ostream& GuardTypeArray3D<T>::WriteArray3DToIO(
        std::ostream &so,
        const GuardTypeArray3D<T>& gt)
{
    T* p = gt.arr.get();
    for (size_t i=0; i<gt.x; i++) {
        for (size_t j=0; j<gt.y; j++) {
            for (size_t k=0; k<gt.z; k++) {
                if(GuardConfig::_ARRAY_OUT_PUT_SWITCH == true
                   && i == gt.index.d3
                   && j == gt.index.d2
                   && k == gt.index.d1)
                    so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                       << "[" << *(p+i*gt.y*gt.z+j*gt.z+k) << "]";
                else
                    so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                       << " " << *(p+i*gt.y*gt.z+j*gt.z+k) << " ";
            }
            so << std::endl;
        }
        so << std::endl;
    }
    const_cast<size_t&>(gt.index.d3) = -1;
    so << std::endl;
    return so;
}
#endif // GUARDTYPEARRAY3D_CPP
