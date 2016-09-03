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
    
    using SelfType = GuardType<T, DataSource>;
    
    template<typename U, typename V = void*&>
    using enable_if_original_t = typename std::enable_if<GT::isOriginalType<GT::RawType<U> >::value, U>::type;
    
    
    template<typename GT>
    class ReadGuarder {
        GT& gt;
    public:
        ReadGuarder(const GT& gt) : gt(const_cast<GT&>(gt)) {
            MULTITHREAD_GUARD____(gt.lock_guard());
            VALUE_BE_READED_DO___(gt.ValueBeReadedDo());
        }
        ~ReadGuarder() {
            MULTITHREAD_GUARD____(gt.unlock_guard());
        }
    };
    
    class WriteGuarder {
        GuardType& gt;
        T oldValue;
    public:
        WriteGuarder(const GuardType& gt) : gt(const_cast<GuardType&>(gt)) {
            MULTITHREAD_GUARD____(gt.lock_guard());
            this->oldValue = const_cast<T&>(this->gt.Data());
        }
        ~WriteGuarder() {
            OUTPUT_TRACE_SWITCH__(this->gt.OutputExpres());
            OUTPUT_TRACE_SWITCH__(this->gt.OutputArray());
            OLD_TO_NEW_VALUE_DO__(this->gt.ValueChangedDo(oldValue));
            MULTITHREAD_GUARD____(gt.unlock_guard());
        }
    };
    
    
public:
    typedef T value_type;
    
public:
    friend void swap(const GuardType& gt, const GuardType& g2) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(gt));
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy2(g2));
        
        T& r1 = const_cast<T&>(gt.Data());
        T& r2 = const_cast<T&>(g2.Data());
        T temp = r1;
        r1 = r2;
        r2 = temp;
        
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return;
                              GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "swap(";
                              GuardConfig::so << gt.Id() << ", ";
                              GuardConfig::so << g2.Id() << ")" << std::endl);
    }
#define FRIEND_CALC_FUNC(op, CalcReturnType)                                            \
    template<typename U, typename = enable_if_original_t<U> >                           \
    friend const GuardType<CalcReturnType(U, op, T), TemporaryProvider>                 \
    operator op (const U & data, const GuardType& g2) {                                 \
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(g2));                            \
        CalcResultType(U, op, T) result(data op g2.Data());                             \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(data, #op, g2, result));                    \
        GuardType<CalcReturnType(U, op, T), TemporaryProvider>ret(result);              \
        TRACE_STRING_SAVE____(ret.setExpress(GT::PackWithBracket(data, #op, g2)));      \
        return ret;                                                                     \
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
    template<typename U, typename = enable_if_original_t<U> >                           \
    friend const GuardType<bool, TemporaryProvider>                                     \
    operator op (const U & data, const GuardType& g2) {                                 \
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(g2));                            \
        bool result(data op g2.Data());                                                 \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(data, #op, g2, result));                    \
        GuardType<bool, TemporaryProvider>ret(result);                                  \
        TRACE_STRING_SAVE____(ret.setExpress(GT::PackWithBracket(data, #op, g2)));      \
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
    
    
#define FRIEND_ASSIGN_FUNC(assignOp, op)                                                \
    template<typename U, typename = enable_if_original_t<U> >                           \
    friend const GuardType<U, TemporaryProvider>                                        \
    operator assignOp (U & data, const GuardType& g2) {                                 \
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg2(data));                         \
        OUTPUT_TRACE_SWITCH__(T reserveData = data);                                    \
        T result(data assignOp g2.Data());                                              \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(reserveData, #assignOp, g2, result));       \
        GuardType<U, TemporaryProvider>ret(result);                                     \
        TRACE_STRING_SAVE____(ret.setExpress(GT::PackWithBracket(data, #op, g2)));      \
        return ret;                                                                     \
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
    
    
#define IMPLEMENT_CALC_FUNCTION_N(op, CalcReturnType)                                   \
    template<typename U, typename = enable_if_original_t<U> >                           \
    const GuardType<CalcReturnType(T, op, U), TemporaryProvider>                        \
    operator op (const U& data) const {                                                 \
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));                         \
        CalcReturnType(T, op, U) result(this->Data() op data);                          \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        GuardType<CalcReturnType(T, op, U), TemporaryProvider>ret(result);              \
        TRACE_STRING_SAVE____(ret.setExpress(GT::PackWithBracket(*this, #op, data)));   \
        return ret;                                                                     \
    }
    
    IMPLEMENT_CALC_FUNCTION_N(*, CalcMultiplyResultType)
    IMPLEMENT_CALC_FUNCTION_N(/, CalcResultType)
    IMPLEMENT_CALC_FUNCTION_N(+, CalcResultType)
    IMPLEMENT_CALC_FUNCTION_N(-, CalcResultType)
    IMPLEMENT_CALC_FUNCTION_N(%, CalcResultType)
    IMPLEMENT_CALC_FUNCTION_N(^, CalcResultType)
    IMPLEMENT_CALC_FUNCTION_N(&, CalcResultType)
    IMPLEMENT_CALC_FUNCTION_N(|, CalcResultType)
    IMPLEMENT_CALC_FUNCTION_N(<<, CalcResultType)
    IMPLEMENT_CALC_FUNCTION_N(>>, CalcResultType)
    
    
#define IMPLEMENT_CALC_FUNCTION(op, CalcReturnType)                                     \
    template<typename U, template<typename>class DataSource2                            \
    , typename Data = GuardType<U, DataSource2>>                                        \
    const GuardType<CalcReturnType(T, op, U), TemporaryProvider>                        \
    operator op (const GuardType<U, DataSource2>& data) const {                         \
        VALUE_BE_READED_DO___(ReadGuarder<Data> rg2(data));                             \
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));                         \
        CalcReturnType(T, op, U) result(this->Data() op data.Data());                   \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        GuardType<CalcReturnType(T, op, U), TemporaryProvider>ret(result);              \
        TRACE_STRING_SAVE____(ret.setExpress(GT::PackWithBracket(*this, #op, data)));   \
        return ret;                                                                     \
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
    
    
#define IMPLEMENT_BOOL_FUNCTION_N(op)                                                   \
    template<typename U, typename = enable_if_original_t<U> >                           \
    const GuardType<bool, TemporaryProvider> operator op (const U& data) const {        \
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));                         \
        bool result(this->Data() op data);                                              \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        GuardType<bool, TemporaryProvider>ret(result);                                  \
        TRACE_STRING_SAVE____(ret.setExpress(GT::PackWithBracket(*this, #op, data)));   \
        return ret;                                                                     \
    }                                                                                   \

    IMPLEMENT_BOOL_FUNCTION_N(&&)
    IMPLEMENT_BOOL_FUNCTION_N(||)
    IMPLEMENT_BOOL_FUNCTION_N(<)
    IMPLEMENT_BOOL_FUNCTION_N(>)
    IMPLEMENT_BOOL_FUNCTION_N(<=)
    IMPLEMENT_BOOL_FUNCTION_N(>=)
    IMPLEMENT_BOOL_FUNCTION_N(==)
    IMPLEMENT_BOOL_FUNCTION_N(!=)
    
    
#define IMPLEMENT_BOOL_FUNCTION(op)                                                     \
    template<typename U, template<typename>class DataSource2                            \
    , typename Data = GuardType<U, DataSource2> >                                       \
    const GuardType<bool, TemporaryProvider>                                            \
    operator op (const GuardType<U, DataSource2>& data) const {                         \
        VALUE_BE_READED_DO___(ReadGuarder<Data> rg2(data));                             \
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));                         \
        bool result(this->Data() op data.Data());                                       \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        GuardType<bool, TemporaryProvider>ret(result);                                  \
        TRACE_STRING_SAVE____(ret.setExpress(GT::PackWithBracket(*this, #op, data)));   \
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
    
    
#define IMPLEMENT_ASSIGN_CALC_FUNCTION_N(assignOp, op)                                  \
    template<typename U, typename = enable_if_original_t<U> >                           \
    const GuardType<T, DataSource>&                                                     \
    operator assignOp (const U& data) {                                                 \
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));                       \
        this->Data() assignOp data;                                                     \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #assignOp, data, this->Data()));     \
        TRACE_STRING_SAVE____(this->setExpress(GT::PackWithBracket(*this, #op, data))); \
        return *this;                                                                   \
    }                                                                                   \

    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(*=, *)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(/=, /)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(+=, +)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(-=, -)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(%=, %)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(^=, ^)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(&=, &)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(|=, |)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(<<=, <<)
    IMPLEMENT_ASSIGN_CALC_FUNCTION_N(>>=, >>)
    
    
#define IMPLEMENT_ASSIGN_CALC_FUNCTION(assignOp, op)                                    \
    template<typename U, template<typename>class DataSource2                            \
    , typename Data = GuardType<U, DataSource2> >                                       \
    const GuardType & operator assignOp (const GuardType<U, DataSource2>& data) {       \
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));                       \
        VALUE_BE_READED_DO___(ReadGuarder<Data> rg(data));                              \
        this->Data() assignOp data.Data();                                              \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #assignOp, data, this->Data()));     \
        TRACE_STRING_SAVE____(this->setExpress(GT::PackWithBracket(*this, #op, data))); \
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
    GuardType(const IndexProvider<U, 1>& data, size_t n)
    : DataSource<T>(data, n)
    {
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()));
    }
    
    GuardType(const GuardArray<T, 1>& array, size_t N)
    : DataSource<T>(array, N){
    }
    
    template<typename U, typename = enable_if_original_t<U> >
    GuardType(U& data)
    : DataSource<T>(data)
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    template<typename U, typename = enable_if_original_t<U> >
    GuardType(const U& data)
    : DataSource<T>(data)
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    GuardType(GuardType& data)
    : DataSource<T>(data)
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());
    }
    
    GuardType(const GuardType& data)
    : DataSource<T>(data)
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
    template<typename U, typename = enable_if_original_t<U> >
    GuardType(U&& data)
    : DataSource<T>(std::forward<U>(data))
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    template<typename U, typename = enable_if_original_t<U> >
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
    
    template<typename U, typename = enable_if_original_t<U> >
    const GuardType<T, DataSource>&
    operator = (U& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        this->Data() = data;
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        return *this;
    }
    
    template<typename U, typename = enable_if_original_t<U> >
    const GuardType<T, DataSource>&
    operator = (const U& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        this->Data() = data;
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        return *this;
    }
    
    const GuardType& operator = (GuardType& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(data));
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    const GuardType& operator = (const GuardType& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(data));
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2
    , typename Data = GuardType<U, DataSource2> >
    const GuardType& operator = (GuardType<U, DataSource2>& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        VALUE_BE_READED_DO___(ReadGuarder<Data> rg2(data));
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2
    , typename Data = GuardType<U, DataSource2> >
    const GuardType& operator = (const GuardType<U, DataSource2>& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        VALUE_BE_READED_DO___(ReadGuarder<Data> rg2(data));
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    // rvalue assign operator
    template<typename U, typename = enable_if_original_t<U> >
    const GuardType<T, DataSource>&
    operator = (U&& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        this->Data() = std::forward<U>(data);
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        return *this;
    }
    template<typename U, typename = enable_if_original_t<U> >
    const GuardType<T, DataSource>&
    operator = (const U&& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        this->Data() = std::forward<const U>(data);
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        return *this;
    }
    
    const GuardType& operator = (GuardType&& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(data));
        this->Data() = std::forward<T>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    const GuardType& operator = (const GuardType&& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(data));
        this->Data() = std::forward<const T>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2
    , typename Data = GuardType<U, DataSource2> >
    const GuardType& operator = (GuardType<U, DataSource2>&& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        VALUE_BE_READED_DO___(ReadGuarder<Data> rg2(data));
        this->Data() = std::forward<U>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2
    , typename Data = GuardType<U, DataSource2> >
    const GuardType& operator = (const GuardType<U, DataSource2>&& data) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        VALUE_BE_READED_DO___(ReadGuarder<Data> rg2(data));
        this->Data() = std::forward<const U>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U>
    decltype(std::declval<T>()[std::declval<U>()]) operator [] (const U& n) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        decltype(std::declval<T>()[std::declval<U>()]) ret = this->Data()[n];
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "[";
                              GuardConfig::so << n;
                              GuardConfig::so << "]" << std::endl);
        return ret;
    }
    
    template<typename U>
    decltype(std::declval<const T>()[std::declval<U>()]) operator [] (const U& n) const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        decltype(std::declval<const T>()[std::declval<U>()]) ret = this->Data()[n];
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "[";
                              GuardConfig::so << n;
                              GuardConfig::so << "]" << std::endl);
        return ret;
    }
    
    template<typename ...Args>
    typename std::enable_if<std::is_same<typename std::result_of<T(Args...)>::type, void>::value>::type
    operator () (Args... args) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
    }
    
    template<typename ...Args>
    typename std::enable_if<std::is_same<typename std::result_of<T(Args...)>::type, void>::value>::type
    operator () (Args... args) const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
    }
    
    template<typename ...Args>
    typename std::enable_if<
    !std::is_same<typename std::result_of<T(Args...)>::type, void>::value
    , typename std::result_of<T(Args...)>::type>::type
    operator () (Args... args) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        typename std::result_of<T(Args...)>::type ret = this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
        return ret;
    }
    
    template<typename ...Args>
    typename std::enable_if<
    !std::is_same<typename std::result_of<T(Args...)>::type, void>::value
    , typename std::result_of<T(Args...)>::type>::type
    operator () (Args... args) const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        typename std::result_of<T(Args...)>::type ret = this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
        return ret;
    }
    
    template<typename U = T, typename = typename std::enable_if<std::is_pointer<U>::value>::type >
    typename std::remove_pointer<T>::type& operator* () {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        return *(this->Data());
    }
    
    template<typename U = T, typename = typename std::enable_if<std::is_pointer<U>::value>::type >
    const typename std::remove_pointer<T>::type& operator* () const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        return *(this->Data());
    }
    
    template<typename U = T, typename = typename std::enable_if<GT::isDereferencable<U>::value&&std::is_class<U>::value>::type >
    decltype(*(std::declval<U>())) operator* () {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        return *(this->Data());
    }
    
    template<typename U = T, typename = typename std::enable_if<std::is_pointer<U>::value>::type >
    decltype(*(std::declval<U>())) operator* () const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        return *(this->Data());
    }
    
    // Guarantee the security of multithreading by copy
    operator const T () const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_TRACE_READ_SWITCH == false) return this->Data());
        OUTPUT_TRACE_SWITCH__(this->TraceReadGT("", *this));
        return this->Data();
    }
    
    //// Can not guarantee the security of multithreading
    //operator const T& () const {
    //    VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
    //    OUTPUT_TRACE_SWITCH__(if(GuardConfig::_TRACE_READ_SWITCH == false) return this->Data());
    //    OUTPUT_TRACE_SWITCH__(this->TraceReadGT("", *this));
    //    return this->Data();
    //}
    
    // Can not guarantee the security of multithreading when member function called
    T* operator -> () {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        return &this->Data();
    }
    
    // Can not guarantee the security of multithreading when member function called
    const T* operator -> () const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        return &this->Data();
    }
    
    // Do not use this
    //T* operator &() {
    //    VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
    //    return &this->Data();
    //}
    //
    //const T* operator &()const {
    //    VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
    //    return &this->Data();
    //}
    
    const GuardType<T, TemporaryProvider> operator ! () const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        OUTPUT_TRACE_SWITCH__(this->TraceReadGT("!", GuardType<T, TemporaryProvider>(!this->Data())));
        GuardType<T, TemporaryProvider> ret(!this->Data());
        TRACE_STRING_SAVE____(ret.setExpress("!("+this->CalcString()+")"));
        return ret;
    }
    
    const GuardType<T, TemporaryProvider> operator ~ () const {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg(*this));
        OUTPUT_TRACE_SWITCH__(this->TraceReadGT("~", GuardType<T, TemporaryProvider>(~this->Data())));
        GuardType<T, TemporaryProvider>ret(~this->Data());
        TRACE_STRING_SAVE____(ret.setExpress("~("+this->CalcString()+")"));
        return ret;
    }
    
    const GuardType& operator ++() {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        ++this->Data();
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"+1"));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("++", *this, ""));
        return *this;
    }
    
    const GuardType<T, TemporaryProvider> operator ++(int) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "++"));
        GuardType<T, TemporaryProvider> result(this->Data());
        TRACE_STRING_SAVE____(result.setExpress(this->CalcString()));
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"+1"));
        ++(this->Data());
        return result;
    }
    
    const GuardType& operator --() {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        --this->Data();
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"-1"));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("--", *this, ""));
        return *this;
    }
    
    const GuardType<T, TemporaryProvider> operator --(int) {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(*this));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "--"));
        GuardType<T, TemporaryProvider> result(this->Data());
        TRACE_STRING_SAVE____(result.setExpress(this->CalcString()));
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"-1"));
        --(this->Data());
        return result;
    }
    
    friend std::istream& operator >> (std::istream &si, GuardType& gt)
    {
        OLD_TO_NEW_VALUE_DO__(WriteGuarder doWhenDestroy(gt));
        if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true) {
            std::cout << "Please input Data ";
            std::cout << gt.Id();
            std::cout << ": ";
        }
        si >> gt.Data();
        //if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return si;
        //if(GuardConfig::rule[">>"] == true) {
        //    std::cout<< _SPACES << "TRACE: si >> ";
        //    std::cout<< gt.Id();
        //    std::cout<< " = " << gt.Data() << std::endl;
        //}
        return si;
    }
    
    friend std::ostream& operator << (std::ostream & so, const GuardType& data)
    {
        VALUE_BE_READED_DO___(ReadGuarder<SelfType> rg2(data));
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_OUTPUT_TRACE_SWITCH == false)
                              return so << data.Data();
                              if(GuardConfig::rule["<<"] == false) return so << data.Data();
                              so << _SPACES << "TRACE: so<< " ;
                              so << data.Id();
                              so << " : " << data.Data() << std::endl);
        return so << data.Data();
    }
    
    void OutputExpres() const {
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
};

#endif /* GuardType_hpp */
