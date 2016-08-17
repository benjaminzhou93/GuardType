#ifndef GuardArrayN_hpp
#define GuardArrayN_hpp

#include <iostream>
#include <iomanip>
#include "IndexProviderN.hpp"
#include "GuardArray.hpp"

//---------------------------------------------------------------------------
//                            class GuardArray

template<typename T, int Demention>
class GuardArray : public GuardArrayBase<T> {
public:
    template<int D>
    friend struct GT::InitWithCArray;
    
    using Ptr = IndexProvider<T, Demention-1>;
    
private:
    GuardArray();
    
public:
    
    //template<int N, typename U>
    //GuardArray(const U (&pArr)[N], const std::string& id)
    //: GuardArrayBase<T>(Demention)
    //{
	//	  this->array = new T[N];
	//	  this->isAlloc = true;
	//    TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
    //    GT::InitWithCArray<Demention>::Init(*this, pArr);
    //}
    
    template<int N, typename U>
    GuardArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
	: GuardArrayBase<T>(Demention)
	{
		TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
		this->isAlloc = false;
        GT::InitWithCArray<Demention>::Init(*this, pArr);
    }
    
    template<int N, typename U>
    GuardArray(bool isReferenceFromArray, const U (&pArr)[N])
	: GuardArrayBase<T>(Demention)
	{
		TRACE_STRING_SAVE____(this->id = GT::GetNewId());
		this->isAlloc = isReferenceFromArray;
        GT::InitWithCArray<Demention>::Init(*this, pArr);
    }
    
    template<typename ...Int>
    GuardArray(size_t first, Int...n)
	: GuardArrayBase<T>(Demention)
	{
		TRACE_STRING_SAVE____(this->id = GT::GetNewId());
		this->isAlloc = true;
        this->InitWithIndexs<Demention>(first, n...);
    }
    
    template<int N, typename ...V>
    void InitWithIndexs(size_t index, V ...n) {
        this->dementions[N] = index;
        this->InitWithIndexs<N-1>(n...);
    }
    
    template<int N, typename ...V>
    void InitWithIndexs(const std::string& id) {
        static_assert(N == 0, "Array init with wrong index count");
        TRACE_STRING_SAVE____(this->id = id);
        this->AllocWithDementions();
    }
    
    template<int N, typename ...V>
    void InitWithIndexs(size_t index) {
        static_assert(N == 1, "Array init with wrong index count");
        this->dementions[1] = index;
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
        this->AllocWithDementions();
    }
    
    size_t size() const {
        return this->dementions[Demention];
    }
    
    Ptr operator [] (size_t n) {
        return Ptr(*this, n);
    }
    
    const Ptr operator [] (size_t n) const {
        return Ptr(*this, n);
    }
    
};

#endif /* GuardArrayN_hpp */
