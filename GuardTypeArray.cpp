#ifndef GUARDTYPEARR1_CPP
#define GUARDTYPEARR1_CPP
#include "GuardType.h"
#include "GuardTypeArray.h"
#include <assert.h>


//----------------------------GuardType--------------------------------------------
//                         The members of GuardType::Ptr

template<typename T>
template<int N>
GuardType<T>::Ptr::Ptr(const T (&pArr)[N])
: index(), pos(const_cast<T*>(pArr)), isGtAlloc(true) {
    gt = (GuardType<T>*)new GuardTypeArray<T>(pArr, true);
}

//----------------------------GuardTypeArray--------------------------------------------
//                         The members of GuardTypeArray::Ptr2

template<typename T>
GuardTypeArray<T>::Ptr2::Ptr2()
{}

template<typename T>
GuardTypeArray<T>::Ptr2::Ptr2(const ArrayIndex& index, T* pData, const GuardType<T>* gt)
: GuardType<T>::Ptr(index , pData, const_cast<GuardType<T>*>(gt)) {
    assert(pData != NULL);
}

template<typename T>
void GuardTypeArray<T>::Ptr2::SetArrayId(const std::string id) {
    this->gt->id = id;
}

template<typename T>
typename GuardTypeArray<T>::Ptr
GuardTypeArray<T>::Ptr2::operator [] (size_t m) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    this->index.d2 = m;
    typename GuardTypeArray<T>::Ptr
    ptr(this->index, this->pos + m*(this->gt->D1()==0 ? 1 : this->gt->D1()), this->gt);
    ASSERT(0 <= m && m <= this->gt->D2(),
           "TRACE: out of range "+this->gt->MaxIndex()+" used: "+ ptr[0].IdIndex());
    return ptr;
}

template<typename T>
const typename GuardTypeArray<T>::Ptr
GuardTypeArray<T>::Ptr2::operator [] (size_t m) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    const_cast<size_t&>(this->index.d2) = m;
    typename GuardTypeArray<T>::Ptr
    ptr(this->index, this->pos + m*(this->gt->D1()==0 ? 1 : this->gt->D1()), this->gt);
    ASSERT(0 <= m && m <= this->gt->D2(),
           "TRACE: out of range "+this->gt->MaxIndex()+" used: "+ ptr[0].IdIndex());
    return ptr;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator < (const Ptr2& ptr2) const {
    return this->pos < ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator <= (const Ptr2& ptr2) const {
    return this->pos <= ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator > (const Ptr2& ptr2) const {
    return this->pos > ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator >= (const Ptr2& ptr2) const {
    return this->pos >= ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator == (const Ptr2& ptr2) const {
    return this->pos == ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator != (const Ptr2& ptr2) const {
    return this->pos != ptr2.pos;
}

template<typename T>
typename GuardTypeArray<T>::Ptr
GuardTypeArray<T>::Ptr2::operator * () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    typename GuardTypeArray<T>::Ptr ptr(this->index, this->pos, this->gt);
    return ptr;
}

template<typename T>
const typename GuardTypeArray<T>::Ptr
GuardTypeArray<T>::Ptr2::operator * () const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    typename GuardTypeArray<T>::Ptr ptr(this->index, this->pos, this->gt);
    return ptr;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2
GuardTypeArray<T>::Ptr2::operator + (size_t i) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2+i <= this->gt->D2());
    Ptr2 ptr2(this->index, this->pos+this->gt->D1(), this->gt);
    ptr2.index.d2 += i;
    return ptr2;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2
GuardTypeArray<T>::Ptr2::operator - (size_t i) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2-i >= 0);
    Ptr2 ptr2(this->index, this->pos-i*this->gt->D1(), this->gt);
    ptr2.index.d2 -= i;
    return ptr2;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2&
GuardTypeArray<T>::Ptr2::operator += (size_t i) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2+i <= this->gt->D2());
    this->index.d2 += i;
    this->pos += i*this->gt->D1();
    return *this;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2&
GuardTypeArray<T>::Ptr2::operator -= (size_t i) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2-i >= 0);
    this->index.d2 -= i;
    this->pos -= i*this->gt->D1();
    return *this;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2&
GuardTypeArray<T>::Ptr2::operator ++ () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2+1 <= this->gt->D2());
    this->index.d2 += 1;
    this->pos += this->gt->D1();
    return *this;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2
GuardTypeArray<T>::Ptr2::operator ++ (int) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2+1 <= this->gt->D2());
    Ptr2 ptr2(*this);
    this->index.d2 += 1;
    this->pos += this->gt->D1();
    return ptr2;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2&
GuardTypeArray<T>::Ptr2::operator -- () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2-1 >= 0);
    this->index.d2 -= 1;
    this->pos -= this->gt->D1();
    return *this;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2
GuardTypeArray<T>::Ptr2::operator -- (int) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2-1 >= 0);
    Ptr2 ptr2(*this);
    this->pos -= this->gt->D1();
    return ptr2;
}

template<typename T>
size_t GuardTypeArray<T>::Ptr2::operator - (const Ptr2& ptr2) const {
    return this->pos-ptr2.pos;
}





//----------------------------GuardType1--------------------------------------------
//                         The members of GuardTypeArray::Array_ptr

template<typename T>
GuardTypeArray<T>::Array_ptr::Array_ptr(const T* pArr, bool isRef)
    : isReferenceFromArray(isRef), pArr(const_cast<T*>(pArr)) {
}

template<typename T>
T* GuardTypeArray<T>::Array_ptr::get() const {
    return pArr;
}

template<typename T>
void GuardTypeArray<T>::Array_ptr::set(const T* pArr, bool isRef) {
    if (this->pArr != NULL) {
        delete[] this->pArr;
    }
    this->isReferenceFromArray = isRef;
    this->pArr = const_cast<T*>(pArr);
}

template<typename T>
GuardTypeArray<T>::Array_ptr::~Array_ptr() {
    if (pArr != NULL && isReferenceFromArray == false) {
        delete[] pArr;
    }
}





//------------------------------------GuardTypeArray---------------------------------
//                          The members of GuardTypeArray


template<typename T>
GuardTypeArray<T>::GuardTypeArray() : arr(NULL, true){
    
}

template<typename T>
GuardTypeArray<T>::GuardTypeArray(const GuardTypeArray<T>& gt)
    : GuardType<T>(gt.GetNewNameByIncreaseId(gt.id)), length(gt.length),  arr(new T[length+1])
{
    T* pDestination = this->arr.get();
    T* pSource = gt.arr.get();
    for (size_t i=0; i<length; i++) {
        *(pDestination + i) = *(pSource + i);
    }
}

template<typename T>
GuardTypeArray<T>::GuardTypeArray(size_t n, const std::string& id)
    : GuardType<T>(id), length(n), arr(new T[n+1])
{
    assert( n>0);
    T* begin = arr.get();
    T* end = begin + n;
    for(T* iter=begin; iter!=end; iter++)
        new(iter) T();
}

template<typename T>
template<size_t N>
GuardTypeArray<T>::GuardTypeArray(const T (&pArr)[N], const std::string& id)
    : GuardType<T>(GuardType<T>::GetNewId(id)), length(N), arr(new T[N+1])
{
    T* a = arr.get();
    for(size_t i=0; i<N; i++) {
        
        a[i] = pArr[i];
    }
}

template<typename T>
template<size_t N>
GuardTypeArray<T>::GuardTypeArray(const T (&pArr)[N], bool isReferenceFromArray)
    : GuardType<T>(), length(N), arr(pArr, isReferenceFromArray) {
    if(isReferenceFromArray == false) {
        T* a = new T[N+1];
        arr.set(a);
        for(size_t i=0; i<N; i++) {
            a[i] = pArr[i];
        }
    }
}

template<typename T>
size_t GuardTypeArray<T>::size() const {
    return this->length;
}

template<typename T>
size_t GuardTypeArray<T>::Length() const {
    return this->length;
}

template<typename T>
GuardType<T>& GuardTypeArray<T>::operator [] (size_t n) {
    ASSERT(0 <= n && n < length, "TRACE: out of range "+this->MaxIndex()+" used: "+
           this->id+"["+NumToString::Transform(n)+"]");
    if(this->arrReturnValue.insert(std::pair<size_t, GuardType<T>* >(n, NULL)).second == true) {
        this->arrReturnValue[n] = new GuardType<T>(ArrayIndex(0, 0, n), this->Arr()+n, this);
    }
    return *this->arrReturnValue[n];
}

template<typename T>
const GuardType<T>& GuardTypeArray<T>::operator [] (size_t n) const {
    ASSERT(0 <= n && n < length, "TRACE: out of range "+this->MaxIndex()+" used: "+
           this->id+"["+NumToString::Transform(n)+"]");
    if(const_cast<std::map<size_t, GuardType<int> >& >(this->arrReturnValue)
       .insert(std::pair<size_t, GuardType<T> >(n, NULL)).second == true) {
        const_cast<std::map<size_t, GuardType<int> >& >(this->arrReturnValue)[n]
        = new GuardType<T>(ArrayIndex(0, 0, n), this->Arr()+n, this);
    }
    return const_cast<std::map<size_t, GuardType<int> >& >(this->arrReturnValue)[n];
}


template<typename T>
GuardTypeArray<T>::operator const Ptr () {
    return Ptr(ArrayIndex(), Arr(), this);
}

template<typename T>
bool GuardTypeArray<T>::operator == (const GuardTypeArray<T>& gt) const {
    return this->Arr() == gt.Arr();
}

template<typename T>
bool GuardTypeArray<T>::operator != (const GuardTypeArray<T>& gt) const {
    return this->Arr() != gt.Arr();
}

template<typename T>
bool GuardTypeArray<T>::operator == (const Ptr& ptr) const {
    return this->Arr() == ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator < (const Ptr& ptr) const {
    return this->Arr() < ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator <= (const Ptr& ptr) const {
    return this->Arr() <= ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator > (const Ptr& ptr) const {
    return this->Arr() > ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator >= (const Ptr& ptr) const {
    return this->Arr() >= ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator != (const Ptr& ptr) const {
    return this->Arr() != ptr.pos;
}

template<typename T>
template<typename U>
typename GuardTypeArray<T>::Ptr GuardTypeArray<T>::operator + (U n) {
    return Ptr(*this + n);
}

template<typename T>
std::istream& GuardTypeArray<T>::ReadArrayFromIO(
        std::istream &si,
        GuardTypeArray<T>& gt)
{
    T data;
    if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
        if(typeid(si) == typeid(std::cin)) {
            std::cout<< "Please input ";
            std::cout<< "["<< (gt.D2()==0?1:gt.D2())*gt.D1()<< "] Datas "
                      << gt.id << ": " << std::endl;
        }
    }
    T * arr = gt.arr.get();
    for (size_t i=0; i<gt.Length(); i++) {
        si >> data;
        arr[i] = data;
    }
    return si;
}

template<typename T>
std::ostream& GuardTypeArray<T>::WriteArrayToIO(
        std::ostream &so,
        const GuardTypeArray<T>& gt)
{
    T* p = gt.arr.get();
    for (size_t i=0; i<gt.length; i++) {
        if(GuardConfig::_ARRAY_OUT_PUT_SWITCH == true && i == gt.index.d1)
            so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
               << "[" << *(p+i) << "]";
        else
            so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
               << " " << *(p+i) << " ";
    }
    so << std::endl << std::endl;
    const_cast<size_t&>(gt.index.d1) = -1;
    return so;
}


#endif // GUARDTYPEARR1_CPP
