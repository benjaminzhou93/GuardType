#ifndef GuardType_hpp
#define GuardType_hpp

#include <functional>
#include "GuardConfig.hpp"
#include "Tools.hpp"
#include "TemplateTools.hpp"
#include "IndexProviderO.hpp"
#include "NumericProvider.hpp"
#include "TemporaryProvider.hpp"

//--------------------------------------------------------------------------
//                            class GuardType

template<typename T, template<typename> class DataSource>
class GuardType : public DataSource<T> {
    template<typename U, template<typename>class DataSource2>
    friend class GuardType;
    
    template<typename U>
    using TP = TemporaryProvider<U>;
    
    template<typename U>
    using NP = NumericProvider<U>;
    
    template<typename U>
    using IP = IndexProvider<U>;
    
    using SelfType = GuardType<T, DataSource>;
    
    class FunctionOverGuarder {
        const GuardType& data;
        T oldValue;
        
    public:
        FunctionOverGuarder(const GuardType& data) : data(data) {
            MULTITHREAD_GUARD____(data.lock_guard());
            oldValue = data.Data();
        }
        
        ~FunctionOverGuarder() {
            if(GT::optionalEqual(oldValue, data.Data())) {
                data.ValueBeReadedDo();
            }
            else {
                const_cast<GuardType&>(data).ValueChangedDo(oldValue);
            }
            MULTITHREAD_GUARD____(data.unlock_guard());
        }
        
        T* operator -> () {
            return const_cast<T*>(&data.Data());
        }
        
        const T* operator -> () const {
            return &data.Data();
        }
    };
    
public:
    typedef SelfType isGuardType;
    
    typedef T value_type;
    
public:
    
#define FRIEND_CALC_FUNC(op, CalcReturnType)                                            \
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type> \
    friend const CalcReturnType(U, op, T)                                               \
    operator op (const U & data, const GuardType& g2) {                                 \
        PRE_VALUE_BE_READED_DO(DataSource, T, g2)                                       \
        CalcResultType(U, op, T) result(data op g2.Data());                             \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(data, #op, g2, result));                    \
        TRACE_STRING_SAVE____(SetExpres(result, GT::PackWithBracket(data, #op, g2)));   \
        END_VALUE_BE_READED_DO(DataSource, T, g2)                                       \
        return result;                                                                  \
    }
    
    FRIEND_CALC_FUNC(*, CalcMultiplyResultType)
    FRIEND_CALC_FUNC(/, CalcResultType)
    FRIEND_CALC_FUNC(+, CalcResultType)
    FRIEND_CALC_FUNC(-, CalcResultType)
    FRIEND_CALC_FUNC(%, CalcResultType)
    FRIEND_CALC_FUNC(^, CalcResultType)
    FRIEND_CALC_FUNC(&, CalcResultType)
    FRIEND_CALC_FUNC(|, CalcResultType)
    FRIEND_CALC_FUNC(<<, CalcResultType)
    FRIEND_CALC_FUNC(>>, CalcResultType)
    
    
#define FRIEND_BOOL_FUNC(op)                                                            \
    template<typename U, typename =  typename std::enable_if<GT::isOriginalType<U>::value>::type> \
    friend const GuardTypeResult(bool)                                                  \
    operator op (const U & data, const GuardType& g2) {                                 \
        PRE_VALUE_BE_READED_DO(DataSource, T, g2)                                       \
        GuardTypeResult(bool) result(data op g2.Data());                                \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(data, #op, g2, result));                    \
        TRACE_STRING_SAVE____(SetExpres(result, GT::PackWithBracket(data, #op, g2)));   \
        END_VALUE_BE_READED_DO(DataSource, T, g2)                                       \
        return result;                                                                  \
    }
    
    FRIEND_BOOL_FUNC(&&)
    FRIEND_BOOL_FUNC(||)
    FRIEND_BOOL_FUNC(<)
    FRIEND_BOOL_FUNC(>)
    FRIEND_BOOL_FUNC(<=)
    FRIEND_BOOL_FUNC(>=)
    FRIEND_BOOL_FUNC(==)
    FRIEND_BOOL_FUNC(!=)
    
    
#define FRIEND_ASSIGN_FUNC(assignOp, op)                                                \
    template<typename U, typename =  typename std::enable_if<GT::isOriginalType<U>::value>::type> \
    friend const U& operator assignOp (U & data, const GuardType& g2) {                 \
        PRE_VALUE_BE_READED_DO(DataSource, T, g2)                                       \
        OUTPUT_TRACE_SWITCH__(T reserveData = data);                                    \
        data assignOp g2.Data();                                                        \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(reserveData, #assignOp, g2, data));         \
        END_VALUE_BE_READED_DO(DataSource, T, g2)                                       \
        return data;                                                                    \
    }
    
    FRIEND_ASSIGN_FUNC(*=, *)
    FRIEND_ASSIGN_FUNC(/=, /)
    FRIEND_ASSIGN_FUNC(+=, +)
    FRIEND_ASSIGN_FUNC(-=, -)
    FRIEND_ASSIGN_FUNC(%=, %)
    FRIEND_ASSIGN_FUNC(^=, ^)
    FRIEND_ASSIGN_FUNC(&=, &)
    FRIEND_ASSIGN_FUNC(|=, |)
    FRIEND_ASSIGN_FUNC(<<=, <<)
    FRIEND_ASSIGN_FUNC(>>=, >>)
    
    
#define IMPLEMENT_CALC_FUNCTION(op, CalcReturnType)                                     \
    template<typename U, typename =  typename std::enable_if<GT::isOriginalType<U>::value>::type> \
    const CalcReturnType(T, op, U)                                                      \
    operator op (const U& data) const {                                                 \
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)                                    \
        CalcReturnType(T, op, U) result(this->Data() op data);                          \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        TRACE_STRING_SAVE____(SetExpres(result, GT::PackWithBracket(*this, #op, data)));\
        END_VALUE_BE_READED_DO(DataSource, T, *this)                                    \
        return result;                                                                  \
    }                                                                                   \
\
    template<typename U, template<typename>class DataSource2>                           \
    const CalcReturnType(T, op, U)                                                      \
    operator op (const GuardType<U, DataSource2>& data) const {                         \
        PRE_VALUE_BE_READED_DO(DataSource2, U, data)                                    \
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)                                    \
        CalcReturnType(T, op, U) result(this->Data() op data.Data());                   \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        TRACE_STRING_SAVE____(SetExpres(result, GT::PackWithBracket(*this, #op, data)));\
        END_VALUE_BE_READED_DO(DataSource2, U, data)                                    \
        END_VALUE_BE_READED_DO(DataSource, T, *this)                                    \
        return result;                                                                  \
    }
    
    IMPLEMENT_CALC_FUNCTION(*, CalcMultiplyResultType)
    IMPLEMENT_CALC_FUNCTION(/, CalcResultType)
    IMPLEMENT_CALC_FUNCTION(+, CalcResultType)
    IMPLEMENT_CALC_FUNCTION(-, CalcResultType)
    IMPLEMENT_CALC_FUNCTION(%, CalcResultType)
    IMPLEMENT_CALC_FUNCTION(^, CalcResultType)
    IMPLEMENT_CALC_FUNCTION(&, CalcResultType)
    IMPLEMENT_CALC_FUNCTION(|, CalcResultType)
    IMPLEMENT_CALC_FUNCTION(<<, CalcResultType)
    IMPLEMENT_CALC_FUNCTION(>>, CalcResultType)
    
    
#define IMPLEMENT_BOOL_FUNCTION(op)                                                     \
    template<typename U, typename =  typename std::enable_if<GT::isOriginalType<U>::value>::type> \
    const GuardTypeResult(bool) operator op (const U& data) const {                     \
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)                                    \
        GuardTypeResult(bool) result(this->Data() op data);                             \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        TRACE_STRING_SAVE____(SetExpres(result, GT::PackWithBracket(*this, #op, data)));\
        END_VALUE_BE_READED_DO(DataSource, T, *this)                                    \
        return result;                                                                  \
    }                                                                                   \
\
    template<typename U, template<typename>class DataSource2>                           \
    const GuardTypeResult(bool)                                                         \
    operator op (const GuardType<U, DataSource2>& data) const {                         \
        PRE_VALUE_BE_READED_DO(DataSource2, U, data)                                    \
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)                                    \
        GuardTypeResult(bool) result(this->Data() op data.Data());                      \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        TRACE_STRING_SAVE____(SetExpres(result, GT::PackWithBracket(*this, #op, data)));\
        END_VALUE_BE_READED_DO(DataSource2, U, data)                                    \
        END_VALUE_BE_READED_DO(DataSource, T, *this)                                    \
        return result;                                                                  \
    }                                                                                   \

    IMPLEMENT_BOOL_FUNCTION(&&)
    IMPLEMENT_BOOL_FUNCTION(||)
    IMPLEMENT_BOOL_FUNCTION(<)
    IMPLEMENT_BOOL_FUNCTION(>)
    IMPLEMENT_BOOL_FUNCTION(<=)
    IMPLEMENT_BOOL_FUNCTION(>=)
    IMPLEMENT_BOOL_FUNCTION(==)
    IMPLEMENT_BOOL_FUNCTION(!=)
    
    
#define IMPLEMENT_ASSIGN_CALC_FUNCTION(assignOp, op)                                    \
    template<typename U, typename =  typename std::enable_if<GT::isOriginalType<U>::value>::type> \
    const GuardType<T, DataSource>&                                                     \
    operator assignOp (const U& data) {                                                 \
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)                                   \
        this->Data() assignOp data;                                                     \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #assignOp, data, this->Data()));     \
        TRACE_STRING_SAVE____(this->setExpress(GT::PackWithBracket(*this, #op, data))); \
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)                                   \
        return *this;                                                                   \
    }                                                                                   \
\
    template<typename U, template<typename>class DataSource2>                           \
    const GuardType & operator assignOp (const GuardType<U, DataSource2>& data) {       \
        PRE_VALUE_BE_READED_DO(DataSource2, U, data)                                    \
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)                                   \
        this->Data() assignOp data.Data();                                              \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #assignOp, data, this->Data()));     \
        TRACE_STRING_SAVE____(this->setExpress(GT::PackWithBracket(*this, #op, data))); \
        END_VALUE_BE_READED_DO(DataSource2, U, data)                                    \
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)                                   \
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
    
    
    
    template<typename... Args>
    GuardType(Args... args)
    : DataSource<T>(args...){
    }
    
    GuardType(const char* id = GuardConfig::defaultId)
    TRACE_STRING_SAVE____(:DataSource<T>(id))
    {
    }
    
    // construct from array
    template<typename U>
    GuardType(const IndexProvider<U, 1>& data, int n)
    : DataSource<T>(data, n)
    {
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()));
    }
    
    GuardType(const GuardArray<T, 1>& array, int n)
    : DataSource<T>(array, n){
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    GuardType(U& data)
    : DataSource<T>(data)
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    GuardType(const U& data)
    : DataSource<T>(data)
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    GuardType(GuardType& data)
    : DataSource<T>(static_cast<DataSource<T>&>(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    GuardType(const GuardType& data)
    : DataSource<T>(static_cast<const DataSource<T>&>(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(GuardType<U, DataSource2>& data)
    : DataSource<T>(data.Data())
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(const GuardType<U, DataSource2>& data)
    : DataSource<T>(data.Data())
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    // rvalue constructor
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    GuardType(U&& data)
    : DataSource<T>(std::forward<U>(data))
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    GuardType(const U&& data)
    : DataSource<T>(std::forward<const U>(data))
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    GuardType(GuardType&& data)
    : DataSource<T>(std::forward<DataSource<T> >(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    GuardType(const GuardType&& data)
    : DataSource<T>(std::forward<const DataSource<T> >(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(GuardType<U, DataSource2>&& data)
    : DataSource<T>(std::forward<U>(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(const GuardType<U, DataSource2>&& data)
    : DataSource<T>(std::forward<const U>(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    const GuardType<T, DataSource>&
    operator = (U& data) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = data;
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    const GuardType<T, DataSource>&
    operator = (const U& data) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = data;
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    const GuardType& operator = (GuardType& data) {
        PRE_VALUE_BE_READED_DO(DataSource, T, data)
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        END_VALUE_BE_READED_DO(DataSource, T, data)
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    const GuardType& operator = (const GuardType& data) {
        PRE_VALUE_BE_READED_DO(DataSource, T, data)
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        END_VALUE_BE_READED_DO(DataSource, T, data)
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (GuardType<U, DataSource2>& data) {
        PRE_VALUE_BE_READED_DO(DataSource2, U, data)
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        END_VALUE_BE_READED_DO(DataSource2, U, data)
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<U, DataSource2>& data) {
        PRE_VALUE_BE_READED_DO(DataSource2, U, data)
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        END_VALUE_BE_READED_DO(DataSource2, U, data)
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    // rvalue assign operator
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    const GuardType<T, DataSource>&
    operator = (U&& data) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = std::forward<U>(data);
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    const GuardType<T, DataSource>&
    operator = (const U&& data) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = std::forward<const U>(data);
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    const GuardType& operator = (GuardType&& data) {
        PRE_VALUE_BE_READED_DO(DataSource, T, data)
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = std::forward<T>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        END_VALUE_BE_READED_DO(DataSource, T, data)
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    const GuardType& operator = (const GuardType&& data) {
        PRE_VALUE_BE_READED_DO(DataSource, T, data)
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = std::forward<const T>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        END_VALUE_BE_READED_DO(DataSource, T, data)
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (GuardType<U, DataSource2>&& data) {
        PRE_VALUE_BE_READED_DO(DataSource2, U, data)
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = std::forward<U>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        END_VALUE_BE_READED_DO(DataSource2, U, data)
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<U, DataSource2>&& data) {
        PRE_VALUE_BE_READED_DO(DataSource2, U, data)
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data() = std::forward<const U>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        END_VALUE_BE_READED_DO(DataSource2, U, data)
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    template<typename U>
    decltype(std::declval<T>()[std::declval<U>()]) operator [] (const U& n) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        decltype(std::declval<T>()[std::declval<U>()]) result = this->Data()[n];
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "[";
                              GuardConfig::so << n;
                              GuardConfig::so << "]" << std::endl);
        END_OLD_MAYBE_TO_NEW_VALUE_DO(DataSource, T, *this)
        return result;
    }
    
    template<typename U>
    decltype(std::declval<const T>()[std::declval<U>()]) operator [] (const U& n) const {
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)
        decltype(std::declval<const T>()[std::declval<U>()]) result = this->Data()[n];
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "[";
                              GuardConfig::so << n;
                              GuardConfig::so << "]" << std::endl);
        END_VALUE_BE_READED_DO(DataSource, T, *this)
        return result;
    }
    
    template<typename ...Args>
    typename std::enable_if<std::is_same<typename std::result_of<T(Args...)>::type, void>::value>::type
    operator () (Args... args) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
        END_OLD_MAYBE_TO_NEW_VALUE_DO(DataSource, T, *this)
    }
    
    template<typename ...Args>
    typename std::enable_if<std::is_same<typename std::result_of<T(Args...)>::type, void>::value>::type
    operator () (Args... args) const {
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)
        this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
        END_VALUE_BE_READED_DO(DataSource, T, *this)
    }
    
    template<typename ...Args>
    typename std::enable_if<
    !std::is_same<typename std::result_of<T(Args...)>::type, void>::value
    , typename std::result_of<T(Args...)>::type>::type
    operator () (Args... args) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        typename std::result_of<T(Args...)>::type result = this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
        END_OLD_MAYBE_TO_NEW_VALUE_DO(DataSource, T, *this)
        return result;
    }
    
    template<typename ...Args>
    typename std::enable_if<
    !std::is_same<typename std::result_of<T(Args...)>::type, void>::value
    , typename std::result_of<T(Args...)>::type>::type
    operator () (Args... args) const {
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)
        typename std::result_of<T(Args...)>::type result = this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
        END_VALUE_BE_READED_DO(DataSource, T, *this)
        return result;
    }
    
    template<typename U = T, typename = typename std::enable_if<GT::isDereferencable<U>::value>::type>
    decltype(*(std::declval<U>())) operator* () {
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)
        decltype(*(std::declval<U>())) result = *(this->Data());
        END_VALUE_BE_READED_DO(DataSource, T, *this)
        return result;
    }
    
    template<typename U = T, typename = typename std::enable_if<GT::isDereferencable<U>::value>::type>
    decltype(*(std::declval<U>())) operator* () const {
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)
        decltype(*(std::declval<U>())) result = *(this->Data());
        END_VALUE_BE_READED_DO(DataSource, T, *this)
        return result;
    }
    
    operator typename std::conditional<ENSURE_MULTITHREAD_SAFETY, const T, const T&>::type () const {
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_TRACE_READ_SWITCH == true)this->TraceReadGT("", *this));
        typename std::conditional<ENSURE_MULTITHREAD_SAFETY, const T, const T&>::type result = this->Data();
        END_VALUE_BE_READED_DO(DataSource, T, *this)
        return result;
    }
    
    FunctionOverGuarder operator -> () {
        return FunctionOverGuarder(*this);
    }
    
    const FunctionOverGuarder operator -> () const {
        return FunctionOverGuarder(*this);
    }
    
    const GuardTypeResult(T) operator ! () const {
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)
        OUTPUT_TRACE_SWITCH__(this->TraceReadGT("!", GuardType<T, TemporaryProvider>(!this->Data())));
        GuardTypeResult(T) result(!this->Data());
        TRACE_STRING_SAVE____(SetExpres(result, "!("+this->CalcString()+")"));
        END_VALUE_BE_READED_DO(DataSource, T, *this)
        return result;
    }
    
    const GuardTypeResult(T) operator ~ () const {
        PRE_VALUE_BE_READED_DO(DataSource, T, *this)
        OUTPUT_TRACE_SWITCH__(this->TraceReadGT("~", GuardType<T, TemporaryProvider>(~this->Data())));
        GuardTypeResult(T) result(~this->Data());
        TRACE_STRING_SAVE____(SetExpres(result, "~("+this->CalcString()+")"));
        END_VALUE_BE_READED_DO(DataSource, T, *this)
        return result;
    }
    
    const GuardType& operator ++() {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        ++this->Data();
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"+1"));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("++", *this, ""));
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    const GuardTypeResult(T) operator ++(int) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "++"));
        GuardTypeResult(T) result(this->Data());
        TRACE_STRING_SAVE____(SetExpres(result, this->CalcString()));
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"+1"));
        ++(this->Data());
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return result;
    }
    
    const GuardType& operator --() {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        --this->Data();
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"-1"));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("--", *this, ""));
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return *this;
    }
    
    const GuardTypeResult(T) operator --(int) {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "--"));
        GuardTypeResult(T) result(this->Data());
        TRACE_STRING_SAVE____(SetExpres(result, this->CalcString()));
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"-1"));
        --(this->Data());
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, *this)
        return result;
    }
    
    friend std::istream& operator >> (std::istream &si, GuardType& data)
    {
        PRE_OLD_TO_NEW_VALUE_DO(DataSource, T, data)
        if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
            std::cout << "Please input Data ";
            std::cout << data.Id();
            std::cout << ": ";
        }
        si >> data.Data();
        END_OLD_TO_NEW_VALUE_DO(DataSource, T, data)
        return si;
    }
    
    friend std::ostream& operator << (std::ostream & so, const GuardType& data)
    {
        PRE_VALUE_BE_READED_DO(DataSource, T, data)
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_OUTPUT_TRACE_SWITCH == true)
                              if(GuardConfig::rule["<<"] == true) {
                                  so << _SPACES << "TRACE: so<< " ;
                                  so << data.Id();
                                  so << " : " << data.Data() << std::endl;});
        so << data.Data();
        END_VALUE_BE_READED_DO(DataSource, T, data)
        return so;
    }
    
    void OutputExpres() const {
        if(GT::isTemporaryProvider<DataSource<T> >::value) return;
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) GuardConfig::so
            << _SPACES << "EXPRES:"
            << this->Id() << " = "
            << this->CalcString() << std::endl;
    }
    
    template<typename U, typename V, typename W>
    static void OutputOpTrace(const U& data1,
                              const char* op,
                              const V& data2,
                              const W& result)
    {
        if((GT::isTemporaryProvider<U>::value
            || GT::isTemporaryProvider<V>::value)
           && (std::strcmp(op, "=") == 0)) return;
        if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return;
        if(GuardConfig::rule[op] == false) return;
        GuardConfig::so << _SPACES << "TRACE: ";
        GuardConfig::so << GT::NumericToString(data1);
        GuardConfig::so << " " << op << " ";
        GuardConfig::so << GT::NumericToString(data2);
        if(std::strcmp(op, "=") != 0) {
            GuardConfig::so << " = ";
            GuardConfig::so << GT::NumericToString(result);
        }
        GuardConfig::so << std::endl;
    }
    
    template<typename U, template<typename>class DataSource2>
    void TraceReadGT(const char* op,
                     const GuardType<U, DataSource2>& result) const
    {
        if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return;
        if(GuardConfig::rule[op] == false) return;
        GuardConfig::so << _SPACES << "TRACE: ";
        GuardConfig::so << op;
        GuardConfig::so << this->Id();
        GuardConfig::so << " : ";
        GuardConfig::so << GT::NumericToString(result.Data()) <<std::endl;
    }
    
    template<typename U, template<typename>class DataSource2>
    void TraceSelfIncrease(const char* frontOp,
                           const GuardType<U, DataSource2>& result,
                           const char* backOp) const
    {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return;
        if(GuardConfig::rule[frontOp] == false
           && GuardConfig::rule[backOp] == false) return;
        GuardConfig::so << _SPACES << "TRACE: ";
        GuardConfig::so << frontOp;
        GuardConfig::so << this->Id();
        GuardConfig::so << backOp << " = ";
        GuardConfig::so << GT::NumericToString(result.Data()) << std::endl;
    }
    
    template<typename U>
    static void SetExpres(const U&, const std::string&) {}
    
    template<typename U, template<typename>class DataSource2>
    static void SetExpres(const GuardType<U, DataSource2>& data, const std::string& s) {
        data.setExpress(s);
    }
    
};

#endif /* GuardType_hpp */
