#ifndef GuardArray_hpp
#define GuardArray_hpp

#include <iostream>
#include <iomanip>
#include "GuardType.hpp"
#include "IndexProvider.hpp"
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
    
private:
    GuardArray();
    
public:
    
    GuardArray(size_t n, const char* id = GuardConfig::defaultId)
	: GuardArrayBase<T>(1)
    {
        assert(n>0);
		TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
		this->array = new T[n]();
		this->isAlloc = true;
        this->dementions[0] = 1;
        this->dementions[1] = n;
    }
    
    //template<int N, typename U>
    //GuardArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    //: GuardArrayBase<T>(1)
    //{
	//    TRACE_STRING_SAVE____(this->id = GT::GetNewId(defaultId));
	//	  this->array = new T[N];
	//	  this->isAlloc = true;
    //    T* begin = array;
    //    T* end = begin + N;
    //    T* source = const_cast<int*>(&pArr[0]);
    //    for(; begin != end; begin++, source++) {
    //        *begin = *source;
    //    }
    //}
    
    template<int N, typename U>
    GuardArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
	: GuardArrayBase<T>(1)
    {
		TRACE_STRING_SAVE____(this->id = id);
		this->isAlloc = false;
        this->dementions[0] = 1;
        this->dementions[1] = N;
        this->array = const_cast<int*>(&pArr[0]);
        this->isAlloc = false;
    }
    
    template<int N, typename U>
    GuardArray(bool isReferenceFromArray, const U (&pArr)[N])
	: GuardArrayBase<T>(1)
	{
		TRACE_STRING_SAVE____(this->id = GT::GetNewId());
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
    
    bool operator == (const GuardArray<T, 1>& gt) const {
        return this->array == gt.array;
    }
    
    bool operator != (const GuardArray<T, 1>& gt) const {
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
    
};

#endif /* GuardArray_hpp */
