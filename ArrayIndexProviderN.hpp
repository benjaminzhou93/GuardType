#ifndef ArrayIndexProviderN_hpp
#define ArrayIndexProviderN_hpp

#include <iomanip>

template<typename T, int Demention>
class GuardTypeArray;

//--------------------------------------------------------------------------
//                            class ArrayIndexProvider

template<typename T, int Demention, int N>
class ArrayIndexProvider {
    using Ptr = ArrayIndexProvider<T, Demention, N-1>;
    
    friend Ptr;
    
private:
    T* pos;
    GuardTypeArray<T, Demention> * array;
    
public:
    
    ArrayIndexProvider(const ArrayIndexProvider& idx)
    :pos(idx.pos), array(idx.array){
    }
    
    ArrayIndexProvider(const GuardTypeArray<T, Demention>& arr, size_t n)
    : array(&const_cast<GuardTypeArray<T, Demention>& >(arr)), pos(arr.array)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        pos += n * arr.dementions[Demention-1];
    }
    
    ArrayIndexProvider(const ArrayIndexProvider<T, Demention, N+1>& frontIndex, size_t n)
    : array(frontIndex.array), pos(frontIndex.pos)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
        pos += n * array->dementions[N];
    }
    
    T& Data() const {
        return *pos;
    }
    
    const std::string Id() const {
        std::string id = array->id;
        char str_idx[32];
        size_t shift = pos - array->array;
        for (int i = Demention-1; i >= 0; i--) {
            sprintf(str_idx, "[%ld]", shift/array->dementions[i]);
            shift %= array->dementions[i];
            id += str_idx;
        }
        return id;
    }
    
    void OutOfIndexDetect(size_t n) {
        if(n < array->dementions[N+1]/array->dementions[N]) return;
        std::string usedIndex = array->id;
        size_t shift = pos - array->array;
        size_t index = 0;
        char str_idx[32];
        for (int i = Demention-1; i >= 0; i--) {
            index = (i == N ? n : shift/array->dementions[i]);
            shift %= array->dementions[i];
            sprintf(str_idx, "[%ld]", index);
            usedIndex += str_idx;
        }
        std::string maxIndex = array->id;
        for (int i = Demention; i > 0; i--) {
            sprintf(str_idx, "[%ld]", array->dementions[i]/array->dementions[i-1]);
            maxIndex += str_idx;
        }
        std::cout << "Out of index Array: " << maxIndex << ", Used: " << usedIndex << std::endl;
        int OutOfIndex = 0;
        assert(OutOfIndex);
    }
    
    void OutPutArray() const {
        T* p = array->array;
        T* end = p + array->dementions[Demention];
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
            for(int j = 2; j < Demention; j++) {
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
    
    const ArrayIndexProvider& operator = (const ArrayIndexProvider& ptr) {
        this->pos = ptr.pos;
        this->array = ptr.array;
        return *this;
    }
};

#endif /* ArrayIndexProviderN_hpp */
