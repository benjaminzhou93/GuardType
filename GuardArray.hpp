#ifndef GuardArray_hpp
#define GuardArray_hpp

#include "GuardArrayO.hpp"
#include "GuardArrayN.hpp"

namespace gt {

template<typename T, int ...Dementions>
class GTArray : public GuardArray<T, sizeof...(Dementions)
#if ENSURE_MULTITHREAD_SAFETY
    , ThreadSafetyProvider
#else
    , IndexProvider<T, sizeof...(Dementions)>
#endif

#if TRACE_STRING_SAVE
    , IDExpressProvider
#endif
>
{
private:
    T datas[gt::MultiplyParameters<Dementions...>::value] = {};
    
public:
    template<typename ...Int>
    GTArray(const char *id = gt::defaultId) noexcept
    {
        if (std::is_base_of<IDExpressProvider, GTArray>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId(id));
        this->InitDementions<sizeof...(Dementions)>(Dementions...);
        this->setRefArray(this->datas);
    }
    
    GTArray(const GTArray& array) noexcept
    : GuardArray<T, sizeof...(Dementions)>()
    {
        TRACE_STRING_SAVE____(this->id = gt::GetNewIdByIncreaseId(array.id));
        T* begin = this->datas;
        const T* source = &array.datas[0];
        T* end = this->datas + gt::MultiplyParameters<Dementions...>::value;
        while (begin != end) {
            *begin++ = *source++;
        }
    }
    
    GTArray(const gt::RecursivePack_t<sizeof...(Dementions), std::initializer_list, T>& arr) noexcept
    {
        if (std::is_base_of<IDExpressProvider, GTArray>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        this->setRefArray(this->datas);
        this->InitDementions<sizeof...(Dementions)>(Dementions...);
        this->InitFromInitialList<1>(arr, 0);
    }
    
    template<int N, typename U>
    void InitFromInitialList(const std::initializer_list<U>& arr, size_t n) noexcept
    {
        int i = 0;
        for (auto a : arr) {
            InitFromInitialList<N+1>(a, n + i * this->dementions[sizeof...(Dementions) - N]);
            ++i;
        }
    }
    
    template<int N>
    void InitFromInitialList(const T& a, size_t n) noexcept
    {
        this->datas[n] = a;
    }
    
protected:
    template<int N, typename ...V>
    void InitDementions(size_t index, V ...n) noexcept
    {
        this->dementions[N] = index;
        this->InitDementions<N-1>(n...);
    }
    
    template<int N, typename ...V>
    void InitDementions(size_t index) noexcept
    {
        this->dementions[1] = index;
        this->dementions[0] = 1;
        for (int i = 0; i < sizeof...(Dementions); ++i) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
};

}
#endif /* GuardArray_hpp */
