#ifndef GuardArrayC_hpp
#define GuardArrayC_hpp

#include "GuardArrayN.hpp"

template<typename T, int ...Dementions>
class GuardArrayC : public GuardArray<T, sizeof...(Dementions)> {
private:
    T datas[GT::MultiplyParameters<Dementions...>::result] = {};
    
public:
    template<typename ...Int>
    GuardArrayC(const char * id = GuardConfig::defaultId)
    : GuardArray<T, sizeof...(Dementions)>()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
        this->setRefArray(this->datas);
        this->InitDementions<sizeof...(Dementions)>(Dementions...);
    }
    
    GuardArrayC(const GuardArrayC& array)
    : GuardArray<T, sizeof...(Dementions)>()
    {
        T* begin = this->datas;
        T* source = const_cast<T*>(&array.datas[0]);
        T* end = this->datas + GT::MultiplyParameters<Dementions...>::result;
        while (begin != end) {
            *begin++ = *source++;
        }
    }
    
    template<int N, typename ...V>
    void InitDementions(size_t index, V ...n) {
        this->dementions[N] = index;
        this->InitDementions<N-1>(n...);
    }
    
    template<int N, typename ...V>
    void InitDementions(size_t index) {
        this->dementions[1] = index;
        this->dementions[0] = 1;
        for (int i = 0; i < sizeof...(Dementions); i++) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
};

#endif /* GuardArrayC_hpp */
