#ifndef IndexProviderO_hpp
#define IndexProviderO_hpp

#include <iomanip>
#include "GuardType.hpp"

template<typename T>
class GuardArrayBase;

template<typename T, int Demention>
class GuardArray;

//--------------------------------------------------------------------------
//                            class IndexProvider

template<typename T>
class IndexProvider<T, 1> {
public:
    using Ptr = IndexProvider<T, 1>;
    
    template<typename U>
    using Provider = IndexProvider<U, 1>;
    
    typedef std::random_access_iterator_tag     iterator_category;
    typedef GuardType<T, Provider>              value_type;
    typedef size_t                              difference_type;
    typedef Ptr                                 pointer;
    typedef value_type                          reference;
    
private:

    T* pos;
    GuardArrayBase<T> * array;
    
public:
    
    IndexProvider(const IndexProvider<T, 1>& idx)
    : pos(idx.pos), array(idx.array){
    }
    
    IndexProvider(const IndexProvider<T, 2>& frontIndex, size_t n)
    : array(frontIndex.array), pos(frontIndex.pos)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(2, n));
        this->pos += n * array->dementions[2 - 1];
    }
    
    IndexProvider(const GuardArray<T, 1>& arr, size_t n)
    : array(&const_cast<GuardArray<T, 1>&>(arr)), pos(arr.array + n)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(1, n));
    }
    
    IndexProvider(const GuardArray<T, 2>& arr, size_t n)
    : array(&const_cast<GuardArray<T, 2>&>(arr)), pos(arr.array)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(2, n));
        this->pos += n * arr.dementions[2-1];
    }
    
    void lock_guard() const {
        MULTITHREAD_GUARD____(this->array->lock_guard(pos - array->array));
    }
    
    void unlock_guard() const {
        MULTITHREAD_GUARD____(this->array->unlock_guard(pos - array->array));
    }
    
    T& Data() {
        return *pos;
    }
    
    const T& Data() const {
        return *pos;
    }
    
    void ValueBeReadedDo() const {
    }
    
    void ValueChangedDo(const T& oldValue) {
    }
    
    const std::string Id() const {
        std::string id = array->id;
        size_t shift = this->pos - array->array;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            id += "[" + std::to_string(shift / array->dementions[i]) + "]";
            shift %= this->array->dementions[i];
        }
        return id;
    }
    
    void OutOfIndexDetect(int N, size_t n) {
        if(n < array->dementions[N]/array->dementions[N-1]) return;
        std::string usedIndex = array->id;
        size_t shift = pos - array->array;
        size_t index = 0;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            index = (i == 1 ? n : shift/array->dementions[i]);
            usedIndex += "["+std::to_string(index)+"]";
            shift %= array->dementions[i];
        }
        std::string maxIndex = array->id;
        for (int i = array->dementionCount; i > 0; i--) {
            maxIndex += "["+std::to_string(array->dementions[i] / array->dementions[i-1])+"]";
        }
        std::cout << "Out of index Array: " << maxIndex << ", Used: " << usedIndex << std::endl;
        int OutOfIndex = 0;
        assert(OutOfIndex);
    }
    
    void OutputArray() const {
        if(GuardConfig::_ARRAY_OUT_PUT_SWITCH == false) return;
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
            for (int j = 2; j < array->dementionCount; ++j) {
                if((p - array->array) % array->dementions[j] == 0) {
                    GuardConfig::so << std::endl;
                }
            }
        }
    }
    
    const std::string CalcString() const {
        if(GuardConfig::GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        if(GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
            return this->Id();
        } else {
            return GT::NumericToString(this->Data());
        }
    }
    
    void setExpress(const std::string& express) const {
    }
    
    
    //--------------------------------------------------------------------------
    //                            Pointer
    IndexProvider(const Ptr& ptr, size_t n)
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

#endif /* IndexProviderO_hpp */
