#ifndef ArrayIndexProvider_hpp
#define ArrayIndexProvider_hpp

#include <iomanip>

template<typename T, int Demention>
class GuardTypeArray;

//--------------------------------------------------------------------------
//                            class ArrayIndexProvider

template<typename T, int Demention>
class ArrayIndexProvider<T, Demention, 1> {
public:
    using Ptr = ArrayIndexProvider<T, Demention, 1>;
    
    template<typename U>
    using Provider = ArrayIndexProvider<U, Demention, 1>;
    
    typedef std::random_access_iterator_tag     iterator_category;
    typedef GuardType<T, Provider>              value_type;
    typedef size_t                              difference_type;
    typedef Ptr                                 pointer;
    typedef value_type                          reference;
    
private:
    
    T* pos;
    GuardTypeArray<T, Demention> * array;
    
public:
    
    ArrayIndexProvider(const ArrayIndexProvider& idx)
    :pos(idx.pos), array(idx.array){
    }
    
    ArrayIndexProvider(const GuardTypeArray<T, 1>& arr, size_t n)
    : array(&const_cast<GuardTypeArray<T, Demention>& >(arr)), pos(arr.array + n) {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(1, n));
    }
    
    ArrayIndexProvider(const GuardTypeArray<T, 2>& arr, size_t n)
    : array(&const_cast<GuardTypeArray<T, Demention>& >(arr)), pos(arr.array)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(2, n));
        this->pos += n * arr.dementions[2-1];
    }
    
    ArrayIndexProvider(const ArrayIndexProvider<T, Demention, 2>& frontIndex, size_t n)
    : array(frontIndex.array), pos(frontIndex.pos)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(2, n));
        this->pos += n * array->dementions[2-1];
    }
    
    T& Data() const {
        return *pos;
    }
    
    const std::string Id() const {
        std::string id = array->id;
        char str_idx[32];
        size_t shift = this->pos - array->array;
        for (int i = Demention-1; i >= 0; i--) {
            sprintf(str_idx, "[%ld]", shift/array->dementions[i]);
            shift %= this->array->dementions[i];
            id += str_idx;
        }
        return id;
    }
    
    void OutOfIndexDetect(int N, size_t n) {
        if(n < array->dementions[N]/array->dementions[N-1]) return;
        std::string usedIndex = array->id;
        size_t shift = pos - array->array;
        size_t index = 0;
        char str_idx[32];
        for (int i = Demention-1; i >= 0; i--) {
            index = (i == 1 ? n : shift/array->dementions[i]);
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
    ArrayIndexProvider(const Ptr& ptr, size_t n)
    : array(ptr.array), pos(ptr.pos){
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(1, (pos - array->array) % array->dementions[1] + n));
        pos += n;
    }
    
    value_type operator [] (size_t m) {
        return value_type(*this, m);
    }
    
    const value_type operator [] (size_t m) const {
        return value_type(*this, m);
    }
    
    const Ptr& operator = (const Ptr& ptr) {
        this->pos = ptr.pos;
        this->array = ptr.array;
        return *this;
    }
    
    value_type operator * () {
        return value_type(*this, 0);
    }
    
    const value_type operator * () const {
        return value_type(*this, 0);
    }
    
    operator const T* () const {
        return this->pos;
    }
    
    bool operator < (const Ptr& ptr) const {
        return this->pos < ptr.pos;
    }
    
    bool operator <= (const Ptr& ptr) const {
        return this->pos <= ptr.pos;
    }
    
    bool operator > (const Ptr& ptr) const {
        return this->pos > ptr.pos;
    }
    
    bool operator >= (const Ptr& ptr) const {
        return this->pos >= ptr.pos;
    }
    
    bool operator == (const Ptr& ptr) const {
        return this->pos == ptr.pos;
    }
    
    bool operator != (const Ptr& ptr) const {
        return this->pos != ptr.pos;
    }
    
    bool operator == (const T* p) const {
        return this->pos == p;
    }
    
    bool operator != (const T* p) const {
        return this->pos != p;
    }
    
    Ptr operator + (size_t i) const {
        return Ptr(*this, i);
    }
    
    Ptr operator - (size_t i) const {
        return Ptr(*this, -1*i);
    }
    
    Ptr&operator += (size_t i) {
        Ptr(*this, i);
        this->pos += i;
        return *this;
    }
    
    Ptr&operator -= (size_t i) {
        Ptr(*this, -1*i);
        this->pos -= i;
        return *this;
    }
    
    Ptr&operator ++ () {
        Ptr(*this, 1);
        this->pos += 1;
        return *this;
    }
    
    Ptr operator ++ (int) {
        Ptr ret(*this, 1);
        this->pos += 1;
        return ret;
    }
    
    Ptr& operator -- () {
        Ptr(*this, -1);
        this->pos -= 1;
        return *this;
    }
    
    Ptr operator -- (int) {
        Ptr ret(*this, -1);
        this->pos -= 1;
        return ret;
    }
    
    size_t operator - (const Ptr& ptr) const {
        return this->pos-ptr.pos;
    }

};

#endif /* ArrayIndexProvider_hpp */
