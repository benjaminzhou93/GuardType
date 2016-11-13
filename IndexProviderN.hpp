#ifndef IndexProviderN_hpp
#define IndexProviderN_hpp

#include <iomanip>
#include "IndexProviderO.hpp"

template<typename T, int Demention>
class GuardTypeArray;

//--------------------------------------------------------------------------
//                            class IndexProvider

template<typename T, int N, typename... Providers>
class IndexProvider {
    using Ptr_1 = IndexProvider<T, N-1, Providers...>;
    using Ptr2 = IndexProvider<T,N+1, Providers...>;
    friend IndexProvider<T, N-1, Providers...>;
    friend IndexProvider<T, N+1, Providers...>;
    
private:
    T* pos;
    GuardArrayBase<T> * array;
    
public:
    
    IndexProvider(const IndexProvider& idx)
    :pos(idx.pos), array(idx.array){
    }
    
    IndexProvider(const IndexProvider<T, N+1, Providers...>& frontIndex, int n)
    : array(frontIndex.array), pos(frontIndex.pos)
    {
        OUT_OF_INDEX_DETECT__(reinterpret_cast<Ptr2*>(this)->OutOfIndexDetect(n));
        pos += n * array->dementions[N];
    }
    
    IndexProvider(const GuardArrayBase<T>& arr, int n)
    : array(&const_cast<GuardArrayBase<T>&>(arr)), pos(arr.array)
    {
        OUT_OF_INDEX_DETECT__(reinterpret_cast<Ptr2*>(this)->OutOfIndexDetect(n));
        pos += n * array->dementions[array->dementionCount - 1];
    }
    
    T& Data() const {
        return *pos;
    }
    
    const std::string Id() const {
        std::string id;
        TRACE_STRING_SAVE____(id = array->id);
        size_t shift = pos - array->array;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            id += "[" + std::to_string(shift / array->dementions[i]) + "]";
            shift %= array->dementions[i];
        }
        return id;
    }
    
    void OutOfIndexDetect(long n) const {
        if(0 <= n && n < array->dementions[N]/array->dementions[N-1]) return;
        std::string usedIndex("array");
        TRACE_STRING_SAVE____(usedIndex = array->id);
        long shift = pos - array->array;
        long index = 0;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            index = (i == N-1 ? n : shift / array->dementions[i]);
            usedIndex += "[" + std::to_string(index) + "]";
            shift %= array->dementions[i];
        }
        std::string maxIndex("array");
        TRACE_STRING_SAVE____(maxIndex = array->id);
        for (int i = array->dementionCount; i > 0; i--) {
            maxIndex += "[" + std::to_string(array->dementions[i] / array->dementions[i - 1]) + "]";
        }
        std::cout << "Out of index Array: " << maxIndex << ", Used: " << usedIndex << std::endl;
        int OutOfIndex = 0;
        assert(OutOfIndex);
    }
    
    void OutputArray() const {
        T* p = array->array;
        T* end = p + array->dementions[array->dementionCount];
        size_t lineCount = array->dementions[1];
        
        while(p < end) {
            for(int j = 0; j < lineCount; ++j, ++p) {
                if(p == this->pos) {
                    IDExpressManager::so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << "[" << *(p) << "]";
                } else {
                    IDExpressManager::so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << " " << *(p) << " ";
                }
            }
            IDExpressManager::so << std::endl;
            for(int j = 2; j < array->dementionCount; ++j) {
                if((p - array->array) % array->dementions[j] == 0) {
                    IDExpressManager::so << std::endl;
                }
            }
        }
    }
    
    //--------------------------------------------------------------------------
    //                            Pointer
    
    const IndexProvider& operator = (const IndexProvider& ptr) {
        this->pos = ptr.pos;
        this->array = ptr.array;
        return *this;
    }
    
#if ENSURE_MULTITHREAD_SAFETY || SAVE_EXPRES_SLOWER_SPEED
    Ptr_1 operator [] (int m) {
        return Ptr_1(*this, m);
    }
    
    const Ptr_1 operator [] (int m) const {
        return Ptr_1(*this, m);
    }
    
    Ptr_1 operator * () {
        return Ptr_1(*this, 0);
    }
    
    const Ptr_1 operator * () const {
        return Ptr_1(*this, 0);
    }
#else
    Ptr_1& operator [] (int m) {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        const_cast<T*&>(this->array->index.pos) = this->pos + m * array->dementions[N-1];
        return reinterpret_cast<Ptr_1&>(this->array->index);
    }
    
    const Ptr_1& operator [] (int m) const {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        const_cast<T*&>(this->array->index.pos) = this->pos + m * array->dementions[N-1];
        return reinterpret_cast<Ptr_1&>(this->array->index);
    }
    
    Ptr_1& operator * () {
        return reinterpret_cast<Ptr_1&>(*this);
    }
    
    const Ptr_1& operator * () const {
        return reinterpret_cast<Ptr_1&>(*this);
    }
#endif
};

#endif /* IndexProviderN_hpp */
