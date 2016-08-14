#ifndef GuardType_hpp
#define GuardType_hpp

#include "GuardConfig.hpp"
#include "Tools.hpp"
#include "TemplateTools.hpp"
#include "ArrayIndexProvider.hpp"
#include "NumericProvider.hpp"
#include <set>
#include <functional>
//--------------------------------------------------------------------------
//                            class GuardType

#define GT_VALUE_BE_READED_DO(gt)\
    VALUE_BE_READED_DO___(\
        if ((gt).ValueBeReadedDoing != NULL)\
            (gt).ValueBeReadedDoing((gt).p.Data()));

#define GT_VALUE_CHANGED_DO__(gt) \
    OLD_TO_NEW_VALUE_DO__(\
        if ((gt).ValueChangedDoingWithOldAndNewValue != NULL)\
            (gt).ValueChangedDoingWithOldAndNewValue(oldValue, (gt).p.Data()));\
    VALUE_CHANGED_DO_____(\
        if ((gt).ValueChangedDoing != NULL)\
            (gt).ValueChangedDoing((gt).p.Data()));


template<typename T, template<typename> class DataSource>
class GuardType {
protected:
    
    template<typename U, template<typename>class DataSource2>
    friend class GuardType;
    
    template<typename U, int D>
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
    
    friend std::istream& operator >> (std::istream &si, GuardType& gt)
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
        gt.p.OutPutArray();
        return si;
    }
    
    friend std::ostream& operator << (std::ostream & so, const GuardType& gt)
    {
        OUTPUT_TRACE_SWITCH__(
                              if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return so << gt.p.Data();
                              if(GuardConfig::rule["<<"] == false) return so << gt.p.Data();
                              so << _SPACES << "TRACE: so<< " ;
                              so << gt.p.Id();
                              so << " : " << gt.p.Data() << std::endl;)
        return so << gt.p.Data();
    }
    
    
    
#define FRIEND_CALC_FUNC(op, Type, CalcReturnType)                                      \
    friend const GuardType<typename GT::CalcReturnType<Type, T>::value_type>            \
    operator op (const Type & data, const GuardType& g2) {                              \
        typename GT::CalcReturnType<Type, T>::value_type result(data op g2.p.Data());   \
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(data, #op, g2, result));                    \
        GT_VALUE_BE_READED_DO(g2);                                                      \
        GuardType<typename GT::CalcReturnType<Type, T>::value_type>ret(result, false);  \
        TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
        return ret;                                                                     \
    }
    
#define Friend_CALC_FUNC_(Type)\
    FRIEND_CALC_FUNC(*, Type, ResultTypeMultiply)\
    FRIEND_CALC_FUNC(/, Type, ResultType)\
    FRIEND_CALC_FUNC(+, Type, ResultType)\
    FRIEND_CALC_FUNC(-, Type, ResultType)\
    FRIEND_CALC_FUNC(%, Type, ResultType)\
    FRIEND_CALC_FUNC(^, Type, ResultType)\
    FRIEND_CALC_FUNC(&, Type, ResultType)\
    FRIEND_CALC_FUNC(|, Type, ResultType)\
    FRIEND_CALC_FUNC(<<, Type, ResultType)\
    FRIEND_CALC_FUNC(>>, Type, ResultType)
    
    EXPAND_NUMERIC_MACRO(Friend_CALC_FUNC_)
    
#define FRIEND_BOOL_FUNC(op, Type)                                                      \
    friend const GuardType<bool>                                                        \
    operator op (const Type & data, const GuardType& g2) {                              \
        bool result(data op g2.p.Data());                                               \
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(data, #op, g2, result));                    \
        GT_VALUE_BE_READED_DO(g2);                                                      \
        GuardType<bool>ret(result, false);                                              \
        TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
        return ret;                                                                     \
    }
#define FRIEND_BOOL_FUNC_(Type)\
    FRIEND_BOOL_FUNC(&&, Type)\
    FRIEND_BOOL_FUNC(||, Type)\
    FRIEND_BOOL_FUNC(<, Type)\
    FRIEND_BOOL_FUNC(>, Type)\
    FRIEND_BOOL_FUNC(<=, Type)\
    FRIEND_BOOL_FUNC(>=, Type)\
    FRIEND_BOOL_FUNC(==, Type)\
    FRIEND_BOOL_FUNC(!=, Type)
    
    EXPAND_NUMERIC_MACRO(FRIEND_BOOL_FUNC_)
    
#define FRIEND_ASSIGN_FUNC(assignOp, op, Type)                                          \
    friend const GuardType<Type>                                                        \
    operator assignOp (Type & data, const GuardType& g2) {                              \
        OUTPUT_TRACE_SWITCH__(T reserveData = data);                                    \
        T result(data assignOp g2.p.Data());                                            \
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(reserveData, #assignOp, g2, result));       \
        GT_VALUE_BE_READED_DO(g2);                                                      \
        GuardType<Type>ret(result, false);                                              \
        TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(data, #op, g2));     \
        return ret;                                                                     \
    }
    
#define FRIEND_ASSIGN_FUNC_(Type)\
    FRIEND_ASSIGN_FUNC(*=, *, Type)\
    FRIEND_ASSIGN_FUNC(/=, /, Type)\
    FRIEND_ASSIGN_FUNC(+=, +, Type)\
    FRIEND_ASSIGN_FUNC(-=, -, Type)\
    FRIEND_ASSIGN_FUNC(%=, %, Type)\
    FRIEND_ASSIGN_FUNC(^=, ^, Type)\
    FRIEND_ASSIGN_FUNC(&=, &, Type)\
    FRIEND_ASSIGN_FUNC(|=, |, Type)\
    FRIEND_ASSIGN_FUNC(<<=, <<, Type)\
    FRIEND_ASSIGN_FUNC(>>=, >>, Type)
    
    EXPAND_NUMERIC_MACRO(FRIEND_ASSIGN_FUNC_)
    
#define IMPLEMENT_CALC_FUNCTION_N(op, Type, CalcReturnType)                             \
    const GuardType<typename GT::CalcReturnType<T, Type>::value_type>                   \
    operator op (const Type& data) const {                                              \
        GT_VALUE_BE_READED_DO(*this);                                                   \
        typename GT::CalcReturnType<T, Type>::value_type result(this->p.Data() op data);\
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
        GuardType<typename GT::CalcReturnType<T, Type>::value_type>ret(result, false);  \
        TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
        return ret;                                                                     \
    }                                                                                   \

#define IMPLEMENT_CALC_FUNCTION_N_(Type)\
    IMPLEMENT_CALC_FUNCTION_N(*, Type, ResultTypeMultiply)\
    IMPLEMENT_CALC_FUNCTION_N(/, Type, ResultType)\
    IMPLEMENT_CALC_FUNCTION_N(+, Type, ResultType)\
    IMPLEMENT_CALC_FUNCTION_N(-, Type, ResultType)\
    IMPLEMENT_CALC_FUNCTION_N(%, Type, ResultType)\
    IMPLEMENT_CALC_FUNCTION_N(^, Type, ResultType)\
    IMPLEMENT_CALC_FUNCTION_N(&, Type, ResultType)\
    IMPLEMENT_CALC_FUNCTION_N(|, Type, ResultType)\
    IMPLEMENT_CALC_FUNCTION_N(<<, Type, ResultType)\
    IMPLEMENT_CALC_FUNCTION_N(>>, Type, ResultType)
    
    EXPAND_NUMERIC_MACRO(IMPLEMENT_CALC_FUNCTION_N_)
    
#define IMPLEMENT_CALC_FUNCTION(op, CalcReturnType)                                     \
    template<typename U, template<typename>class DataSource2>                           \
    const GuardType<typename GT::CalcReturnType<T, U>::value_type>                      \
    operator op (const GuardType<U, DataSource2>& data) const {                         \
        GT_VALUE_BE_READED_DO(data);                                                    \
        GT_VALUE_BE_READED_DO(*this);                                                   \
        typename GT::CalcReturnType<T, U>::value_type result(this->p.Data() op data.p.Data());\
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
        GuardType<typename GT::CalcReturnType<T, U>::value_type>ret(result, false);     \
        TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
        return ret;                                                                     \
    }
    
    IMPLEMENT_CALC_FUNCTION(*, ResultTypeMultiply)
    IMPLEMENT_CALC_FUNCTION(/, ResultType)
    IMPLEMENT_CALC_FUNCTION(+, ResultType)
    IMPLEMENT_CALC_FUNCTION(-, ResultType)
    IMPLEMENT_CALC_FUNCTION(%, ResultType)
    IMPLEMENT_CALC_FUNCTION(^, ResultType)
    IMPLEMENT_CALC_FUNCTION(&, ResultType)
    IMPLEMENT_CALC_FUNCTION(|, ResultType)
    IMPLEMENT_CALC_FUNCTION(<<, ResultType)
    IMPLEMENT_CALC_FUNCTION(>>, ResultType)
    
    
#define IMPLEMENT_BOOL_FUNCTION_N(op, Type)                                             \
    const GuardType<bool>                                                               \
    operator op (const Type& data) const {                                              \
        GT_VALUE_BE_READED_DO(*this);                                                   \
        bool result(this->p.Data() op data);                                            \
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
        GuardType<bool>ret(result, false);                                              \
        TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
        return ret;                                                                     \
    }                                                                                   \

#define IMPLEMENT_BOOL_FUNCTION_N_(Type)\
    IMPLEMENT_BOOL_FUNCTION_N(&&, Type)\
    IMPLEMENT_BOOL_FUNCTION_N(||, Type)\
    IMPLEMENT_BOOL_FUNCTION_N(<, Type)\
    IMPLEMENT_BOOL_FUNCTION_N(>, Type)\
    IMPLEMENT_BOOL_FUNCTION_N(<=, Type)\
    IMPLEMENT_BOOL_FUNCTION_N(>=, Type)\
    IMPLEMENT_BOOL_FUNCTION_N(==, Type)\
    IMPLEMENT_BOOL_FUNCTION_N(!=, Type)
    
    EXPAND_NUMERIC_MACRO(IMPLEMENT_BOOL_FUNCTION_N_)
    
#define IMPLEMENT_BOOL_FUNCTION(op)                                                     \
    template<typename U, template<typename>class DataSource2>                           \
    const GuardType<bool>                                                               \
    operator op (const GuardType<U, DataSource2>& data) const {                         \
        GT_VALUE_BE_READED_DO(data);                                                    \
        GT_VALUE_BE_READED_DO(*this);                                                   \
        bool result(this->p.Data() op data.p.Data());                                   \
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #op, data, result));                 \
        GuardType<bool>ret(result, false);                                              \
        TRACE_STRING_SAVE____(ret.calcExpres = GT::PackWithBracket(*this, #op, data));  \
        return ret;                                                                     \
    }                                                                                   \

    IMPLEMENT_BOOL_FUNCTION(&&)
    IMPLEMENT_BOOL_FUNCTION(||)
    IMPLEMENT_BOOL_FUNCTION(<)
    IMPLEMENT_BOOL_FUNCTION(>)
    IMPLEMENT_BOOL_FUNCTION(<=)
    IMPLEMENT_BOOL_FUNCTION(>=)
    IMPLEMENT_BOOL_FUNCTION(==)
    IMPLEMENT_BOOL_FUNCTION(!=)
    
    
#define IMPLEMENT_ASSIGN_CALC_FUNCTION_N(assignOp, op, Type)                            \
    const GuardType & operator assignOp (const Type& data) {                            \
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());                             \
        this->p.Data() assignOp data;                                                   \
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #assignOp, data, this->p.Data()));   \
        TRACE_STRING_SAVE____(const_cast<std::string&>(this->calcExpres)                \
                              = GT::PackWithBracket(*this, #op, data));                 \
        OUTPUT_TRACE_SWITCH__(this->OutPutExpres());                                    \
        OUTPUT_TRACE_SWITCH__(this->p.OutPutArray());                                   \
        GT_VALUE_CHANGED_DO__(*this);                                                   \
        return *this;                                                                   \
    }                                                                                   \
    
#define IMPLEMENT_ASSIGN_CALC_FUNCTION_N_(Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(*=, *, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(/=, /, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(+=, +, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(-=, -, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(%=, %, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(^=, ^, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(&=, &, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(|=, |, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(<<=, <<, Type)\
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(>>=, >>, Type)
    
    EXPAND_NUMERIC_MACRO(IMPLEMENT_ASSIGN_CALC_FUNCTION_N_)
    
#define IMPLEMENT_ASSIGN_CALC_FUNCTION(assignOp, op)                                    \
    template<typename U, template<typename>class DataSource2>                           \
    const GuardType & operator assignOp (const GuardType<U, DataSource2>& data) {       \
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());                             \
        GT_VALUE_BE_READED_DO(data);                                                    \
        this->p.Data() assignOp data.p.Data();                                          \
        OUTPUT_TRACE_SWITCH__(OutPutOpTrace(*this, #assignOp, data, this->p.Data()));   \
        TRACE_STRING_SAVE____(const_cast<std::string&>(this->calcExpres)                \
                              =  GT::PackWithBracket(*this, #op, data));                \
        OUTPUT_TRACE_SWITCH__(this->OutPutExpres());                                    \
        OUTPUT_TRACE_SWITCH__(this->p.OutPutArray());                                   \
        GT_VALUE_CHANGED_DO__(*this);                                                   \
        return *this;                                                                   \
    }                                                                                   \

    IMPLEMENT_ASSIGN_CALC_FUNCTION(*=, *)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(/=, /)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(+=, +)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(-=, -)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(%=, %)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(^=, ^)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(&=, &)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(|=, |)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(<<=, <<)
    IMPLEMENT_ASSIGN_CALC_FUNCTION(>>=, >>)
    
    
    
    GuardType(const char* id = GuardConfig::defaultId)
    TRACE_STRING_SAVE____(:p(id))
    {
    }
    
#define GuardTypeConstructN(type)                   \
    GuardType(const type& data)                     \
    :p(data)                                        \
    {                                               \
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));\
    }
    
    EXPAND_NUMERIC_MACRO(GuardTypeConstructN)
    
    
#define GuardTypeConstructN_IF(type)                \
    GuardType(const type& data, bool outputTrace)   \
    :p(data)                                        \
    {                                               \
        OUTPUT_TRACE_SWITCH__(if(outputTrace)this->TraceAssignWithT(data));\
    }
    
    EXPAND_NUMERIC_MACRO(GuardTypeConstructN_IF)
    
    template<typename U, template<typename>class DataSource2>
    GuardType(const GuardType<U, DataSource2>& data)
    :p(data.p)
    {
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    template<typename U>
    GuardType(const NumericProvider<U>& data)
    :p(data)
    {
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString());
    }
    
    template<typename U, int D>
    GuardType(const ArrayIndexProvider<U, D, 1>& data, size_t n)
    :p(data, n)
    {
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString());
    }
    
    template<int D>
    GuardType<T, ArrayIndexProvider<T, D, 1> >(const GuardTypeArray<T, D>& array, size_t N)
    : p(array, N){
    }
    
    // Do not use this
    //T* operator &() {
    //    GT_VALUE_BE_READED_DO___(data);
    //    return &this->p.Data();
    //}
    //
    //const T* operator &()const {
    //    GT_VALUE_BE_READED_DO___(data);
    //    return &this->p.Data();
    //}
    
#define ASSIGN_FUNC_N(type)                                     \
    const GuardType& operator = (const type& data) {            \
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());     \
        this->p.Data() = data;                                  \
        TRACE_STRING_SAVE____(this->calcExpres = "");           \
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));    \
        GT_VALUE_CHANGED_DO__(*this);                           \
        return *this;                                           \
    }
    
    EXPAND_NUMERIC_MACRO(ASSIGN_FUNC_N)
    
    const GuardType& operator = (const GuardType& data) {
        VALUE_BE_READED_DO___(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data.p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    template<template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<T, DataSource2>& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data.p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    template<typename U>
    const GuardType& operator = (const GuardType<U, DataSource>& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data.p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<U, DataSource2>& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        this->p.Data() = data.p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = data.CalcString());
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }

    operator const T& () const {
        GT_VALUE_BE_READED_DO(*this);
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
    
    const GuardType<T> operator ! () const {
        GT_VALUE_BE_READED_DO(*this);
        OUTPUT_TRACE_SWITCH__(this->TraceReadGuardType("!", GuardType<T>(!this->p.Data(), false)));
        GuardType<T> ret(!this->p.Data(), false);
        TRACE_STRING_SAVE____(ret.calcExpres = "!("+this->CalcString()+")");
        return ret;
    }
    
    const GuardType<T> operator ~ () const {
        GT_VALUE_BE_READED_DO(*this);
        OUTPUT_TRACE_SWITCH__(this->TraceReadGuardType("~", GuardType<T>(~this->p.Data(), false)));
        GuardType<T>ret(~this->p.Data(), false);
        TRACE_STRING_SAVE____(ret.calcExpres = "~("+this->CalcString()+")");
        return ret;
    }
    
    const GuardType& operator ++() {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        ++this->p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString()+"+1");
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("++", *this, ""));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    const GuardType<T> operator ++(int) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "++"));
        GuardType<T> result(this->p.Data(), false);
        TRACE_STRING_SAVE____(result.calcExpres = this->CalcString());
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString()+"+1");
        (this->p.Data())++;
        GT_VALUE_CHANGED_DO__(*this);
        return result;
    }
    
    const GuardType& operator --() {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        --this->p.Data();
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString()+"-1");
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("--", *this, ""));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    const GuardType<T> operator --(int) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->p.Data());
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "--"));
        GuardType<T> result(this->p.Data(), false);
        TRACE_STRING_SAVE____(result.calcExpres = this->CalcString());
        TRACE_STRING_SAVE____(this->calcExpres = this->CalcString()+"-1");
        (this->p.Data())--;
        GT_VALUE_CHANGED_DO__(*this);
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
            GuardConfig::so << const_cast<W&>(result);
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
            this->p.OutPutArray();
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
        this->p.OutPutArray();
    }
    
    template<typename U, template<typename>class DataSource2>
    void TraceAssignWithGT(const GuardType<U, DataSource2>& data) const
    {
        OutPutOpTrace(*this, "=", data, data.p.Data());
        this->OutPutExpres();
        this->p.OutPutArray();
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
