#ifndef GuardConfig_hpp
#define GuardConfig_hpp

#include <map>
#include <queue>
#include <string>
#include <iostream>

//---------------------------------------------------------------------------
//                              GuardConfig


#define OUT_OF_INDEX_DETECT__(detect)           //detect

#define OUTPUT_TRACE_SWITCH__(trace)            trace

#define VALUE_CHANGED_DO_____(someting)         someting

#define VALUE_BE_READED_DO___(someting)         someting

#define OLD_TO_NEW_VALUE_DO__(someting)         someting

#define TRACE_STRING_SAVE_DECLARE(member)       member,
#define TRACE_STRING_SAVE____(string)           string

#define _SPACES "\t\t\t\t"



class GuardConfig
{
    GuardConfig();
    GuardConfig(GuardConfig&);
    template<typename T, template<typename>class DataSource>
    friend class GuardType;
public:
    
    static void TurnAllGuardOff();
    static void TurnAllGuardOn();
    
    static void TurnReadSwitch(bool yes);
    // +, -, *, /, %, ^, &,|, ~, <<, >>
    static void TurnMathSwitch(bool yes);
    // !, &&, ||
    static void TurnLogicSwitch(bool yes);
    // <, >, <=, >=, !=, ==
    static void TurnCompareSwitch(bool yes);
    // =, ++, --, +=, -=, *=, /=, %=, ^=, <<=, >>=
    static void TurnAssignSwitch(bool yes);
    static void TurnOutPutCalcTraceSwitch(bool yes);
    static void TurnOutPutCalcExpressSwitch(bool yes);
    
    static void TurnIOTipSwitch(bool yes);
    static void TurnArrayOutPutSwitch(bool yes);
    static void TurnCalcExpressIdOrNum(bool yes);
    static void SetArrayOutPutInterval(int n);
    
    static bool _TRACE_READ_SWITCH;
    static bool _OUTPUT_TRACE_SWITCH;
    static bool _OUT_PUT_EXPRES_SWITCH;
    static bool _OUT_PUT_EXPRES_ID_OR_NUM_SWITCH;
    static bool _ARRAY_IO_TIP_SWITCH;;
    static bool _ARRAY_OUT_PUT_SWITCH;
    static int  _ARRAY_OUT_PUT_INTERVAL;
    const static bool defaultGuard;
public:
    static const char defaultId[];
    static const std::string defaultIdStr;
    static std::ostream& so;
    static std::queue<std::string> idArray;
    static std::map<std::string, bool> rule;
    static GuardConfig config;
};



void TurnTrace(bool s);

void TurnExpres(bool s);

#define GTRule GuardConfig::rule

const char GuardConfig::defaultId[] = "GT";
std::ostream& GuardConfig::so = std::cout;

const bool GuardConfig::defaultGuard        = true;
bool GuardConfig::_TRACE_READ_SWITCH        = false;
bool GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH = false;
bool GuardConfig::_OUTPUT_TRACE_SWITCH      = GuardConfig::defaultGuard;
bool GuardConfig::_OUT_PUT_EXPRES_SWITCH    = GuardConfig::defaultGuard;
bool GuardConfig::_ARRAY_IO_TIP_SWITCH      = GuardConfig::defaultGuard;
bool GuardConfig::_ARRAY_OUT_PUT_SWITCH     = GuardConfig::defaultGuard;
int  GuardConfig::_ARRAY_OUT_PUT_INTERVAL   = 2;


std::queue<std::string> GuardConfig::idArray;
std::map<std::string, bool> GuardConfig::rule;
GuardConfig GuardConfig::config;
const std::string GuardConfig::defaultIdStr = std::string(GuardConfig::defaultId);

GuardConfig::GuardConfig()
{
    rule.insert(std::make_pair("+", defaultGuard));
    rule.insert(std::make_pair("-", defaultGuard));
    rule.insert(std::make_pair("*", defaultGuard));
    rule.insert(std::make_pair("/", defaultGuard));
    rule.insert(std::make_pair("%", defaultGuard));
    rule.insert(std::make_pair("^", defaultGuard));
    rule.insert(std::make_pair("&", defaultGuard));
    rule.insert(std::make_pair("|", defaultGuard));
    rule.insert(std::make_pair("~", defaultGuard));
    rule.insert(std::make_pair("<<", defaultGuard));
    rule.insert(std::make_pair(">>", defaultGuard));
    rule.insert(std::make_pair("!", defaultGuard));
    rule.insert(std::make_pair("&&", defaultGuard));
    rule.insert(std::make_pair("||", defaultGuard));
    rule.insert(std::make_pair("<", defaultGuard));
    rule.insert(std::make_pair(">", defaultGuard));
    rule.insert(std::make_pair("<=", defaultGuard));
    rule.insert(std::make_pair(">=", defaultGuard));
    rule.insert(std::make_pair("==", defaultGuard));
    rule.insert(std::make_pair("!=", defaultGuard));
    rule.insert(std::make_pair("+=", defaultGuard));
    rule.insert(std::make_pair("-=", defaultGuard));
    rule.insert(std::make_pair("*=", defaultGuard));
    rule.insert(std::make_pair("/=", defaultGuard));
    rule.insert(std::make_pair("%=", defaultGuard));
    rule.insert(std::make_pair("^=", defaultGuard));
    rule.insert(std::make_pair("<<=", defaultGuard));
    rule.insert(std::make_pair(">>=", defaultGuard));
    rule.insert(std::make_pair("++", defaultGuard));
    rule.insert(std::make_pair("--", defaultGuard));
    rule.insert(std::make_pair("=", defaultGuard));
    rule.insert(std::make_pair("", true));
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
    _OUTPUT_TRACE_SWITCH = yes;
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

void TurnTrace(bool yes) {
    GuardConfig::TurnOutPutCalcTraceSwitch(yes);
}

void TurnExpres(bool yes) {
    GuardConfig::TurnOutPutCalcExpressSwitch(yes);
}

#endif /* GuardConfig_hpp */





#ifndef Tools_hpp
#define Tools_hpp

#include <assert.h>
#include <set>
//#include "GuardConfig.h"

//--------------------------------------------------------------------------
//                             GT tools

#define ASSERT(yes, outPut)\
if(! (yes) ) GuardConfig::so << outPut << std::endl;\
assert(yes);

namespace GT {
    
    const std::string GetNewId() {
        if(!GuardConfig::idArray.empty()) {
            std::string newId = GuardConfig::idArray.front();
            GuardConfig::idArray.pop();
            return newId;
        } else {
            return GuardConfig::defaultId;
        }
    }
    
    const std::string GetNewId(std::string userDef) {
        if(userDef != GuardConfig::defaultId) {
            return userDef;
        } else {
            return GetNewId();
        }
    }
    
    const std::string GetNewIdByIncreaseId(const std::string& id) {
        std::string getName = (id == "" ? GT::GetNewId() : id);
        if(getName == GuardConfig::defaultId) return getName;
        std::string newName = id;
        if(newName == "") newName = GuardConfig::defaultId;
        int num = 0;
        while(newName.length() != 0
              && ('0' <= newName[newName.length()-1])
              && (newName[newName.length()-1] <= '9')) {
            num = num*10 + atoi(&newName[newName.length()-1]);
            newName.erase(newName.length()-1);
        }
        ++num;
        char str_num[4];
        sprintf(str_num, "%d", num);
        newName += str_num;
        return newName;
    }
    
    int PriorityOfSymbol(const std::string& symbol) {
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
    
    const std::string NextCalculateOp(std::string::iterator& current,
                                      const std::string::iterator& end)
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
    
    int MinCalcPriorityOf(const std::string& calcExpression) {
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
    
}

#endif /* Tools_hpp */






#ifndef TemplateTools_hpp
#define TemplateTools_hpp

#include <iostream>
//#include "Tools.h"

template<typename T, template<typename>class DataSource>
class GuardType;

template<typename T, int Demention>
class GuardTypeArray;

//--------------------------------------------------------------------------
//                             GT template tools

template<typename T>
void AddId(const T& id) {
    GuardConfig::idArray.push(id);
}

template<typename T, typename ...U>
void AddId(const T& id, const U&...ids) {
    GuardConfig::idArray.push(id);
    AddId(ids...);
}

namespace GT {
    
    //---------------------------------------------------------------------------
    //                              GT::type_traits
    
    template<typename T>
    struct type_traits {
        typedef T value_type;
    };
    
    template<typename T, template<typename>class DataSource>
    struct type_traits<GuardType<T, DataSource> > {
        typedef T value_type;
    };
    
    template<typename T, typename U>
    struct type_equals {
        enum { value = 0 };
    };
    
    template<typename T>
    struct type_equals<T, T> {
        enum { value = 1 };
    };
    
    template<typename... T>
    int printf(const char * s, const T&... arg1) {
        return std::printf(s, static_cast<typename type_traits<T>::value_type>(arg1)...);
    }
    
    
    //---------------------------------------------------------------------------
    //                              GT::LargerType
    
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
    struct TypePriority<bool> {             enum { N = 0 }; };
    
    template<>
    struct TypePriority<unsigned char> {    enum { N = 1 }; };
    
    template<>
    struct TypePriority<char> {             enum { N = 2 }; };
    
    template<>
    struct TypePriority<unsigned short> {   enum { N = 3 }; };
    
    template<>
    struct TypePriority<short> {            enum { N = 4 }; };
    
    template<>
    struct TypePriority<unsigned int> {     enum { N = 5 }; };
    
    template<>
    struct TypePriority<int> {              enum { N = 6 }; };
    
    template<>
    struct TypePriority<unsigned long> {    enum { N = 7 }; };
    
    template<>
    struct TypePriority<long> {             enum { N = 8 }; };
    
    template<>
    struct TypePriority<float> {            enum { N = 9 }; };
    
    template<>
    struct TypePriority<double> {           enum { N = 10 }; };
    
    template<>
    struct TypePriority<long double> {      enum { N = 11 }; };
    
    
    //---------------------------------------------------------------------------
    //                              PackExpres
    // (data1) op (data2)
    
    template<typename T>
    const std::string NumericToString(const T& data) {
        std::string num = std::to_string(data);
        if((GT::type_equals<T, float>::value
            || GT::type_equals<T, double>::value
            || GT::type_equals<T, long double>::value)) {
            while (num.back() == '0') {
                num.pop_back();
            }
            if(num.back() == '.') {
                num.push_back('0');
            }
        }
        return num;
    }
    
    template<typename T, template<typename>class DataSource>
    const std::string NumericToString(const GuardType<T, DataSource>& data) {
        return data.Id();
    }
    
    template<typename T, template<typename>class DataSource>
    std::string CalcString(const GuardType<T, DataSource>& data) {
        return data.CalcString();
    }
    
    template<typename T>
    std::string CalcString(T data) {
        return NumericToString(data);
    }
    
    template<typename U, typename V>
    const std::string PackWithBracket(const U& data1,
                                      const std::string& opStr,
                                      const V& data2) {
        std::string calcExpress;
        std::string data1CalcString = CalcString(data1);
        std::string data2CalcString = CalcString(data2);
        if(MinCalcPriorityOf(data1CalcString)
           < PriorityOfSymbol(opStr))
            calcExpress = "("+data1CalcString+")" + opStr;
        else
            calcExpress = data1CalcString + opStr;
        
        if(PriorityOfSymbol(opStr) >= MinCalcPriorityOf(data2CalcString))
            calcExpress += "("+data2CalcString+")";
        else
            calcExpress += data2CalcString;
        return calcExpress;
    }
    
    
    //---------------------------------------------------------------------------
    //                              InitWithCArray
    
    template<int D>
    struct InitWithCArray {
        template<typename T, int Demention, typename U, int N>
        static void Init(const GuardTypeArray<T, Demention>& gt, const U (&arr)[N]) {
            const_cast<size_t&>(gt.dementions[D]) = N;
            InitWithCArray<D-1>::Init(gt, arr[0]);
        }
    };
    
    template<>
    struct InitWithCArray<1> {
        template<typename T, int Demention, typename U, int N>
        static void Init(const GuardTypeArray<T, Demention>& gt, const U (&arr)[N]) {
            const_cast<size_t&>(gt.dementions[0]) = 1;
            const_cast<size_t&>(gt.dementions[1]) = N;
            const_cast<GuardTypeArray<T, Demention>&>(gt).array = const_cast<int*>(&arr[0]);
            const_cast<GuardTypeArray<T, Demention>&>(gt).InitDementions();
        }
    };
    
}

#endif /* TemplateTools_hpp */





#ifndef NumericProvider_hpp
#define NumericProvider_hpp


//--------------------------------------------------------------------------
//                            class NumericProvider

template<typename T>
class NumericProvider {
    template<typename U>
    friend class NumericProvider;
    
    TRACE_STRING_SAVE____(std::string id);
    T data;
public:
    
    NumericProvider(const char* id = GuardConfig::defaultId)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId(id)))
    data() {
    }
    
    template<typename U>
    NumericProvider(const U& data)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId()))
    data(data) {
    }
    
    template<typename U>
    NumericProvider(const NumericProvider<U>& data)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewIdByIncreaseId(data.id)))
    data(data.data) {
    }
    
    T& Data() const {
        return const_cast<T&>(data);
    }
    
    const std::string& Id() const {
        TRACE_STRING_SAVE____(return id);
        return GuardConfig::defaultIdStr;
    }
    
    void DataChangedCallBack() const {}
};

#endif /* NumericProvider_hpp */




#ifndef ArrayIndexProvider_hpp
#define ArrayIndexProvider_hpp

#include <iomanip>

template<typename T, int Demention>
class GuardTypeArray;

template<typename T, int Demention, int N>
class Ptr;

//--------------------------------------------------------------------------
//                            class ArrayIndexProvider

template<typename T, int Demention>
class ArrayIndexProvider {
    friend class Ptr<T, Demention, Demention>;
private:
    T* pos;
    GuardTypeArray<T, Demention> * array;
public:
    
    ArrayIndexProvider(const GuardTypeArray<T, Demention>& arr, size_t n) {
        this->array = &const_cast<GuardTypeArray<T, Demention>& >(arr);
        pos = arr.array;
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(Demention-1, n));
        pos += n * arr.dementions[Demention-1];
    }
    
    ArrayIndexProvider(const ArrayIndexProvider<T, Demention>& frontIndex, int N, size_t n) {
        this->array = frontIndex.array;
        pos = frontIndex.pos;
        OUT_OF_INDEX_DETECT__(this->OutOfIndexDetect(N, n));
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
    
    void DataChangedCallBack() const {
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
                if((p-array->array) % array->dementions[j] == 0) {
                    GuardConfig::so << std::endl;
                }
            }
        }
    }
    
    void OutOfIndexDetect(int N, size_t n) {
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
};

#endif /* ArrayIndexProvider_hpp */




#ifndef GuardType_hpp
#define GuardType_hpp

//#include "Tools.h"
//#include "TemplateTools.hpp"
//#include "GuardConfig.h"
//#include "ArrayIndexProvider.hpp"
//#include "NumericProvider.hpp"
//#include <set>
#include <functional>

template<typename T, int Demention, int N>
class Ptr;

//--------------------------------------------------------------------------
//                            class GuardType

template<typename T, template<typename>class DataSource>
class GuardType {
protected:
    
    template<typename U, template<typename>class DataSource2>
    friend class GuardType;
    template<typename U, int Demention>
    friend class GuardTypeArray;
    
public:
    typedef T value_type;
    
public:
    VALUE_CHANGED_DO_____(std::function<void(T& data)> ValueChangedDoing);
    
    VALUE_BE_READED_DO___(std::function<void(const T& data)> ValueBeReadedDoing);
    
    OLD_TO_NEW_VALUE_DO__(std::function<void(const T oldValue, T& newValue)> ValueChangedDoingWithOldAndNewValue);
    
    TRACE_STRING_SAVE____(std::string  calcExpres);
protected:
    DataSource<T> p;
    
    
public:
    
    friend void swap(const GuardType& gt, const GuardType& gt2) {
        T& r1 = gt.p.Data();
        T& r2 = gt2.p.Data();
        T temp = r1;
        r1 = r2;
        r2 = temp;
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ");
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << "swap(");
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << gt.p.Id() << ", ");
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << gt2.p.Id() << ")" << std::endl);
    }
    
    friend std::istream& operator >> (std::istream &si, GuardType<T, DataSource>& gt)
    {
        if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
            if(typeid(si) == typeid(std::cin)) {
                std::cout << "Please input Data ";
                std::cout << gt.p.Id();
                std::cout << ": ";
            }
        }
        si >> gt.p.Data();
        //if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return si;
        //if(GuardConfig::rule[">>"] == true) {
        //    std::cout<< _SPACES << "TRACE: si >> ";
        //    std::cout<< gt.p.Id();
        //    std::cout<< " = " << gt.p.Data() << std::endl;
        //}
        gt.p.DataChangedCallBack();
        return si;
    }
    
    friend std::ostream& operator << (std::ostream & so, const GuardType<T, DataSource>& gt)
    {
        OUTPUT_TRACE_SWITCH__(
                              if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return so << gt.p.Data();
                              if(GuardConfig::rule["<<"] == false) return so << gt.p.Data();
                              so << _SPACES << "TRACE: so<< " ;
                              so << gt.p.Id();
                              so << " : " << gt.p.Data() << std::endl;)
        return so << gt.p.Data();
    }
    
    
    
#define FRIEND_CALC_FUNC(op)                                                        \
friend const GuardType<T, NumericProvider>                                          \
operator op (const T & data, const GuardType<T, DataSource>& g2) {                  \
    T result(data op g2.p.Data());                                                  \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(data, #op, g2, result));                    \
    VALUE_BE_READED_DO___(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.p.Data()));\
    GuardType<T, NumericProvider>ret(result, false);                                \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
    return ret;                                                                     \
}                                                                                   \
\
template<typename U>                                                                \
friend const GuardType<typename GT::LargerType<U, T>::value_type, NumericProvider>  \
operator op (const U & data, const GuardType<T, DataSource>& g2) {                  \
    typename GT::LargerType<U, T>::value_type result(data op g2.p.Data());          \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(data, #op, g2, result));                    \
    VALUE_BE_READED_DO___(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.p.Data()));\
    GuardType<typename GT::LargerType<U, T>::value_type, NumericProvider>ret(result, false);\
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
    return ret;                                                                     \
}
    
    FRIEND_CALC_FUNC(+)
    FRIEND_CALC_FUNC(-)
    FRIEND_CALC_FUNC(*)
    FRIEND_CALC_FUNC(/)
    FRIEND_CALC_FUNC(%)
    FRIEND_CALC_FUNC(^)
    FRIEND_CALC_FUNC(&)
    FRIEND_CALC_FUNC(|)
    FRIEND_CALC_FUNC(<<)
    FRIEND_CALC_FUNC(>>)
    
    
#define FRIEND_BOOL_FUNC(op)                                                        \
friend const GuardType<bool, NumericProvider>                                       \
operator op (const T & data, const GuardType<T, DataSource>& g2) {                  \
    bool result(data op g2.p.Data());                                               \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(data, #op, g2, result));                    \
    VALUE_BE_READED_DO___(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.p.Data()));\
    GuardType<bool, NumericProvider>ret(result, false);                             \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
    return ret;                                                                     \
}                                                                                   \
\
template<typename U>                                                                \
friend const GuardType<bool, NumericProvider>                                       \
operator op (const U & data, const GuardType<T, DataSource>& g2) {                  \
    bool result(data op g2.p.Data());                                               \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(data, #op, g2, result));                    \
    VALUE_BE_READED_DO___(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.p.Data()));\
    GuardType<bool, NumericProvider>ret(result, false);                             \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
    return ret;                                                                     \
}
    
    FRIEND_BOOL_FUNC(&&)
    FRIEND_BOOL_FUNC(||)
    FRIEND_BOOL_FUNC(<)
    FRIEND_BOOL_FUNC(>)
    FRIEND_BOOL_FUNC(<=)
    FRIEND_BOOL_FUNC(>=)
    FRIEND_BOOL_FUNC(==)
    FRIEND_BOOL_FUNC(!=)
    
    
#define FRIEND_ASSIGN_FUNC(assignOp, op)                                            \
friend const GuardType<T, NumericProvider>                                          \
operator assignOp (T & data, const GuardType<T, DataSource>& g2) {                  \
    OUTPUT_TRACE_SWITCH__(T reserveData = data);                                    \
    T result(data assignOp g2.p.Data());                                            \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(reserveData, #assignOp, g2, result));       \
    VALUE_BE_READED_DO___(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.p.Data()));\
    GuardType<T, NumericProvider>ret(result, false);                                \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
    return ret;                                                                     \
}\
\
template<typename U>                                                                \
friend const GuardType<typename GT::LargerType<U, T>::value_type, NumericProvider>  \
operator assignOp (U & data, const GuardType<T, DataSource>& g2) {                  \
    OUTPUT_TRACE_SWITCH__(U reserveData = data);                                    \
    typename GT::LargerType<U, T>::value_type result(data assignOp g2.p.Data());    \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(reserveData, #assignOp, g2, result));       \
    VALUE_BE_READED_DO___(if (g2.ValueBeReadedDoing != NULL) g2.ValueBeReadedDoing(g2.p.Data()));\
    GuardType<typename GT::LargerType<U, T>::value_type, NumericProvider>ret(result, false);\
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
    return ret;                                                                     \
}
    
    FRIEND_ASSIGN_FUNC(+=, +)
    FRIEND_ASSIGN_FUNC(-=, -)
    FRIEND_ASSIGN_FUNC(*=, *)
    FRIEND_ASSIGN_FUNC(/=, /)
    FRIEND_ASSIGN_FUNC(%=, %)
    FRIEND_ASSIGN_FUNC(^=, ^)
    FRIEND_ASSIGN_FUNC(&=, &)
    FRIEND_ASSIGN_FUNC(|=, |)
    FRIEND_ASSIGN_FUNC(<<=, <<)
    FRIEND_ASSIGN_FUNC(>>=, >>)
    
    
#define IMPLEMENT_CALC_FUNCTION(op)                                                 \
template<typename U>                                                                \
const GuardType<typename GT::LargerType<T, U>::value_type, NumericProvider>         \
operator op (const U& data) const {                                                 \
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    typename GT::LargerType<T, U>::value_type result(this->p.Data() op data);       \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<typename GT::LargerType<T, U>::value_type, NumericProvider>ret(result, false);\
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
}                                                                                   \
\
template<typename U>                                                                \
const GuardType<typename GT::LargerType<T, U>::value_type, NumericProvider>         \
operator op (const GuardType<U, DataSource>& data) const {                          \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    typename GT::LargerType<T, U>::value_type result(this->p.Data() op data.p.Data());\
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<typename GT::LargerType<T, U>::value_type, NumericProvider>ret(result, false);\
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
}                                                                                   \
\
template<typename U, template<typename>class DataSource2>                           \
const GuardType<typename GT::LargerType<T, U>::value_type, NumericProvider>         \
operator op (const GuardType<U, DataSource2>& data) const {                         \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    typename GT::LargerType<T, U>::value_type result(this->p.Data() op data.p.Data());\
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<typename GT::LargerType<T, U>::value_type, NumericProvider>ret(result, false);\
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
}                                                                                   \
\
const GuardType<T, NumericProvider>                                                 \
operator op (const GuardType& data) const {                                         \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    T result(this->p.Data() op data.p.Data());                                      \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<T, NumericProvider>ret(result, false);                                \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
}                                                                                   \
\
template<template<typename>class DataSource2>                                       \
const GuardType<T, NumericProvider>                                                 \
operator op (const GuardType<T, DataSource2>& data) const {                         \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    T result(this->p.Data() op data.p.Data());                                      \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<T, NumericProvider>ret(result, false);                                \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
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
    
    
#define IMPLEMENT_BOOL_FUNCTION(op)                                                 \
template<typename U>                                                                \
const GuardType<bool, NumericProvider>                                              \
operator op (const U& data) const {                                                 \
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    bool result(this->p.Data() op data);                                            \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<bool, NumericProvider>ret(result, false);                             \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
}                                                                                   \
\
template<typename U>                                                                \
const GuardType<bool, NumericProvider>                                              \
operator op (const GuardType<U, DataSource>& data) const {                          \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    bool result(this->p.Data() op data.p.Data());                                   \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<bool, NumericProvider>ret(result, false);                             \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;\
}\
\
template<typename U, template<typename>class DataSource2>\
const GuardType<bool, NumericProvider>\
operator op (const GuardType<U, DataSource2>& data) const {                         \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    bool result(this->p.Data() op data.p.Data());                                   \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<bool, NumericProvider>ret(result, false);                             \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
}                                                                                   \
\
const GuardType<bool, NumericProvider>                                              \
operator op (const GuardType& data) const {                                         \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    bool result(this->p.Data() op data.p.Data());                                   \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<bool, NumericProvider>ret(result, false);                             \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
}                                                                                   \
\
template<template<typename>class DataSource2>                                       \
const GuardType<bool, NumericProvider>                                              \
operator op (const GuardType<T, DataSource2>& data) const {                         \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL) this->ValueBeReadedDoing(this->p.Data()));\
    bool result(this->p.Data() op data.p.Data());                                   \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
    GuardType<bool, NumericProvider>ret(result, false);                             \
    TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
    return ret;                                                                     \
}

    IMPLEMENT_BOOL_FUNCTION(&&)
    IMPLEMENT_BOOL_FUNCTION(||)
    IMPLEMENT_BOOL_FUNCTION(<)
    IMPLEMENT_BOOL_FUNCTION(>)
    IMPLEMENT_BOOL_FUNCTION(<=)
    IMPLEMENT_BOOL_FUNCTION(>=)
    IMPLEMENT_BOOL_FUNCTION(==)
    IMPLEMENT_BOOL_FUNCTION(!=)
    
    
#define IMPLEMENT_ASSIGN_CALC_FUNCTION(assignOp, op)                                \
template<typename U>                                                                \
const GuardType & operator assignOp (const U& data) {                               \
    OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());                             \
    this->p.Data() assignOp data;                                                   \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #assignOp, data, this->p.Data()));   \
    TRACE_STRING_SAVE____(const_cast<std::string&>(this->calcExpres)                \
    = GT::PackWithBracket(*this, #op, data));                                       \
    OUTPUT_TRACE_SWITCH__(this->OutPutExpres());                                    \
    OUTPUT_TRACE_SWITCH__(this->p.DataChangedCallBack());                           \
    OLD_TO_NEW_VALUE_DO__                                                           \
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)                         \
    this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));           \
    VALUE_CHANGED_DO_____(if(this->ValueChangedDoing!= NULL)this->ValueChangedDoing(this->p.Data()));\
    return *this;                                                                   \
}                                                                                   \
\
template<typename U>                                                                \
const GuardType & operator assignOp (const GuardType<U, DataSource>& data) {        \
    OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());                             \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    this->p.Data() assignOp data.p.Data();                                          \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #assignOp, data, this->p.Data()));   \
    TRACE_STRING_SAVE____(const_cast<std::string&>(this->calcExpres)                \
    =  GT::PackWithBracket(*this, #op, data));                                      \
    OUTPUT_TRACE_SWITCH__(this->OutPutExpres());                                    \
    OUTPUT_TRACE_SWITCH__(this->p.DataChangedCallBack());                           \
    OLD_TO_NEW_VALUE_DO__                                                           \
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)                         \
    this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));           \
    VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->p.Data()));\
    return *this;                                                                   \
}                                                                                   \
\
template<typename U, template<typename>class DataSource2>                           \
const GuardType & operator assignOp (const GuardType<U, DataSource2>& data) {       \
    OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());                             \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    this->p.Data() assignOp data.p.Data();                                          \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #assignOp, data, this->p.Data()));   \
    TRACE_STRING_SAVE____(const_cast<std::string&>(this->calcExpres)                \
    =  GT::PackWithBracket(*this, #op, data));                                      \
    OUTPUT_TRACE_SWITCH__(this->OutPutExpres());                                    \
    OUTPUT_TRACE_SWITCH__(this->p.DataChangedCallBack());                           \
    OLD_TO_NEW_VALUE_DO__                                                           \
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)                         \
    this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));           \
    VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->p.Data()));\
    return *this;                                                                   \
}                                                                                   \
\
const GuardType & operator assignOp (const GuardType& data) {                       \
    OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());                             \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    this->p.Data() assignOp data.p.Data();                                          \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #assignOp, data, this->p.Data()));   \
    TRACE_STRING_SAVE____(const_cast<std::string&>(this->calcExpres)                \
    =  GT::PackWithBracket(*this, #op, data));                                      \
    OUTPUT_TRACE_SWITCH__(this->OutPutExpres());                                    \
    OUTPUT_TRACE_SWITCH__(this->p.DataChangedCallBack());                           \
    OLD_TO_NEW_VALUE_DO__                                                           \
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)                         \
    this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));           \
    VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->p.Data()));\
    return *this;                                                                   \
}                                                                                   \
\
template<template<typename>class DataSource2>                                       \
const GuardType & operator assignOp (const GuardType<T, DataSource2>& data) {       \
    OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());                             \
    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));\
    this->p.Data() assignOp data.p.Data();                                          \
    OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #assignOp, data, this->p.Data()));   \
    TRACE_STRING_SAVE____(const_cast<std::string&>(this->calcExpres)                \
    =  GT::PackWithBracket(*this, #op, data));                                      \
    OUTPUT_TRACE_SWITCH__(this->OutPutExpres());                                    \
    OUTPUT_TRACE_SWITCH__(this->p.DataChangedCallBack());                           \
    OLD_TO_NEW_VALUE_DO__                                                           \
    (if (this->ValueChangedDoingWithOldAndNewValue != NULL)                         \
    this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));           \
    VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL) this->ValueChangedDoing(this->p.Data()));\
    return *this;                                                                   \
}

    IMPLEMENT_ASSIGN_CALC_FUNCTION(+=, +)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(-=, -)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(*=, *)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(/=, /)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(%=, %)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(^=, ^)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(&=, &)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(|=, |)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(<<=, <<)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(>>=, >>)
    
    
    
    GuardType(const char* id = GuardConfig::defaultId)
    :p(id)
    {
    }
    
    template<typename U>
    GuardType(const U& data)
    :p(data)
    {
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));
    }
    
    GuardType(const GuardType& data)
    :p(data.p)
    {
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    template<template<typename>class DataSource2>
    GuardType(const GuardType<T, DataSource2>& data)
    :p(data.p)
    {
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    template<typename U>
    GuardType(const GuardType<U, DataSource>& data)
    :p(data.p)
    {
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(const GuardType<U, DataSource2>& data)
    :p(data.p)
    {
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    template<typename U>
    GuardType(const U& data, bool OutPutOpTrace)
    :p(data)
    {
        OUTPUT_TRACE_SWITCH__(if(OutPutOpTrace) this->TraceAssignWithT(data));
    }
    
    template<typename U>
    GuardType(const NumericProvider<U>& data)
    :p(data)
    {
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString());
    }
    
    template<typename U, int Demention>
    GuardType(const ArrayIndexProvider<U, Demention>& data)
    :p(data)
    {
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString());
    }
    
    // Do not use this
    //T* operator &() {
    //    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));
    //    return &this->p.Data();
    //}
    //
    //const T* operator &()const {
    //    VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL) data.ValueBeReadedDoing(data.p.Data()));
    //    return &this->p.Data();
    //}
    
    template<typename U>
    const GuardType& operator = (const U& data) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data;
        TRACE_STRING_SAVE____(this->calcExpres = "");
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return *this;
    }
    
    const GuardType& operator = (const GuardType& data) {
        VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL)
                              data.ValueBeReadedDoing(data.p.Data()));
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data.p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return *this;
    }
    
    template<template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<T, DataSource2>& data) {
        VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL)
                              data.ValueBeReadedDoing(data.p.Data()));
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data.p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return *this;
    }
    
    template<typename U>
    const GuardType& operator = (const GuardType<U, DataSource>& data) {
        VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL)
                              data.ValueBeReadedDoing(data.p.Data()));
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data.p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<U, DataSource2>& data) {
        VALUE_BE_READED_DO___(if (data.ValueBeReadedDoing != NULL)
                              data.ValueBeReadedDoing(data.p.Data()));
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data.p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return *this;
    }
    
    operator const T& () const {
        VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL)
                              this->ValueBeReadedDoing(this->p.Data()));
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_TRACE_READ_SWITCH == false) return this->p.Data());
        OUTPUT_TRACE_SWITCH__(this->TraceReadGuardType("", *this));
        return this->p.Data();
    }
    
    const T* operator -> () const {
        return &this->p.Data();
    }
    
    T* operator -> () {
        return &this->p.Data();
    }
    
    const GuardType<T, NumericProvider> operator ! () const {
        VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL)
                              this->ValueBeReadedDoing(this->p.Data()));
        OUTPUT_TRACE_SWITCH__(this->TraceReadGuardType("!", GuardType<T, NumericProvider>(!this->p.Data(), false)));
        GuardType<T, NumericProvider> ret(!this->p.Data(), false);
        TRACE_STRING_SAVE____(ret.calcExpres = "!("+this->CalcString()+")");
        return ret;
    }
    
    const GuardType<T, NumericProvider> operator ~ () const {
        VALUE_BE_READED_DO___(if (this->ValueBeReadedDoing != NULL)
                              this->ValueBeReadedDoing(this->p.Data()));
        OUTPUT_TRACE_SWITCH__(this->TraceReadGuardType("~", GuardType<T, NumericProvider>(~this->p.Data(), false)));
        GuardType<T, NumericProvider>ret(~this->p.Data(), false);
        TRACE_STRING_SAVE____(ret.calcExpres = "~("+this->CalcString()+")");
        return ret;
    }
    
    const GuardType& operator ++() {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        ++this->p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString()+"+1");
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("++", *this, ""));
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return *this;
    }
    
    const GuardType<T, NumericProvider> operator ++(int) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "++"));
        GuardType<T, NumericProvider> result(this->p.Data(), false);
        TRACE_STRING_SAVE____(result.calcExpres = this->CalcString());
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString()+"+1");
        (this->p.Data())++;
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return result;
    }
    
    const GuardType& operator --() {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        --this->p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString()+"-1");
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("--", *this, ""));
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return *this;
    }
    
    const GuardType<T, NumericProvider> operator --(int) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "--"));
        GuardType<T, NumericProvider> result(this->p.Data(), false);
        TRACE_STRING_SAVE____(result.calcExpres = this->CalcString());
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString()+"-1");
        (this->p.Data())--;
        OLD_TO_NEW_VALUE_DO__\
        (if (this->ValueChangedDoingWithOldAndNewValue != NULL)
         this->ValueChangedDoingWithOldAndNewValue(oldValue, this->p.Data()));
        VALUE_CHANGED_DO_____(if (this->ValueChangedDoing != NULL)
                              this->ValueChangedDoing(this->p.Data()));
        return result;
    }
    
    const std::string Id() const {
        return this->p.Id();
    }
    
    void OutPutExpres() const {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) GuardConfig::so
            << _SPACES << "EXPRES:"
            << this->p.Id() << " = "
            << this->CalcString() << std::endl;
    }
    
    template<typename U, typename V, typename W>
    static void OutPutOpTrace(const U& data1,
                              const std::string& op,
                              const V& data2,
                              const W& result)
    {
        if(GuardConfig::_OUTPUT_TRACE_SWITCH == false || GuardConfig::rule[op] == false) return;
        GuardConfig::so << _SPACES << "TRACE: ";
        GuardConfig::so << GT::NumericToString(data1);
        GuardConfig::so << " " << op << " ";
        GuardConfig::so << GT::NumericToString(data2);
        if(op != "=") {
            GuardConfig::so << " = ";
            GuardConfig::so << result;
        }
        GuardConfig::so << std::endl;
    }
    
    template<typename U, template<typename>class DataSource2>
    void TraceReadGuardType(const std::string& op,
                            const GuardType<U, DataSource2>& result) const
    {
        if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return;
        if(GuardConfig::rule[op] == false) return;
        GuardConfig::so << _SPACES << "TRACE: ";
        GuardConfig::so << op;
        GuardConfig::so << this->p.Id();
        GuardConfig::so << " : ";
        GuardConfig::so << result.p.Data() <<std::endl;
    }
    
    template<typename U, template<typename>class DataSource2>
    void TraceSelfIncrease(const std::string& frontOp,
                           const GuardType<U, DataSource2>& result,
                           const std::string& backOp) const
    {
        if(frontOp+backOp == "" && GuardConfig::rule["="] == false) return;
        if(frontOp+backOp != "" && GuardConfig::rule[frontOp+backOp] == false) return;
        if(GuardConfig::_OUTPUT_TRACE_SWITCH == true) {
            GuardConfig::so << _SPACES << "TRACE: ";
            GuardConfig::so << frontOp;
            GuardConfig::so << this->p.Id();
            GuardConfig::so << backOp << " = ";
            GuardConfig::so << result.p.Data() << std::endl;
        }
        if(backOp == "") {
            this->OutPutExpres();
            this->p.DataChangedCallBack();
        }
    }
    
    template<typename U>
    void TraceAssignWithT(const U& result) const
    {
        OutPutOpTrace(*this, "=", result, result);
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH
           && GuardConfig::rule["="] == true) GuardConfig::so
            << _SPACES << "EXPRES:"
            << this->p.Id() << " = "
            << GT::NumericToString(result) << std::endl;
        this->p.DataChangedCallBack();
    }
    
    template<typename U, template<typename>class DataSource2>
    void TraceAssignWithGT(const GuardType<U, DataSource2>& data) const
    {
        OutPutOpTrace(*this, "=", data, data.p.Data());
        this->OutPutExpres();
        this->p.DataChangedCallBack();
    }
    
    const std::string CalcString() const {
        TRACE_STRING_SAVE____(if(this->calcExpres != "") return calcExpres);
        
        if(GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
            return this->p.Id();
        } else {
            return GT::NumericToString(this->p.Data());
        }
    }
    
};

#endif /* GuardType_hpp */




#ifndef Ptr_hpp
#define Ptr_hpp

//#include "GuardType.hpp"

template<typename T, int Demention>
class ArrayIndexProvider;

template<typename T, int Demention>
class GuardTypeArray;

//--------------------------------------------------------------------------
//                            class Ptr

template<typename T, int Demention>
class Ptr<T, Demention, 1> {
public:
    template<typename U>
    class ArrayIndexProviderN : public ArrayIndexProvider<U,Demention> {
    public:
        ArrayIndexProviderN(const ArrayIndexProvider<U, Demention>& p)
        : ArrayIndexProvider<U,Demention>(p) {
        }
        
        ArrayIndexProviderN(const GuardTypeArray<T, Demention>& arr, size_t n)
        : ArrayIndexProvider<U,Demention>(arr, n) {
        }
        
        ArrayIndexProviderN(const ArrayIndexProvider<T, Demention>& frontIndex, int N, size_t n)
        : ArrayIndexProvider<U,Demention>(frontIndex, N, n) {
        }
    };
    
    typedef std::random_access_iterator_tag     iterator_category;
    typedef GuardType<T, ArrayIndexProviderN>   value_type;
    typedef size_t                              difference_type;
    typedef Ptr                                 pointer;
    typedef GuardType<T, ArrayIndexProviderN>   reference;
private:
    Ptr();
protected:
    ArrayIndexProvider<T, Demention> data;
public:
    
    Ptr(const ArrayIndexProvider<T, Demention>& index, size_t n)
    : data(index, 1-1, n){
    }
    
    Ptr(const GuardTypeArray<T, 2>& arr, size_t n)
    : data(arr, n) {
    }
    
    Ptr(const Ptr& ptr)
    : data(ptr.data, 0, 0) {
    }
    
    GuardType<T, ArrayIndexProviderN> operator [] (size_t m) {
        return GuardType<T, ArrayIndexProviderN>(ArrayIndexProvider<T, Demention>(this->data, 0, m));
    }
    
    const GuardType<T, ArrayIndexProviderN> operator [] (size_t m) const {
        return GuardType<T, ArrayIndexProviderN>(ArrayIndexProvider<T, Demention>(this->data, 0, m));
    }
    
    const Ptr<T, Demention, 1>& operator = (const Ptr<T, Demention, 1>& ptr) {
        this->data.pos = ptr.data.pos;
        this->data.array = ptr.data.array;
        return *this;
    }
    
    GuardType<T, ArrayIndexProviderN> operator * () {
        return GuardType<T, ArrayIndexProviderN>(ArrayIndexProvider<T, Demention>(this->data, 0, 0));
    }
    
    const GuardType<T, ArrayIndexProviderN> operator * () const {
        return GuardType<T, ArrayIndexProviderN>(ArrayIndexProvider<T, Demention>(this->data, 0, 0));
    }
    
    operator const T* () const {
        return this->data.pos;
    }
    
    bool operator < (const Ptr<T, Demention, 1>& ptr) const {
        return this->data.pos < ptr.data.pos;
    }
    
    bool operator <= (const Ptr<T, Demention, 1>& ptr) const {
        return this->data.pos <= ptr.data.pos;
    }
    
    bool operator > (const Ptr<T, Demention, 1>& ptr) const {
        return this->data.pos > ptr.data.pos;
    }
    
    bool operator >= (const Ptr<T, Demention, 1>& ptr) const {
        return this->data.pos >= ptr.data.pos;
    }
    
    bool operator == (const Ptr<T, Demention, 1>& ptr) const {
        return this->data.pos == ptr.data.pos;
    }
    
    bool operator != (const Ptr<T, Demention, 1>& ptr) const {
        return this->data.pos != ptr.data.pos;
    }
    
    bool operator == (const T* ptr) const {
        return this->data.pos == ptr;
    }
    
    bool operator != (const T* ptr) const {
        return this->data.pos != ptr;
    }
    
    Ptr<T, Demention, 1> operator + (size_t i) const {
        return Ptr<T, Demention, 1>(this->data, i);
    }
    
    Ptr<T, Demention, 1> operator - (size_t i) const {
        return Ptr<T, Demention, 1>(this->data, -1*i);
    }
    
    Ptr<T, Demention, 1>&operator += (size_t i) {
        Ptr<T, Demention, 1>(this->data, i);
        this->data.pos += i;
        return *this;
    }
    
    Ptr<T, Demention, 1>&operator -= (size_t i) {
        Ptr<T, Demention, 1>(this->data, -1*i);
        this->data.pos -= i;
        return *this;
    }
    
    Ptr<T, Demention, 1>&operator ++ () {
        Ptr<T, Demention, 1>(this->data, 1);
        this->data.pos += 1;
        return *this;
    }
    
    Ptr<T, Demention, 1> operator ++ (int) {
        Ptr<T, Demention, 1> ret(this->data, 1);
        this->data.pos += 1;
        return ret;
    }
    
    Ptr<T, Demention, 1>& operator -- () {
        Ptr<T, Demention, 1>(this->data, -1);
        this->data.pos -= 1;
        return *this;
    }
    
    Ptr<T, Demention, 1> operator -- (int) {
        Ptr<T, Demention, 1> ret(this->data, -1);
        this->data.pos -= 1;
        return ret;
    }
    
    size_t operator - (const Ptr<T, Demention, 1>& ptr) const {
        return this->data.pos-ptr.data.pos;
    }
};

#endif /* Ptr_hpp */






#ifndef PtrN_hpp
#define PtrN_hpp

//#include "GuardType.hpp"
//#include "Ptr.hpp"

template<typename T, int Demention>
class ArrayIndexProvider;

template<typename T, int Demention>
class GuardTypeArray;

//--------------------------------------------------------------------------
//                            class Ptr

template<typename T, int Demention, int PtrN>
class Ptr {
private:
    Ptr();
protected:
    ArrayIndexProvider<T, Demention> data;
    
public:
    Ptr(const ArrayIndexProvider<T, Demention>& index, size_t n)
    : data(index, PtrN, n){
    }
    
    Ptr(const GuardTypeArray<T, Demention>& arr, size_t n)
    : data(arr, n){
    }
    
    Ptr<T, Demention, PtrN-1> operator [] (size_t m) {
        return Ptr<T, Demention, PtrN-1>(this->data, m);
    }
    
    const Ptr<T, Demention, PtrN-1> operator [] (size_t m) const {
        return Ptr<T, Demention, PtrN-1>(this->data, m);
    }
    
    Ptr<T, Demention, PtrN-1> operator * () {
        return Ptr<T, Demention, PtrN-1>(this->data, 0);
    }
    
    const Ptr<T, Demention, PtrN-1> operator * () const {
        return Ptr<T, Demention, PtrN-1>(this->data, 0);
    }
    
    const Ptr<T, Demention, PtrN>& operator = (const Ptr<T, Demention, PtrN>& ptr) {
        this->data.pos = ptr.data.pos;
        this->data.array = ptr.data.array;
        return *this;
    }
};

#endif /* PtrN_hpp */




#ifndef GuardTypeArray_hpp
#define GuardTypeArray_hpp

#include <iostream>
#include <iomanip>
//#include "GuardType.hpp"
//#include "Ptr.hpp"
//#include "ArrayIndexProvider.hpp"

//-----------------------------------------------------------------------------
//                            class GuardTypeArray

template<typename T>
class GuardTypeArray<T, 1> {
public:
    template<typename U>
    class ArrayIndexProviderN : public ArrayIndexProvider<U,1> {
    public:
        ArrayIndexProviderN(const ArrayIndexProvider<U, 1>& p)
        : ArrayIndexProvider<U,1>(p) {
        }
        
        ArrayIndexProviderN(const GuardTypeArray<T, 1>& arr, size_t n)
        : ArrayIndexProvider<U,1>(arr, n) {
        }
        
        ArrayIndexProviderN(const ArrayIndexProvider<T, 1>& frontIndex, int N, size_t n)
        : ArrayIndexProvider<U,1>(frontIndex, N, n) {
        }
    };
    
    typedef Ptr<T, 1, 1>                        iterator;
    typedef GuardType<T, ArrayIndexProviderN>   value_type;
    friend class ArrayIndexProvider<T, 1>;
    friend class Ptr<T, 1, 1>;
    
private:
    GuardTypeArray();
private:
    size_t dementions[2];
protected:
    T*   array;
    bool isAlloc;
public:
    std::string id;
    
public:
    ~GuardTypeArray() {
        if(isAlloc) {
            delete[] this->array;
        }
    }
    
    GuardTypeArray(const GuardTypeArray<T, 1>& gt)
    : id(GT::GetNewIdByIncreaseId(gt.id)), isAlloc(true)
    {
        size_t elementCount = this->dementions[1] = gt.dementions[1];
        this->dementions[0] = 1;
        array = new T[elementCount];
        T* begin = array;
        T* end = begin + elementCount;
        for(T* iter=begin; iter!=end; iter++) {
            new(iter) T();
        }
    }
    
    GuardTypeArray(size_t n, const char* id = GuardConfig::defaultId)
    : id(GT::GetNewId(id)), array(new T[n]), isAlloc(true)
    {
        assert( n>0);
        this->dementions[0] = 1;
        this->dementions[1] = n;
        T* begin = this->array;
        T* end = begin + n;
        for(T* iter=begin; iter!=end; iter++) {
            new(iter) T();
        }
    }
    
    //template<typename T>
    //template<int N, typename U>
    //GuardTypeArray<T, 1>::GuardTypeArray(const U (&pArr)[N], const std::string& id)
    //: id(GT::GetNewId(id)), array(new T[N]), isAlloc(true)
    //{
    //    for(int i=0; i<N; i++) {
    //        array[i] = pArr[i];
    //    }
    //}
    
    template<int N, typename U>
    GuardTypeArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    : id(id), isAlloc(false)
    {
        this->dementions[0] = 1;
        this->dementions[1] = N;
        this->array = const_cast<int*>(&pArr[0]);
        this->isAlloc = false;
    }
    
    template<int N, typename U>
    GuardTypeArray(bool isReferenceFromArray, const U (&pArr)[N])
    : id(GT::GetNewId()) {
        this->dementions[0] = 1;
        this->dementions[1] = N;
        if(isReferenceFromArray == false) {
            this->array = new T[N];
            this->isAlloc = true;
            for(int i=0; i<N; i++) {
                this->array[i] = pArr[i];
            }
        } else {
            this->array = const_cast<int*>(&pArr[0]);
            this->isAlloc = false;
        }
    }
    
    size_t size() const {
        return this->dementions[1];
    }
    
    size_t length() const {
        return this->dementions[1];
    }
    
    Ptr<T, 1, 1> begin() const  {
        return Ptr<T, 1, 1>(ArrayIndexProvider<T, 1>(*this, 0), 0);
    }
    
    Ptr<T, 1, 1> end() const  {
        return Ptr<T, 1, 1>(ArrayIndexProvider<T, 1>(*this, this->dementions[1]), 0);
    }
    
    GuardType<T, ArrayIndexProviderN> operator [] (size_t n) {
        return GuardType<T, ArrayIndexProviderN>(ArrayIndexProvider<T, 1>(*this, n));
    }
    
    const GuardType<T, ArrayIndexProviderN> operator [] (size_t n) const {
        return GuardType<T, ArrayIndexProviderN>(ArrayIndexProvider<T, 1>(*this, n));
    }
    
    operator const Ptr<T, 1, 1> () {
        return Ptr<T, 1, 1>(ArrayIndexProvider<T, 1>(*this, 0), 0);
    }
    
    bool operator == (const GuardTypeArray<T, 1>& gt) const {
        return this->array == gt.array;
    }
    
    bool operator != (const GuardTypeArray<T, 1>& gt) const {
        return this->array != gt.array;
    }
    
    bool operator == (const Ptr<T, 1, 1>& ptr) const {
        return this->array == ptr.pos;
    }
    
    bool operator < (const Ptr<T, 1, 1>& ptr) const {
        return this->array < ptr.pos;
    }
    
    bool operator <= (const Ptr<T, 1, 1>& ptr) const {
        return this->array <= ptr.pos;
    }
    
    bool operator > (const Ptr<T, 1, 1>& ptr) const {
        return this->array > ptr.pos;
    }
    
    bool operator >= (const Ptr<T, 1, 1>& ptr) const {
        return this->array >= ptr.pos;
    }
    
    bool operator != (const Ptr<T, 1, 1>& ptr) const {
        return this->array != ptr.pos;
    }
    
    template<typename U>
    Ptr<T, 1, 1> operator + (U n) {
        return Ptr<T, 1, 1>(*this, n);
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
        T* p = gt.array;
        for (int i=0; i<gt.size(); i++) {
            so << std::setw(GuardConfig::_ARRAY_OUT_PUT_INTERVAL)
            << " " << *(p+i) << " ";
        }
        so << std::endl << std::endl;
        return so;
    }
};

#endif /* GuardTypeArray_hpp */





#ifndef GuardTypeArrayN_hpp
#define GuardTypeArrayN_hpp

#include <iostream>
#include <iomanip>
//#include "GuardType.hpp"
//#include "PtrN.hpp"
//#include "GuardTypeArray.hpp"

//---------------------------------------------------------------------------
//                            class GuardTypeArray

template<typename T, int Demention>
class GuardTypeArray {
public:
    friend class ArrayIndexProvider<T, Demention>;
    
    friend class Ptr<T, Demention, Demention>;
    
    template<int D>
    friend struct GT::InitWithCArray;
    
private:
    GuardTypeArray();
private:
    size_t dementions[Demention+1];
protected:
    T*   array;
    bool isAlloc;
public:
    std::string id;
    
public:
    ~GuardTypeArray() {
        if(this->isAlloc) {
            delete[] this->array;
        }
    }
    
    GuardTypeArray(const GuardTypeArray<T, Demention>& gt)
    : id(GT::GetNewIdByIncreaseId(gt.id)), isAlloc(true)
    {
        for (int i=0; i<Demention; i++) {
            this->dementions[i] = gt.dementions[i];
        }
        size_t elementCount = this->dementions[1];
        this->array = new T[elementCount];
        T* pSource = gt.array;
        for (int i=0; i<elementCount; i++) {
            *(this->array + i) = *(pSource + i);
        }
    }
    
    //template<int N, typename U>
    //GuardTypeArray(const U (&pArr)[N], const std::string& id)
    //: id(GT::GetNewId(id)), array(new T[N]), isAlloc(true)
    //{
    //    GT::InitWithCArray<Demention>::Init(*this, pArr);
    //}
    
    template<int N, typename U>
    GuardTypeArray(const U (&pArr)[N], const char* id = GuardConfig::defaultId)
    : id(GT::GetNewId(id)), isAlloc(false)
    {
        GT::InitWithCArray<Demention>::Init(*this, pArr);
    }
    
    template<int N, typename U>
    GuardTypeArray(bool isReferenceFromArray, const U (&pArr)[N])
    : id(GT::GetNewId()), isAlloc(isReferenceFromArray) {
        GT::InitWithCArray<Demention>::Init(*this, pArr);
    }
    
    template<typename ...Int>
    GuardTypeArray(size_t first, Int...n)
    : id(GT::GetNewId()), isAlloc(true)
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
        this->id = id;
        this->AllocWithDementions();
    }
    
    template<int N, typename ...V>
    void InitWithIndexs(size_t index) {
        static_assert(N == 1, "Array init with wrong index count");
        this->dementions[Demention] = index;
        this->id = GT::GetNewId();
        this->AllocWithDementions();
    }
    
    void AllocWithDementions() {
        this->dementions[0] = 1;
        for(int i = 0; i < Demention; i++) {
            this->dementions[i+1] *= this->dementions[i];
        }
        
        if(this->isAlloc == false) return;
        size_t allElement = this->dementions[Demention];
        this->array = new T[allElement];
        T* begin = this->array;
        T* end = begin + allElement;
        for(T* iter=begin; iter!=end; iter++) {
            new(iter) T();
        }
    }
    
    void InitDementions() {
        this->dementions[0] = 1;
        for(int i = 0; i < Demention; i++) {
            this->dementions[i+1] *= this->dementions[i];
        }
        
        if(this->isAlloc == false) return;
        size_t allElement = this->dementions[Demention];
        T* source = array;
        this->array = new T[allElement];
        T* begin = array;
        T* end = begin + allElement;
        for(T* iter=begin; iter!=end; iter++) {
            new(iter) T(*source++);
        }
    }
    
    size_t size() const {
        return this->dementions[Demention];
    }
    
    Ptr<T, Demention, Demention-1> operator [] (size_t n) {
        return Ptr<T, Demention, Demention-1>(*this, n);
    }
    
    const Ptr<T, Demention, Demention-1> operator [] (size_t n) const {
        return Ptr<T, Demention, Demention-1>(*this, n);
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




#ifndef gt_h
#define gt_h

//#include "GuardType.hpp"
//#include "GuardTypeArrayN.hpp"

//---------------------------------------------------------------------------
//                            Type Define

#define GT_TYPE(type, name)\
typedef GuardType<type, NumericProvider>        name;\
typedef Ptr<type, 1, 1>                         name##Ptr;\
typedef GuardTypeArray<type, 1>                 name##Arr;\
typedef GuardTypeArray<type, 2>                 name##Arr2;\
typedef GuardTypeArray<type, 3>                 name##Arr3;
// ...

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

#endif /* gt_h */
