#ifndef GuardType_hpp
#define GuardType_hpp

#include <functional>
#include "GuardConfig.hpp"
#include "Tools.hpp"
#include "TemplateTools.hpp"
#include "IndexProviderO.hpp"
#include "NumericProvider.hpp"

//--------------------------------------------------------------------------
//                            class GuardType

#define GT_VALUE_BE_READED_DO(gt)                                               \
    VALUE_BE_READED_DO___((gt).ValueBeReadDo());

#define GT_VALUE_CHANGED_DO__(gt)                                               \
    OLD_TO_NEW_VALUE_DO__(OldToNewValueDo doWhenDestroy(gt));

template<typename T, template<typename> class DataSource>
class GuardType : public DataSource<T> {
    template<typename U, template<typename>class DataSource2>
    friend class GuardType;
    
    template<typename U, typename V = void*&>
    using enable_if_original_t = typename std::enable_if<GT::isOriginalType<GT::RawType<U> >::value, U>::type;
    
    class OldToNewValueDo {
        GuardType& gt;
        const T oldValue;
    public:
        OldToNewValueDo(const GuardType& gt)
        : gt(const_cast<GuardType&>(gt)), oldValue(gt.Data())
        {
        }
        ~OldToNewValueDo() {
            OUTPUT_TRACE_SWITCH__(this->gt.OutputExpres());
            OUTPUT_TRACE_SWITCH__(this->gt.OutputArray());
            OLD_TO_NEW_VALUE_DO__(if(this->gt.changedDo != NULL)
                this->gt.changedDo(gt.Data(), oldValue));
        }
    };
public:
    typedef T value_type;
    
public:
    VALUE_BE_READED_DO___(std::function<void(const T& data)> readedDo);
    
    OLD_TO_NEW_VALUE_DO__(std::function<void(T& newValue, const T oldValue)> changedDo);
    
public:
    friend void swap(GuardType& gt, GuardType& gt2) {
        OLD_TO_NEW_VALUE_DO__(OldToNewValueDo doWhenDestroy(gt));
        OLD_TO_NEW_VALUE_DO__(OldToNewValueDo doWhenDestroy2(gt2));
        
        T& r1 = gt.Data();
        T& r2 = gt2.Data();
        T temp = r1;
        r1 = r2;
        r2 = temp;
        
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return;
                              GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "swap(";
                              GuardConfig::so << gt.Id() << ", ";
                              GuardConfig::so << gt2.Id() << ")" << std::endl);
    }
    
    
#define FRIEND_CALC_FUNC(op, CalcReturnType)                                            \
    template<typename U, typename = enable_if_original_t<U> >                           \
    friend const GuardType<CalcReturnType(U, op, T)>                                    \
    operator op (const U & data, const GuardType& g2) {                                 \
        GT_VALUE_BE_READED_DO(g2);                                                      \
        CalcResultType(U, op, T) result(data op g2.Data());                             \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(data, #op, g2, result));                    \
        GuardType<CalcReturnType(U, op, T)>ret(result, false);                          \
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
    friend const GuardType<bool>                                                        \
    operator op (const U & data, const GuardType& g2) {                                 \
        GT_VALUE_BE_READED_DO(g2);                                                      \
        bool result(data op g2.Data());                                                 \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(data, #op, g2, result));                    \
        GuardType<bool>ret(result, false);                                              \
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
    template<typename U>                                                                \
    friend const GuardType<enable_if_original_t<U> >                                    \
    operator assignOp (U & data, const GuardType& g2) {                                 \
        GT_VALUE_BE_READED_DO(g2);                                                      \
        OUTPUT_TRACE_SWITCH__(T reserveData = data);                                    \
        T result(data assignOp g2.Data());                                              \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(reserveData, #assignOp, g2, result));       \
        GuardType<U>ret(result, false);                                                 \
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
    const GuardType<CalcReturnType(T, op, U)>                                           \
    operator op (const U& data) const {                                                 \
        GT_VALUE_BE_READED_DO(*this);                                                   \
        CalcReturnType(T, op, U) result(this->Data() op data);                          \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        GuardType<CalcReturnType(T, op, U)>ret(result, false);                          \
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
    template<typename U, template<typename>class DataSource2>                           \
    const GuardType<CalcReturnType(T, op, U)>                                           \
    operator op (const GuardType<U, DataSource2>& data) const {                         \
        GT_VALUE_BE_READED_DO(data);                                                    \
        GT_VALUE_BE_READED_DO(*this);                                                   \
        CalcReturnType(T, op, U) result(this->Data() op data.Data());                   \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        GuardType<CalcReturnType(T, op, U)>ret(result, false);                          \
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
    template<typename U, typename = enable_if_original_t<U> >                            \
    const GuardType<bool> operator op (const U& data) const {                           \
        GT_VALUE_BE_READED_DO(*this);                                                   \
        bool result(this->Data() op data);                                              \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        GuardType<bool>ret(result, false);                                              \
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
    , typename = enable_if_original_t<U> >                                              \
    const GuardType<bool> operator op (const GuardType<U, DataSource2>& data) const {   \
        GT_VALUE_BE_READED_DO(data);                                                    \
        GT_VALUE_BE_READED_DO(*this);                                                   \
        bool result(this->Data() op data.Data());                                       \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #op, data, result));                 \
        GuardType<bool>ret(result, false);                                              \
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
        GT_VALUE_CHANGED_DO__(*this);                                                   \
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
    template<typename U, template<typename>class DataSource2>                           \
    const GuardType & operator assignOp (const GuardType<U, DataSource2>& data) {       \
        GT_VALUE_CHANGED_DO__(*this);                                                   \
        GT_VALUE_BE_READED_DO(data);                                                    \
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
    
    template<typename U, typename = enable_if_original_t<U> >
    GuardType(const U& data, bool)
    : DataSource<T>(data, false)
    { // operator result temp value
    }
    
    template<typename U, typename = enable_if_original_t<U> >
    GuardType(const U& data)
    : DataSource<T>(data)
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    GuardType(const GuardType& data)
    : DataSource<T>(data)
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(const GuardType<U, DataSource2>& data)
    : DataSource<T>(data)
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
    }
    
    // const rvalue constructor
    template<typename U, typename = enable_if_original_t<U> >
    GuardType(const U&& data)
    : DataSource<T>(std::forward<const U>(data))
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    GuardType(const GuardType&& data)
    : DataSource<T>(std::forward<const T>(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(const GuardType<U, DataSource2>&& data)
    : DataSource<T>(std::forward<const DataSource2<U> >(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
    }
    
    // rvalue constructor
    template<typename U, typename = enable_if_original_t<U> >
    GuardType(U&& data)
    : DataSource<T>(std::forward<U>(data))
    {
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
    }
    
    GuardType(GuardType&& data)
    : DataSource<T>(std::forward<GuardType>(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(GuardType<U, DataSource2>&& data)
    : DataSource<T>(std::forward<DataSource2<U> >(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
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
    
    // Do not use this
    //T* operator &() {
    //    GT_VALUE_BE_READED_DO(data);
    //    return &this->Data();
    //}
    //
    //const T* operator &()const {
    //    GT_VALUE_BE_READED_DO(data);
    //    return &this->Data();
    //}
    
    template<typename U, typename = enable_if_original_t<U> >
    const GuardType<T, DataSource>&
    operator = (const U& data) {
        GT_VALUE_CHANGED_DO__(*this);
        this->Data() = data;
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        return *this;
    }
    
    const GuardType& operator = (const GuardType& data) {
        GT_VALUE_CHANGED_DO__(*this);
        GT_VALUE_BE_READED_DO(data);
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<U, DataSource2>& data) {
        GT_VALUE_CHANGED_DO__(*this);
        GT_VALUE_BE_READED_DO(data);
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    // const rvalue assign operator
    template<typename U, typename = enable_if_original_t<U> >
    const GuardType<T, DataSource>&
    operator = (const U&& data) {
        GT_VALUE_CHANGED_DO__(*this);
        this->Data() = std::forward<const U>(data);
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        return *this;
    }
    
    const GuardType& operator = (const GuardType&& data) {
        GT_VALUE_CHANGED_DO__(*this);
        GT_VALUE_BE_READED_DO(data);
        this->Data() = std::forward<const T>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<U, DataSource2>&& data) {
        GT_VALUE_CHANGED_DO__(*this);
        GT_VALUE_BE_READED_DO(data);
        this->Data() = std::forward<const U>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    // rvalue assign operator
    template<typename U, typename = enable_if_original_t<U> >
    const GuardType<T, DataSource>&
    operator = (U&& data) {
        GT_VALUE_CHANGED_DO__(*this);
        this->Data() = std::forward<U>(data);
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data));
        return *this;
    }
    
    const GuardType& operator = (GuardType&& data) {
        GT_VALUE_CHANGED_DO__(*this);
        GT_VALUE_BE_READED_DO(data);
        this->Data() = std::forward<T>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (GuardType<U, DataSource2>&& data) {
        GT_VALUE_CHANGED_DO__(*this);
        GT_VALUE_BE_READED_DO(data);
        this->Data() = std::forward<U>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, "=", data, data.Data()));
        return *this;
    }
    
    template<typename U>
    decltype(std::declval<T>()[std::declval<U>()]) operator [] (const U& n) {
        decltype(std::declval<T>()[std::declval<U>()]) ret = this->Data()[n];
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "[";
                              GuardConfig::so << n;
                              GuardConfig::so << "]" << std::endl);
        return ret;
    }
    
    template<typename U>
    decltype(std::declval<const T>()[std::declval<U>()]) operator [] (const U& n) const {
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
        this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
    }
    
    template<typename ...Args>
    typename std::enable_if<std::is_same<typename std::result_of<T(Args...)>::type, void>::value>::type
    operator () (Args... args) const {
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
        typename std::result_of<T(Args...)>::type ret = this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(args...);
                              GuardConfig::so << ")" << std::endl);
        return ret;
    }
    
    template<typename U = T, typename = typename std::enable_if<std::is_pointer<U>::value>::type >
    typename std::remove_pointer<T>::type& operator* () {
        return *(this->Data());
    }
    
    template<typename U = T, typename = typename std::enable_if<std::is_pointer<U>::value>::type >
    const typename std::remove_pointer<T>::type& operator* () const {
        return *(this->Data());
    }
    
    template<typename U = T, typename = typename std::enable_if<GT::isSupportDereference<U>::value&&std::is_class<U>::value>::type >
    decltype(*(std::declval<U>())) operator* () {
        return *(this->Data());
    }
    
    template<typename U = T, typename = typename std::enable_if<std::is_pointer<U>::value>::type >
    decltype(*(std::declval<U>())) operator* () const {
        return *(this->Data());
    }
    
    void ValueBeReadDo() const {
        OLD_TO_NEW_VALUE_DO__(if(this->readedDo != NULL)
            this->readedDo(this->Data()));
    }
    
    // Can not guarantee the security of multithreading
    operator const T& () const {
        GT_VALUE_BE_READED_DO(*this);
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_TRACE_READ_SWITCH == false) return this->Data());
        OUTPUT_TRACE_SWITCH__(this->TraceReadGT("", *this));
        return this->Data();
    }
    
    // Can not guarantee the security of multithreading when member function called
    T* operator -> () {
        // may be wrote
        GT_VALUE_BE_READED_DO(*this);
        return &this->Data();
    }
    
    // Can not guarantee the security of multithreading when member function called
    const T* operator -> () const {
        GT_VALUE_BE_READED_DO(*this);
        return &this->Data();
    }
    
    const GuardType<T> operator ! () const {
        GT_VALUE_BE_READED_DO(*this);
        OUTPUT_TRACE_SWITCH__(this->TraceReadGT("!", GuardType<T>(!this->Data(), false)));
        GuardType<T> ret(!this->Data(), false);
        TRACE_STRING_SAVE____(ret.setExpress("!("+this->CalcString()+")"));
        return ret;
    }
    
    const GuardType<T> operator ~ () const {
        GT_VALUE_BE_READED_DO(*this);
        OUTPUT_TRACE_SWITCH__(this->TraceReadGT("~", GuardType<T>(~this->Data(), false)));
        GuardType<T>ret(~this->Data(), false);
        TRACE_STRING_SAVE____(ret.setExpress("~("+this->CalcString()+")"));
        return ret;
    }
    
    const GuardType& operator ++() {
        GT_VALUE_CHANGED_DO__(*this);
        ++this->Data();
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"+1"));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("++", *this, ""));
        return *this;
    }
    
    const GuardType<T> operator ++(int) {
        GT_VALUE_CHANGED_DO__(*this);
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "++"));
        GuardType<T> result(this->Data(), false);
        TRACE_STRING_SAVE____(result.setExpress(this->CalcString()));
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"+1"));
        ++(this->Data());
        return result;
    }
    
    const GuardType& operator --() {
        GT_VALUE_CHANGED_DO__(*this);
        --this->Data();
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"-1"));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("--", *this, ""));
        return *this;
    }
    
    const GuardType<T> operator --(int) {
        GT_VALUE_CHANGED_DO__(*this);
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "--"));
        GuardType<T> result(this->Data(), false);
        TRACE_STRING_SAVE____(result.setExpress(this->CalcString()));
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"-1"));
        --(this->Data());
        return result;
    }
    
    friend std::istream& operator >> (std::istream &si, GuardType& gt)
    {
        GT_VALUE_CHANGED_DO__(gt);
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
    
    friend std::ostream& operator << (std::ostream & so, const GuardType& gt)
    {
        GT_VALUE_BE_READED_DO(gt);
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return so << gt.Data();
                              if(GuardConfig::rule["<<"] == false) return so << gt.Data();
                              so << _SPACES << "TRACE: so<< " ;
                              so << gt.Id();
                              so << " : " << gt.Data() << std::endl);
        return so << gt.Data();
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
        if(GuardConfig::GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return;
        if(std::strcmp(frontOp, "")==0
           && std::strcmp(backOp, "")==0
           && GuardConfig::rule["="] == false) return;
        if(GuardConfig::rule[frontOp] == false
           && GuardConfig::rule[backOp] == false) return;
        GuardConfig::so << _SPACES << "TRACE: ";
        GuardConfig::so << frontOp;
        GuardConfig::so << this->Id();
        GuardConfig::so << backOp << " = ";
        GuardConfig::so << GT::NumericToString(result.Data()) << std::endl;
    }
    
    const std::string IdIndex() const {
        if(GuardConfig::GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        return this->Id();
    }
};

#endif /* GuardType_hpp */
