#ifndef GuardArray_hpp
#define GuardArray_hpp

#include "GuardArrayO.hpp"
#include "GuardArrayN.hpp"

template<typename T, int ...Dementions>
class GTArray : public GuardArray<T, sizeof...(Dementions)> {
private:
    T datas[GT::MultiplyParameters<Dementions...>::result] = {};
    
public:
    template<typename ...Int>
    GTArray(const char * id = GuardConfig::defaultId)
    : GuardArray<T, sizeof...(Dementions)>()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
        this->setRefArray(this->datas);
        this->InitDementions<sizeof...(Dementions)>(Dementions...);
    }
    
    GTArray(const GTArray& array)
    : GuardArray<T, sizeof...(Dementions)>()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(array.id));
        T* begin = this->datas;
        T* source = const_cast<T*>(&array.datas[0]);
        T* end = this->datas + GT::MultiplyParameters<Dementions...>::result;
        while (begin != end) {
            *begin++ = *source++;
        }
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
        for (int i = 0; i < sizeof...(Dementions); i++) {
            this->dementions[i + 1] *= this->dementions[i];
        }
    }
};

#endif /* GuardArray_hpp */
