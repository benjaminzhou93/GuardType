#ifndef GuardTypeArray_hpp
#define GuardTypeArray_hpp

#include <iostream>
#include <iomanip>
#include "GuardType.hpp"
#include "ArrayIndexProvider.hpp"

//-----------------------------------------------------------------------------
//                            class GuardTypeArray

template<typename T>
class GuardTypeArray<T, 1> {
public:
    template<typename U, int Demention, int N>
    friend class ArrayIndexProvider;
    
    using Ptr = ArrayIndexProvider<T, 1, 1>;
    
    template<typename U>
    using Provider = ArrayIndexProvider<U, 1, 1>;
    
    typedef Ptr                         iterator;
    
    typedef GuardType<T, Provider>      value_type;
    
private:
    GuardTypeArray();
    
private:
    size_t dementions[2];
    
protected:
    T*   array;
    bool isAlloc;
    
public:
    TRACE_STRING_SAVE____(std::string id);
    
public:
    ~GuardTypeArray() {
        if(isAlloc) {
            delete[] this->array;
        }
    }
    
    GuardTypeArray(const GuardTypeArray<T, 1>& gt)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewIdByIncreaseId(gt.id)))
    isAlloc(true)
    {
        size_t elementCount = this->dementions[1] = gt.dementions[1];
        this->dementions[0] = 1;
        array = new T[elementCount];
        
        T* begin = array;
        T* end = begin + elementCount;
        T* source = gt.array;
        for(; begin!=end; begin++, source++) {
            *begin = *source;
        }
    }
    
    GuardTypeArray(size_t n, const char* id = GuardConfig::defaultId)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId(id)))
    array(new T[n]()), isAlloc(true)
    {
        assert(n>0);
        this->dementions[0] = 1;
        this->dementions[1] = n;
    }
    
    //template<int N, typename U>
    //GuardTypeArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    //: TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId(id)))
    //array(new T[N]), isAlloc(true)
    //{
    //    T* begin = array;
    //    T* end = begin + N;
    //    T* source = const_cast<int*>(&pArr[0]);
    //    for(; begin != end; begin++, source++) {
    //        *begin = *source;
    //    }
    //}
    
    template<int N, typename U>
    GuardTypeArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    : TRACE_STRING_SAVE_DECLARE(id(id))
    isAlloc(false)
    {
        this->dementions[0] = 1;
        this->dementions[1] = N;
        this->array = const_cast<int*>(&pArr[0]);
        this->isAlloc = false;
    }
    
    template<int N, typename U>
    GuardTypeArray(bool isReferenceFromArray, const U (&pArr)[N])
    TRACE_STRING_SAVE____(: id(GT::GetNewId())) {
        this->dementions[0] = 1;
        this->dementions[1] = N;
        if(isReferenceFromArray == false) {
            this->array = new T[N];
            this->isAlloc = true;
            
            T* begin = this->array;
            T* end = begin+N;
            T* source = pArr;
            for(; begin != end; begin++, source++) {
                *begin = *source;
            }
        } else {
            this->array = const_cast<int*>(&pArr[0]);
            this->isAlloc = false;
        }
    }
    
    size_t size() const {
        return this->dementions[1];
    }
    
    size_t length() const {
        return this->dementions[1];
    }
    
    Ptr begin() const  {
        return Ptr(*this, 0);
    }
    
    Ptr end() const  {
        return Ptr(*this, this->dementions[1]);
    }
    
    value_type operator [] (size_t n) {
        return value_type(*this, n);
    }
    
    const value_type operator [] (size_t n) const {
        return value_type(*this, n);
    }
    
    operator const Ptr () {
        return Ptr(*this, 0);
    }
    
    bool operator == (const GuardTypeArray<T, 1>& gt) const {
        return this->array == gt.array;
    }
    
    bool operator != (const GuardTypeArray<T, 1>& gt) const {
        return this->array != gt.array;
    }
    
    bool operator == (const Ptr& ptr) const {
        return this->array == ptr.pos;
    }
    
    bool operator < (const Ptr& ptr) const {
        return this->array < ptr.pos;
    }
    
    bool operator <= (const Ptr& ptr) const {
        return this->array <= ptr.pos;
    }
    
    bool operator > (const Ptr& ptr) const {
        return this->array > ptr.pos;
    }
    
    bool operator >= (const Ptr& ptr) const {
        return this->array >= ptr.pos;
    }
    
    bool operator != (const Ptr& ptr) const {
        return this->array != ptr.pos;
    }
    
    template<typename U>
    Ptr operator + (U n) {
        return Ptr(*this, n);
    }
    
    friend std::istream& operator >> (std::istream &   si,
                                      GuardTypeArray& gt) {
        T data;
        if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
            if(typeid(si) == typeid(std::cin)) {
                std::cout<< "Please input ";
                std::cout<< "["<< gt.size() << "] Datas "
                << gt.id << ": " << std::endl;
            }
        }
        T * arr = gt.array;
        for (int i=0; i<gt.size(); i++) {
            si >> data;
            arr[i] = data;
        }
        return si;
    }
    
    friend std::ostream& operator << (std::ostream &        so,
                                      const GuardTypeArray& gt) {
        T* p = gt.array;
        for (int i=0; i<gt.size(); i++) {
            so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
            << " " << *(p+i) << " ";
        }
        so << std::endl << std::endl;
        return so;
    }
};

#endif /* GuardTypeArray_hpp */
