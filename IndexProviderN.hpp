#ifndef IndexProviderN_hpp
#define IndexProviderN_hpp

#include <iomanip>
#include "IndexProviderO.hpp"

template<typename T, int Demention>
class GuardTypeArray;

//--------------------------------------------------------------------------
//                            class IndexProvider

template<typename T, int N>
class IndexProvider {
    using Ptr = IndexProvider<T, N-1>;
    friend Ptr;
    
private:
    T* pos;
    GuardArrayBase<T> * array;
    
public:
    
    IndexProvider(const IndexProvider& idx)
    :pos(idx.pos), array(idx.array){
    }
    
    IndexProvider(const IndexProvider<T, N+1>& frontIndex, size_t n)
    : array(frontIndex.array), pos(frontIndex.pos)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        pos += n * array->dementions[N];
    }
    
    IndexProvider(const GuardArrayBase<T>& arr, size_t n)
    : array(&const_cast<GuardArrayBase<T>&>(arr)), pos(arr.array)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        pos += n * array->dementions[array->dementionCount - 1];
    }
    
    T& Data() const {
        return *pos;
    }
    
    const std::string Id() const {
        std::string id = array->id;
        size_t shift = pos - array->array;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            id += "[" + std::to_string(shift / array->dementions[i]) + "]";
            shift %= array->dementions[i];
        }
        return id;
    }
    
    void OutOfIndexDetect(size_t n) {
        if(n < array->dementions[N+1]/array->dementions[N]) return;
        std::string usedIndex = array->id;
        size_t shift = pos - array->array;
        size_t index = 0;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            index = (i == N ? n : shift / array->dementions[i]);
            usedIndex += "[" + std::to_string(index) + "]";
            shift %= array->dementions[i];
        }
        std::string maxIndex = array->id;
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
                    GuardConfig::so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << "[" << *(p) << "]";
                } else {
                    GuardConfig::so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << " " << *(p) << " ";
                }
            }
            GuardConfig::so << std::endl;
            for(int j = 2; j < array->dementionCount; ++j) {
                if((p - array->array) % array->dementions[j] == 0) {
                    GuardConfig::so << std::endl;
                }
            }
        }
    }
    
    //--------------------------------------------------------------------------
    //                            Pointer
    
    Ptr operator [] (size_t m) {
        return Ptr(*this, m);
    }
    
    const Ptr operator [] (size_t m) const {
        return Ptr(*this, m);
    }
    
    Ptr operator * () {
        return Ptr(*this, 0);
    }
    
    const Ptr operator * () const {
        return Ptr(*this, 0);
    }
    
    const IndexProvider& operator = (const IndexProvider& ptr) {
        this->pos = ptr.pos;
        this->array = ptr.array;
        return *this;
    }
};

#endif /* IndexProviderN_hpp */
