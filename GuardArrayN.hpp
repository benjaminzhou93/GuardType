#ifndef GuardArrayN_hpp
#define GuardArrayN_hpp

#include <iostream>
#include <iomanip>
#include "IndexProviderN.hpp"
#include "GuardArrayBase.hpp"

//---------------------------------------------------------------------------
//                            class GuardArray

template<typename T, int Demention, typename... Providers>
class GuardArray : public GuardArrayBase<T> {
public:
    using Ptr = IndexProvider<T, Demention, Providers...>;
    using Ptr_1 = IndexProvider<T, Demention-1, Providers...>;
    
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
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewId());
        this->InitDementions<Demention>(first, n...);
        size_t allElement = this->dementions[Demention];
        this->setNewArray(allElement);
        if(GT::isContainMultiFirstType<ArrayThreadSafetyProvider, Providers...>::value)
            this->setNewMutexes(allElement);
    }
    
    template<typename U, int N>
    GuardArray(const U (&pArr)[N], const char* id = IDExpressManager::defaultId)
    : GuardArrayBase<T>(Demention, demen)
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewId(id));
        this->InitWithCArray<Demention>(pArr);
        if(GT::isContainMultiFirstType<ArrayThreadSafetyProvider, Providers...>::value)
            this->setNewMutexes(this->dementions[Demention]);
    }
    
    size_t size() const {
        return this->dementions[Demention];
    }
    
#if ENSURE_MULTITHREAD_SAFETY || SAVE_EXPRES_SLOWER_SPEED
    Ptr_1 operator [] (int n) {
        return Ptr_1(*this, n);
    }
    
    const Ptr_1 operator [] (int n) const {
        return Ptr_1(*this, n);
    }
#else
    Ptr_1& operator [] (int n) {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        const_cast<T*&>(this->index.pos) = this->array + n * this->dementions[Demention-1];
        return reinterpret_cast<Ptr_1&>(this->index);
    }
    
    const Ptr_1& operator [] (int n) const {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        const_cast<T*&>(this->index.pos) = this->array + n * this->dementions[Demention-1];
        return reinterpret_cast<Ptr_1&>(this->index);
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
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewId());
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
    
    void OutOfIndexDetect(long n) const {
        if(0  <= n && n < this->dementions[Demention]/this->dementions[Demention-1]) return;
        std::string usedIndex("array");
        TRACE_STRING_SAVE____(usedIndex = this->id);
        int index = 0;
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
