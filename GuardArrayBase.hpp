#ifndef GuardArrayBase_hpp
#define GuardArrayBase_hpp

#include <iostream>
#include <iomanip>
#include "GuardType.hpp"
#include "IndexProvider.hpp"

//-----------------------------------------------------------------------------
//                            class GuardArrayBase

template<typename T>
class GuardArrayBase {
public:
    template<typename U, int N>
    friend class IndexProvider;
    
private:
    GuardArrayBase();
    
private:
    T*   array;
    bool isAlloc;
    
protected:
    int dementionCount;         // a[1][2][3][4][5] dementionCount = 5;
    size_t *dementions;         // a[1][2][3][4][5] dementions[0] = 1; dementions[1] = 5; dementions[2] = 20; dementions[3] = 60;
    
public:
    TRACE_STRING_SAVE____(std::string id);
    
public:
    GuardArrayBase(int dementionCount, size_t * dementions)
    : dementionCount(dementionCount), dementions(dementions), array(NULL)
    {
    }
    
    GuardArrayBase(const GuardArrayBase& array)
    : dementionCount(array.dementionCount), dementions(array.dementions), array(NULL)
    {
        this->setNewArray(this->dementions[this->dementionCount]);
    }
    
    ~GuardArrayBase() {
        if(isAlloc) {
            delete[] this->array;
        }
    }
    
    friend std::istream& operator >> (std::istream &   si,
                                      GuardArrayBase& gt) {
        T data;
        if (GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
            if (typeid(si) == typeid(std::cin)) {
                std::cout << "Please input ";
                std::cout << "[" << gt.size() << "] Datas "
                << gt.id << ": " << std::endl;
            }
        }
        T * arr = gt.array;
        for (int i = 0; i<gt.dementions[gt.dementionCount]; i++) {
            si >> data;
            arr[i] = data;
        }
        return si;
    }
    
    friend std::ostream& operator << (std::ostream &        so,
                                      const GuardArrayBase& gt) {
        T* p = gt.array;
        T* end = p + gt.dementions[gt.dementionCount];
        while (p < end)
        {
            for (int i = 0; i<gt.dementions[1]; i++) {
                so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                << " " << *p++ << " ";
            }
            so << std::endl;
        }
        so << std::endl;
        return so;
    }
protected:
    void setRefArray(const T* array) {
        this->array = const_cast<T*>(array);
        isAlloc = false;
    }
    
    void setNewArray(size_t n) {
        if(this->array != NULL)
            delete [] this->array;
        this->array = new T[n]();
        isAlloc = true;
    }
};

#endif /* GuardArrayBase_hpp */
