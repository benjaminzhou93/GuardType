#ifndef GuardArrayN_hpp
#define GuardArrayN_hpp

#include <iostream>
#include <iomanip>
#include "IndexProviderN.hpp"
#include "GuardArrayBase.hpp"

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
        this->setNewMutexes(allElement);
    }
    
    template<typename U, int N>
    GuardArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    : GuardArrayBase<T>(Demention, demen)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
        this->InitWithCArray<Demention>(pArr);
        this->setNewMutexes(this->dementions[Demention]);
    }
    
    size_t size() const {
        return this->dementions[Demention];
    }
    
#if ENSURE_MULTITHREAD_SAFETY || !ORIGINAL_FASTER_BUT_UNSAFE
    Ptr operator [] (size_t n) {
        return Ptr(*this, n);
    }
    
    const Ptr operator [] (size_t n) const {
        return Ptr(*this, n);
    }
#else
    Ptr& operator [] (size_t n) {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        this->index.pos = this->array + n * this->dementions[Demention-1];
        return reinterpret_cast<Ptr&>(this->index);
    }
    
    const Ptr& operator [] (size_t n) const {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        this->index[Demention-2].pos = this->array + n * this->dementions[Demention-1];
        return reinterpret_cast<Ptr&>(this->index[Demention-2]);
    }
#endif
    
private:
    template<int N, typename ...V>
    void InitDementions(size_t index, V ...n) {
        this->dementions[N] = index;
        this->InitDementions<N-1>(n...);
    }
    
    template<int N, typename ...V>
    void InitDementions(const std::string& id) {
        static_assert(N == 0, "Array init with wrong number of Dementions");
        TRACE_STRING_SAVE____(this->id = id);
        this->dementions[0] = 1;
        for (int i = 0; i < Demention; ++i) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
    
    template<int N, typename ...V>
    void InitDementions(size_t index) {
        static_assert(N == 1, "Array init with wrong number of Dementions");
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
        this->dementions[1] = index;
        this->dementions[0] = 1;
        for (int i = 0; i < Demention; ++i) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
    
    template<int D, typename U, int N>
    void InitWithCArray(const U (&arr)[N]) {
        static_assert(D >= 1, "Array init with wrong number of Dementions");
        this->dementions[D] = N;
        this->InitWithCArray<D-1>(arr[0]);
    }
    
    template<int D, typename U>
    void InitWithCArray(const U& firstArrayElem) {
        static_assert(D == 0, "Array init with wrong number of Dementions");
        this->dementions[0] = 1;
        for (int i = 0; i < Demention; ++i) {
            this->dementions[i + 1] *= this->dementions[i];
        }
        this->setRefArray(&firstArrayElem);
    }
    
    void OutOfIndexDetect(size_t n) const {
        if(n < this->dementions[Demention]/this->dementions[Demention-1]) return;
        std::string usedIndex("array");
        TRACE_STRING_SAVE____(usedIndex = this->id);
        size_t index = 0;
        for (int i = Demention-1; i >= 0; i--) {
            index = (i == Demention-1 ? n : 0);
            usedIndex += "[" + std::to_string(index) + "]";
        }
        std::string maxIndex("array");
        TRACE_STRING_SAVE____(maxIndex = this->id);
        for (int i = Demention; i > 0; i--) {
            maxIndex += "[" + std::to_string(this->dementions[i] / this->dementions[i - 1]) + "]";
        }
        std::cout << "Out of index Array: " << maxIndex << ", Used: " << usedIndex << std::endl;
        int OutOfIndex = 0;
        assert(OutOfIndex);
    }
};

#endif /* GuardArrayN_hpp */
