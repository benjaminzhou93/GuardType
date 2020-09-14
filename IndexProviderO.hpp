#ifndef IndexProviderO_hpp
#define IndexProviderO_hpp

#include <iomanip>
#include <cassert>
#include "IDExpressManager.hpp"
#include "IDExpressProvider.hpp"
#include "ThreadSafetyProvider.hpp"
#include "GuardType.hpp"

namespace gt {

template<typename T, typename... Providers>
class GuardArrayBase;

template<typename T, int Demention, typename... Providers>
class GuardArray;

//--------------------------------------------------------------------------
//                            class IndexProvider

template<typename T, typename... Providers>
class IndexProvider<T, 1, Providers...>
{
public:
    using Ptr = IndexProvider<T, 1, Providers...>;
    using Ptr2 = IndexProvider<T, 2, Providers...>;
    
    template<typename U>
    using PtrProvider = IndexProvider<U, 1, Providers...>;
    
    friend IndexProvider<T, 1+1, Providers...>;
    
    template<typename U, template<typename>class DataSource, typename... Providers2>
    friend class GuardType;
    
    template<typename U, typename... Providers2>
    friend class GuardArrayBase;
    
    template<typename U, int Demention, typename... Providers2>
    friend class GuardArray;
    
    typedef std::random_access_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef size_t                              difference_type;
    typedef Ptr                                 pointer;
    typedef T&                                  reference;
    
    template<typename... Providers2>
    using ValueTemplate = GuardType<T, PtrProvider, Providers2...>;
    typedef gt::TemplatePacker_t<ValueTemplate, gt::TypeFilter_t<gt::ExcludeIf<gt::ConditionOr<gt::isIndexProvider, gt::isIDExpressProvider>::template tpl>, Providers...> > ValueType;
    
private:
    inline IndexProvider(GuardArrayBase<T, Providers...> * array) noexcept : array(array), pos(array->array) {}
    
protected:
    inline IndexProvider() noexcept : array(nullptr), pos(nullptr) {}
    
public:
    T* const pos;
    GuardArrayBase<T, Providers...> * const array;
    
public:
    inline IndexProvider(const GuardArrayBase<T, Providers...>* array) noexcept
    : array(const_cast<GuardArrayBase<T, Providers...>*>(array))
    {
    }
    
    inline IndexProvider(const IndexProvider<T, 1, Providers...>& idx) noexcept
    : pos(idx.pos), array(idx.array)
    {
    }
    
    inline IndexProvider(const IndexProvider<T, 2, Providers...>& frontIndex, int n) noexcept
    : array(frontIndex.array), pos(frontIndex.pos)
    {
        OUT_OF_INDEX_DETECT__(frontIndex.OutOfIndexDetect(n));
        const_cast<T*&>(this->pos) += n * array->dementions[2 - 1];
    }
    
    template<typename... Provider2>
    inline IndexProvider(const GuardArray<T, 1, Provider2...>& arr, int n) noexcept
    : array(&const_cast<GuardArray<T, 1, Provider2...>&>(arr)), pos(arr.array + n)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
    }
    
    template<typename... Provider2>
    inline IndexProvider(const GuardArray<T, 2, Provider2...>& arr, int n) noexcept
    : array(&const_cast<GuardArray<T, 2, Provider2...>&>(arr)), pos(arr.array)
    {
        OUT_OF_INDEX_DETECT__(reinterpret_cast<Ptr2*>(this)->OutOfIndexDetect(n));
        const_cast<T*&>(this->pos) += n * arr.dementions[2-1];
    }
    
    inline T& Data() noexcept
    {
        return *pos;
    }
    
    
    inline const T& Data() const noexcept
    {
        return *pos;
    }
    
    inline std::string Id() const noexcept
    {
        std::string id = "array";
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            id = ((IDExpressProvider*)array)->Id();
        long shift = this->pos - array->array;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            id += "[" + std::to_string(shift / array->dementions[i]) + "]";
            shift %= this->array->dementions[i];
        }
        return id;
    }
    
    void OutOfIndexDetect(int n) const noexcept
    {
        if(0 <= n && n < array->dementions[1]) return;
        std::string usedIndex("array");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            usedIndex = ((IDExpressProvider*)array)->Id();
        long shift = pos - array->array;
        long index = 0;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            index = (i == 0 ? n : shift/array->dementions[i]);
            usedIndex += "["+std::to_string(index)+"]";
            shift %= array->dementions[i];
        }
        std::string maxIndex("array");
        if (gt::isContainFirstType<IDExpressProvider, Providers...>::value)
            maxIndex = ((IDExpressProvider*)array)->Id();
        for (int i = array->dementionCount; i > 0; i--) {
            maxIndex += "["+std::to_string(array->dementions[i] / array->dementions[i-1])+"]";
        }
        std::cout << "Out of index Array: " << maxIndex << ", Used: " << usedIndex << std::endl;
        int OutOfIndex = 0;
        assert(OutOfIndex);
    }
    
    void OutputArray() const noexcept
    {
        if(GuardConfig::_ARRAY_OUT_PUT_SWITCH == false) return;
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
            for (int j = 2; j < array->dementionCount; ++j) {
                if((p - array->array) % array->dementions[j] == 0) {
                    gt::so << std::endl;
                }
            }
        }
    }
    
    
    //--------------------------------------------------------------------------
    //                            Pointer
    
    inline IndexProvider(const Ptr& ptr, int n) noexcept
    : array(ptr.array), pos(ptr.pos)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(int((pos - array->array) % array->dementions[1] + n)));
        const_cast<T*&>(this->pos) += n;
    }
    
    inline const Ptr& operator = (const Ptr& ptr) noexcept
    {
        const_cast<T*&>(this->pos) = ptr.pos;
        this->array = ptr.array;
        return *this;
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<thread || express> >
    inline ValueType operator [] (int m) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        return ValueType(*this, m);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<thread || express> >
    inline const ValueType operator [] (int m) const noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        return ValueType(*this, m);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<thread || express> >
    inline ValueType operator * () noexcept
    {
        return ValueType(*this, 0);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<thread || express> >
    inline const ValueType operator * () const noexcept
    {
        return ValueType(*this, 0);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<!thread && !express> >
    inline T& operator [] (int m) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        return *(pos+m);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<!thread && !express> >
    inline const T& operator [] (int m) const noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        return *(pos+m);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<!thread && !express> >
    inline T& operator * () noexcept
    {
        return *(pos);
    }
    
    template<bool thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            typename = std::enable_if_t<!thread && !express> >
    inline const T& operator * () const noexcept
    {
        return *(pos);
    }
    
    inline bool operator < (const Ptr& ptr) const noexcept
    {
        return this->pos < ptr.pos;
    }
    
    inline bool operator <= (const Ptr& ptr) const noexcept
    {
        return this->pos <= ptr.pos;
    }
    
    inline bool operator > (const Ptr& ptr) const noexcept
    {
        return this->pos > ptr.pos;
    }
    
    inline bool operator >= (const Ptr& ptr) const noexcept
    {
        return this->pos >= ptr.pos;
    }
    
    inline bool operator == (const Ptr& ptr) const noexcept
    {
        return this->pos == ptr.pos;
    }
    
    inline bool operator != (const Ptr& ptr) const noexcept
    {
        return this->pos != ptr.pos;
    }
    
    inline bool operator == (const T* p) const noexcept
    {
        return this->pos == p;
    }
    
    inline bool operator != (const T* p) const noexcept
    {
        return this->pos != p;
    }
    
    inline Ptr operator + (int i) const noexcept
    {
        return Ptr(*this, i);
    }
    
    inline Ptr operator - (int i) const noexcept
    {
        return Ptr(*this, -1*i);
    }
    
    inline Ptr&operator += (int i) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(i+(pos-array->array)%array->dementions[1]));
        const_cast<T*&>(this->pos) += i;
        return *this;
    }
    
    inline Ptr&operator -= (int i) noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(-i+(pos-array->array)%array->dementions[1]));
        const_cast<T*&>(this->pos) -= i;
        return *this;
    }
    
    inline Ptr&operator ++ () noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(1+(pos-array->array)%array->dementions[1]));
        const_cast<T*&>(this->pos) += 1;
        return *this;
    }
    
    inline Ptr operator ++ (int) noexcept
    {
        Ptr ret(*this, 1);
        const_cast<T*&>(this->pos) += 1;
        return ret;
    }
    
    inline Ptr& operator -- () noexcept
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(-1+(pos-array->array)%array->dementions[1]));
        const_cast<T*&>(this->pos) -= 1;
        return *this;
    }
    
    inline Ptr operator -- (int) noexcept
    {
        Ptr ret(*this ,-1);
        const_cast<T*&>(this->pos) -= 1;
        return ret;
    }
    
    inline size_t operator - (const Ptr& ptr) const noexcept
    {
        return const_cast<T*&>(this->pos)-ptr.pos;
    }
};

}

#endif /* IndexProviderO_hpp */
