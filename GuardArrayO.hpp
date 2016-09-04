#ifndef GuardArrayO_hpp
#define GuardArrayO_hpp

#include <iostream>
#include <iomanip>
#include "GuardType.hpp"
#include "IndexProviderO.hpp"
#include "GuardArrayBase.hpp"

//-----------------------------------------------------------------------------
//                            class GuardArray

template<typename T>
class GuardArray<T, 1> : public GuardArrayBase<T> {
public:
    using Ptr = IndexProvider<T, 1>;
    
    template<typename U>
    using Provider = IndexProvider<U, 1>;
    
    typedef Ptr                         iterator;
    typedef GuardType<T, Provider>      value_type;
    
protected:
    size_t demen[1+1];
    
    GuardArray()
    : GuardArrayBase<T>(1, demen)
    {
    }
    
public:
    GuardArray(size_t n, const char* id = GuardConfig::defaultId)
    : GuardArrayBase<T>(1, demen)
    {
        assert(n>0);
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
        this->dementions[0] = 1;
        this->dementions[1] = n;
        this->setNewArray(n);
        this->setNewMutexes(n);
    }
    
    template<int N, typename U>
    GuardArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    : GuardArrayBase<T>(1, demen)
    {
        TRACE_STRING_SAVE____(this->id = id);
        this->dementions[0] = 1;
        this->dementions[1] = N;
        this->setRefArray(&pArr[0]);
        this->setNewMutexes(N);
    }
    
    size_t size() const {
        return this->dementions[1];
    }
    
    size_t length() const {
        return this->dementions[1];
    }
    
    T* begin() const  {
        return this->array;
    }
    
    T* end() const  {
        return this->array+this->dementions[1];
    }
    
#if ENSURE_MULTITHREAD_SAFETY || !ORIGINAL_FASTER_BUT_UNSAFE
    value_type operator [] (size_t n) {
        return value_type(*this, n);
    }
    
    const value_type operator [] (size_t n) const {
        return value_type(*this, n);
    }
#else
    T& operator [] (size_t n) {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        return this->array[n];
    }
    
    const T& operator [] (size_t n) const {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        return this->array[n];
    }
#endif
    
    void OutOfIndexDetect(size_t n) const {
        if(n < this->dementions[1]) return;
        std::string id("array");
        TRACE_STRING_SAVE____(id = this->id);
        OUT_OF_INDEX_DETECT__(std::cout << "Out of index Array: "
                              << id << "[" << std::to_string(this->dementions[1]) << "]"
                              << ", Used: "
                              << id << "[" << std::to_string(n) << "]"
                              << std::endl);
        int OutOfIndex = 0;
        assert(OutOfIndex);
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
};

#endif /* GuardArrayO_hpp */
