#ifndef IndexProviderO_hpp
#define IndexProviderO_hpp

#include <iomanip>
#include <cassert>
#include "IDExpressManager.hpp"
#include "GuardType.hpp"

template<typename T>
class GuardArrayBase;

template<typename T, int Demention, typename... Providers>
class GuardArray;

//--------------------------------------------------------------------------
//                            class IndexProvider

template<typename T, typename... Providers>
class IndexProvider<T, 1, Providers...> {
public:
    using Ptr = IndexProvider<T, 1, Providers...>;
    using Ptr2 = IndexProvider<T, 2, Providers...>;
    
    template<typename U>
    using Provider = IndexProvider<U, 1, Providers...>;
    
    friend IndexProvider<T, 1+1, Providers...>;
    
    template<typename U, template<typename>class DataSource, typename... Providers2>
    friend class GuardType;
    
    template<typename U>
    friend class GuardArrayBase;
    
    template<typename U, int Demention, typename... Providers2>
    friend class GuardArray;
    
    typedef std::random_access_iterator_tag     iterator_category;
    typedef T                                   value_type;
    typedef size_t                              difference_type;
    typedef Ptr                                 pointer;
    typedef T&                                  reference;
    typedef GuardType<T, Provider>              ValueType;
    
private:
    IndexProvider(GuardArrayBase<T> * array) : array(array), pos(array->array) {}
    
public:
    T* const pos;
    GuardArrayBase<T> * const array;
    
public:
    IndexProvider(const GuardArrayBase<T>* array)
    : array(const_cast<GuardArrayBase<T>*>(array))
    {
    }
    
    IndexProvider(const IndexProvider<T, 1, Providers...>& idx)
    : pos(idx.pos), array(idx.array){
    }
    
    IndexProvider(const IndexProvider<T, 2, Providers...>& frontIndex, int n)
    : array(frontIndex.array), pos(frontIndex.pos)
    {
        OUT_OF_INDEX_DETECT__(frontIndex.OutOfIndexDetect(n));
        const_cast<T*&>(this->pos) += n * array->dementions[2 - 1];
    }
    
    IndexProvider(const GuardArray<T, 1, Providers...>& arr, int n)
    : array(&const_cast<GuardArray<T, 1, Providers...>&>(arr)), pos(arr.array + n)
    {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(n));
    }
    
    IndexProvider(const GuardArray<T, 2, Providers...>& arr, int n)
    : array(&const_cast<GuardArray<T, 2, Providers...>&>(arr)), pos(arr.array)
    {
        OUT_OF_INDEX_DETECT__(reinterpret_cast<Ptr2*>(this)->OutOfIndexDetect(n));
        const_cast<T*&>(this->pos) += n * arr.dementions[2-1];
    }
    
    T& Data() {
        return *pos;
    }
    
    const T& Data() const {
        return *pos;
    }
    
    const std::string Id() const {
        std::string id;
        TRACE_STRING_SAVE____(id = array->id);
        long shift = this->pos - array->array;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            id += "[" + std::to_string(shift / array->dementions[i]) + "]";
            shift %= this->array->dementions[i];
        }
        return id;
    }
    
    void OutOfIndexDetect(long n) const {
        if(0 <= n && n < array->dementions[1]) return;
        std::string usedIndex("array");
        TRACE_STRING_SAVE____(usedIndex = array->id);
        long shift = pos - array->array;
        long index = 0;
        for (int i = array->dementionCount-1; i >= 0; i--) {
            index = (i == 0 ? n : shift/array->dementions[i]);
            usedIndex += "["+std::to_string(index)+"]";
            shift %= array->dementions[i];
        }
        std::string maxIndex("array");
        TRACE_STRING_SAVE____(maxIndex = array->id);
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
                    IDExpressManager::so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << "[" << *(p) << "]";
                } else {
                    IDExpressManager::so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << " " << *(p) << " ";
                }
            }
            IDExpressManager::so << std::endl;
            for (int j = 2; j < array->dementionCount; ++j) {
                if((p - array->array) % array->dementions[j] == 0) {
                    IDExpressManager::so << std::endl;
                }
            }
        }
    }
    
    const std::string CalcString() const {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        if(GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
            return this->Id();
        } else {
            return IDExpressManager::NumericToString(this->Data());
        }
    }
    
    void setExpress(const std::string& express) const {
    }
    
    
    //--------------------------------------------------------------------------
    //                            Pointer
    IndexProvider(const Ptr& ptr, int n)
    : array(ptr.array), pos(ptr.pos){
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect((pos - array->array) % array->dementions[1] + n));
        const_cast<T*&>(this->pos) += n;
    }
    
    const Ptr& operator = (const Ptr& ptr) {
        const_cast<T*&>(this->pos) = ptr.pos;
        this->array = ptr.array;
        return *this;
    }
    
#if ENSURE_MULTITHREAD_SAFETY || SAVE_EXPRES_SLOWER_SPEED
    ValueType operator [] (int m) {
        return ValueType(*this, m);
    }
    
    const ValueType operator [] (int m) const {
        return ValueType(*this, m);
    }
    
    ValueType operator * () {
        return ValueType(*this, 0);
    }
    
    const ValueType operator * () const {
        return ValueType(*this, 0);
    }
#else
    T& operator [] (int m) {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        return *(pos+m);
    }
    
    const T& operator [] (int m) const {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(m));
        return *(pos+m);
    }
    
    T& operator * () {
        return *(pos);
    }
    
    const T& operator * () const {
        return *(pos);
    }
#endif
    
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
    
    Ptr operator + (int i) const {
        return Ptr(*this, i);
    }
    
    Ptr operator - (int i) const {
        return Ptr(*this, -1*i);
    }
    
    Ptr&operator += (int i) {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(i+(pos-array->array)%array->dementions[1]));
        const_cast<T*&>(this->pos) += i;
        return *this;
    }
    
    Ptr&operator -= (int i) {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(-i+(pos-array->array)%array->dementions[1]));
        const_cast<T*&>(this->pos) -= i;
        return *this;
    }
    
    Ptr&operator ++ () {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(1+(pos-array->array)%array->dementions[1]));
        const_cast<T*&>(this->pos) += 1;
        return *this;
    }
    
    Ptr operator ++ (int) {
        Ptr ret(*this, 1);
        const_cast<T*&>(this->pos) += 1;
        return ret;
    }
    
    Ptr& operator -- () {
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(-1+(pos-array->array)%array->dementions[1]));
        const_cast<T*&>(this->pos) -= 1;
        return *this;
    }
    
    Ptr operator -- (int) {
        Ptr ret(*this ,-1);
        const_cast<T*&>(this->pos) -= 1;
        return ret;
    }
    
    size_t operator - (const Ptr& ptr) const {
        return const_cast<T*&>(this->pos)-ptr.pos;
    }
};

#endif /* IndexProviderO_hpp */
