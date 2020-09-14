#ifndef GuardArrayN_hpp
#define GuardArrayN_hpp

#include <iostream>
#include <iomanip>
#include "IndexProviderN.hpp"
#include "GuardArrayBase.hpp"

namespace gt {

//---------------------------------------------------------------------------
//                            class GuardArray

template<typename T, int Demention, typename... Providers>
class GuardArray : public GuardArrayBase<T, Providers...>
{
public:
    using Ptr = IndexProvider<T, Demention, Providers...>;
    using Ptr1 = IndexProvider<T, Demention-1, Providers...>;
    typedef gt::GetTplArgs_t<1, gt::TemplatePacker_t<gt::TemplateTypes, gt::TypeFilter_t<gt::IncludeIf<gt::isIndexProvider>, Providers...> > > PtrProvider;
    
protected:
    size_t demen[Demention + 1];
    
    GuardArray() noexcept
    : GuardArrayBase<T, Providers...>(Demention, demen)
    {
    }
    
public:
    template<typename ...Int>
    GuardArray(size_t first, Int...n) noexcept
    : GuardArrayBase<T, Providers...>(Demention, demen)
    {
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        this->InitDementions<Demention>(first, n...);
        size_t allElement = this->dementions[Demention];
        this->setNewArray(allElement);
    }
    
    template<typename U, int N>
    GuardArray(const U (&pArr)[N], const char* id = gt::defaultId) noexcept
    : GuardArrayBase<T, Providers...>(Demention, demen)
    {
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId(id));
        this->InitWithCArray<Demention>(pArr);
    }
    
    size_t size() const noexcept
    {
        return this->dementions[Demention];
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<!index> >
    inline Ptr1 operator [] (int n) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        return Ptr1(*this, n);
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<!index> >
    inline const Ptr1 operator [] (int n) const noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        return Ptr1(*this, n);
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<index> >
    inline Ptr1& operator [] (int n) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        auto& idx = static_cast<PtrProvider&>(*this);
        const_cast<T*&>(idx.pos) = this->array + n * this->dementions[Demention-1];
        auto& p = reinterpret_cast<Ptr1&>(idx);
        const_cast<GuardArrayBase<T, Providers...>*&>(p.array) = this;
        return p;
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<index> >
    inline const Ptr1& operator [] (int n) const noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        auto& idx = static_cast<PtrProvider&>(const_cast<GuardArray&>(*this));
        const_cast<T*&>(idx.pos) = this->array + n * this->dementions[Demention-1];
        auto& p = reinterpret_cast<Ptr1&>(idx);
        const_cast<GuardArrayBase<T, Providers...>*&>(p.array) = const_cast<GuardArray*>(this);
        return p;
    }
    
private:
    template<int N, typename ...V>
    inline void InitDementions(size_t index, V ...n) noexcept
    {
        this->dementions[N] = index;
        this->InitDementions<N-1>(n...);
    }
    
    template<int N, typename ...V>
    inline void InitDementions(const char* id) noexcept
    {
        static_assert(N == 0, "Array init with wrong number of Dementions");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId(id));
        this->dementions[0] = 1;
        for (int i = 0; i < Demention; ++i) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
    
    template<int N, typename ...V>
    inline void InitDementions(size_t index) noexcept
    {
        static_assert(N == 1, "Array init with wrong number of Dementions");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        this->dementions[1] = index;
        this->dementions[0] = 1;
        for (int i = 0; i < Demention; ++i) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
    
    template<int D, typename U, int N>
    inline void InitWithCArray(const U (&arr)[N]) noexcept
    {
        static_assert(D >= 1, "Array init with wrong number of Dementions");
        this->dementions[D] = N;
        this->InitWithCArray<D-1>(arr[0]);
    }
    
    template<int D, typename U>
    inline void InitWithCArray(const U& firstArrayElem) noexcept
    {
        static_assert(D == 0, "Array init with wrong number of Dementions");
        this->dementions[0] = 1;
        for (int i = 0; i < Demention; ++i) {
            this->dementions[i + 1] *= this->dementions[i];
        }
        this->setRefArray(&firstArrayElem);
    }
    
    void OutOfIndexDetect(int n) const noexcept
    {
        if(0  <= n && n < this->dementions[Demention]/this->dementions[Demention-1])
            return;
        std::string usedIndex("array");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            usedIndex = ((IDExpressProvider*)this)->Id();
        int index = 0;
        for (int i = Demention-1; i >= 0; i--) {
            index = (i == Demention-1 ? n : 0);
            usedIndex += "[" + std::to_string(index) + "]";
        }
        std::string maxIndex("array");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            maxIndex = ((IDExpressProvider*)this)->Id();
        for (int i = Demention; i > 0; i--) {
            maxIndex += "[" + std::to_string(this->dementions[i] / this->dementions[i - 1]) + "]";
        }
        std::cout << "Out of index Array: " << maxIndex << ", Used: " << usedIndex << std::endl;
        int OutOfIndex = 0;
        assert(OutOfIndex);
    }
};

}

#endif /* GuardArrayN_hpp */
