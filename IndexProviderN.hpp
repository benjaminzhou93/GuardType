#ifndef IndexProviderN_hpp
#define IndexProviderN_hpp

#include <iomanip>
#include "IndexProviderO.hpp"

namespace gt {

template<typename T, int Demention>
class GuardTypeArray;

//--------------------------------------------------------------------------
//                            class IndexProvider

template<typename T, int N, typename... Providers>
class IndexProvider
{
    using Ptr1 = IndexProvider<T, N-1, Providers...>;
    using Ptr2 = IndexProvider<T,N+1, Providers...>;

    template<typename U, int M, typename... Providers2>
    friend class IndexProvider;
    
    template<typename U, int Demention, typename... Providers2>
    friend class GuardArray;
    
    typedef gt::GetTplArgs_t<1, gt::TemplatePacker_t<gt::TemplateTypes, gt::TypeFilter_t<gt::IncludeIf<gt::isIndexProvider>, Providers...> > > PtrProvider;
    
private:
    T* pos;
    GuardArrayBase<T, Providers...> * array;
    
protected:
    inline IndexProvider() noexcept : pos(nullptr), array(nullptr) {}
        
public:
    
    inline IndexProvider(const IndexProvider& idx) noexcept
    :pos(idx.pos), array(idx.array)
    {
    }
    
    inline IndexProvider(const IndexProvider<T, N+1, Providers...>& frontIndex, int n) noexcept
    : array(frontIndex.array), pos(frontIndex.pos)
    {
        OUT_OF_INDEX_DETECT__(reinterpret_cast<Ptr2*>(this)->OutOfIndexDetect(n));
        pos += n * array->dementions[N];
    }
    
    inline IndexProvider(const GuardArrayBase<T, Providers...>& arr, int n) noexcept
    : array(&const_cast<GuardArrayBase<T, Providers...>&>(arr)), pos(arr.array)
    {
        OUT_OF_INDEX_DETECT__(reinterpret_cast<Ptr2*>(this)->OutOfIndexDetect(n));
        pos += n * array->dementions[array->dementionCount - 1];
    }
    
    inline T& Data() const noexcept
    {
        return *pos;
    }
    
    void OutOfIndexDetect(int n) const noexcept
    {
        if(0 <= n && n < array->dementions[N]/array->dementions[N-1])
            return;
        std::string usedIndex("array");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            usedIndex = ((IDExpressProvider*)array)->Id();
        long shift = pos - array->array;
        long index = 0;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            index = (i == N-1 ? n : shift / array->dementions[i]);
            usedIndex += "[" + std::to_string(index) + "]";
            shift %= array->dementions[i];
        }
        std::string maxIndex("array");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            maxIndex = ((IDExpressProvider*)array)->Id();
        for (int i = array->dementionCount; i > 0; i--) {
            maxIndex += "[" + std::to_string(array->dementions[i] / array->dementions[i - 1]) + "]";
        }
        std::cout << "Out of index Array: " << maxIndex << ", Used: " << usedIndex << std::endl;
        int OutOfIndex = 0;
        assert(OutOfIndex);
    }
    
    void OutputArray() const noexcept
    {
        T* p = array->array;
        T* end = p + array->dementions[array->dementionCount];
        size_t lineCount = array->dementions[1];
        
        while(p < end) {
            for(int j = 0; j < lineCount; ++j, ++p) {
                if(p == this->pos) {
                    gt::so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << "[" << *(p) << "]";
                } else {
                    gt::so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << " " << *(p) << " ";
                }
            }
            gt::so << std::endl;
            for(int j = 2; j < array->dementionCount; ++j) {
                if((p - array->array) % array->dementions[j] == 0) {
                    gt::so << std::endl;
                }
            }
        }
    }
    
    //--------------------------------------------------------------------------
    //                            Pointer
    
    inline const IndexProvider& operator = (const IndexProvider& ptr) noexcept
    {
        this->pos = ptr.pos;
        this->array = ptr.array;
        return *this;
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<!index> >
    inline Ptr1 operator [] (int m) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        return Ptr1(*this, m);
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<!index> >
    inline const Ptr1 operator [] (int m) const noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        return Ptr1(*this, m);
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<!index> >
    inline Ptr1 operator * () noexcept
    {
        return Ptr1(*this, 0);
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<!index> >
    inline const Ptr1 operator * () const noexcept
    {
        return Ptr1(*this, 0);
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<index> >
    inline Ptr1& operator [] (int m) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        auto& idx = static_cast<PtrProvider&>(*this->array);
        const_cast<T*&>(idx.pos) = this->pos + m * array->dementions[N-1];
        auto& p = reinterpret_cast<Ptr1&>(idx);
        return p;
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<index> >
    inline const Ptr1& operator [] (int m) const noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        auto& idx = static_cast<PtrProvider&>(*this->array);
        const_cast<T*&>(idx.pos) = this->pos + m * array->dementions[N-1];
        auto& p = reinterpret_cast<Ptr1&>(idx);
        return p;
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<index> >
    inline Ptr1& operator * () noexcept
    {
        return reinterpret_cast<Ptr1&>(*this);
    }
    
    template<bool index = gt::isContainFirstType<PtrProvider, Providers...>::value,
            typename = std::enable_if_t<index> >
    inline const Ptr1& operator * () const noexcept
    {
        return reinterpret_cast<Ptr1&>(*this);
    }
};

}

#endif /* IndexProviderN_hpp */
