#ifndef GuardArray_hpp
#define GuardArray_hpp

#include <vector>
#include "GuardArrayO.hpp"
#include "GuardArrayN.hpp"

template<typename T, int ...Dementions>
class GTArray : public GuardArray<T, sizeof...(Dementions)> {
private:
    T datas[GT::MultiplyParameters<Dementions...>::value] = {};
    MULTITHREAD_GUARD____(std::recursive_mutex mutexes[GT::MultiplyParameters<Dementions...>::value] = {};)
public:
    template<typename ...Int>
    GTArray(const char * id = GuardConfig::defaultId)
    : GuardArray<T, sizeof...(Dementions)>()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
        this->InitDementions<sizeof...(Dementions)>(Dementions...);
        this->setRefArray(this->datas);
        MULTITHREAD_GUARD____(this->setRefMutexes(this->mutexes));
    }
    
    GTArray(const GTArray& array)
    : GuardArray<T, sizeof...(Dementions)>()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(array.id));
        T* begin = this->datas;
        const T* source = &array.datas[0];
        T* end = this->datas + GT::MultiplyParameters<Dementions...>::value;
        while (begin != end) {
            *begin++ = *source++;
        }
    }
    
    GTArray(const typename GT::RecursivePack<sizeof...(Dementions), std::initializer_list, T>::type& arr) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
        this->setRefArray(this->datas);
        this->InitDementions<sizeof...(Dementions)>(Dementions...);
        this->InitFromInitialList<1>(arr, 0);
    }
    
    template<int N, typename U>
    void InitFromInitialList(const std::initializer_list<U>& arr, size_t n) {
        int i = 0;
        for (auto a : arr) {
            InitFromInitialList<N+1>(a, n + i * this->dementions[sizeof...(Dementions) - N]);
            ++i;
        }
    }
    
    template<int N>
    void InitFromInitialList(const T& a, size_t n) {
        this->datas[n] = a;
    }
    
protected:
    template<int N, typename ...V>
    void InitDementions(size_t index, V ...n) {
        this->dementions[N] = index;
        this->InitDementions<N-1>(n...);
    }
    
    template<int N, typename ...V>
    void InitDementions(size_t index) {
        this->dementions[1] = index;
        this->dementions[0] = 1;
        for (int i = 0; i < sizeof...(Dementions); ++i) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
};

#endif /* GuardArray_hpp */
