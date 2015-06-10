#ifndef GUARDTYPE_H
#define GUARDTYPE_H
#include "GuardConfig.h"
#include "LargerType.h"


template<typename T, typename TBase>
struct TIsDerived{
    static int t(TBase*) {
        return 1;
    }
    static char t(void *) {
        return 0;
    }
    enum { result = sizeof(int) == sizeof(t((T*)NULL))};
};

template<typename T>
class type_traits {
    public :
    typedef T value_type;
};

template<typename T>
class GuardType;

template<typename T>
class type_traits<GuardType<T> > {
    public :
    typedef T value_type;
};

#define ASSERT(yes, outPut)\
    if(! (yes) ) GuardConfig::so << outPut << std::endl;\
    assert(yes);


#define DECLARE_CALC_FUNCTION(ReturnRef, op, FunctionType) \
    template<typename U>\
    const GuardType<typename LargerType<T, U>::value_type> ReturnRef \
    operator op (const U&            data) FunctionType;\
\
    template<typename U>\
    const GuardType<typename LargerType<T, U>::value_type> ReturnRef \
    operator op (const GuardType<U>& g2) FunctionType;


#define DECLARE_BOOL_FUNCTION(op) \
    template<typename U>\
    const GuardType<bool>\
    operator op (const U&            data) const;\
\
    template<typename U>\
    const GuardType<bool>\
    operator op (const GuardType<U>& g2) const;


#define FRIEND_CALC_TYPE_FUNCTION(op, Const, Type) \
friend const GuardType<typename LargerType<T, Type>::value_type> \
    operator op (Const Type & data, const GuardType<T>& g2) {\
    Type reserveData = data;\
    typename LargerType<T, Type>::value_type result(data op *(g2.pData));\
    if(GuardConfig::rule[#op] == true) {\
        GuardType<T>::OutPutTrace(reserveData, #op, g2, result);\
    }\
    std::string opStr = #op;\
    if(IsAssignOp(opStr)) opStr.pop_back();\
    return GuardType<typename LargerType<T, Type>::value_type>\
        (result, GuardType<T>::PackWithBracket(data, opStr, g2), false);\
}

#define FRIEND_CALC_FUNCTION(op, Const)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, T)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, bool)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, unsigned char)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, char)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, short)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, unsigned short)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, unsigned int)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, int)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, unsigned long)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, long)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, float)\
FRIEND_CALC_TYPE_FUNCTION(op, Const, double)



#define FRIEND_BOOL_FUNCTION(op) \
    friend const GuardType<bool> operator op (const T& data, const GuardType<T>& g2) {\
        bool result(data op *(g2.pData));\
        if(GuardConfig::rule[#op] == true) {\
            GuardType<T>::OutPutTrace(data, #op, g2, result);\
        }\
        return GuardType<bool>\
            (result, GuardType<bool>::PackWithBracket(data, #op, g2), false);\
    }
    
    

#define DECLARE_CALC_FUNCTION_MACRO\
    \
    DECLARE_CALC_FUNCTION(, +, const)\
    DECLARE_CALC_FUNCTION(, -, const)\
    DECLARE_CALC_FUNCTION(, *, const)\
    DECLARE_CALC_FUNCTION(, /, const)\
    DECLARE_CALC_FUNCTION(, %, const)\
    DECLARE_CALC_FUNCTION(, ^, const)\
    DECLARE_CALC_FUNCTION(, &, const)\
    DECLARE_CALC_FUNCTION(, |, const)\
    DECLARE_CALC_FUNCTION(, <<, const)\
    DECLARE_CALC_FUNCTION(, >>, const)\
\
    DECLARE_CALC_FUNCTION(&, +=, )\
    DECLARE_CALC_FUNCTION(&, -=, )\
    DECLARE_CALC_FUNCTION(&, *=, )\
    DECLARE_CALC_FUNCTION(&, /=, )\
    DECLARE_CALC_FUNCTION(&, %=, )\
    DECLARE_CALC_FUNCTION(&, ^=, )\
    DECLARE_CALC_FUNCTION(&, &=, )\
    DECLARE_CALC_FUNCTION(&, |=, )\
    DECLARE_CALC_FUNCTION(&, <<=,)\
    DECLARE_CALC_FUNCTION(&, >>=,)\
\
    DECLARE_BOOL_FUNCTION(&&)\
    DECLARE_BOOL_FUNCTION(||)\
    DECLARE_BOOL_FUNCTION(<)\
    DECLARE_BOOL_FUNCTION(>)\
    DECLARE_BOOL_FUNCTION(<=)\
    DECLARE_BOOL_FUNCTION(>=)\
    DECLARE_BOOL_FUNCTION(==)\
    DECLARE_BOOL_FUNCTION(!=)

#define FRIEND_CALC_FUNCTION_MACRO\
    \
    FRIEND_CALC_FUNCTION(+,const);\
    FRIEND_CALC_FUNCTION(-,const);\
    FRIEND_CALC_FUNCTION(*,const);\
    FRIEND_CALC_FUNCTION(/,const);\
    FRIEND_CALC_FUNCTION(%,const);\
    FRIEND_CALC_FUNCTION(^,const);\
    FRIEND_CALC_FUNCTION(&,const);\
    FRIEND_CALC_FUNCTION(|,const);\
    FRIEND_CALC_FUNCTION(<<,const);\
    FRIEND_CALC_FUNCTION(>>,const);\
\
    FRIEND_CALC_FUNCTION(+=,);\
    FRIEND_CALC_FUNCTION(-=,);\
    FRIEND_CALC_FUNCTION(*=,);\
    FRIEND_CALC_FUNCTION(/=,);\
    FRIEND_CALC_FUNCTION(%=,);\
    FRIEND_CALC_FUNCTION(^=,);\
    FRIEND_CALC_FUNCTION(&=,);\
    FRIEND_CALC_FUNCTION(|=,);\
    FRIEND_CALC_FUNCTION(<<=,);\
    FRIEND_CALC_FUNCTION(>>=,);\
\
    FRIEND_BOOL_FUNCTION(&&);\
    FRIEND_BOOL_FUNCTION(||);\
    FRIEND_BOOL_FUNCTION(<);\
    FRIEND_BOOL_FUNCTION(>);\
    FRIEND_BOOL_FUNCTION(<=);\
    FRIEND_BOOL_FUNCTION(>=);\
    FRIEND_BOOL_FUNCTION(==);\
    FRIEND_BOOL_FUNCTION(!=);

template<typename T>
class GuardTypeArray;
//--------------------------------------------------------------------------
//                            class GuardType

template<typename T>
class GuardType : public GuardConfig{
protected :
    // class ArrayIndex
    class ArrayIndex {
        public :
        ArrayIndex(): d3(0), d2(0), d1(0) {}
        ArrayIndex(size_t d3, size_t d2, size_t d1): d3(d3), d2(d2), d1(d1) {}
        size_t d3, d2, d1;
    };
    
    class canBeDestroy {
        public :
        canBeDestroy(bool countRefOrNot = false);
        canBeDestroy(const canBeDestroy & ref);
        void startCount();
        virtual ~canBeDestroy();
        operator bool () const;
        private :
        unsigned long * n;
    };
    
    // class Ptr
    class Ptr {
        template<typename U>
        friend class GuardTypeArray;
        public :
        typedef std::random_access_iterator_tag     iterator_category;
        typedef GuardType<T>                        value_type;
        typedef size_t                              difference_type;
        typedef Ptr                                 pointer;
        typedef GuardType<T>&                       reference;
        public :
        Ptr();
        virtual ~ Ptr();
        template<int N>
        Ptr(const T (&pArr)[N]);
        Ptr(const ArrayIndex& index, const T* pData, const GuardType<T>* gt);
        virtual void            SetArrayId(const std::string id);
        GuardType<T>&           operator [] (size_t m);
        const GuardType<T>&     operator [] (size_t m) const;
        GuardType<T>&           operator * ();
        const GuardType<T>&     operator * () const;
        operator const T* () const;
        const Ptr&              operator = (const Ptr& ptr);
        bool operator == (const Ptr& ptr) const;
        bool operator != (const Ptr& ptr) const;
        bool operator == (const T* ptr) const;
        bool operator != (const T* ptr) const;
        bool operator < (const Ptr& ptr) const;
        bool operator <= (const Ptr& ptr) const;
        bool operator > (const Ptr& ptr) const;
        bool operator >= (const Ptr& ptr) const;
        Ptr operator + (size_t i) const;
        Ptr operator - (size_t i) const;
        Ptr& operator += (size_t i);
        Ptr& operator -= (size_t i);
        Ptr& operator ++ ();
        Ptr operator ++ (int);
        Ptr& operator -- ();
        Ptr operator -- (int);
        size_t operator - (const Ptr& ptr) const;
        protected :
        ArrayIndex                      index;
        T*                              pos;
        GuardType<T>*                   gt;
        canBeDestroy                    isGtAlloc;
    };


    // class GuardType
    template<typename U>
    friend class GuardType;
    template<typename U>
    friend class GuardTypeArray;
    template<typename U>
    friend class GuardTypeArray2D;
public :
    typedef T value_type;
    DECLARE_CALC_FUNCTION_MACRO
    FRIEND_CALC_FUNCTION_MACRO
    GuardType(const char* id);
    GuardType(const std::string& id="GT");
    template<typename U>
    GuardType(const U&     data);
    GuardType(const GuardType<T>&      data);
    template<typename U>
    GuardType(const GuardType<U>&      gt);
    template<typename U>
    GuardType(const U&     data, const std::string& calc, bool outPutTrace = true);
    template<typename U>
    GuardType(const ArrayIndex& index, U* pData, const GuardType<U>* gt);
    virtual             ~GuardType();
    void                SetId(const std::string& id);
    operator const T& () const;
    const GuardType<T>& operator = (const GuardType<T>& data);
    template<typename U>
    const GuardType<T>& operator = (const GuardType<U>& data);
    template<typename U>
    const GuardType<T>& operator = (const U& data);
    Ptr                 operator & ();
    const Ptr           operator & () const;
    const GuardType<T>  operator ! () const;
    const GuardType<T>  operator ~ () const;
    const GuardType<T>&  operator ++ ();
    const GuardType<T>  operator ++ (int);
    const GuardType<T>&  operator -- ();
    const GuardType<T>  operator -- (int);
    const std::string   CalcString() const;
    const std::string   IdIndex() const;
    // a[D3][D2][D1];
    virtual size_t      D1()    const { return 0; }
    virtual size_t      D2()    const { return 0; }
    virtual size_t      D3()    const { return 0; }
    virtual T*          Arr()   const { return NULL; }

    friend std::istream& operator >> (
            std::istream        &si,
            GuardType&          gt) {
        return ReadGuardTypeFromIO(si, gt);
    }
    friend std::ostream& operator << (
            std::ostream &      so,
            const GuardType&    gt) {
        return WriteGuardTypeToIO(so, gt);
    }
    virtual void PrintArray() const {}
    template<typename U>
    static const std::string    ToString(const U& data);
    template<typename U>
    static const std::string    ToString(const GuardType<U>& data);
private :
    static std::istream& ReadGuardTypeFromIO(
            std::istream&       si,
            GuardType&          gt);
    static std::ostream& WriteGuardTypeToIO(
            std::ostream&       so,
            const GuardType<T>& gt);
protected :
    template<typename U, typename V, typename W>
    static void                 OutPutTrace(const U& data1,
                                            std::string op,
                                            const V& data2,
                                            const W& result);
    template<typename U, typename V>
    static const std::string    PackWithBracket(const U& data1,
                                            std::string op,
                                            const V& data2);
    void                        OutPutExpresAndArray() const;
    static int                  MinCalcPriorityOf(const std::string calcExpression);
    static int                  PriorityOfSymbol(const std::string symbol);
    static const std::string    NextCalculateOp(
                std::string::iterator& begin,
                std::string::iterator end);
    static const std::string    GetNewId(std::string id = "GT");
    static const std::string    GetNewIdByIncreaseId(std::string id);
    const std::string           MaxIndex() const;
    static bool                 IsAssignOp(const std::string operatorName);
    void                        GuardArrayOutOfIndex(const std::string op) const;
    template<typename U>
    void TraceReadGuardType(
            const std::string&      op,
            const GuardType<U>&     data) const;
    template<typename U>
    void TraceWriteGuardType(
            const std::string&      frontOp,
            const GuardType<U>&     data,
            const std::string&      backOp) const;
    template<typename U>
    void TraceOperateGTWithGT(
            const std::string&      opStr,
            const GuardType<U>&     data,
            const T&       value)   const;
    
protected:
    std::string     id;             // id 为空代表计算时所产生的临时变量
    std::string     calc;           // 得到当前值的计算过程
    ArrayIndex      index;          // 当GT为数组GuardTypeArray使用下标[N]返回的元素时，使用d3,d2,d1记录多维数组下标
    T*              pData;          // 对GT的操作或者对GuardTypeArray中元素的操作通过pData获取实际操作元素地址
    GuardType<T> *  gt;             // 当数组GuardTypeArray使用下标[N]返回GT时,用gt关联GT和GuardTypeArray
    std::map<size_t, GuardType<T>* > arrReturnValue;
private :
    T               data;
};




#include "GuardType.cpp"
#endif // GUARDTYPE_H
