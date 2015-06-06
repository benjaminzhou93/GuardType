#ifndef GUARDTYPEARRAY_H
#define GUARDTYPEARRAY_H
#include <iomanip>
#include "GuardType.h"


//-----------------------------------------------------------------------------
//                            class GuardTypeArray

template<typename T>
class GuardTypeArray : protected GuardType<T> {
private :
    // class Array_ptr
    class Array_ptr {
    public :
        Array_ptr(const T* pArr);
        T*      get() const;
        ~Array_ptr();
    private :
        T* pArr;
    };

    public :
    using typename GuardType<T>::ArrayIndex;
    using typename GuardType<T>::Ptr;
    // class Ptr2
    class Ptr2 {
        template<typename U>
        friend class GuardTypeArray2D;
        public :
        Ptr2();
        Ptr2(const ArrayIndex&          index,
             T*                         pData,
             const GuardType<T>* gt);
        typename GuardTypeArray<T>::Ptr         operator [] (size_t m);
        const typename GuardTypeArray<T>::Ptr   operator [] (size_t m) const;
        typename GuardTypeArray<T>::Ptr         operator * ();
        const typename GuardTypeArray<T>::Ptr   operator * () const;
        const Ptr2& operator = (const Ptr2& ptr2);
        bool operator == (const Ptr2& ptr2) const;
        bool operator != (const Ptr2& ptr2) const;
        bool operator < (const Ptr2& ptr2) const;
        bool operator <= (const Ptr2& ptr2) const;
        bool operator > (const Ptr2& ptr2) const;
        bool operator >= (const Ptr2& ptr2) const;
        Ptr2 operator + (size_t i) const;
        Ptr2 operator - (size_t i) const;
        Ptr2& operator += (size_t i);
        Ptr2& operator -= (size_t i);
        Ptr2& operator ++ ();
        Ptr2 operator ++ (int);
        Ptr2& operator -- ();
        Ptr2 operator -- (int);
        size_t operator - (const Ptr2& ptr2) const;
        protected :
        ArrayIndex                      index;
        T*                              pos;
        GuardType<T>*                   gt;
    };
    
// class GuardTypeArray
public :
    typedef Ptr             iterator;
    typedef GuardType<T>    value_type;

public :
    template<size_t N>
    GuardTypeArray(const T (&pArr)[N], const std::string& id = "GT");
    GuardTypeArray(const GuardTypeArray<T>& gt);
    GuardTypeArray(size_t n, const std::string& id = "GT");
    operator const Ptr ();
    GuardType<T>&           operator [] (size_t n);
    const GuardType<T>&     operator [] (size_t n) const;
    bool operator == (const GuardTypeArray<T>& gt) const;
    bool operator != (const GuardTypeArray<T>& gt) const;
    bool operator == (const Ptr& ptr) const;
    bool operator < (const Ptr& ptr) const;
    bool operator <= (const Ptr& ptr) const;
    bool operator > (const Ptr& ptr) const;
    bool operator >= (const Ptr& ptr) const;
    bool operator != (const Ptr& ptr) const;
    template<typename U>
    Ptr  operator + (U n);
    size_t size() const;
    size_t Length() const;
    virtual size_t D1()     const { return length; }
    virtual size_t D2()     const { return 0; }
    virtual size_t D3()     const { return 0; }
    virtual T* Arr()        const { return arr.get(); }
    Ptr begin() const {
        return Ptr(ArrayIndex(0, 0, 0),
                   Arr(),
                   (GuardTypeArray<T>*)this);
    }
    Ptr end() const {
        return Ptr(ArrayIndex(0, 0, length),
                   Arr()+(D3()?D3():1) * (D2()?D2():1) * D1(),
                   (GuardTypeArray<T>*)this);
    }
    friend std::istream& operator >> (
            std::istream &          si,
            GuardTypeArray<T>&      gt) {
        return ReadArrayFromIO(si, gt);
    }
    friend std::ostream& operator << (
            std::ostream &          so,
            const GuardTypeArray<T>& gt) {
        return WriteArrayToIO(so, gt);
    }
    virtual void PrintArray() const { GuardConfig::so << *this; }
private :
    static std::istream& ReadArrayFromIO(
            std::istream&           si,
            GuardTypeArray&         gt);
    static std::ostream& WriteArrayToIO(
            std::ostream&           so,
            const GuardTypeArray&   gt);

private :
    size_t      length;
protected :
    Array_ptr   arr;
};

#include "GuardTypeArray.cpp"
#endif // GUARDTYPEARRAY_H
