#ifndef GT
#define GT

#include <iostream>


//----------------------------GuardConfig--------------------------------------------
//                         The members of GuardConfig


#include <queue>
#include <map>
#include <string>
#include <iostream>

#define _SPACES "\t\t\t\t"              // 数据读写的提示位置

#define VALUE_CHANGE_DO(someting) someting                          // 数据被修改时执行用户指定方法
#define VALUE_BE_READ_DO(someting) someting                         // 数据被读取时执行用户指定方法
#define VALUE_OLD_SAVING(oldValue) oldValue
#define VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE(someting) someting   // 数据被修改时通过函数参数返回原有值，和改变后的值

// 作为基类只有一个实例对象作为配置
class GuardConfig
{
    GuardConfig();
    template<typename T>
    friend class GuardType;
public:
    struct AddNewId;
    friend struct AddNewId;
public:
    // 预先为要定义的变量赋予名字
    static struct AddNewId PushNewId(std::string newId);
    
    // 开启所有跟踪
    static void TurnAllGuardOff();
    // 关闭所有跟踪
    static void TurnAllGuardOn();
    
    // 读取单元素跟踪开关   GT: 99 （读取 GT 内容为 99）
    static void TurnReadSwitch(bool yes);
    // 算数运算跟踪开关     +, -, *, /, %, ^, &,|, ~, <<, >>
    static void TurnMathSwitch(bool yes);
    // 逻辑运算跟踪开关     !, &&, ||
    static void TurnLogicSwitch(bool yes);
    // 比较运算跟踪开关     <, >, <=, >=, !=, ==
    static void TurnCompareSwitch(bool yes);
    // 赋值运算跟踪开关     =, ++, --, +=, -=, *=, /=, %=, ^=, <<=, >>=
    static void TurnAssignSwitch(bool yes);
    static void TurnOutPutCalcTraceSwitch(bool yes);
    static void TurnOutPutCalcExpressSwitch(bool yes);
    
    static void TurnIOTipSwitch(bool yes);         // 从键盘读取数据时提示开关
    static void TurnArrayOutPutSwitch(bool yes);   // 输出整行数组跟踪开关
    static void TurnCalcExpressIdOrNum(bool yes);  // 输出计算表达式yes为Id,no为num
    static void SetArrayOutPutInterval(int n);     // 调整数组元素之间的输出间隔
    
    static bool _TRACE_READ_SWITCH;                // 读取单元素跟踪开关
    static bool _OUT_PUT_TRACE_SWITCH;             // 输出计算过程跟踪开关
    static bool _OUT_PUT_EXPRES_SWITCH;            // 输出计算表达式跟踪开关
    static bool _OUT_PUT_EXPRES_ID_OR_NUM_SWITCH;  // 设置Expres表达方式为输出纯id还是纯num
    static bool _ARRAY_IO_TIP_SWITCH;              // 从键盘读取数据时提示开关
    static bool _ARRAY_OUT_PUT_SWITCH;             // 输出数组跟踪开关
    static int  _ARRAY_OUT_PUT_INTERVAL;           // 输出的数组元素之间的间隔
    const static bool defaultGuard;                // 默认跟踪全部开启
    public :
    static std::ostream& so;                       // 默认跟踪输出到 std::cout
    static std::queue<std::string> idArray;
    static std::map<std::string, bool> rule;
    
    struct AddNewId {
        public :
        struct AddNewId operator () (std::string name) {
            GuardConfig::idArray.push(name);
            return AddNewId();
        }
    };
};



GuardConfig::AddNewId AddId(std::string id) {
    GuardConfig::idArray.push(id);
    return GuardConfig::AddNewId();
}

enum OnOrOff {OFF = 0, ON = 1};

void TurnTrace(OnOrOff s) {
    GuardConfig::TurnOutPutCalcTraceSwitch(s);
}

void TurnExpres(OnOrOff s) {
    GuardConfig::TurnOutPutCalcExpressSwitch(s);
}

#define GTRule GuardType<int>::rule


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

template<typename... T>
int printf(const char * s, const T&... arg1) {
    return std::printf(s, static_cast<typename type_traits<T>::value_type>(arg1)...);
}

//----------------------------GuardConfig--------------------------------------------
//                         The members of GuardConfig


std::ostream& GuardConfig::so = std::cout;      // 默认将跟踪信息输出到 std::cout

const bool GuardConfig::defaultGuard        = true;
bool GuardConfig::_TRACE_READ_SWITCH        = false;
bool GuardConfig::_OUT_PUT_TRACE_SWITCH     = false;
bool GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH = false;
bool GuardConfig::_OUT_PUT_EXPRES_SWITCH    = GuardConfig::defaultGuard;
bool GuardConfig::_ARRAY_IO_TIP_SWITCH      = GuardConfig::defaultGuard;
bool GuardConfig::_ARRAY_OUT_PUT_SWITCH     = GuardConfig::defaultGuard;
int GuardConfig::_ARRAY_OUT_PUT_INTERVAL    = 2;
std::queue<std::string> GuardConfig::idArray;
std::map<std::string, bool> GuardConfig::rule;

GuardConfig::GuardConfig()
{
    rule.insert(std::pair<std::string, bool>("+", defaultGuard));
    rule.insert(std::pair<std::string, bool>("-", defaultGuard));
    rule.insert(std::pair<std::string, bool>("*", defaultGuard));
    rule.insert(std::pair<std::string, bool>("/", defaultGuard));
    rule.insert(std::pair<std::string, bool>("%", defaultGuard));
    rule.insert(std::pair<std::string, bool>("^", defaultGuard));
    rule.insert(std::pair<std::string, bool>("&", defaultGuard));
    rule.insert(std::pair<std::string, bool>("|", defaultGuard));
    rule.insert(std::pair<std::string, bool>("~", defaultGuard));
    rule.insert(std::pair<std::string, bool>("<<", defaultGuard));
    rule.insert(std::pair<std::string, bool>(">>", defaultGuard));
    rule.insert(std::pair<std::string, bool>("!", defaultGuard));
    rule.insert(std::pair<std::string, bool>("&&", defaultGuard));
    rule.insert(std::pair<std::string, bool>("||", defaultGuard));
    rule.insert(std::pair<std::string, bool>("<", defaultGuard));
    rule.insert(std::pair<std::string, bool>(">", defaultGuard));
    rule.insert(std::pair<std::string, bool>("<=", defaultGuard));
    rule.insert(std::pair<std::string, bool>(">=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("==", defaultGuard));
    rule.insert(std::pair<std::string, bool>("!=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("+=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("-=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("*=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("/=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("%=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("^=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("<<=", defaultGuard));
    rule.insert(std::pair<std::string, bool>(">>=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("++", defaultGuard));
    rule.insert(std::pair<std::string, bool>("--", defaultGuard));
    rule.insert(std::pair<std::string, bool>("=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("", true));
}

struct GuardConfig::AddNewId GuardConfig::PushNewId(std::string newId) {
    idArray.push(newId);
    return GuardConfig::AddNewId();
}

void GuardConfig::TurnAllGuardOff() {
    TurnReadSwitch(false);
    TurnMathSwitch(false);
    TurnLogicSwitch(false);
    TurnCompareSwitch(false);
    TurnAssignSwitch(false);
    TurnIOTipSwitch(false);
    TurnArrayOutPutSwitch(false);
    TurnOutPutCalcTraceSwitch(false);
    TurnOutPutCalcExpressSwitch(false);
}

void GuardConfig::TurnAllGuardOn() {
    TurnReadSwitch(true);
    TurnMathSwitch(true);
    TurnLogicSwitch(true);
    TurnCompareSwitch(true);
    TurnAssignSwitch(true);
    TurnIOTipSwitch(true);
    TurnArrayOutPutSwitch(true);
    TurnOutPutCalcTraceSwitch(true);
    TurnOutPutCalcExpressSwitch(true);
}

void GuardConfig::TurnMathSwitch(bool yes) {
    rule["+"] = yes;
    rule["-"] = yes;
    rule["*"] = yes;
    rule["/"] = yes;
    rule["%"] = yes;
    rule["^"] = yes;
    rule["&"] = yes;
    rule["|"] = yes;
    rule["~"] = yes;
    rule["<<"] = yes;
    rule[">>"] = yes;
}

void GuardConfig::TurnLogicSwitch(bool yes) {
    rule["!"] = yes;
    rule["&&"] = yes;
    rule["||"] = yes;
}

void GuardConfig::TurnCompareSwitch(bool yes) {
    rule["<"] = yes;
    rule[">"] = yes;
    rule["<="] = yes;
    rule[">="] = yes;
    rule["=="] = yes;
    rule["!="] = yes;
}

void GuardConfig::TurnAssignSwitch(bool yes) {
    rule["="] = yes;
    rule["++"] = yes;
    rule["--"] = yes;
    rule["+="] = yes;
    rule["-="] = yes;
    rule["*="] = yes;
    rule["/="] = yes;
    rule["%="] = yes;
    rule["/="] = yes;
    rule["^="] = yes;
    rule["<<="] = yes;
    rule[">>="] = yes;
}

void GuardConfig::TurnReadSwitch(bool yes) {
    rule[""] = yes;
    _TRACE_READ_SWITCH = yes;
}

void GuardConfig::TurnIOTipSwitch(bool yes) {
    _ARRAY_IO_TIP_SWITCH = yes;
}

void GuardConfig::TurnArrayOutPutSwitch(bool yes) {
    _ARRAY_OUT_PUT_SWITCH = yes;
}

void GuardConfig::TurnOutPutCalcTraceSwitch(bool yes) {
    _OUT_PUT_TRACE_SWITCH = yes;
}

void GuardConfig::TurnOutPutCalcExpressSwitch(bool yes) {
    _OUT_PUT_EXPRES_SWITCH = yes;
}

void GuardConfig::TurnCalcExpressIdOrNum(bool yes) {
    _OUT_PUT_EXPRES_ID_OR_NUM_SWITCH = yes;
}

void GuardConfig::SetArrayOutPutInterval(int n) {
    _ARRAY_OUT_PUT_INTERVAL = n;
}




//----------------------------NumToString--------------------------------------------
//                         The members of NumToString

struct NumToString {
    static const std::string    Transform(const std::string& data) { return data; }
    static const std::string    Transform(const char& data);
    static const std::string    Transform(const unsigned char& data);
    static const std::string    Transform(const short& data);
    static const std::string    Transform(const unsigned short& data);
    static const std::string    Transform(const int& data);
    static const std::string    Transform(const unsigned int& data);
    static const std::string    Transform(const long& data);
    static const std::string    Transform(const unsigned long& data);
    static const std::string    Transform(const float& data);
    static const std::string    Transform(const double& data);
    static const std::string    Transform(const long double& data);
};

//----------------------------NumToString--------------------------------------------
//                         The members of NumToString

const std::string NumToString::Transform(const char& data) {
    std::string result;
    result += data;
    return result;
}

const std::string NumToString::Transform(const unsigned char& data) {
    std::string result;
    result += data;
    return result;
}

const std::string NumToString::Transform(const short& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%hd", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const unsigned short& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%hu", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const int& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%d", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const unsigned int& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%u", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const long& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%ld", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const unsigned long& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%lu", data);
    result += str_num;
    return result;
}

const std::string NumToString::Transform(const float& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%f", data);
    result += str_num;
    while(!result.empty() && result.back() == '0')
        result.pop_back();
    if(result.back() == '.')
        result.push_back('0');
    return result;
}

const std::string NumToString::Transform(const double& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%lf", data);
    result += str_num;
    while(!result.empty() && result.back() == '0')
        result.pop_back();
    if(result.back() == '.')
        result.push_back('0');
    return result;
}

const std::string NumToString::Transform(const long double& data) {
    std::string result;
    char str_num[32];
    sprintf(str_num, "%LF", data);
    result += str_num;
    while(!result.empty() && result.back() == '0')
        result.pop_back();
    if(result.back() == '.')
        result.push_back('0');
    return result;
}







//----------------------------LargerType--------------------------------------------


template<typename T>
struct TypePriority {
    enum { N = 9999 };
};

template<typename T, typename U>
struct PriorityIsLarger {
    enum { result = TypePriority<T>::N > TypePriority<U>::N};
};

template <int IsLarger, typename T, typename U>
struct GetLargerType {
};

template <typename T, typename U>
struct GetLargerType<1, T, U> {
    typedef T value_type;
};

template <typename T, typename U>
struct GetLargerType<0, T, U> {
    typedef U value_type;
};

template <typename T, typename U>
struct LargerType {
    typedef typename GetLargerType<PriorityIsLarger<T, U>::result , T, U>::value_type value_type;
};




template<>
struct TypePriority<bool> {
    enum { N = 0 };
};

template<>
struct TypePriority<unsigned char> {
    enum { N = 1 };
};

template<>
struct TypePriority<char> {
    enum { N = 2 };
};

template<>
struct TypePriority<unsigned short> {
    enum { N = 3 };
};

template<>
struct TypePriority<short> {
    enum { N = 4 };
};

template<>
struct TypePriority<unsigned int> {
    enum { N = 5 };
};

template<>
struct TypePriority<int> {
    enum { N = 6 };
};

template<>
struct TypePriority<unsigned long> {
    enum { N = 7 };
};

template<>
struct TypePriority<long> {
    enum { N = 8 };
};

template<>
struct TypePriority<float> {
    enum { N = 9 };
};

template<>
struct TypePriority<double> {
    enum { N = 10 };
};

template<>
struct TypePriority<long double> {
    enum { N = 11 };
};








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

#define ASSERT(yes, outPut)\
if(! (yes) ) GuardConfig::so << outPut << std::endl;\
assert(yes);



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
public:
    
    void (*ValueChangedDoing)(T * data);
    void (*ValueBeReadedDoing)(const T * data);
    void (*ValueChangedDoingWithOldAndNewValue)(const T oldValue, T * newValue);
    
protected:
    std::string     id;             // id 为空代表计算时所产生的临时变量
    std::string     calc;           // 得到当前值的计算过程
    ArrayIndex      index;          // 当GT为数组GuardTypeArray使用下标[N]返回的元素时，使用d3,d2,d1记录多维数组下标
    T*              pData;          // 对GT的操作或者对GuardTypeArray中元素的操作通过pData获取实际操作元素地址
    GuardType<T> *  gt;             // 当数组GuardTypeArray使用下标[N]返回GT时,用gt关联GT和GuardTypeArray
    std::map<size_t, GuardType<T>* > arrReturnValue;
    private :
    T               data;
    
    
    
    
public:
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator + (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator + (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator - (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator - (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator * (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator * (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator / (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator / (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator % (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator % (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator ^ (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator ^ (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator & (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator & (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator | (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator | (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator << (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator << (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator >> (const U&            data) const;
    template<typename U> const GuardType<typename LargerType<T, U>::value_type>
    operator >> (const GuardType<U>& g2) const;
    
    
    
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator += (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator += (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator -= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator -= (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator *= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator *= (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator /= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator /= (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator %= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator %= (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator ^= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator ^= (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator &= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator &= (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator |= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator |= (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator <<= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator <<= (const GuardType<U>& g2);
    
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator >>= (const U&            data);
    template<typename U> const GuardType<typename LargerType<T, U>::value_type> &
    operator >>= (const GuardType<U>& g2);
    
    
    
    
    template<typename U> const GuardType<bool> operator && (const U&            data) const;
    template<typename U> const GuardType<bool> operator && (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<bool> operator || (const U&            data) const;
    template<typename U> const GuardType<bool> operator || (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<bool> operator < (const U&            data) const;
    template<typename U> const GuardType<bool> operator < (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<bool> operator > (const U&            data) const;
    template<typename U> const GuardType<bool> operator > (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<bool> operator <= (const U&            data) const;
    template<typename U> const GuardType<bool> operator <= (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<bool> operator >= (const U&            data) const;
    template<typename U> const GuardType<bool> operator >= (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<bool> operator == (const U&            data) const;
    template<typename U> const GuardType<bool> operator == (const GuardType<U>& g2) const;
    
    template<typename U> const GuardType<bool> operator != (const U&            data) const;
    template<typename U> const GuardType<bool> operator != (const GuardType<U>& g2) const;
    
    
    
    
    friend const GuardType<T>
    operator + (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data + *(g2.pData));
        if(GuardConfig::rule["+"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "+", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "+", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator + (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data + *(g2.pData));
        if(GuardConfig::rule["+"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "+", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "+", g2), false);
    }
    
    friend const GuardType<T>
    operator - (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data - *(g2.pData));
        if(GuardConfig::rule["-"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "-", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "-", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator - (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data - *(g2.pData));
        if(GuardConfig::rule["-"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "-", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "-", g2), false);
    }
    
    friend const GuardType<T>
    operator * (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data * *(g2.pData));
        if(GuardConfig::rule["*"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "*", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "*", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator * (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data * *(g2.pData));
        if(GuardConfig::rule["*"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "*", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "*", g2), false);
    }
    
    friend const GuardType<T>
    operator / (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data / *(g2.pData));
        if(GuardConfig::rule["/"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "/", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "/", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator / (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data / *(g2.pData));
        if(GuardConfig::rule["/"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "/", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "/", g2), false);
    }
    
    friend const GuardType<T>
    operator % (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data % *(g2.pData));
        if(GuardConfig::rule["%"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "%", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "%", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator % (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data % *(g2.pData));
        if(GuardConfig::rule["%"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "%", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "%", g2), false);
    }
    
    friend const GuardType<T>
    operator ^ (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data ^ *(g2.pData));
        if(GuardConfig::rule["^"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "^", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "^", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator ^ (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data ^ *(g2.pData));
        if(GuardConfig::rule["^"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "^", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "^", g2), false);
    }
    
    friend const GuardType<T>
    operator & (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data & *(g2.pData));
        if(GuardConfig::rule["&"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "&", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "&", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator & (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data & *(g2.pData));
        if(GuardConfig::rule["&"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "&", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "&", g2), false);
    }
    
    friend const GuardType<T>
    operator | (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data | *(g2.pData));
        if(GuardConfig::rule["|"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "|", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "|", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator | (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data | *(g2.pData));
        if(GuardConfig::rule["|"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "|", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "|", g2), false);
    }
    
    friend const GuardType<T>
    operator << (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data << *(g2.pData));
        if(GuardConfig::rule["<<"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "<<", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "<<", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator << (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data << *(g2.pData));
        if(GuardConfig::rule["<<"] == true) {
            GuardType<T>::OutPutTrace(reserveData, "<<", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "<<", g2), false);
    }
    
    friend const GuardType<T>
    operator >> (const T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data >> *(g2.pData));
        if(GuardConfig::rule[">>"] == true) {
            GuardType<T>::OutPutTrace(reserveData, ">>", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, ">>", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator >> (const U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data >> *(g2.pData));
        if(GuardConfig::rule[">>"] == true) {
            GuardType<T>::OutPutTrace(reserveData, ">>", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, ">>", g2), false);
    }
    
    friend const GuardType<T>
    operator += (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data += *(g2.pData));
        if(GuardConfig::rule["+="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "+=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "+", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator += (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data += *(g2.pData));
        if(GuardConfig::rule["+="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "+=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "+", g2), false);
    }
    
    friend const GuardType<T>
    operator -= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data -= *(g2.pData));
        if(GuardConfig::rule["-="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "-=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "-", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator -= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data -= *(g2.pData));
        if(GuardConfig::rule["-="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "-=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "-", g2), false);
    }
    
    friend const GuardType<T>
    operator *= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data *= *(g2.pData));
        if(GuardConfig::rule["*="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "*=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "*", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator *= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data *= *(g2.pData));
        if(GuardConfig::rule["*="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "*=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "*", g2), false);
    }
    
    friend const GuardType<T>
    operator /= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data /= *(g2.pData));
        if(GuardConfig::rule["/="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "/=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "/", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator /= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data /= *(g2.pData));
        if(GuardConfig::rule["/="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "/=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "/", g2), false);
    }
    
    friend const GuardType<T>
    operator %= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data %= *(g2.pData));
        if(GuardConfig::rule["%="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "%=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "%", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator %= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data %= *(g2.pData));
        if(GuardConfig::rule["%="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "%=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "%", g2), false);
    }
    
    friend const GuardType<T>
    operator ^= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data ^= *(g2.pData));
        if(GuardConfig::rule["^="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "^=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "^", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator ^= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data ^= *(g2.pData));
        if(GuardConfig::rule["^="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "^=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "^", g2), false);
    }
    
    friend const GuardType<T>
    operator &= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data &= *(g2.pData));
        if(GuardConfig::rule["&="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "&=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "&", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator &= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data &= *(g2.pData));
        if(GuardConfig::rule["&="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "&=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "&", g2), false);
    }
    
    friend const GuardType<T>
    operator |= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data |= *(g2.pData));
        if(GuardConfig::rule["|="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "|=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "|", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator |= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data |= *(g2.pData));
        if(GuardConfig::rule["|="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "|=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "|", g2), false);
    }
    
    friend const GuardType<T>
    operator <<= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data <<= *(g2.pData));
        if(GuardConfig::rule["<<="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "<<=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, "<<", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator <<= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data <<= *(g2.pData));
        if(GuardConfig::rule["<<="] == true) {
            GuardType<T>::OutPutTrace(reserveData, "<<=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, "<<", g2), false);
    }
    
    friend const GuardType<T>
    operator >>= (T & data, const GuardType<T>& g2) {
        T reserveData = data;
        T result(data >>= *(g2.pData));
        if(GuardConfig::rule[">>="] == true) {
            GuardType<T>::OutPutTrace(reserveData, ">>=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<T>
        (result, GuardType<T>::PackWithBracket(data, ">>", g2), false);
    }
    
    template<typename U, typename V>
    friend const GuardType<typename LargerType<U, V>::value_type>
    operator >>= (U & data, const GuardType<V>& g2) {
        U reserveData = data;
        typename LargerType<U, V>::value_type result(data >>= *(g2.pData));
        if(GuardConfig::rule[">>="] == true) {
            GuardType<T>::OutPutTrace(reserveData, ">>=", g2, result);
        }
        VALUE_BE_READ_DO(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.pData));
        return GuardType<typename LargerType<U, V>::value_type>
        (result, GuardType<T>::PackWithBracket(data, ">>", g2), false);
    }
};



#include <assert.h>
#include <set>


//----------------------------GuardType--------------------------------------------
//                         The members of GuardType::canBeDestroy

template<typename T>
GuardType<T>::canBeDestroy::canBeDestroy(bool countRefOrNot) {
    if(countRefOrNot == true){
        startCount();
    } else {
        this->n = NULL;
    }
}

template<typename T>
GuardType<T>::canBeDestroy::canBeDestroy(const canBeDestroy & ref)
: n(ref.n) {
    if(ref.n != NULL){
        ++*n;
    }
}

template<typename T>
void GuardType<T>::canBeDestroy::startCount() {
    this->n = new unsigned long(1);
}

template<typename T>
GuardType<T>::canBeDestroy::~canBeDestroy() {
    if(this->n != NULL){
        if(--*n == 0)  {
            delete this->n;
        }
    }
}

template<typename T>
GuardType<T>::canBeDestroy::operator bool () const {
    return ( !(n == NULL || *n > 1) );
}


//----------------------------GuardType--------------------------------------------
//                         The members of GuardType::Ptr

template<typename T>
GuardType<T>::Ptr::Ptr()
: index(), pos(), gt(), isGtAlloc()
{}

template<typename T>
GuardType<T>::Ptr::Ptr(const ArrayIndex& index, const T* pData, const GuardType<T>* gt)
: index(index) , pos((T*)pData), gt((GuardType<T>*)gt), isGtAlloc() {
    assert(pData != NULL);
}

template<typename T>
GuardType<T>::Ptr::~ Ptr() {
    if(isGtAlloc == true){
        delete gt;
    }
}

template<typename T>
void GuardType<T>::Ptr::SetArrayId(const std::string id) {
    this->gt->id = id;
}

template<typename T>
GuardType<T>& GuardType<T>::Ptr::operator [] (size_t m) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    size_t idx = this->pos+m - this->gt->Arr();
    this->index.d1 = m;
    GuardType<T> result(index, this->pos + m, this->gt);
    ASSERT(0 <= m && m <= this->gt->D1(),
           "TRACE: out of range "+gt->MaxIndex()+" used: "+ result.IdIndex());
    if(gt->arrReturnValue.insert(std::pair<size_t, GuardType<T>* >(idx, NULL)).second == true)
        gt->arrReturnValue[idx] = new GuardType<T>(index, this->pos + m, this->gt);
    return *(gt->arrReturnValue[idx]);
}

template<typename T>
const GuardType<T>& GuardType<T>::Ptr::operator [] (size_t m) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    size_t idx = this->pos+m - this->gt->Arr();
    const_cast<size_t&>(this->index.d1) = m;
    GuardType<T> result(index, this->pos + m, this->gt);
    ASSERT(0 <= m && m <= this->gt->D1(),
           "TRACE: out of range "+gt->MaxIndex()+" used: "+ result.IdIndex());
    if(gt->arrReturnValue.insert(std::pair<size_t, GuardType<T> >(idx, NULL)).second == true)
        gt->arrReturnValue[idx] = new GuardType<T>(index, this->pos + m, this->gt);
    return gt->arrReturnValue[idx];
}

template<typename T>
const typename GuardType<T>::Ptr&
GuardType<T>::Ptr::operator = (const typename GuardType<T>::Ptr& ptr) {
    this->index = ptr.index;
    this->pos = ptr.pos;
    this->gt = ptr.gt;
    return *this;
}

template<typename T>
GuardType<T>& GuardType<T>::Ptr::operator * () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    size_t idx = this->pos - this->gt->Arr();
    if(gt->arrReturnValue.insert(std::pair<size_t, GuardType<T>* >(idx, NULL)).second == true)
        gt->arrReturnValue[idx] = new  GuardType<T>(this->index, this->pos, this->gt);
    return *(gt->arrReturnValue[idx]);
}

template<typename T>
const GuardType<T>& GuardType<T>::Ptr::operator * () const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    size_t idx = this->pos - this->gt->Arr();
    if(gt->arrReturnValue.insert(std::pair<size_t, GuardType<T>* >(idx, NULL)).second == true)
        gt->arrReturnValue[idx] = new GuardType<T>(this->index, this->pos, this->gt);
    return *(gt->arrReturnValue[idx]);
}

template<typename T>
GuardType<T>::Ptr::operator const T* () const {
    return pos;
}

template<typename T>
bool GuardType<T>::Ptr::operator < (const Ptr& ptr) const {
    return this->pos < ptr.pos;
}

template<typename T>
bool GuardType<T>::Ptr::operator <= (const Ptr& ptr) const {
    return this->pos <= ptr.pos;
}

template<typename T>
bool GuardType<T>::Ptr::operator > (const Ptr& ptr) const {
    return this->pos > ptr.pos;
}

template<typename T>
bool GuardType<T>::Ptr::operator >= (const Ptr& ptr) const {
    return this->pos >= ptr.pos;
}

template<typename T>
bool GuardType<T>::Ptr::operator == (const Ptr& ptr) const {
    return this->pos == ptr.pos;
}

template<typename T>
bool GuardType<T>::Ptr::operator != (const Ptr& ptr) const {
    return this->pos != ptr.pos;
}

template<typename T>
bool GuardType<T>::Ptr::operator == (const T* ptr) const {
    return this->pos == ptr;
}

template<typename T>
bool GuardType<T>::Ptr::operator != (const T* ptr) const {
    return this->pos != ptr;
}

template<typename T>
typename GuardType<T>::Ptr
GuardType<T>::Ptr::operator + (size_t i) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d1+i <= this->gt->D1());
    ArrayIndex index(this->index);
    index.d1 += i;
    Ptr ptr(index, this->pos+i, this->gt);
    return ptr;
}

template<typename T>
typename GuardType<T>::Ptr
GuardType<T>::Ptr::operator - (size_t i) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d1-i >= 0);
    ArrayIndex index(this->index);
    index.d1 -= i;
    Ptr ptr(index, this->pos-i, this->gt);
    return ptr;
}

template<typename T>
typename GuardType<T>::Ptr&
GuardType<T>::Ptr::operator += (size_t i) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d1+i <= this->gt->D1());
    this->index.d1 += i;
    this->pos+=i;
    return *this;
}

template<typename T>
typename GuardType<T>::Ptr&
GuardType<T>::Ptr::operator -= (size_t i) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d1-i >= 0);
    this->index.d1 -= i;
    this->pos+=i;
    return *this;
}

template<typename T>
typename GuardType<T>::Ptr&
GuardType<T>::Ptr::operator ++ () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d1+1 <= this->gt->D1());
    this->index.d1 += 1;
    this->pos += 1;
    return *this;
}

template<typename T>
typename GuardType<T>::Ptr
GuardType<T>::Ptr::operator ++ (int) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d1+1 <= this->gt->D1());
    Ptr ptr(*this);
    this->index.d1 += 1;
    this->pos += 1;
    return ptr;
}

template<typename T>
typename GuardType<T>::Ptr&
GuardType<T>::Ptr::operator -- () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d1-1 >= 0);
    this->index.d1 -= 1;
    this->pos -= 1;
    return *this;
}

template<typename T>
typename GuardType<T>::Ptr
GuardType<T>::Ptr::operator -- (int) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d1-1 >= 0);
    Ptr ptr(*this);
    this->index.d1 -= 1;
    this->pos -= 1;
    return ptr;
}

template<typename T>
size_t GuardType<T>::Ptr::operator - (const Ptr& ptr) const {
    return this->pos-ptr.pos;
}





//---------------------------------GuardType--------------------------------
//                      The members of GuardType


#define IMPLEMENT_CALC_FUNCTION(op) \
template<typename T>\
template<typename U>\
const GuardType<typename LargerType<T, U>::value_type> \
GuardType<T>::operator op (const U& data) const {\
VALUE_BE_READ_DO(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->pData));\
this->GuardArrayOutOfIndex(#op);\
if(TIsDerived<U,GuardConfig>::result) {\
VALUE_BE_READ_DO(if (((GuardType<U>&)data).ValueBeReadedDoing != NULL) \
((GuardType<U>&)data).ValueBeReadedDoing(&((GuardType<U>&)data).data));\
typename LargerType<T, U>::value_type \
result(*(this->pData) op *(((GuardType<T>&)data).pData));\
if(GuardConfig::rule[#op] == false) return result;\
this->TraceOperateGTWithGT(#op, data, result);\
return result;\
}\
this->gt->index = this->index;\
typename LargerType<T, U>::value_type result(*(this->pData) op data);\
if(GuardConfig::rule[#op] == false) return result;\
GuardType<T>::OutPutTrace(*this, #op, data, result);\
return GuardType<typename LargerType<T, U>::value_type>\
(result, GuardType<T>::PackWithBracket(*this, #op, data), false);\
}\
\
template<typename T>\
template<typename U>\
const GuardType<typename LargerType<T, U>::value_type> \
GuardType<T>::operator op (const GuardType<U>& data) const {\
VALUE_BE_READ_DO(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(&data.data));\
VALUE_BE_READ_DO(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->pData));\
typename LargerType<T, U>::value_type result(*(this->pData) op *(data.pData));\
GuardType<T>::OutPutTrace(*this, #op, data, result);\
return GuardType<typename LargerType<T, U>::value_type>\
(result, GuardType<T>::PackWithBracket(*this, #op, data), false);\
}


#define IMPLEMENT_BOOL_FUNCTION(op) \
template<typename T>\
template<typename U>\
const GuardType<bool> \
GuardType<T>::operator op (const U& data) const {\
VALUE_BE_READ_DO(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->pData));\
this->GuardArrayOutOfIndex(#op);\
if(TIsDerived<U,GuardConfig>::result) {\
VALUE_BE_READ_DO(if (((GuardType<U>&)data).ValueBeReadedDoing != NULL) \
((GuardType<U>&)data).ValueBeReadedDoing(&((GuardType<U>&)data).data));\
bool result(*(this->pData) op *(((GuardType<T>&)data).pData));\
if(GuardConfig::rule[#op] == false) return result;\
this->TraceOperateGTWithGT(\
#op, (GuardType<typename type_traits<U>::value_type>&)data, result);\
return result;\
}\
this->gt->index = this->index;\
bool result(*(this->pData) op data);\
if(GuardConfig::rule[#op] == false) return result;\
GuardType<T>::OutPutTrace(*this, #op, data, result);\
return GuardType<bool>\
(result, GuardType<T>::PackWithBracket(*this, #op, data), false);\
}\
\
template<typename T>\
template<typename U>\
const GuardType<bool> \
GuardType<T>::operator op (const GuardType<U>& data) const {\
VALUE_BE_READ_DO(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(&data.data));\
VALUE_BE_READ_DO(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->pData));\
this->GuardArrayOutOfIndex(#op);\
data.GuardArrayOutOfIndex(#op);\
bool result(*(this->pData) op *(data.pData));\
GuardType<T>::OutPutTrace(*this, #op, data, result);\
return GuardType<bool>\
(result, GuardType<T>::PackWithBracket(*this, #op, data), false);\
}



#define IMPLEMENT_ASSIGN_CALC_FUNCTION(op)\
template<typename T>\
template<typename U>\
const GuardType<typename LargerType<T, U>::value_type> & \
GuardType<T>::operator op (const U& data) {\
this->GuardArrayOutOfIndex(#op);\
VALUE_OLD_SAVING(T oldValue = *(this->pData));\
if(TIsDerived<U,GuardConfig>::result) {\
VALUE_BE_READ_DO(if (((GuardType<U>&)data).ValueBeReadedDoing != NULL) \
((GuardType<U>&)data).ValueBeReadedDoing(&((GuardType<U>&)data).data));\
typename LargerType<T, U>::value_type result(*(this->pData) op *(((GuardType<U>&)data).pData));\
if(GuardConfig::rule[#op] == false) {\
VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
(if (this->ValueChangedDoingWithOldAndNewValue != NULL) \
this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));\
VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));\
return *this;\
}\
this->TraceOperateGTWithGT(#op, (GuardType<T>&)data, result);\
VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
(if (this->ValueChangedDoingWithOldAndNewValue != NULL) \
this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));\
VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));\
return *this;\
}\
this->gt->index = this->index;\
std::string thisCalc = this->CalcString();\
if(thisCalc == "") thisCalc = NumToString::Transform(*(this->pData));\
typename LargerType<T, U>::value_type result(*(this->pData) op data);\
if(GuardConfig::rule[#op] == false) {\
VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
(if (this->ValueChangedDoingWithOldAndNewValue != NULL) \
this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));\
VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));\
return *this;\
}\
std::string opStr = #op;\
if(IsAssignOp(opStr)) opStr.pop_back();\
GuardType<T>::OutPutTrace(*this, #op, data, result);\
const_cast<std::string&>(this->calc)\
= GuardType<T>::PackWithBracket(thisCalc, opStr, data);\
this->OutPutExpresAndArray();\
VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
(if (this->ValueChangedDoingWithOldAndNewValue != NULL) \
this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));\
VALUE_CHANGE_DO(if(this->ValueChangedDoing!= NULL)this->ValueChangedDoing(this->pData));\
return *this;\
}\
\
template<typename T>\
template<typename U>\
const GuardType<typename LargerType<T, U>::value_type> & \
GuardType<T>::operator op (const GuardType<U>& data) {\
VALUE_OLD_SAVING(T oldValue = *(this->pData));\
VALUE_BE_READ_DO(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(&data.data));\
this->GuardArrayOutOfIndex(#op);\
data.GuardArrayOutOfIndex(#op);\
this->gt->index = this->index;\
std::string thisCalc = this->CalcString();\
if(thisCalc == "") thisCalc = NumToString::Transform(*(this->pData));\
typename LargerType<T, U>::value_type result(*(this->pData) op *(data.pData));\
std::string opStr = #op;\
if(IsAssignOp(opStr)) opStr.pop_back();\
GuardType<T>::OutPutTrace(*this, opStr, data, result);\
const_cast<std::string&>(this->calc)\
=  GuardType<T>::PackWithBracket(thisCalc, opStr, data);\
this->OutPutExpresAndArray();\
VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
(if (this->ValueChangedDoingWithOldAndNewValue != NULL) \
this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));\
VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));\
return *this;\
}




IMPLEMENT_CALC_FUNCTION(+)
IMPLEMENT_CALC_FUNCTION(-)
IMPLEMENT_CALC_FUNCTION(*)
IMPLEMENT_CALC_FUNCTION(/)
IMPLEMENT_CALC_FUNCTION(%)
IMPLEMENT_CALC_FUNCTION(^)
IMPLEMENT_CALC_FUNCTION(&)
IMPLEMENT_CALC_FUNCTION(|)
IMPLEMENT_CALC_FUNCTION(<<)
IMPLEMENT_CALC_FUNCTION(>>)

IMPLEMENT_BOOL_FUNCTION(&&)
IMPLEMENT_BOOL_FUNCTION(||)
IMPLEMENT_BOOL_FUNCTION(<)
IMPLEMENT_BOOL_FUNCTION(>)
IMPLEMENT_BOOL_FUNCTION(<=)
IMPLEMENT_BOOL_FUNCTION(>=)
IMPLEMENT_BOOL_FUNCTION(==)
IMPLEMENT_BOOL_FUNCTION(!=)

IMPLEMENT_ASSIGN_CALC_FUNCTION(+=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(-=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(*=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(/=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(%=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(^=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(&=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(|=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(<<=)
IMPLEMENT_ASSIGN_CALC_FUNCTION(>>=)



template<typename T>
GuardType<T>::GuardType(const char* id)
: id(GuardType::GetNewId(id)), index(), pData(&data), gt(this), data(),
ValueBeReadedDoing(NULL),
ValueChangedDoing(NULL),
ValueChangedDoingWithOldAndNewValue(NULL)
{ }

template<typename T>
GuardType<T>::GuardType(const std::string& id)
: id(GuardType::GetNewId(id)), index(), pData(&data), gt(this), data(),
ValueBeReadedDoing(NULL),
ValueChangedDoing(NULL),
ValueChangedDoingWithOldAndNewValue(NULL)
{ }

template<typename T>
template<typename U>
GuardType<T>::GuardType(const U& data)
: id(GuardType::GetNewId()), index(), pData(&this->data), gt(this),// data(data),
ValueBeReadedDoing(NULL),
ValueChangedDoing(NULL),
ValueChangedDoingWithOldAndNewValue(NULL)
{
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    this->data = data;
    this->TraceWriteGuardType("", *this, "");
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
}

template<typename T>
GuardType<T>::GuardType(const GuardType<T>&      data)
: id(GuardType::GetNewIdByIncreaseId(data.id)), index(),  pData(&this->data), gt(this),
ValueBeReadedDoing(NULL),
ValueChangedDoing(NULL),
ValueChangedDoingWithOldAndNewValue(NULL)
{
    VALUE_BE_READ_DO(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(&data.data));
    data.GuardArrayOutOfIndex("construct");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    T result(*(this->pData) = *(data.pData));
    this->calc = data.CalcString();
    TraceOperateGTWithGT("=", data, result);
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
}

template<typename T>
template<typename U>
GuardType<T>::GuardType(const GuardType<U>&        data)
: id(GuardType::GetNewIdByIncreaseId(data.id)), index(),  pData(&this->data), gt(this),
ValueBeReadedDoing(NULL),
ValueChangedDoing(NULL),
ValueChangedDoingWithOldAndNewValue(NULL)
{
    VALUE_BE_READ_DO(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(&data.data));
    data.GuardArrayOutOfIndex("construct");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    T result(*(this->pData) = *(data.pData));
    this->calc = data.CalcString();
    TraceOperateGTWithGT("=", data, result);
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
}

template<typename T>
template<typename U>
GuardType<T>::GuardType(const U& data, const std::string& calc, bool outPutTrace)
: id(GuardType::GetNewId()), index(), pData(&this->data), gt(this), calc(calc), data(data),
ValueBeReadedDoing(NULL),
ValueChangedDoing(NULL),
ValueChangedDoingWithOldAndNewValue(NULL)
{
    if(outPutTrace == true)
        this->TraceWriteGuardType("", *this, "");
}

template<typename T>
template<typename U>
GuardType<T>::GuardType(const ArrayIndex& index, U* pData, const GuardType<U>* gt)
: id("GT"), index(index), pData(pData), gt((GuardType<U>*)(gt)),
ValueBeReadedDoing(NULL),
ValueChangedDoing(NULL),
ValueChangedDoingWithOldAndNewValue(NULL)
{
    this->calc = this->IdIndex();
}

template<typename T>
GuardType<T>::~GuardType() {
    for(typename std::map<size_t, GuardType<T>* >::iterator iter
        =arrReturnValue.begin(); iter!=arrReturnValue.end(); iter++) {
        if(iter->second != NULL)
            delete iter->second;
    }
}

template<typename T>
void GuardType<T>::SetId(const std::string& id) {
    this->id = id;
}

template<typename T>
typename GuardType<T>::Ptr GuardType<T>::operator &() {
//    VALUE_BE_READ_DO(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(&data.data));
    return typename GuardType<T>::Ptr(this->index, pData, this->gt);
}

template<typename T>
const typename GuardType<T>::Ptr GuardType<T>::operator &() const {
    return typename GuardType<T>::Ptr(this->index, pData, this->gt);
}

template<typename T>
template<typename U>
const GuardType<T>& GuardType<T>::operator = (const U& data) {
    this->GuardArrayOutOfIndex("=");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    *(this->pData) = data;
    this->gt->index = this->index;
    this->calc = "";
    this->TraceWriteGuardType("", *this, "");
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
    return *this;
}

template<typename T>
const GuardType<T>& GuardType<T>::operator = (const GuardType<T>& data) {
    VALUE_BE_READ_DO(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(&data.data));
    this->GuardArrayOutOfIndex("=");
    data.GuardArrayOutOfIndex("=");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    T result(*(this->pData) = *(data.pData));
    this->calc = data.CalcString();
    this->gt->index = this->index;
    TraceOperateGTWithGT("=", data, result);
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
    return *this;
}

template<typename T>
template<typename U>
const GuardType<T>& GuardType<T>::operator = (const GuardType<U>& data) {
    VALUE_BE_READ_DO(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(&data.data));
    this->GuardArrayOutOfIndex("=");
    data.GuardArrayOutOfIndex("=");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    T result(*(this->pData) = *(data.pData));
    this->calc = data.CalcString();
    this->gt->index = this->index;
    TraceOperateGTWithGT("=", data, result);
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
    return *this;
}

template<typename T>
GuardType<T>::operator const T& () const {
    VALUE_BE_READ_DO(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->pData));
    this->GuardArrayOutOfIndex("read data");
    if(GuardConfig::_TRACE_READ_SWITCH == false)
        return *(this->pData);
    if(this->id != "") this->TraceReadGuardType("", *this);
        return *(this->pData);
}

template<typename T>
const GuardType<T> GuardType<T>::operator ! () const {
    VALUE_BE_READ_DO(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->pData));
    this->GuardArrayOutOfIndex("!");
    this->TraceReadGuardType("!", GuardType<T>(!*(pData), ""));
    
    return GuardType<T>(!*(pData), "!("+this->CalcString()+")");
}

template<typename T>
const GuardType<T> GuardType<T>::operator ~ () const {
    VALUE_BE_READ_DO(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->pData));
    this->GuardArrayOutOfIndex("~");
    this->TraceReadGuardType("~", GuardType<T>(~*(pData), ""));
    return GuardType<T>(~*(pData), "~("+this->CalcString()+")");
}

template<typename T>
const GuardType<T>& GuardType<T>::operator ++() {
    this->GuardArrayOutOfIndex("++");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    ++*(this->pData);
    this->gt->index = this->index;
    this->calc = this->CalcString()+"+1";
    this->TraceWriteGuardType("++", *this, "");
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
    return *this;
}

template<typename T>
const GuardType<T> GuardType<T>::operator ++(int) {
    this->GuardArrayOutOfIndex("++");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    this->gt->index = this->index;
    this->TraceWriteGuardType("", *this, "++");
    GuardType<T> returnResult(*(this->pData), this->CalcString(), false);
    this->calc = this->CalcString()+"+1";
    (*(this->pData))++;
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
    return returnResult;
}

template<typename T>
const GuardType<T>& GuardType<T>::operator --() {
    this->GuardArrayOutOfIndex("--");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    --*(this->pData);
    this->gt->index = this->index;
    this->calc = this->CalcString()+"-1";
    this->TraceWriteGuardType("--", *this, "");
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
    return *this;
}

template<typename T>
const GuardType<T> GuardType<T>::operator --(int) {
    this->GuardArrayOutOfIndex("--");
    VALUE_OLD_SAVING(T oldValue = *(this->pData));
    this->gt->index = this->index;
    this->TraceWriteGuardType("", *this, "--");
    GuardType<T> returnResult(*(this->pData), this->CalcString(), false);
    this->calc = this->CalcString()+"-1";
    (*(this->pData))--;
    VALUE_CHANGE_DO_WITH_OLD_AND_NEW_VALUE\
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
     this->ValueChangedDoingWithOldAndNewValue(oldValue, this->pData));
    VALUE_CHANGE_DO(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->pData));
    return returnResult;
}

template<typename T>
void GuardType<T>::GuardArrayOutOfIndex(const std::string op) const{
    if(this->gt->D1() > 0) {
        ASSERT(this->index.d1<this->gt->D1(),
               "TRACE: out of range "+this->gt->MaxIndex()
               +" used: "+this->IdIndex()+" when operator "+op);
    } else if(this->gt->D2() > 0) {
        ASSERT(this->index.d2<this->gt->D2(),
               "TRACE: out of range "+this->gt->MaxIndex()
               +" used: "+this->IdIndex()+" when operator "+op);
    } else if(this->gt->D3() > 0) {
        ASSERT(this->index.d3<this->gt->D3(),
               "TRACE: out of range "+this->gt->MaxIndex()
               +" used: "+this->IdIndex()+" when operator "+op);
    }
}

template<typename T>
int GuardType<T>::PriorityOfSymbol(const std::string symbol) {
    if(symbol == "(" || symbol == ")")
        return 19;
    // Calculate form right to left
    else if(symbol == "++" || symbol == "--" || symbol == "!" || symbol == "~")
        return 17;
    else if(symbol == "*" || symbol == "/" || symbol == "%")
        return 15;
    else if(symbol == "+" || symbol == "-")
        return 13;
    else if(symbol == "<<" || symbol == ">>")
        return 11;
    else if(symbol == "<" || symbol == ">" || symbol == "<=" || symbol == ">=")
        return 9;
    else if(symbol == "==" || symbol == "!=")
        return 7;
    else if(symbol == "&" || symbol == "|" || symbol == "^")
        return 5;
    else if(symbol == "&&" || symbol == "||")
        return 3;
    return 9999;
}

template<typename T>
const std::string GuardType<T>::NextCalculateOp(std::string::iterator& current,
                                                std::string::iterator end)
{
    static std::string calcSymbolsTemp[25] = {
        "(", ")", "=", "+", "++", "-", "--", "*", "/", "%", "<", ">", "<=", ">=",
        "==", "!=", "&&", "||", "!", "&", "|", "~", "^", "<<", ">>"};
    static std::set<std::string> calcSymbols(calcSymbolsTemp,calcSymbolsTemp+25);
    
    std::string op="";
    while(current != end && calcSymbols.find(op) == calcSymbols.end()) {
        op = *current++;
    }
    if(calcSymbols.find(op) != calcSymbols.end()) {
        if(current != end && calcSymbols.find(op + *current) != calcSymbols.end()) {
            return op + *current++;
        }
        else
            return op;
    }else {
        return "";
    }
}

template<typename T>
int GuardType<T>::MinCalcPriorityOf(const std::string calcExpression) {
    int minPriorityOfData2 = 9999;
    int tempPriority;
    std::string& calcExpress = const_cast<std::string&>(calcExpression);
    std::string::iterator iter = calcExpress.begin();
    std::string opTemp = NextCalculateOp(iter, calcExpress.end());
    while(iter != calcExpress.end()) {
        if(opTemp == "(") {
            for(int l=0, r=0; l!=r; opTemp = NextCalculateOp(iter, calcExpress.end())) {
                if(opTemp == "(")
                    ++l;
                else if(opTemp == ")") {
                    ++r;
                }
            }
        } else {
            tempPriority = PriorityOfSymbol(opTemp);
            if(tempPriority < minPriorityOfData2)
                minPriorityOfData2 = tempPriority;
        }
        opTemp = NextCalculateOp(iter, calcExpress.end());
    }
    return minPriorityOfData2;
}

template<typename T>
template<typename U, typename V>
const std::string GuardType<T>::PackWithBracket(const U& data1,
                                                std::string opStr,
                                                const V& data2) {
    std::string data1CalcString = GuardType<T>::ToString(data1);
    std::string data2CalcString = GuardType<T>::ToString(data2);
    std::string calcExpress;
    if(GuardType::MinCalcPriorityOf(data1CalcString)
       <= GuardType::PriorityOfSymbol(opStr))
        calcExpress = "("+data1CalcString+")" + opStr;
    else
        calcExpress = data1CalcString + opStr;
    
    if(GuardType::PriorityOfSymbol(opStr)
       >= GuardType::MinCalcPriorityOf(data2CalcString))
        calcExpress += "("+data2CalcString+")";
    else
        calcExpress += data2CalcString;
    return calcExpress;
}

template<typename T>
bool GuardType<T>::IsAssignOp(const std::string operatorName) {
    return (operatorName.find("=") != std::string::npos) &&
    (operatorName != "<=") &&
    (operatorName != ">=") &&
    (operatorName != "==") &&
    (operatorName != "!=");
}

template<typename T>
const std::string GuardType<T>::IdIndex() const {
    std::string idx = "";
    char str_idx[32];
    if(gt->D3() != 0) {
        sprintf(str_idx, "%d", static_cast<int>(index.d3));
        idx += "[";  idx += str_idx; idx += "]";
    }
    if(gt->D2() != 0) {
        sprintf(str_idx, "%d", static_cast<int>(index.d2));
        idx += "[";  idx += str_idx; idx += "]";
    }
    if(gt->D1() != 0) {
        sprintf(str_idx, "%d", static_cast<int>(index.d1));
        idx += "[";  idx += str_idx; idx += "]";
    }
    idx = this->gt->id+idx;
    return idx;
}

template<typename T>
const std::string GuardType<T>::MaxIndex() const {
    std::string idx = "";
    char str_idx[8];
    if(gt->D3() != 0) {
        sprintf(str_idx, "%d", static_cast<int>(gt->D3()));
        idx += "[";  idx += str_idx; idx += "]";
    }
    if(gt->D2() != 0) {
        sprintf(str_idx, "%d", static_cast<int>(gt->D2()));
        idx += "[";  idx += str_idx; idx += "]";
    }
    if(gt->D1() != 0) {
        sprintf(str_idx, "%d", static_cast<int>(gt->D1()));
        idx += "[";  idx += str_idx; idx += "]";
    }
    idx = this->id+idx;
    return idx;
}

template<typename T>
void GuardType<T>::OutPutExpresAndArray() const {
    if(_OUT_PUT_EXPRES_SWITCH) GuardConfig::so
        << _SPACES << "EXPRES:"
        << this->IdIndex() << " = "
        << this->CalcString() << std::endl;
    if(GuardConfig::_ARRAY_OUT_PUT_SWITCH)
        gt->PrintArray();
}

template<typename T>
template<typename U, typename V, typename W>
void GuardType<T>::OutPutTrace(const U& data1,
                               std::string op,
                               const V& data2,
                               const W& result) {
    if(_OUT_PUT_TRACE_SWITCH == false || GuardConfig::rule[op] == false) return;
    typedef const GuardType<typename type_traits<U>::value_type>& GTU;
    typedef const GuardType<typename type_traits<V>::value_type>& GTV;
    
    GuardConfig::so << _SPACES << "TRACE: ";
    
    // 如果 U 是普通数值类型 V 是 GuardType 类型
    if(TIsDerived<U, GuardConfig>::result == false) {
        GuardConfig::so << data1;
        GuardConfig::so << " " << op << " ";
        if(static_cast<GTV>(data2).gt->id == "")
            GuardConfig::so << *(static_cast<GTV>(data2).pData);
        else
            GuardConfig::so << static_cast<GTV>(data2).IdIndex();
        if(!(static_cast<GTV>(data2).gt->id == "" && op == "=")) {
            GuardConfig::so << " = ";
            GuardConfig::so << result;
        }
        
        // 如果 U 是 GuardType 类型 V 是普通数值类型
    } else if(TIsDerived<V, GuardConfig>::result == false) {
        if(static_cast<GTU>(data1).gt->id == "")
            GuardConfig::so << *(static_cast<GTU>(data1).pData);
        else
            GuardConfig::so << static_cast<GTU>(data1).IdIndex();
        GuardConfig::so << " " << op << " ";
        GuardConfig::so << data2;
        GuardConfig::so << " = ";
        GuardConfig::so << result;
        
        // 如果 U 和 V 都是 GuardType 类型
    } else {
        if(static_cast<GTU>(data1).gt->id == "")
            GuardConfig::so << *(static_cast<GTU>(data1).pData);
        else
            GuardConfig::so << static_cast<GTU>(data1).IdIndex();
        GuardConfig::so << " " << op << " ";
        if(static_cast<GTV>(data2).gt->id == "")
            GuardConfig::so << *(static_cast<GTV>(data2).pData);
        else
            GuardConfig::so << static_cast<GTV>(data2).IdIndex();
        if(!(static_cast<GTV>(data2).gt->id == "" && op == "=")) {
            GuardConfig::so << " = ";
            GuardConfig::so << result;
        }
    }
    GuardConfig::so << std::endl;
}

template<typename T>
template<typename U>
void GuardType<T>::TraceReadGuardType(
                                      const std::string& op,
                                      const GuardType<U>& result) const
{
    if(GuardConfig::rule[op] == false) return;
    if(_OUT_PUT_TRACE_SWITCH == true) {
        GuardConfig::so << _SPACES << "TRACE: ";
        GuardConfig::so << op;
        if(this->gt->id == "")
            GuardConfig::so << *(this->pData);
        else
            GuardConfig::so << this->IdIndex();
        GuardConfig::so << " : ";
        GuardConfig::so << *(result.pData) <<std::endl;
    }
}

template<typename T>
template<typename U>
void GuardType<T>::TraceWriteGuardType(
                                       const std::string& frontOp,
                                       const GuardType<U>& result,
                                       const std::string& backOp) const
{
    this->gt->index = this->index;
    if(frontOp+backOp == "" && GuardConfig::rule["="] == false) return;
    if(frontOp+backOp != "" && GuardConfig::rule[frontOp+backOp] == false) return;
    if(_OUT_PUT_TRACE_SWITCH == true) {
        GuardConfig::so << _SPACES << "TRACE: ";
        GuardConfig::so << frontOp;
        if(this->gt->id == "")
            GuardConfig::so << *(this->pData);
        else
            GuardConfig::so << this->IdIndex();
        GuardConfig::so << backOp << " = ";
        GuardConfig::so << *(result.pData) << std::endl;
    }
    if(backOp == "")
        this->OutPutExpresAndArray();
}

template<typename T>
template<typename U>
void GuardType<T>::TraceOperateGTWithGT(
                                        const std::string&                  opStr,
                                        const GuardType<U>&                 data,
                                        const T&                            value) const
{
    this->GuardArrayOutOfIndex(opStr);
    data.GuardArrayOutOfIndex(opStr);
    this->gt->index = this->index;
    if(GuardConfig::rule[opStr] == false) return;
    if(!(IsAssignOp(opStr) && data.id == "GT")) {
        GuardType<T>::OutPutTrace(*this, opStr, data, value);
    }
    if(IsAssignOp(opStr)) {
        this->OutPutExpresAndArray();
    }
}

template<typename T>
template<typename U>
const std::string GuardType<T>::ToString(const U& data) {
    return NumToString::Transform(data);
}

template<typename T>
template<typename U>
const std::string GuardType<T>::ToString(const GuardType<U>& data) {
    return data.CalcString();
}

template<typename T>
const std::string GuardType<T>::CalcString() const {
    if(this->calc != "") return calc;
    
    if(GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
        if(this->gt->id != "") {
            return this->IdIndex();
        } else {
            return "GT";
        }
    } else {
        return NumToString::Transform(*(this->pData));
    }
}

template<typename T>
const std::string GuardType<T>::GetNewId(std::string id) {
    std::string  newId = id;
    if(id != "" && id != "GT") {
        while(!GuardConfig::idArray.empty())
            GuardConfig::idArray.pop();
        return id;
    } else if(id == "" || GuardConfig::idArray.empty()) {
        return "GT";
    } else {
        newId = GuardConfig::idArray.front();
        GuardConfig::idArray.pop();
    }
    return newId;
}

template<typename T>
const std::string GuardType<T>::GetNewIdByIncreaseId(std::string id) {
    std::string getName = GuardType<T>::GetNewId();
    if(getName != "GT") return getName;
    std::string& newName = id;
    if(newName == "") newName = "GT";
    int num = 0;
    while(newName.length() != 0 && isnumber(newName[newName.length()-1])) {
        num = num*10 + atoi(&newName[newName.length()-1]);
        newName.erase(newName.length()-1);
    }
    ++num;
    char str_num[4];
    sprintf(str_num, "%d", num);
    newName += str_num;
    return newName;
}

template<typename T>
std::istream& GuardType<T>::ReadGuardTypeFromIO(
                                                std::istream& si,
                                                GuardType<T>& gt)
{
    if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
        if(typeid(si) == typeid(std::cin)) {
            std::cout << "Please input Data ";
            std::cout << gt.IdIndex();
            std::cout << ": ";
        }
    }
    si >> *(gt.pData);
    if(GuardConfig::rule[">>"] == true) {
        if(_OUT_PUT_TRACE_SWITCH == true) {
            std::cout<< _SPACES << "TRACE: si >> ";
            std::cout<< gt.IdIndex();
            std::cout<< " = " << *(gt.pData) << std::endl;
            if(GuardConfig::_ARRAY_OUT_PUT_SWITCH)
                gt.gt->PrintArray();
        }
    }
    return si;
}

template<typename T>
std::ostream& GuardType<T>::WriteGuardTypeToIO(
                                               std::ostream & so,
                                               const GuardType<T>& gt)
{
    if(GuardConfig::rule["<<"] == true) {
        if(_OUT_PUT_TRACE_SWITCH == true) {
            so << _SPACES << "TRACE: so<< " ;
            so << gt.IdIndex();
            so << " : " << *(gt.pData) << std::endl;
        }
    }
    so << *(gt.pData);
    return so;
}




#include <iomanip>
//-----------------------------------------------------------------------------
//                            class GuardTypeArray

template<typename T>
class GuardTypeArray : protected GuardType<T> {
    private :
    // class Array_ptr
    class Array_ptr {
        public :
        Array_ptr(const T* pArr, bool isReferenceFromArray = false);
        T*      get() const;
        void    set(const T* pArr, bool isReferenceFromArray = false);
        ~Array_ptr();
        private :
        bool isReferenceFromArray;
        T* pArr;
    };
    
    public :
    using typename GuardType<T>::ArrayIndex;
    using typename GuardType<T>::Ptr;
    // class Ptr2
    class Ptr2 : protected Ptr{
        template<typename U>
        friend class GuardTypeArray2D;
        public :
        Ptr2();
        template<int M, int N>
        Ptr2(const T (&pArr)[M][N]);
        Ptr2(const ArrayIndex&          index,
             T*                         pData,
             const GuardType<T>* gt);
        void                                    SetArrayId(const std::string id);
        typename GuardTypeArray<T>::Ptr         operator [] (size_t m);
        const typename GuardTypeArray<T>::Ptr   operator [] (size_t m) const;
        typename GuardTypeArray<T>::Ptr         operator * ();
        const typename GuardTypeArray<T>::Ptr   operator * () const;
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
    };
    
    // class GuardTypeArray
    public :
    typedef Ptr             iterator;
    typedef GuardType<T>    value_type;
    protected :
    GuardTypeArray();
    public :
    template<size_t N, typename U>
    GuardTypeArray(const U (&pArr)[N], const std::string& id = "GT");
    template<size_t N, typename U>
    GuardTypeArray(const U (&pArr)[N], bool isReferenceFromArray);
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





//----------------------------GuardType--------------------------------------------
//                         The members of GuardType::Ptr

template<typename T>
template<int N>
GuardType<T>::Ptr::Ptr(const T (&pArr)[N])
: index(), pos(const_cast<T*>(pArr)), isGtAlloc(true) {
    gt = (GuardType<T>*)new GuardTypeArray<T>(pArr, true);
}

//----------------------------GuardTypeArray--------------------------------------------
//                         The members of GuardTypeArray::Ptr2

template<typename T>
GuardTypeArray<T>::Ptr2::Ptr2()
{}

template<typename T>
GuardTypeArray<T>::Ptr2::Ptr2(const ArrayIndex& index, T* pData, const GuardType<T>* gt)
: GuardType<T>::Ptr(index , pData, const_cast<GuardType<T>*>(gt)) {
    assert(pData != NULL);
}

template<typename T>
void GuardTypeArray<T>::Ptr2::SetArrayId(const std::string id) {
    this->gt->id = id;
}

template<typename T>
typename GuardTypeArray<T>::Ptr
GuardTypeArray<T>::Ptr2::operator [] (size_t m) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    this->index.d2 = m;
    typename GuardTypeArray<T>::Ptr
    ptr(this->index, this->pos + m*(this->gt->D1()==0 ? 1 : this->gt->D1()), this->gt);
    ASSERT(0 <= m && m <= this->gt->D2(),
           "TRACE: out of range "+this->gt->MaxIndex()+" used: "+ ptr[0].IdIndex());
    return ptr;
}

template<typename T>
const typename GuardTypeArray<T>::Ptr
GuardTypeArray<T>::Ptr2::operator [] (size_t m) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    const_cast<size_t&>(this->index.d2) = m;
    typename GuardTypeArray<T>::Ptr
    ptr(this->index, this->pos + m*(this->gt->D1()==0 ? 1 : this->gt->D1()), this->gt);
    ASSERT(0 <= m && m <= this->gt->D2(),
           "TRACE: out of range "+this->gt->MaxIndex()+" used: "+ ptr[0].IdIndex());
    return ptr;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator < (const Ptr2& ptr2) const {
    return this->pos < ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator <= (const Ptr2& ptr2) const {
    return this->pos <= ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator > (const Ptr2& ptr2) const {
    return this->pos > ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator >= (const Ptr2& ptr2) const {
    return this->pos >= ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator == (const Ptr2& ptr2) const {
    return this->pos == ptr2.pos;
}

template<typename T>
bool GuardTypeArray<T>::Ptr2::operator != (const Ptr2& ptr2) const {
    return this->pos != ptr2.pos;
}

template<typename T>
typename GuardTypeArray<T>::Ptr
GuardTypeArray<T>::Ptr2::operator * () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    typename GuardTypeArray<T>::Ptr ptr(this->index, this->pos, this->gt);
    return ptr;
}

template<typename T>
const typename GuardTypeArray<T>::Ptr
GuardTypeArray<T>::Ptr2::operator * () const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    typename GuardTypeArray<T>::Ptr ptr(this->index, this->pos, this->gt);
    return ptr;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2
GuardTypeArray<T>::Ptr2::operator + (size_t i) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2+i <= this->gt->D2());
    Ptr2 ptr2(this->index, this->pos+this->gt->D1(), this->gt);
    ptr2.index.d2 += i;
    return ptr2;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2
GuardTypeArray<T>::Ptr2::operator - (size_t i) const {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2-i >= 0);
    Ptr2 ptr2(this->index, this->pos-i*this->gt->D1(), this->gt);
    ptr2.index.d2 -= i;
    return ptr2;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2&
GuardTypeArray<T>::Ptr2::operator += (size_t i) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2+i <= this->gt->D2());
    this->index.d2 += i;
    this->pos += i*this->gt->D1();
    return *this;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2&
GuardTypeArray<T>::Ptr2::operator -= (size_t i) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2-i >= 0);
    this->index.d2 -= i;
    this->pos -= i*this->gt->D1();
    return *this;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2&
GuardTypeArray<T>::Ptr2::operator ++ () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2+1 <= this->gt->D2());
    this->index.d2 += 1;
    this->pos += this->gt->D1();
    return *this;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2
GuardTypeArray<T>::Ptr2::operator ++ (int) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2+1 <= this->gt->D2());
    Ptr2 ptr2(*this);
    this->index.d2 += 1;
    this->pos += this->gt->D1();
    return ptr2;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2&
GuardTypeArray<T>::Ptr2::operator -- () {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2-1 >= 0);
    this->index.d2 -= 1;
    this->pos -= this->gt->D1();
    return *this;
}

template<typename T>
typename GuardTypeArray<T>::Ptr2
GuardTypeArray<T>::Ptr2::operator -- (int) {
    ASSERT(this->pos != NULL && this->gt != NULL, "TRACE: Used NULL pointer");
    assert(this->index.d2-1 >= 0);
    Ptr2 ptr2(*this);
    this->pos -= this->gt->D1();
    return ptr2;
}

template<typename T>
size_t GuardTypeArray<T>::Ptr2::operator - (const Ptr2& ptr2) const {
    return this->pos-ptr2.pos;
}





//----------------------------GuardType1--------------------------------------------
//                         The members of GuardTypeArray::Array_ptr

template<typename T>
GuardTypeArray<T>::Array_ptr::Array_ptr(const T* pArr, bool isRef)
: isReferenceFromArray(isRef), pArr(const_cast<T*>(pArr)) {
}

template<typename T>
T* GuardTypeArray<T>::Array_ptr::get() const {
    return pArr;
}

template<typename T>
void GuardTypeArray<T>::Array_ptr::set(const T* pArr, bool isRef) {
    if (this->pArr != NULL) {
        delete[] this->pArr;
    }
    this->isReferenceFromArray = isRef;
    this->pArr = const_cast<T*>(pArr);
}

template<typename T>
GuardTypeArray<T>::Array_ptr::~Array_ptr() {
    if (pArr != NULL && isReferenceFromArray == false) {
        delete[] pArr;
    }
}





//------------------------------------GuardTypeArray---------------------------------
//                          The members of GuardTypeArray


template<typename T>
GuardTypeArray<T>::GuardTypeArray() : arr(NULL, true){
    
}

template<typename T>
GuardTypeArray<T>::GuardTypeArray(const GuardTypeArray<T>& gt)
: GuardType<T>(gt.GetNewNameByIncreaseId(gt.id)), length(gt.length),  arr(new T[length+1])
{
    T* pDestination = this->arr.get();
    T* pSource = gt.arr.get();
    for (size_t i=0; i<length; i++) {
        *(pDestination + i) = *(pSource + i);
    }
}

template<typename T>
GuardTypeArray<T>::GuardTypeArray(size_t n, const std::string& id)
: GuardType<T>(id), length(n), arr(new T[n+1])
{
    assert( n>0);
    T* begin = arr.get();
    T* end = begin + n;
    for(T* iter=begin; iter!=end; iter++)
        new(iter) T();
}

template<typename T>
template<size_t N, typename U>
GuardTypeArray<T>::GuardTypeArray(const U (&pArr)[N], const std::string& id)
: GuardType<T>(GuardType<T>::GetNewId(id)), length(N), arr(new T[N+1])
{
    T* a = arr.get();
    for(size_t i=0; i<N; i++) {
        
        a[i] = pArr[i];
    }
}

template<typename T>
template<size_t N, typename U>
GuardTypeArray<T>::GuardTypeArray(const U (&pArr)[N], bool isReferenceFromArray)
: GuardType<T>(), length(N), arr(pArr, isReferenceFromArray) {
    if(isReferenceFromArray == false) {
        T* a = new T[N+1];
        arr.set(a);
        for(size_t i=0; i<N; i++) {
            a[i] = pArr[i];
        }
    }
}

template<typename T>
size_t GuardTypeArray<T>::size() const {
    return this->length;
}

template<typename T>
size_t GuardTypeArray<T>::Length() const {
    return this->length;
}

template<typename T>
GuardType<T>& GuardTypeArray<T>::operator [] (size_t n) {
    ASSERT(0 <= n && n < length, "TRACE: out of range "+this->MaxIndex()+" used: "+
           this->id+"["+NumToString::Transform(n)+"]");
    if(this->arrReturnValue.insert(std::pair<size_t, GuardType<T>* >(n, NULL)).second == true) {
        this->arrReturnValue[n] = new GuardType<T>(ArrayIndex(0, 0, n), this->Arr()+n, this);
    }
    return *this->arrReturnValue[n];
}

template<typename T>
const GuardType<T>& GuardTypeArray<T>::operator [] (size_t n) const {
    ASSERT(0 <= n && n < length, "TRACE: out of range "+this->MaxIndex()+" used: "+
           this->id+"["+NumToString::Transform(n)+"]");
    if(const_cast<std::map<size_t, GuardType<int> >& >(this->arrReturnValue)
       .insert(std::pair<size_t, GuardType<T> >(n, NULL)).second == true) {
        const_cast<std::map<size_t, GuardType<int> >& >(this->arrReturnValue)[n]
        = new GuardType<T>(ArrayIndex(0, 0, n), this->Arr()+n, this);
    }
    return const_cast<std::map<size_t, GuardType<int> >& >(this->arrReturnValue)[n];
}


template<typename T>
GuardTypeArray<T>::operator const Ptr () {
    return Ptr(ArrayIndex(), Arr(), this);
}

template<typename T>
bool GuardTypeArray<T>::operator == (const GuardTypeArray<T>& gt) const {
    return this->Arr() == gt.Arr();
}

template<typename T>
bool GuardTypeArray<T>::operator != (const GuardTypeArray<T>& gt) const {
    return this->Arr() != gt.Arr();
}

template<typename T>
bool GuardTypeArray<T>::operator == (const Ptr& ptr) const {
    return this->Arr() == ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator < (const Ptr& ptr) const {
    return this->Arr() < ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator <= (const Ptr& ptr) const {
    return this->Arr() <= ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator > (const Ptr& ptr) const {
    return this->Arr() > ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator >= (const Ptr& ptr) const {
    return this->Arr() >= ptr.pos;
}

template<typename T>
bool GuardTypeArray<T>::operator != (const Ptr& ptr) const {
    return this->Arr() != ptr.pos;
}

template<typename T>
template<typename U>
typename GuardTypeArray<T>::Ptr GuardTypeArray<T>::operator + (U n) {
    return Ptr(*this + n);
}

template<typename T>
std::istream& GuardTypeArray<T>::ReadArrayFromIO(
                                                 std::istream &si,
                                                 GuardTypeArray<T>& gt)
{
    T data;
    if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
        if(typeid(si) == typeid(std::cin)) {
            std::cout<< "Please input ";
            std::cout<< "["<< (gt.D2()==0?1:gt.D2())*gt.D1()<< "] Datas "
            << gt.id << ": " << std::endl;
        }
    }
    T * arr = gt.arr.get();
    for (size_t i=0; i<gt.Length(); i++) {
        si >> data;
        arr[i] = data;
    }
    return si;
}

template<typename T>
std::ostream& GuardTypeArray<T>::WriteArrayToIO(
                                                std::ostream &so,
                                                const GuardTypeArray<T>& gt)
{
    T* p = gt.arr.get();
    for (size_t i=0; i<gt.length; i++) {
        if(GuardConfig::_ARRAY_OUT_PUT_SWITCH == true && i == gt.index.d1)
            so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
            << "[" << *(p+i) << "]";
        else
            so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
            << " " << *(p+i) << " ";
    }
    so << std::endl << std::endl;
    const_cast<size_t&>(gt.index.d1) = -1;
    return so;
}








//-----------------------------------------------------------------------------
//                            class GuardTypeArray2D

template<typename T>
class GuardTypeArray2D : protected GuardTypeArray<T> {
    public :
    using typename GuardType<T>::ArrayIndex;
    using typename GuardTypeArray<T>::Ptr2;
    
    // class GuardTypeArray2D
    public :
    template<size_t M, size_t N, typename U>
    GuardTypeArray2D(const U (&pArr)[M][N], const std::string& id = "GT");
    template<size_t M, size_t N, typename U>
    GuardTypeArray2D(const U (&pArr)[M][N], bool isReferenceFromArray);
    GuardTypeArray2D(const GuardTypeArray2D<T>& gt);
    GuardTypeArray2D(size_t m, size_t n, const std::string& id = "GT");
    operator const Ptr2();
    template<typename U>
    Ptr2                                    operator + (U n);
    typename GuardTypeArray<T>::Ptr         operator [] (size_t n);
    const typename GuardTypeArray<T>::Ptr   operator [] (size_t n) const;
    size_t          LengthX() const;
    size_t          LengthY() const;
    virtual size_t  D1()     const { return y; }
    virtual size_t  D2()     const { return x; }
    virtual size_t  D3()     const { return 0; }
    
    friend std::istream& operator >> (
                                      std::istream &              si,
                                      GuardTypeArray2D<T>&        gt) {
        return ReadArray2DFromIO(si, gt);
    }
    friend std::ostream& operator << (
                                      std::ostream &              so,
                                      const GuardTypeArray2D<T>&  gt) {
        return WriteArray2DToIO(so, gt);
    }
    virtual void PrintArray() const { GuardConfig::so << *this; }
    private :
    static std::istream& ReadArray2DFromIO(
                                           std::istream&               si,
                                           GuardTypeArray2D&           gt);
    static std::ostream& WriteArray2DToIO(
                                          std::ostream&               so,
                                          const GuardTypeArray2D&     gt);
    
    private :
    size_t x, y;
};









//----------------------------GuardTypeArray--------------------------------------------
//                         The members of GuardTypeArray::Ptr2

template<typename T>
template<int M, int N>
GuardTypeArray<T>::Ptr2::Ptr2(const T (&pArr)[M][N]) {
    this->pos = const_cast<T*>(pArr[0]);
    this->gt = (GuardType<T>*)new GuardTypeArray2D<T>(pArr, true);
    this->isGtAlloc.startCount();
}

//------------------------------------GuardTypeArray2D---------------------------------
//                          The members of GuardTypeArray2D

template<typename T>
GuardTypeArray2D<T>::GuardTypeArray2D(const GuardTypeArray2D<T>& gt)
: GuardTypeArray<T>(gt.x*gt.y, gt.GetNewNameByIncreaseId(gt.id))
{
    this->x = gt.x;
    this->y = gt.y;
    T* pDestination = this->arr.get();
    T* pSource = gt.arr.get();
    for (size_t i=0; i<x*y; i++) {
        *(pDestination + i) = *(pSource + i);
    }
}

template<typename T>
GuardTypeArray2D<T>::GuardTypeArray2D(size_t m, size_t n, const std::string& id)
: GuardTypeArray<T>(m*n, id), x(m), y(n)
{
    assert( x>0 && y>0);
}

template<typename T>
template<size_t M, size_t N, typename U>
GuardTypeArray2D<T>::GuardTypeArray2D(const U (&pArr)[M][N], const std::string& id)
: GuardTypeArray<T>(M*N, GuardType<T>::GetNewId(id)), x(M) , y(N) {
    T* dest = this->arr.get();
    for (size_t i=0; i<M*N; i++) {
        dest[i] = pArr[i/N][i%N];
    }
}

template<typename T>
template<size_t M, size_t N, typename U>
GuardTypeArray2D<T>::GuardTypeArray2D(const U (&pArr)[M][N], bool isReferenceFromArray)
: GuardTypeArray<T>(), x(M) , y(N) {
    this->arr.set(pArr[0], isReferenceFromArray);
    if(isReferenceFromArray == false) {
        T* a = new T[M*N];
        this->arr.set(a, isReferenceFromArray);
        for (size_t i=0; i<M*N; i++) {
            a[i] = pArr[i/N][i%N];
        }
    }
}

template<typename T>
GuardTypeArray2D<T>::operator const Ptr2() {
    return Ptr2(ArrayIndex(), this->Arr(), (GuardTypeArray2D<T>*)this);
}

template<typename T>
size_t GuardTypeArray2D<T>::LengthX() const {
    return this->x;
}

template<typename T>
size_t GuardTypeArray2D<T>::LengthY() const {
    return this->y;
}

template<typename T>
template<typename U>
typename GuardTypeArray2D<T>::Ptr2 GuardTypeArray2D<T>::operator + (U n) {
    return Ptr2(*this + n);
}

template<typename T>
typename GuardTypeArray<T>::Ptr
GuardTypeArray2D<T>::operator [] (size_t n) {
    T* p = this->arr.get() + y*n;
    typename GuardTypeArray<T>::Ptr ptr(ArrayIndex(0, n, 0), p, this);
    ASSERT(0 <= n && n < x, "TRACE: out of range "+this->MaxIndex()+
           " used: "+static_cast<GuardTypeArray2D<T>&>(ptr[0]).IdIndex());
    return ptr;
}

template<typename T>
const typename GuardTypeArray<T>::Ptr
GuardTypeArray2D<T>::operator [] (size_t n) const {
    T* p = this->arr.get() + y*n;
    typename GuardTypeArray<T>::Ptr ptr(ArrayIndex(0, n, 0), p, this);
    ASSERT(0 <= n && n < x, "TRACE: out of range "+this->MaxIndex()+
           " used: "+static_cast<GuardTypeArray2D<T>&>(ptr[0]).IdIndex());
    return ptr;
}

template<typename T>
std::istream& GuardTypeArray2D<T>::ReadArray2DFromIO(
                                                     std::istream &si,
                                                     GuardTypeArray2D<T>& gt)
{
    T data;
    if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
        if(typeid(si) == typeid(std::cin)) {
            std::cout<< "Please input ";
            std::cout<< "["<< (gt.D2()==0?1:gt.D2())*gt.D1() << "] Datas "
            << gt.id << ": " << std::endl;
        }
    }
    for (size_t i=0; i<gt.x; i++) {
        for (size_t j=0; j<gt.y; j++) {
            si >> data;
            gt[i][j] = data;
        }
    }
    return si;
}

template<typename T>
std::ostream& GuardTypeArray2D<T>::WriteArray2DToIO(
                                                    std::ostream &so,
                                                    const GuardTypeArray2D<T>& gt)
{
    T* p = gt.arr.get();
    for (size_t i=0; i<gt.x; i++) {
        for (size_t j=0; j<gt.y; j++) {
            if(GuardConfig::_ARRAY_OUT_PUT_SWITCH == true
               && i == gt.index.d2 && j == gt.index.d1)
                so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                << "[" << *(p + i*gt.y + j) << "]";
            else
                so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                << " " << *(p + i*gt.y + j) << " ";
        }
        so << std::endl;
    }
    const_cast<size_t&>(gt.index.d2) = -1;
    so << std::endl;
    return so;
}








//-----------------------------------------------------------------------------
//                            class GuardTypeArray3D

template<typename T>
class GuardTypeArray3D : protected GuardTypeArray2D<T> {
    public :
    GuardTypeArray3D(const GuardTypeArray3D<T>& gt);
    GuardTypeArray3D(size_t n, size_t m, size_t k, const std::string& id="GT");
    typename GuardTypeArray2D<T>::Ptr2          operator [] (size_t n);
    const typename GuardTypeArray2D<T>::Ptr2    operator [] (size_t n) const;
    size_t          LengthX() const;
    size_t          LengthY() const;
    size_t          LengthZ() const;
    virtual size_t  D1()     const { return z; }
    virtual size_t  D2()     const { return y; }
    virtual size_t  D3()     const { return x; }
    
    friend std::istream& operator >> (
                                      std::istream &              si,
                                      GuardTypeArray3D<T>&        gt) {
        return ReadArray3DFromIO(si, gt);
    }
    friend std::ostream& operator << (
                                      std::ostream &              so,
                                      const GuardTypeArray3D<T>&  gt) {
        return WriteArray3DToIO(so, gt);
    }
    virtual void PrintArray() const { GuardConfig::so << *this; }
    private :
    static std::istream& ReadArray3DFromIO(
                                           std::istream&               si,
                                           GuardTypeArray3D&           gt);
    static std::ostream& WriteArray3DToIO(
                                          std::ostream&               so,
                                          const GuardTypeArray3D&     gt);
    
    private :
    size_t x, y, z;
};






//------------------------------------GuardTypeArray3D---------------------------------
//                          The members of GuardTypeArray3D

template<typename T>
GuardTypeArray3D<T>::GuardTypeArray3D(const GuardTypeArray3D<T>& gt)
: GuardTypeArray2D<T>(gt.x*gt.y, gt.z, gt.GetNewNameByIncreaseId(gt.id))
{
    this->x = gt.x;
    this->y = gt.y;
    this->z = gt.z;
    T* pDestination = this->arr.get();
    T* pSource = gt.arr.get();
    for (size_t i=0; i<x*y*z; i++) {
        *(pDestination + i) = *(pSource + i);
    }
}

template<typename T>
GuardTypeArray3D<T>::GuardTypeArray3D(
                                      size_t n, size_t m, size_t k, const std::string& id)
: GuardTypeArray2D<T>(n*m, k, id), x(n), y(m), z(k)
{
    assert( x>0 && y>0 && z>0);
}

template<typename T>
size_t GuardTypeArray3D<T>::LengthX() const {
    return this->x;
}

template<typename T>
size_t GuardTypeArray3D<T>::LengthY() const {
    return this->y;
}

template<typename T>
size_t GuardTypeArray3D<T>::LengthZ() const {
    return this->z;
}

template<typename T>
typename GuardTypeArray2D<T>::Ptr2
GuardTypeArray3D<T>::operator [] (size_t n) {
    ASSERT(0 <= n && n < x, "TRACE: out of range "+this->MaxIndex()+" used: "+
           this->id+"["+NumToString::Transform(n)+"]"+"[0][0]");
    T* p = this->arr.get() + y*z*n;
    typename GuardTypeArray2D<T>::Ptr2
    ptr2(typename GuardType<T>::ArrayIndex(n, 0, 0), p, this);
    return ptr2;
}

template<typename T>
const typename GuardTypeArray2D<T>::Ptr2
GuardTypeArray3D<T>::operator [] (size_t n) const {
    ASSERT(0 <= n && n < x, "TRACE: out of range "+this->MaxIndex()+" used: "+
           this->id+"["+NumToString::Transform(n)+"]"+"[0][0]");
    T* p = this->arr.get() + y*z*n;
    typename GuardTypeArray2D<T>::Ptr2
    ptr2(typename GuardType<T>::ArrayIndex(n, 0, 0), p, *this);
    return ptr2;
}

template<typename T>
std::istream& GuardTypeArray3D<T>::ReadArray3DFromIO(
                                                     std::istream &si,
                                                     GuardTypeArray3D<T>& gt)
{
    T data;
    if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
        if(typeid(si) == typeid(std::cin)) {
            std::cout<< "Please input ";
            std::cout<< "["<<(gt.D2()==0?1:gt.D2())*gt.D1()<< "] Datas "
            << gt.id << ": " << std::endl;
        }
    }
    for (size_t i=0; i<gt.x; i++) {
        for (size_t j=0; j<gt.y; j++) {
            for (size_t k=0; k<gt.z; k++) {
                si >> data;
                gt[i][j][k] = data;
            }
        }
    }
    return si;
}

template<typename T>
std::ostream& GuardTypeArray3D<T>::WriteArray3DToIO(
                                                    std::ostream &so,
                                                    const GuardTypeArray3D<T>& gt)
{
    T* p = gt.arr.get();
    for (size_t i=0; i<gt.x; i++) {
        for (size_t j=0; j<gt.y; j++) {
            for (size_t k=0; k<gt.z; k++) {
                if(GuardConfig::_ARRAY_OUT_PUT_SWITCH == true
                   && i == gt.index.d3
                   && j == gt.index.d2
                   && k == gt.index.d1)
                    so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << "[" << *(p+i*gt.y*gt.z+j*gt.z+k) << "]";
                else
                    so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
                    << " " << *(p+i*gt.y*gt.z+j*gt.z+k) << " ";
            }
            so << std::endl;
        }
        so << std::endl;
    }
    const_cast<size_t&>(gt.index.d3) = -1;
    so << std::endl;
    return so;
}




//-----------------------------------------------------------------------------
//                            Type Define

#include <cmath>

#define GT_TYPE(type, name)\
typedef GuardType<type>                         name;\
typedef GuardTypeArray<type>                    name##Arr;\
typedef GuardTypeArray2D<type>                  name##Arr2;\
typedef GuardTypeArray3D<type>                  name##Arr3;\
typedef typename GuardTypeArray<type>::Ptr      name##Ptr;\
typedef typename GuardTypeArray2D<type>::Ptr2   name##Ptr2;

GT_TYPE(bool,              Bool)
GT_TYPE(char,              Char)
GT_TYPE(unsigned char,     UChar)
GT_TYPE(short,             Short)
GT_TYPE(unsigned short,    UShort)
GT_TYPE(int,               Int)
GT_TYPE(unsigned int,      UInt)
GT_TYPE(long,              Long)
GT_TYPE(unsigned long,     ULong)
GT_TYPE(float,             Float)
GT_TYPE(double,            Double)
GT_TYPE(long double,       LongDouble)
GT_TYPE(std::string,       String)



//--------------------------------------------------------------------------------
//                              C math library

#define C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, T)\
GuardType<typename LargerType<float, T>::value_type>\
Function(const T& x) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+")";\
return GuardType<typename LargerType<float, T>::value_type>\
(std::Function(x), Expres, false);\
}

#define C_MATH_FUNCTION_SINGLE_PARAMETER(Function)\
template<typename T>\
GuardType<typename LargerType<float, T>::value_type> Function(const GuardType<T>& x) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+")";\
return GuardType<typename LargerType<float, T>::value_type>\
(std::Function(static_cast<T>(x)), Expres, false);\
}\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, unsigned short)\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, short)\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, unsigned int)\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, int)\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, unsigned long)\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, long)\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, float)\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, double)\
C_MATH_FUNCTION_SINGLE_PARAMETER_T(Function, long double)

C_MATH_FUNCTION_SINGLE_PARAMETER(acos)
C_MATH_FUNCTION_SINGLE_PARAMETER(asin)
C_MATH_FUNCTION_SINGLE_PARAMETER(atan)
C_MATH_FUNCTION_SINGLE_PARAMETER(ceil)
C_MATH_FUNCTION_SINGLE_PARAMETER(cos)
C_MATH_FUNCTION_SINGLE_PARAMETER(cosh)
C_MATH_FUNCTION_SINGLE_PARAMETER(exp)
C_MATH_FUNCTION_SINGLE_PARAMETER(fabs)
C_MATH_FUNCTION_SINGLE_PARAMETER(floor)
C_MATH_FUNCTION_SINGLE_PARAMETER(log)
C_MATH_FUNCTION_SINGLE_PARAMETER(log10)
C_MATH_FUNCTION_SINGLE_PARAMETER(sin)
C_MATH_FUNCTION_SINGLE_PARAMETER(sinh)
C_MATH_FUNCTION_SINGLE_PARAMETER(sqrt)
C_MATH_FUNCTION_SINGLE_PARAMETER(tan)
C_MATH_FUNCTION_SINGLE_PARAMETER(tanh)
C_MATH_FUNCTION_SINGLE_PARAMETER(signbit)
C_MATH_FUNCTION_SINGLE_PARAMETER(fpclassify)


#define C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(Function)\
template<typename T>\
GuardType<bool> Function(const GuardType<T>& x) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+")";\
return GuardType<bool>(std::Function(static_cast<T>(x)), Expres, false);\
}

C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(isfinite)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(isinf)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(isnan)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(isnormal)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(ilogb)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_BOOL(acos)


#define C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_LONG(Function)\
template<typename T>\
GuardType<long> Function(const GuardType<T>& x) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+")";\
return GuardType<long>(std::Function(static_cast<T>(x)), Expres, false);\
}

C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_LONG(lrint)
C_MATH_FUNCTION_SINGLE_PARAMETER_RETURN_LONG(lround)


#define C_MATH_FUNCTION_COUPLE_PARAMETER(Function)\
template<typename T, typename U>\
GuardType<typename LargerType<float,\
typename LargerType<\
typename type_traits<T>::value_type, \
typename type_traits<U>::value_type>::value_type\
>::value_type >\
Function(const GuardType<T>& x, const U& y) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+", "+GuardType<T>::ToString(y)+")";\
return GuardType<typename LargerType<float,\
typename LargerType<\
typename type_traits<T>::value_type, \
typename type_traits<U>::value_type>::value_type\
>::value_type >\
(std::Function(static_cast<typename type_traits<T>::value_type>(x),\
static_cast<typename type_traits<U>::value_type>(y)),\
Expres, false);\
}\
template<typename T, typename U>\
GuardType<typename LargerType<float,\
typename LargerType<\
typename type_traits<T>::value_type, \
typename type_traits<U>::value_type>::value_type\
>::value_type >\
Function(const T& x, const GuardType<U>& y) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+", "+GuardType<T>::ToString(y)+")";\
return GuardType<typename LargerType<float,\
typename LargerType<\
typename type_traits<T>::value_type, \
typename type_traits<U>::value_type>::value_type\
>::value_type >\
(std::Function(static_cast<typename type_traits<T>::value_type>(x),\
static_cast<typename type_traits<U>::value_type>(y)),\
Expres, false);\
}\
template<typename T, typename U>\
GuardType<typename LargerType<float,\
typename LargerType<\
typename type_traits<T>::value_type, \
typename type_traits<U>::value_type>::value_type\
>::value_type >\
Function(const GuardType<T>& x, const GuardType<U>& y) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+", "+GuardType<T>::ToString(y)+")";\
return GuardType<typename LargerType<float,\
typename LargerType<\
typename type_traits<T>::value_type, \
typename type_traits<U>::value_type>::value_type\
>::value_type >\
(std::Function(static_cast<typename type_traits<T>::value_type>(x),\
static_cast<typename type_traits<U>::value_type>(y)),\
Expres, false);\
}


C_MATH_FUNCTION_COUPLE_PARAMETER(atan2f)
C_MATH_FUNCTION_COUPLE_PARAMETER(fmodf)
C_MATH_FUNCTION_COUPLE_PARAMETER(frexp)
C_MATH_FUNCTION_COUPLE_PARAMETER(ldexp)
C_MATH_FUNCTION_COUPLE_PARAMETER(modf)
C_MATH_FUNCTION_COUPLE_PARAMETER(pow)
C_MATH_FUNCTION_COUPLE_PARAMETER(acosh)
C_MATH_FUNCTION_COUPLE_PARAMETER(asinh)
C_MATH_FUNCTION_COUPLE_PARAMETER(atanh)
C_MATH_FUNCTION_COUPLE_PARAMETER(cbrt)
C_MATH_FUNCTION_COUPLE_PARAMETER(erf)
C_MATH_FUNCTION_COUPLE_PARAMETER(erfc)
C_MATH_FUNCTION_COUPLE_PARAMETER(exp2)
C_MATH_FUNCTION_COUPLE_PARAMETER(expm1)
C_MATH_FUNCTION_COUPLE_PARAMETER(fdim)
C_MATH_FUNCTION_COUPLE_PARAMETER(fmax)
C_MATH_FUNCTION_COUPLE_PARAMETER(fmin)
C_MATH_FUNCTION_COUPLE_PARAMETER(hypot)
C_MATH_FUNCTION_COUPLE_PARAMETER(lgamma)
C_MATH_FUNCTION_COUPLE_PARAMETER(llrint)
C_MATH_FUNCTION_COUPLE_PARAMETER(llround)
C_MATH_FUNCTION_COUPLE_PARAMETER(log1p)
C_MATH_FUNCTION_COUPLE_PARAMETER(log2)
C_MATH_FUNCTION_COUPLE_PARAMETER(logb)
C_MATH_FUNCTION_COUPLE_PARAMETER(nearbyint)
C_MATH_FUNCTION_COUPLE_PARAMETER(nextafter)
C_MATH_FUNCTION_COUPLE_PARAMETER(nexttoward)
C_MATH_FUNCTION_COUPLE_PARAMETER(remainder)
C_MATH_FUNCTION_COUPLE_PARAMETER(rint)
C_MATH_FUNCTION_COUPLE_PARAMETER(round)
C_MATH_FUNCTION_COUPLE_PARAMETER(scalbln)
C_MATH_FUNCTION_COUPLE_PARAMETER(scalbn)
C_MATH_FUNCTION_COUPLE_PARAMETER(tgamma)
C_MATH_FUNCTION_COUPLE_PARAMETER(trunc)


#define C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(Function)\
template<typename T, typename U>\
GuardType<bool> Function(const GuardType<T>& x, const U& y) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+", "+GuardType<T>::ToString(y)+")";\
return GuardType<bool>\
(std::Function(static_cast<typename type_traits<T>::value_type>(x),\
static_cast<typename type_traits<T>::value_type>(y)),\
Expres, false);\
}\
template<typename T, typename U>\
GuardType<bool> Function(const T& x, const GuardType<U>& y) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+", "+GuardType<T>::ToString(y)+")";\
return GuardType<bool>\
(std::Function(static_cast<typename type_traits<T>::value_type>(x),\
static_cast<typename type_traits<T>::value_type>(y)),\
Expres, false);\
}\
template<typename T, typename U>\
GuardType<bool> Function(const GuardType<T>& x, const GuardType<U>& y) {\
std::string Expres = #Function;\
Expres += "("+GuardType<T>::ToString(x)+", "+GuardType<T>::ToString(y)+")";\
return GuardType<bool>\
(std::Function(static_cast<typename type_traits<T>::value_type>(x),\
static_cast<typename type_traits<T>::value_type>(y)),\
Expres, false);\
}

C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(isgreater)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(isgreaterequal)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(isless)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(islessequal)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(islessgreater)
C_MATH_FUNCTION_COUPLE_PARAMETER_RETURN_BOOL(isunordered)


#endif // GT_H