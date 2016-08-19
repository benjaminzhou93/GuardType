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
    using Ptr = IndexProvider<T, Demention-1>;
    
protected:
    size_t demen[Demention + 1];
    
    GuardArray()
    : GuardArrayBase<T>(Demention, demen)
    {
    }
    
public:
    template<typename ...Int>
    GuardArray(size_t first, Int...n)
    : GuardArrayBase<T>(Demention, demen)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
        this->InitDementions<Demention>(first, n...);
        size_t allElement = this->dementions[Demention];
        this->setNewArray(allElement);
    }
    
    template<int N, typename U>
    GuardArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    : GuardArrayBase<T>(Demention, demen)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
        this->InitWithCArray<Demention>(pArr, true);
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
    
private:
    template<int N, typename ...V>
    void InitDementions(size_t index, V ...n) {
        this->dementions[N] = index;
        this->InitDementions<N-1>(n...);
    }
    
    template<int N, typename ...V>
    void InitDementions(const std::string& id) {
        static_assert(N == 0, "Array init with wrong index count");
        TRACE_STRING_SAVE____(this->id = id);
        this->dementions[0] = 1;
        for (int i = 0; i < Demention; i++) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
    
    template<int N, typename ...V>
    void InitDementions(size_t index) {
        static_assert(N == 1, "Array init with wrong index count");
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
        this->dementions[1] = index;
        this->dementions[0] = 1;
        for (int i = 0; i < Demention; i++) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
    
    template<int D, typename U, int N>
    void InitWithCArray(const U (&arr)[N], bool isRef) {
        this->dementions[D] = N;
        this->InitWithCArray<D-1>(arr[0], isRef);
    }
    
    template<int D, typename U>
    void InitWithCArray(const U& firstArrayElem, bool isRef) {
        for (int i = 0; i < Demention; i++) {
            this->dementions[i + 1] *= this->dementions[i];
        }
        if(isRef) {
            this->setRefArray(&firstArrayElem);
        } else {
            this->setNewArray(this->dementions[Demention]);
        }
    }
};

#endif /* GuardArrayN_hpp */
