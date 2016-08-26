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
    VALUE_BE_READED_DO___(                                                      \
        if ((gt).ValueBeReadedDoing != NULL)                                    \
            (gt).ValueBeReadedDoing((gt).Data()));

#define GT_VALUE_CHANGED_DO__(gt)                                               \
    OLD_TO_NEW_VALUE_DO__(                                                      \
        if ((gt).ValueChangedDoingWithOldAndNewValue != NULL)                   \
            (gt).ValueChangedDoingWithOldAndNewValue(oldValue, (gt).Data()));   \
    VALUE_CHANGED_DO_____(                                                      \
        if ((gt).ValueChangedDoing != NULL)                                     \
            (gt).ValueChangedDoing((gt).Data()));


template<typename T, template<typename> class DataSource>
class GuardType : protected DataSource<T> {
    template<typename U, template<typename>class DataSource2>
    friend class GuardType;
    
    template<typename U, typename V = void*&>
    using enable_if_original_t = typename std::enable_if<GT::isOriginalType<U>::value, typename std::conditional<std::is_same<void*&, V>::value, U, V>::type >::type;
    
public:
    typedef T value_type;
    
public:
    VALUE_CHANGED_DO_____(std::function<void(T& data)> ValueChangedDoing);
    
    VALUE_BE_READED_DO___(std::function<void(const T& data)> ValueBeReadedDoing);
    
    OLD_TO_NEW_VALUE_DO__(std::function<void(const T oldValue, T& newValue)> ValueChangedDoingWithOldAndNewValue);
    
    TRACE_STRING_SAVE____(std::string  calcExpres);
    
public:
    friend void swap(const GuardType& gt, const GuardType& gt2) {
        T& r1 = gt.Data();
        T& r2 = gt2.Data();
        T temp = r1;
        r1 = r2;
        r2 = temp;
        if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return;
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "swap(";
                              GuardConfig::so << gt.Id() << ", ";
                              GuardConfig::so << gt2.Id() << ")" << std::endl);
        OUTPUT_TRACE_SWITCH__(gt.OutputArray());
        OUTPUT_TRACE_SWITCH__(gt2.OutputArray());
    }
    
    friend std::istream& operator >> (std::istream &si, GuardType& gt)
    {
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
        gt.OutputArray();
        return si;
    }
    
    friend std::ostream& operator << (std::ostream & so, const GuardType& gt)
    {
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_OUTPUT_TRACE_SWITCH == false) return so << gt.Data();
                              if(GuardConfig::rule["<<"] == false) return so << gt.Data();
                              so << _SPACES << "TRACE: so<< " ;
                              so << gt.Id();
                              so << " : " << gt.Data() << std::endl;)
        return so << gt.Data();
    }
    
    template<typename ...Args>
    decltype(std::declval<T>()(std::declval<Args>()...)) operator () (Args... args) {
        decltype(std::declval<T>()(std::declval<Args>()...)) ret = this->Data().operator() (args...);
        OUTPUT_TRACE_SWITCH__(GuardConfig::so << _SPACES << "TRACE: ";
                              GuardConfig::so << "Called " + this->Id() + "(";
                              GT::Output(GuardConfig::so, ", ", args...);
                              GuardConfig::so << ")" << std::endl);
        return ret;
    }
    
    
#define FRIEND_CALC_FUNC(op, CalcReturnType)                                            \
    template<typename U>                                                                \
    friend const GuardType<CalcReturnType(enable_if_original_t<U>, op, T)>              \
    operator op (const U & data, const GuardType& g2) {                                 \
        CalcResultType(U, op, T) result(data op g2.Data());                             \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(data, #op, g2, result));                    \
        GT_VALUE_BE_READED_DO(g2);                                                      \
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
    template<typename U>                                                                \
    friend const GuardType<enable_if_original_t<U, bool> >                              \
    operator op (const U & data, const GuardType& g2) {                                 \
        bool result(data op g2.Data());                                                 \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(data, #op, g2, result));                    \
        GT_VALUE_BE_READED_DO(g2);                                                      \
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
        OUTPUT_TRACE_SWITCH__(T reserveData = data);                                    \
        T result(data assignOp g2.Data());                                              \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(reserveData, #assignOp, g2, result));       \
        GT_VALUE_BE_READED_DO(g2);                                                      \
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
    template<typename U>                                                                \
    const GuardType<CalcReturnType(T, op, enable_if_original_t<U>)>                     \
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
    template<typename U>                                                                \
    const GuardType<enable_if_original_t<U, bool> >                                     \
    operator op (const U& data) const {                                                 \
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
    template<typename U, template<typename>class DataSource2>                           \
    const GuardType<enable_if_original_t<U, bool> >                                     \
    operator op (const GuardType<U, DataSource2>& data) const {                         \
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
    template<typename U>                                                                \
    const GuardType<enable_if_original_t<U, T>, DataSource>&                            \
        operator assignOp (const U& data) {                                             \
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());                               \
        this->Data() assignOp data;                                                     \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #assignOp, data, this->Data()));     \
        TRACE_STRING_SAVE____(this->setExpress(GT::PackWithBracket(*this, #op, data))); \
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());                                    \
        OUTPUT_TRACE_SWITCH__(this->OutputArray());                                     \
        GT_VALUE_CHANGED_DO__(*this);                                                   \
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
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());                               \
        GT_VALUE_BE_READED_DO(data);                                                    \
        this->Data() assignOp data.Data();                                              \
        OUTPUT_TRACE_SWITCH__(OutputOpTrace(*this, #assignOp, data, this->Data()));     \
        TRACE_STRING_SAVE____(this->setExpress(GT::PackWithBracket(*this, #op, data))); \
        OUTPUT_TRACE_SWITCH__(this->OutputExpres());                                    \
        OUTPUT_TRACE_SWITCH__(this->OutputArray());                                     \
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
    TRACE_STRING_SAVE____(:DataSource<T>(id))
    {
    }
    
    template<typename U>
    GuardType(const U& data, enable_if_original_t<U, bool> = 0)
    : DataSource<T>(data)
    { // operator result temp value
    }
    
    template<typename U>
    GuardType(const U& data, enable_if_original_t<U>* = 0)
    : DataSource<T>(data)
    {
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));
    }
    
    GuardType(const GuardType& data)
    : DataSource<T>(data)
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(const GuardType<U, DataSource2>& data)
    : DataSource<T>(data)
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    // const rvalue constructor
    template<typename U>
    GuardType(const U&& data, enable_if_original_t<U>* = 0)
    : DataSource<T>(std::forward<const U>(data))
    {
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));
    }
    
    GuardType(const GuardType&& data)
    : DataSource<T>(std::forward<const T>(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(const GuardType<U, DataSource2>&& data)
    : DataSource<T>(std::forward<const DataSource2<U> >(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    // rvalue constructor
    template<typename U>
    GuardType(U&& data, enable_if_original_t<U>* = 0)
    : DataSource<T>(std::forward<U>(data))
    {
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));
    }
    
    GuardType(GuardType&& data)
    : DataSource<T>(std::forward<GuardType>(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
    }
    
    template<typename U, template<typename>class DataSource2>
    GuardType(GuardType<U, DataSource2>&& data)
    : DataSource<T>(std::forward<DataSource2<U> >(data))
    {
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
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
    //    GT_VALUE_BE_READED_DO___(data);
    //    return &this->Data();
    //}
    //
    //const T* operator &()const {
    //    GT_VALUE_BE_READED_DO___(data);
    //    return &this->Data();
    //}
    
    template<typename U>
    const GuardType<enable_if_original_t<U, T>, DataSource>&
    operator = (const U& data) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = data;
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    const GuardType& operator = (const GuardType& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<U, DataSource2>& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    // const rvalue assign operator
    template<typename U>
    const GuardType<enable_if_original_t<U, T>, DataSource>&
    operator = (const U&& data) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = std::forward<const U>(data);
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    const GuardType& operator = (const GuardType&& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = std::forward<const T>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (const GuardType<U, DataSource2>&& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = std::forward<const U>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    // rvalue assign operator
    template<typename U>
    const GuardType<enable_if_original_t<U, T>, DataSource>&
    operator = (U&& data) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = std::forward<U>(data);
        TRACE_STRING_SAVE____(this->setExpress(""));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    const GuardType& operator = (GuardType&& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = std::forward<T>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2>
    const GuardType& operator = (GuardType<U, DataSource2>&& data) {
        GT_VALUE_BE_READED_DO(data);
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        this->Data() = std::forward<U>(data.Data());
        TRACE_STRING_SAVE____(this->setExpress(data.CalcString()));
        OUTPUT_TRACE_SWITCH__(this->TraceAssignWithGT(data));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }

    operator const T& () const {
        GT_VALUE_BE_READED_DO(*this);
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_TRACE_READ_SWITCH == false) return this->Data());
        OUTPUT_TRACE_SWITCH__(this->TraceReadGuardType("", *this));
        return this->Data();
    }
    
    const T* operator -> () const {
        return &this->Data();
    }
    
    T* operator -> () {
        return &this->Data();
    }
    
    const GuardType<T> operator ! () const {
        GT_VALUE_BE_READED_DO(*this);
        OUTPUT_TRACE_SWITCH__(this->TraceReadGuardType("!", GuardType<T>(!this->Data(), false)));
        GuardType<T> ret(!this->Data(), false);
        TRACE_STRING_SAVE____(ret.setExpress("!("+this->CalcString()+")"));
        return ret;
    }
    
    const GuardType<T> operator ~ () const {
        GT_VALUE_BE_READED_DO(*this);
        OUTPUT_TRACE_SWITCH__(this->TraceReadGuardType("~", GuardType<T>(~this->Data(), false)));
        GuardType<T>ret(~this->Data(), false);
        TRACE_STRING_SAVE____(ret.setExpress("~("+this->CalcString()+")"));
        return ret;
    }
    
    const GuardType& operator ++() {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        ++this->Data();
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"+1"));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("++", *this, ""));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    const GuardType<T> operator ++(int) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "++"));
        GuardType<T> result(this->Data(), false);
        TRACE_STRING_SAVE____(result.setExpress(this->CalcString()));
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"+1"));
        (this->Data())++;
        GT_VALUE_CHANGED_DO__(*this);
        return result;
    }
    
    const GuardType& operator --() {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        --this->Data();
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"-1"));
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("--", *this, ""));
        GT_VALUE_CHANGED_DO__(*this);
        return *this;
    }
    
    const GuardType<T> operator --(int) {
        OLD_TO_NEW_VALUE_DO__(T oldValue = this->Data());
        OUTPUT_TRACE_SWITCH__(this->TraceSelfIncrease("", *this, "--"));
        GuardType<T> result(this->Data(), false);
        TRACE_STRING_SAVE____(result.setExpress(this->CalcString()));
        TRACE_STRING_SAVE____(this->setExpress(this->CalcString()+"-1"));
        (this->Data())--;
        GT_VALUE_CHANGED_DO__(*this);
        return result;
    }
    
    void OutputExpres() const {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) GuardConfig::so
            << _SPACES << "EXPRES:"
            << this->Id() << " = "
            << this->CalcString() << std::endl;
    }
    
    template<typename U, typename V, typename W>
    static void OutputOpTrace(const U& data1,
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
        GuardConfig::so << this->Id();
        GuardConfig::so << " : ";
        GuardConfig::so << result.Data() <<std::endl;
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
            GuardConfig::so << this->Id();
            GuardConfig::so << backOp << " = ";
            GuardConfig::so << result.Data() << std::endl;
        }
        if(backOp == "") {
            this->OutputExpres();
            this->OutputArray();
        }
    }
    
    template<typename U>
    void TraceAssignWithT(const U& result, enable_if_original_t<U>* = 0) const
    {
        OutputOpTrace(*this, "=", result, result);
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH
           && GuardConfig::rule["="] == true) GuardConfig::so
            << _SPACES << "EXPRES:"
            << this->Id() << " = "
            << GT::NumericToString(this->Data()) << std::endl;
        this->OutputArray();
    }
    
    template<typename U, template<typename>class DataSource2>
    void TraceAssignWithGT(const GuardType<U, DataSource2>& data) const
    {
        OutputOpTrace(*this, "=", data, data.Data());
        this->OutputExpres();
        this->OutputArray();
    }
    
    const std::string CalcString() const {
        TRACE_STRING_SAVE____(if(this->calcExpres != "") return this->calcExpres);
        
        if(GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
            return this->Id();
        } else {
            return GT::NumericToString(this->Data());
        }
    }
    
    const std::string IdIndex() const {
        return this->Id();
    }
    
    void setExpress(const std::string& express) const {
        TRACE_STRING_SAVE____(if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) const_cast<std::string&>(this->calcExpres) = express);
    }
    
};

#endif /* GuardType_hpp */
