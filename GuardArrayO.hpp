#ifndef GuardArrayO_hpp
#define GuardArrayO_hpp

#include <iostream>
#include <iomanip>
#include "GuardType.hpp"
#include "TemporaryProvider.hpp"
#include "IndexProviderO.hpp"
#include "GuardArrayBase.hpp"

namespace gt {

//-----------------------------------------------------------------------------
//                            class GuardArray

template<typename T, typename... Providers>
class GuardArray<T, 1, Providers...> : public GuardArrayBase<T, Providers...>
{
public:
    using Ptr = IndexProvider<T, 1, Providers...>;
    
    template<typename U>
    using PtrProvider = IndexProvider<U, 1, Providers...>;
    
    template<typename... Providers2>
    using ValueTemplate = GuardType<T, PtrProvider, Providers2...>;
    
    typedef Ptr iterator;
    
    typedef gt::TemplatePacker_t<ValueTemplate, gt::TypeFilter_t<gt::Exclude<IDExpressProvider>, Providers...> > value_type;
    
protected:
    size_t demen[1+1];
    
    GuardArray() noexcept
    : GuardArrayBase<T, Providers...>(1, demen)
    {
    }
    
public:
    GuardArray(size_t n, const char* id = gt::defaultId) noexcept
    : GuardArrayBase<T, Providers...>(1, demen)
    {
        assert(n>0);
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId(id));
        this->dementions[0] = 1;
        this->dementions[1] = n;
        this->setNewArray(n);
    }
    
    template<int N, typename U>
    GuardArray(const U (&pArr)[N], const char* id = gt::defaultId) noexcept
    : GuardArrayBase<T, Providers...>(1, demen)
    {
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId(id));
        this->dementions[0] = 1;
        this->dementions[1] = N;
        this->setRefArray(&pArr[0]);
    }
    
    inline size_t size() const noexcept
    {
        return this->dementions[1];
    }
    
    inline size_t length() const noexcept
    {
        return this->dementions[1];
    }
    
    inline T* begin() const noexcept
    {
        return this->array;
    }
    
    inline T* end() const noexcept
    {
        return this->array+this->dementions[1];
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<thread || express> >
    inline value_type operator [] (int n) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        return value_type(*this, n);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<thread || express> >
    inline const value_type operator [] (int n) const noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        return value_type(*this, n);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<!thread && !express> >
    inline T& operator [] (int n) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        return this->array[n];
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<!thread && !express> >
    inline const T& operator [] (int n) const noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        return this->array[n];
    }
    
    void OutOfIndexDetect(int n) const noexcept
    {
        if(0 <= n && n < this->dementions[1]) return;
        std::string id("array");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            id = ((IDExpressProvider*)this)->Id();
        OUT_OF_INDEX_DETECT__(std::cout << "Out of index Array: "
                              << id << "[" << std::to_string(this->dementions[1]) << "]"
                              << ", Used: "
                              << id << "[" << std::to_string(n) << "]"
                              << std::endl);
        int OutOfIndex = 0;
        assert(OutOfIndex);
    }
    
    inline bool operator == (const Ptr& ptr) const noexcept
    {
        return this->array == ptr.pos;
    }
    
    inline bool operator < (const Ptr& ptr) const noexcept
    {
        return this->array < ptr.pos;
    }
    
    inline bool operator <= (const Ptr& ptr) const noexcept
    {
        return this->array <= ptr.pos;
    }
    
    inline bool operator > (const Ptr& ptr) const noexcept
    {
        return this->array > ptr.pos;
    }
    
    inline bool operator >= (const Ptr& ptr) const noexcept
    {
        return this->array >= ptr.pos;
    }
    
    inline bool operator != (const Ptr& ptr) const noexcept
    {
        return this->array != ptr.pos;
    }
};

}

#endif /* GuardArrayO_hpp */
