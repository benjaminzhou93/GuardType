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
