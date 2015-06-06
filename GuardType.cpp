#ifndef GUARDTYPE_CPP
#define GUARDTYPE_CPP
#include <assert.h>
#include <set>
#include "GuardType.h"
#include "NumToString.h"

//----------------------------GuardType--------------------------------------------
//                         The members of GuardType::Ptr

template<typename T>
GuardType<T>::Ptr::Ptr()
: index(), pos(), gt()
{}

template<typename T>
GuardType<T>::Ptr::Ptr(const ArrayIndex& index, const T* pData, const GuardType<T>* gt)
: index(index) , pos((T*)pData), gt((GuardType<T>*)gt) {
    assert(pData != NULL);
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
        if(TIsDerived<U,GuardConfig>::result) {\
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
        if(TIsDerived<U,GuardConfig>::result) {\
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
        if(TIsDerived<U,GuardConfig>::result) {\
            typename LargerType<T, U>::value_type\
                result(*(this->pData) op *(((GuardType<U>&)data).pData));\
            if(GuardConfig::rule[#op] == false) return *this;\
            this->TraceOperateGTWithGT(#op, (GuardType<T>&)data, result);\
            return *this;\
        }\
        this->gt->index = this->index;\
        std::string thisCalc = this->CalcString();\
        if(thisCalc == "") thisCalc = NumToString::Transform(*(this->pData));\
        typename LargerType<T, U>::value_type result(*(this->pData) op data);\
        if(GuardConfig::rule[#op] == false) return *this;\
        std::string opName = #op;\
        if(IsAssignOp(opName)) opName.pop_back();\
            GuardType<T>::OutPutTrace(*this, #op, data, result);\
        const_cast<std::string&>(this->calc)\
            = GuardType<T>::PackWithBracket(thisCalc, opName, data);\
        this->OutPutExpresAndArray();\
        return *this;\
    }\
    \
    template<typename T>\
    template<typename U>\
    const GuardType<typename LargerType<T, U>::value_type> & \
    GuardType<T>::operator op (const GuardType<U>& data) {\
        this->gt->index = this->index;\
        std::string thisCalc = this->CalcString();\
        if(thisCalc == "") thisCalc = NumToString::Transform(*(this->pData));\
        typename LargerType<T, U>::value_type result(*(this->pData) op *(data.pData));\
        std::string opName = #op;\
        if(IsAssignOp(opName)) opName.pop_back();\
        GuardType<T>::OutPutTrace(*this, opName, data, result);\
        const_cast<std::string&>(this->calc)\
            =  GuardType<T>::PackWithBracket(thisCalc, opName, data);\
        this->OutPutExpresAndArray();\
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
    : id(GuardType::GetNewName(id)), index(), pData(&data), gt(this), data()
{ }

template<typename T>
GuardType<T>::GuardType(const std::string& id)
    : id(GuardType::GetNewName(id)), index(), pData(&data), gt(this), data()
{ }

template<typename T>
template<typename U>
GuardType<T>::GuardType(const U& data)
    : id(GuardType::GetNewName()), index(), pData(&this->data), gt(this), data(data)
{
    this->TraceWriteGuardType("", *this, "");
}

template<typename T>
GuardType<T>::GuardType(const GuardType<T>&      data)
: id(GuardType::GetNewNameByIncreaseId(data.id)), index(),  pData(&this->data), gt(this)
{
    T result(*(this->pData) = *(data.pData));
    this->calc = data.CalcString();
    TraceOperateGTWithGT("=", data, result);
}

template<typename T>
template<typename U>
GuardType<T>::GuardType(const GuardType<U>&        data)
    : id(GuardType::GetNewNameByIncreaseId(data.id)), index(),  pData(&this->data), gt(this)
{
    T result(*(this->pData) = *(data.pData));
    this->calc = data.CalcString();
    TraceOperateGTWithGT("=", data, result);
}

template<typename T>
template<typename U>
GuardType<T>::GuardType(const U& data, const std::string& calc, bool outPutTrace)
: id(GuardType::GetNewName()), index(), pData(&this->data), gt(this), calc(calc), data(data)
{
    if(outPutTrace == true)
        this->TraceWriteGuardType("", *this, "");
}

template<typename T>
template<typename U>
GuardType<T>::GuardType(const ArrayIndex& index, U* pData, const GuardType<U>* gt)
    : id("GT"), index(index), pData(pData), gt((GuardType<U>*)(gt))
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
void GuardType<T>::SetName(const std::string& id) {
    this->id = id;
}

template<typename T>
typename GuardType<T>::Ptr GuardType<T>::operator &() {
    return typename GuardType<T>::Ptr(this->index, pData, this->gt);
}

template<typename T>
const typename GuardType<T>::Ptr GuardType<T>::operator &() const {
    return typename GuardType<T>::Ptr(this->index, pData, this->gt);
}

template<typename T>
template<typename U>
const GuardType<T>& GuardType<T>::operator = (const U& data) {
    *(this->pData) = data;
    this->gt->index = this->index;
    this->calc = "";
    this->TraceWriteGuardType("", *this, "");
    return *this;
}

template<typename T>
const GuardType<T>& GuardType<T>::operator = (const GuardType<T>& data) {
    T result(*(this->pData) = *(data.pData));
    this->calc = data.CalcString();
    this->gt->index = this->index;
    TraceOperateGTWithGT("=", data, result);
    return *this;
}

template<typename T>
template<typename U>
const GuardType<T>& GuardType<T>::operator = (const GuardType<U>& data) {
    T result(*(this->pData) = *(data.pData));
    this->calc = data.CalcString();
    this->gt->index = this->index;
    TraceOperateGTWithGT("=", data, result);
    return *this;
}

template<typename T>
GuardType<T>::operator const T& () const {
    if(GuardConfig::_TRACE_READ_SWITCH == false)
        return *(this->pData);
    if(this->id != "") this->TraceReadGuardType("", *this);
    return *(this->pData);
}

template<typename T>
const GuardType<T> GuardType<T>::operator ! () const {
    this->TraceReadGuardType("!", GuardType<T>(!*(pData), ""));

    return GuardType<T>(!*(pData), "!("+this->CalcString()+")");
}

template<typename T>
const GuardType<T> GuardType<T>::operator ~ () const {
    this->TraceReadGuardType("~", GuardType<T>(~*(pData), ""));
    return GuardType<T>(~*(pData), "~("+this->CalcString()+")");
}

template<typename T>
const GuardType<T>& GuardType<T>::operator ++() {
    ++*(this->pData);
    this->gt->index = this->index;
    this->calc = this->CalcString()+"+1";
    this->TraceWriteGuardType("++", *this, "");
    return *this;
}

template<typename T>
const GuardType<T> GuardType<T>::operator ++(int) {
    this->gt->index = this->index;
    this->TraceWriteGuardType("", *this, "++");
    T result((*(this->pData))++);
    GuardType<T> returnResult(result, this->CalcString(), false);
    this->calc = this->CalcString()+"+1";
    return returnResult;
}

template<typename T>
const GuardType<T>& GuardType<T>::operator --() {
    --*(this->pData);
    this->gt->index = this->index;
    this->calc = this->CalcString()+"-1";
    this->TraceWriteGuardType("--", *this, "");
    return *this;
}

template<typename T>
const GuardType<T> GuardType<T>::operator --(int) {
    this->gt->index = this->index;
    this->TraceWriteGuardType("", *this, "--");
    T result((*(this->pData))--);
    GuardType<T> returnResult(result, this->CalcString(), false);
    this->calc = this->CalcString()+"-1";
    return returnResult;
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
                                            std::string opName,
                                            const V& data2) {
    std::string data1CalcString = GuardType<T>::ToString(data1);
    std::string data2CalcString = GuardType<T>::ToString(data2);
    std::string calcExpress;
    if(GuardType::MinCalcPriorityOf(data1CalcString)
       <= GuardType::PriorityOfSymbol(opName))
        calcExpress = "("+data1CalcString+")" + opName;
    else
        calcExpress = data1CalcString + opName;
    
    if(GuardType::PriorityOfSymbol(opName)
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
        const std::string&                  opName,
        const GuardType<U>&                 data,
        const T&                            value) const
{
    this->gt->index = this->index;
    if(GuardConfig::rule[opName] == false) return;
    if(!(IsAssignOp(opName) && data.id == "GT")) {
        GuardType<T>::OutPutTrace(*this, opName, data, value);
    }
    if(IsAssignOp(opName)) {
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
const std::string GuardType<T>::GetNewName(std::string id) {
    std::string  newName = id;
    if(id != "" && id != "GT") {
        while(!GuardConfig::idArray.empty())
            GuardConfig::idArray.pop();
        return id;
    } else if(id == "" || GuardConfig::idArray.empty()) {
        return "GT";
    } else {
        newName = GuardConfig::idArray.front();
        GuardConfig::idArray.pop();
    }
    return newName;
}

template<typename T>
const std::string GuardType<T>::GetNewNameByIncreaseId(std::string id) {
    std::string getName = GuardType<T>::GetNewName();
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

#endif //GUARDTYPE_CPP
