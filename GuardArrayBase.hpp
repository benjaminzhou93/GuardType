#ifndef GuardArrayBase_hpp
#define GuardArrayBase_hpp

#include <iostream>
#include <iomanip>
#include "ValueObserverProvider.hpp"

namespace gt {

//-----------------------------------------------------------------------------
//                            class GuardArrayBase

template<typename T, typename... Providers>
class GuardArrayBase : public Providers...
{
public:
    template<typename U, int N, typename... Providers2>
    friend class IndexProvider;
    
    template<typename U, template<typename>class DataSource, typename... Providers2>
    friend class GuardType;
    
private:
    GuardArrayBase();
    
private:
    bool isAlloc;
    
protected:
    // a[2][3][4] dementionCount = 3;
    unsigned short dementionCount;
    size_t *dementions;
    // a[2][3][4]
    // dementions[0] = 1;
    // dementions[1] = 4;
    // dementions[2] = 12;
    // dementions[3] = 24;
    
    GuardArrayBase(const GuardArrayBase& array);
    
public:
    T* const array;
    
public:
    GuardArrayBase(int dementionCount, size_t* dementions) noexcept
    : dementionCount(dementionCount), dementions(dementions),
    array(NULL), isAlloc(false)
    {
    }
    
    ~GuardArrayBase() noexcept
    {
        if(std::is_base_of<ValueObserverProvider<T>, GuardArrayBase>::value) {
            for (auto p = array, end = p + size(); p != end; ++p) {
                ValueObserverProvider<T>::ReadObserver().RemoveMessage(p);
                ValueObserverProvider<T>::WriteObserver().RemoveMessage(p);
            }
        }
        if(isAlloc) {
            delete[] this->array;
        }
    }
    
    size_t size() noexcept
    {
        return dementions[dementionCount];
    }
    
    friend std::istream& operator >> (std::istream& si, GuardArrayBase& gt) noexcept
    {
        T data;
        if (GuardConfig::_ARRAY_IO_TIP_SWITCH == true && si.rdbuf() == std::cin.rdbuf()) {
            std::cout << "Please input ";
            std::cout << "[" << gt.size() << "] Datas: " << std::endl;
        }
        T * arr = gt.array;
        for (int i = 0; i<gt.dementions[gt.dementionCount]; ++i) {
            si >> data;
            arr[i] = data;
        }
        return si;
    }
    
    friend std::ostream& operator << (std::ostream& so, const GuardArrayBase& gt) noexcept
    {
        T* p = gt.array;
        T* end = p + gt.dementions[gt.dementionCount];
        while (p < end)
        {
            for (int i = 0; i<gt.dementions[1]; ++i) {
                so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                << " " << *p++ << " ";
            }
            so << std::endl;
            for (int j = 2; j < gt.dementionCount; ++j) {
                if((p - gt.array) % gt.dementions[j] == 0) {
                    so << std::endl;
                }
            }
        }
        return so;
    }
    
protected:
    inline void setRefArray(const T* array) noexcept
    {
        if(isAlloc) delete [] this->array;
        const_cast<T*&>(this->array) = const_cast<T*>(array);
        isAlloc = false;
    }
    
    inline void setNewArray(size_t n) noexcept
    {
        if(isAlloc) delete [] this->array;
        const_cast<T*&>(this->array) = new T[n]();
        isAlloc = true;
    }
};

}

#endif /* GuardArrayBase_hpp */
