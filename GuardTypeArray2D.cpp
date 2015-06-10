#ifndef GUARDTYPEARRAY2D_CPP
#define GUARDTYPEARRAY2D_CPP
#include "GuardTypeArray2D.h"


//----------------------------GuardTypeArray--------------------------------------------
//                         The members of GuardTypeArray::Ptr2

template<typename T>
template<int M, int N>
GuardTypeArray<T>::Ptr2::Ptr2(const T (&pArr)[M][N]) {
    this->pos = const_cast<T*>(pArr[0]);
    this->gt = (GuardType<T>*)new GuardTypeArray2D<T>(pArr, true);
    this->isGtAlloc.startCount();
}

//------------------------------------GuardTypeArray2D---------------------------------
//                          The members of GuardTypeArray2D

template<typename T>
GuardTypeArray2D<T>::GuardTypeArray2D(const GuardTypeArray2D<T>& gt)
    : GuardTypeArray<T>(gt.x*gt.y, gt.GetNewNameByIncreaseId(gt.id))
{
    this->x = gt.x;
    this->y = gt.y;
    T* pDestination = this->arr.get();
    T* pSource = gt.arr.get();
    for (size_t i=0; i<x*y; i++) {
        *(pDestination + i) = *(pSource + i);
    }
}

template<typename T>
GuardTypeArray2D<T>::GuardTypeArray2D(size_t m, size_t n, const std::string& id)
    : GuardTypeArray<T>(m*n, id), x(m), y(n)
{
    assert( x>0 && y>0);
}

template<typename T>
template<size_t M, size_t N>
GuardTypeArray2D<T>::GuardTypeArray2D(const T (&pArr)[M][N], const std::string& id)
    : GuardTypeArray<T>(M*N, GuardType<T>::GetNewId(id)), x(M) , y(N) {
    T* dest = this->arr.get();
    for (size_t i=0; i<M*N; i++) {
        dest[i] = pArr[i/N][i%N];
    }
}

template<typename T>
template<size_t M, size_t N>
GuardTypeArray2D<T>::GuardTypeArray2D(const T (&pArr)[M][N], bool isReferenceFromArray)
    : GuardTypeArray<T>(), x(M) , y(N) {
    this->arr.set(pArr[0], isReferenceFromArray);
    if(isReferenceFromArray == false) {
        T* a = new T[M*N];
        this->arr.set(a, isReferenceFromArray);
        for (size_t i=0; i<M*N; i++) {
            a[i] = pArr[i/N][i%N];
        }
    }
}

template<typename T>
GuardTypeArray2D<T>::operator const Ptr2() {
    return Ptr2(ArrayIndex(), this->Arr(), (GuardTypeArray2D<T>*)this);
}

template<typename T>
size_t GuardTypeArray2D<T>::LengthX() const {
    return this->x;
}

template<typename T>
size_t GuardTypeArray2D<T>::LengthY() const {
    return this->y;
}

template<typename T>
template<typename U>
typename GuardTypeArray2D<T>::Ptr2 GuardTypeArray2D<T>::operator + (U n) {
    return Ptr2(*this + n);
}

template<typename T>
typename GuardTypeArray<T>::Ptr
GuardTypeArray2D<T>::operator [] (size_t n) {
    T* p = this->arr.get() + y*n;
    typename GuardTypeArray<T>::Ptr ptr(ArrayIndex(0, n, 0), p, this);
    ASSERT(0 <= n && n < x, "TRACE: out of range "+this->MaxIndex()+
           " used: "+static_cast<GuardTypeArray2D<T>&>(ptr[0]).IdIndex());
    return ptr;
}

template<typename T>
const typename GuardTypeArray<T>::Ptr
GuardTypeArray2D<T>::operator [] (size_t n) const {
    T* p = this->arr.get() + y*n;
    typename GuardTypeArray<T>::Ptr ptr(ArrayIndex(0, n, 0), p, this);
    ASSERT(0 <= n && n < x, "TRACE: out of range "+this->MaxIndex()+
           " used: "+static_cast<GuardTypeArray2D<T>&>(ptr[0]).IdIndex());
    return ptr;
}

template<typename T>
std::istream& GuardTypeArray2D<T>::ReadArray2DFromIO(
        std::istream &si,
        GuardTypeArray2D<T>& gt)
{
    T data;
    if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
        if(typeid(si) == typeid(std::cin)) {
            std::cout<< "Please input ";
            std::cout<< "["<< (gt.D2()==0?1:gt.D2())*gt.D1() << "] Datas "
                      << gt.id << ": " << std::endl;
        }
    }
    for (size_t i=0; i<gt.x; i++) {
        for (size_t j=0; j<gt.y; j++) {
            si >> data;
            gt[i][j] = data;
        }
    }
    return si;
}

template<typename T>
std::ostream& GuardTypeArray2D<T>::WriteArray2DToIO(
        std::ostream &so,
        const GuardTypeArray2D<T>& gt)
{
    T* p = gt.arr.get();
    for (size_t i=0; i<gt.x; i++) {
        for (size_t j=0; j<gt.y; j++) {
            if(GuardConfig::_ARRAY_OUT_PUT_SWITCH == true
               && i == gt.index.d2 && j == gt.index.d1)
                so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                   << "[" << *(p + i*gt.y + j) << "]";
            else
                so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                   << " " << *(p + i*gt.y + j) << " ";
        }
        so << std::endl;
    }
    const_cast<size_t&>(gt.index.d2) = -1;
    so << std::endl;
    return so;
}


#endif // GUARDTYPEARRAY2D_CPP
