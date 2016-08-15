#ifndef GuardTypeArrayN_hpp
#define GuardTypeArrayN_hpp

#include <iostream>
#include <iomanip>
#include "ArrayIndexProviderN.hpp"
#include "GuardTypeArray.hpp"

//---------------------------------------------------------------------------
//                            class GuardTypeArray

template<typename T, int Demention>
class GuardTypeArray {
public:
    template<typename U, int D, int N>
    friend class ArrayIndexProvider;
    
    template<int D>
    friend struct GT::InitWithCArray;
    
    using Ptr = ArrayIndexProvider<T, Demention, Demention-1>;
    
private:
    GuardTypeArray();
    
private:
    size_t dementions[Demention+1];
    
protected:
    T*   array;
    bool isAlloc;
    
public:
    TRACE_STRING_SAVE____(std::string id);
    
public:
    ~GuardTypeArray() {
        if(this->isAlloc) {
            delete[] this->array;
        }
    }
    
    GuardTypeArray(const GuardTypeArray<T, Demention>& gt)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewIdByIncreaseId(gt.id)))
    isAlloc(true)
    {
        for (int i=0; i<Demention; i++) {
            this->dementions[i] = gt.dementions[i];
        }
        size_t elementCount = this->dementions[1];
        this->array = new T[elementCount];
        
        T* begin = this->array;
        T* end = begin + elementCount;
        T* source = gt.array;
        for (; begin != end; begin++, source++) {
            *begin = *source;
        }
    }
    
    //template<int N, typename U>
    //GuardTypeArray(const U (&pArr)[N], const std::string& id)
    //: TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId(id)))
    //array(new T[N]()), isAlloc(true)
    //{
    //    GT::InitWithCArray<Demention>::Init(*this, pArr);
    //}
    
    template<int N, typename U>
    GuardTypeArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId(id)))
    isAlloc(false)
    {
        GT::InitWithCArray<Demention>::Init(*this, pArr);
    }
    
    template<int N, typename U>
    GuardTypeArray(bool isReferenceFromArray, const U (&pArr)[N])
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId()))
    isAlloc(isReferenceFromArray) {
        GT::InitWithCArray<Demention>::Init(*this, pArr);
    }
    
    template<typename ...Int>
    GuardTypeArray(size_t first, Int...n)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId()))
    isAlloc(true)
    {
        this->InitWithIndexs<Demention>(first, n...);
    }
    
    template<int N, typename ...V>
    void InitWithIndexs(size_t index, V ...n) {
        this->dementions[N] = index;
        this->InitWithIndexs<N-1>(n...);
    }
    
    template<int N, typename ...V>
    void InitWithIndexs(const std::string& id) {
        static_assert(N == 0, "Array init with wrong index count");
        TRACE_STRING_SAVE____(this->id = id);
        this->AllocWithDementions();
    }
    
    template<int N, typename ...V>
    void InitWithIndexs(size_t index) {
        static_assert(N == 1, "Array init with wrong index count");
        this->dementions[1] = index;
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
        this->AllocWithDementions();
    }
    
    void AllocWithDementions() {
        this->dementions[0] = 1;
        for(int i = 0; i < Demention; i++) {
            this->dementions[i+1] *= this->dementions[i];
        }
        
        if(this->isAlloc == false) return;
        size_t allElement = this->dementions[Demention];
        this->array = new T[allElement]();
    }
    
    void InitDementions() {
        this->dementions[0] = 1;
        for(int i = 0; i < Demention; i++) {
            this->dementions[i+1] *= this->dementions[i];
        }
        
        if(this->isAlloc == false) return;
        size_t allElement = this->dementions[Demention];
        this->array = new T[allElement];
        
        T* begin = array;
        T* end = begin + allElement;
        T* source = array;
        for(; begin!=end; begin++, source++) {
            *begin = *source;
        }
    }
    
    size_t size() const {
        return this->dementions[Demention];
    }
    
    Ptr operator [] (size_t n) {
        return Ptr(*this, n);
    }
    
    const Ptr operator [] (size_t n) const {
        return Ptr(*this, n);
    }
    
    
    friend std::istream& operator >> (std::istream &   si,
                                      GuardTypeArray& gt) {
        T data;
        if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
            if(typeid(si) == typeid(std::cin)) {
                std::cout<< "Please input ";
                std::cout<< "["<< gt.size() << "] Datas "
                << gt.id << ": " << std::endl;
            }
        }
        T * arr = gt.array;
        for (int i=0; i<gt.size(); i++) {
            si >> data;
            arr[i] = data;
        }
        return si;
    }
    
    friend std::ostream& operator << (std::ostream &        so,
                                      const GuardTypeArray& gt) {
        {
            T* p = gt.array;
            for (int i=0; i<gt.size(); i++) {
                so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                << " " << *(p+i) << " ";
            }
            so << std::endl << std::endl;
            return so;
        }
    }
};

#endif /* GuardTypeArrayN_hpp */
