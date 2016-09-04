#ifndef GuardArrayBase_hpp
#define GuardArrayBase_hpp

#include <iostream>
#include <iomanip>

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
    bool isAlloc;
    MULTITHREAD_GUARD____(bool isMutexesAlloc);
protected:
    // a[2][3][4] dementionCount = 3;
    unsigned short dementionCount;
    T* const array;
    size_t *dementions;
    // a[2][3][4]
    // dementions[0] = 1;
    // dementions[1] = 4;
    // dementions[2] = 12;
    // dementions[3] = 24;
    IndexProvider<T> index;
    MULTITHREAD_GUARD____(std::recursive_mutex* mWritable);
    
    GuardArrayBase(const GuardArrayBase& array);
    
public:
    TRACE_STRING_SAVE____(std::string id);
    
public:
    GuardArrayBase(int dementionCount, size_t * dementions)
    : dementionCount(dementionCount), dementions(dementions),
    array(NULL), isAlloc(false)
    {
        index.array = this;
        MULTITHREAD_GUARD____(isMutexesAlloc = false);
    }
    
    ~GuardArrayBase() {
        if(isAlloc) {
            delete[] this->array;
        }
        MULTITHREAD_GUARD____(if(isMutexesAlloc) { delete[] this->mWritable; })
    }
    
    void lock_guard(size_t n) const {
        const_cast<GuardArrayBase*>(this)->mWritable[n].lock();
    }
    
    void unlock_guard(size_t n) const {
        const_cast<GuardArrayBase*>(this)->mWritable[n].unlock();
    }
    
    friend std::istream& operator >> (std::istream &   si,
                                      GuardArrayBase& gt) {
        T data;
        if (GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
            std::cout << "Please input ";
            std::cout << "[" << gt.size() << "] Datas "
            << gt.id << ": " << std::endl;
        }
        T * arr = gt.array;
        for (int i = 0; i<gt.dementions[gt.dementionCount]; ++i) {
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
    void setRefArray(const T* array) {
        if(isAlloc) delete [] this->array;
        const_cast<T*&>(this->array) = const_cast<T*>(array);
        isAlloc = false;
    }
    
    void setNewArray(size_t n) {
        if(isAlloc) delete [] this->array;
        const_cast<T*&>(this->array) = new T[n]();
        isAlloc = true;
    }
    
    void setRefMutexes(const std::recursive_mutex* mutexes) {
        MULTITHREAD_GUARD____(if(isMutexesAlloc) delete [] this->mWritable);
        MULTITHREAD_GUARD____(const_cast<std::recursive_mutex*&>(this->mWritable) = const_cast<std::recursive_mutex*>(mutexes));
        MULTITHREAD_GUARD____(isMutexesAlloc = false);
    }
    
    void setNewMutexes(size_t n) {
        MULTITHREAD_GUARD____(if(isMutexesAlloc) delete [] this->mWritable);
        MULTITHREAD_GUARD____(const_cast<std::recursive_mutex*&>(this->mWritable) = new std::recursive_mutex[n]());
        MULTITHREAD_GUARD____(isMutexesAlloc = true);
    }
};

#endif /* GuardArrayBase_hpp */
