#ifndef GuardType_hpp
#define GuardType_hpp

#include <functional>
#include "GuardConfig.hpp"
#include "IDExpressManager.hpp"
#include "TemplateTools.hpp"
#include "IndexProviderO.hpp"
#include "NumericProvider.hpp"
#include "TemporaryProvider.hpp"
#include "ThreadSafetyProvider.hpp"
#include "ValueObserverProvider.hpp"
#include "IDExpressProvider.hpp"

namespace gt {

//--------------------------------------------------------------------------
//                            class GuardType

template<typename T, template<typename> class DataSource, typename... Providers>
class GuardType : public DataSource<T>, public Providers...
{
    template<typename U, template<typename>class DataSource2, typename... Providers2>
    friend class GuardType;
    
    using SelfType = GuardType<T, DataSource, Providers...>;

    template <typename U, typename... Providers2>
    using GTemporaryType = GuardType<U, TemporaryProvider, Providers2...>;
    
    template<typename U,
            bool Thread = gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value,
            bool Observer = gt::isContainFirstType<ValueObserverProvider<U>, Providers...>::value,
            bool Express = gt::isContainFirstType<IDExpressProvider, Providers...>::value,
            bool ID = gt::isExistArrayId<DataSource<T> >::value,
            typename ResType = std::conditional_t<Express || ID, GTemporaryType<U, IDExpressProvider>, GTemporaryType<U> > >
    using ResultType = std::conditional_t<Thread || Observer || Express || ID, ResType, U>;
    
    
    class LockGuarder
    {
    public:
        inline LockGuarder(const GuardType& gt) noexcept
        : gt(const_cast<GuardType&>(gt))
        {
            if(std::is_base_of<ThreadSafetyProvider, gt::RawType<decltype(gt)> >::value) {
                ((ThreadSafetyProvider&)gt).thread_lock();
            }
        }
        
        inline ~LockGuarder() noexcept
        {
            if(std::is_base_of<ThreadSafetyProvider, gt::RawType<decltype(gt)> >::value) {
                ((ThreadSafetyProvider&)gt).thread_unlock();
            }
        }
        
    protected:
        GuardType& gt;
    };
    
    
    class ValueChangeGuarder
    {
    public:
        inline ValueChangeGuarder(const GuardType& gt) noexcept
        : gt(const_cast<GuardType&>(gt)), oldValue(gt.Data())
        {
            
        }
        
        template<typename U = T,
                typename = std::enable_if_t<gt::isNEqualable<U, U>::value> >
        inline void ChangedCallback(int* = NULL) const
        {
            auto& newData = gt.Data();
            if (oldValue != newData) {
                if (gt::isValueObserverProvider<SelfType>::value)
                    ((ValueObserverProvider<typename gt::RawType<decltype(gt)>::value_type>&)gt).CallWroteCallback(newData, oldValue);
                if(gt::isIndexProvider<decltype(gt)>::value) {
                    OUTPUT_TRACE_SWITCH__(gt::OutputArray(gt));
                }
            }
        }

        template<typename U = T,
                typename = std::enable_if_t<!gt::isNEqualable<U, U>::value>,
                typename = std::enable_if_t<gt::isEqualable<U, U>::value> >
        inline void ChangedCallback(short* = NULL) const
        {
            auto& newData = gt.Data();
            if (!(oldValue == newData)) {
                if (gt::isValueObserverProvider<SelfType>::value)
                    ((ValueObserverProvider<typename gt::RawType<decltype(gt)>::value_type>&)gt).CallWroteCallback(newData, oldValue);
                if(gt::isIndexProvider<decltype(gt)>::value) {
                    OUTPUT_TRACE_SWITCH__(gt::OutputArray(gt));
                }
            }
        }
        
        template<typename U = T,
                typename = std::enable_if_t<!gt::isNEqualable<U, U>::value>,
                typename = std::enable_if_t<!gt::isEqualable<U, U>::value> >
        void ChangedCallback(double* = NULL) const
        {
        }
        
        inline ~ValueChangeGuarder()
        {
            ChangedCallback();
        }
    protected:
        T oldValue;
        GuardType& gt;
    };
    
    
    class FunctionOverGuarder
    {
    public:
        inline FunctionOverGuarder(const GuardType& data) noexcept
        : data(data), lockGuarder(data), valueChangeGuarder(data)
        {
        }
        
        inline T* operator -> () noexcept
        {
            return const_cast<T*>(&data.Data());
        }
        
        inline const T* operator -> () const noexcept
        {
            return &data.Data();
        }
        
    protected:
        const GuardType& data;
        LockGuarder lockGuarder;
        ValueChangeGuarder valueChangeGuarder;
    };
    
    inline void ReadCallback() const
    {
        if(gt::isValueObserverProvider<SelfType>::value) {
            ((ValueObserverProvider<typename gt::RawType<decltype(*this)>::value_type>&)(*this)).CallReadedCallback(this->Data());
        }
    }
    
    
public:
    typedef T value_type;
    
    using isGuardType = SelfType;
    
    
#define FRIEND_CALC_FUNC(op)                                                            \
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>     \
    friend const auto operator op (const U & data, const GuardType& g2)                 \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(g2));                                 \
        VALUE_BE_READED_DO___(g2.ReadCallback());                                       \
        ResultType<decltype(data op g2.Data())> result(data op g2.Data());              \
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(data, #op, g2, result));                \
        TRACE_STRING_SAVE____(gt::SetExpress(result, gt::PackWithBracket(data, #op, g2)));\
        return result;                                                                  \
    }
    
    FRIEND_CALC_FUNC(*)
    FRIEND_CALC_FUNC(/)
    FRIEND_CALC_FUNC(+)
    FRIEND_CALC_FUNC(-)
    FRIEND_CALC_FUNC(%)
    FRIEND_CALC_FUNC(^)
    FRIEND_CALC_FUNC(&)
    FRIEND_CALC_FUNC(|)
    FRIEND_CALC_FUNC(<<)
    FRIEND_CALC_FUNC(>>)
    
    
#define FRIEND_BOOL_FUNC(op)                                                            \
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>     \
    friend const auto operator op (const U & data, const GuardType& g2)                 \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(g2));                                 \
        VALUE_BE_READED_DO___(g2.ReadCallback());                                       \
        ResultType<decltype(data op g2.Data())> result(data op g2.Data());              \
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(data, #op, g2, result));                \
        TRACE_STRING_SAVE____(gt::SetExpress(result, gt::PackWithBracket(data, #op, g2)));\
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
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>     \
    friend const U& operator assignOp (U & data, const GuardType& g2)                   \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(g2));                                 \
        VALUE_BE_READED_DO___(g2.ReadCallback());                                       \
        OUTPUT_TRACE_SWITCH__(T reserveData = data);                                    \
        data assignOp g2.Data();                                                        \
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(reserveData, #assignOp, g2, data));     \
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
    
    
#define IMPLEMENT_CALC_FUNCTION(op)                                                     \
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>     \
    const auto operator op (const U& data) const                                        \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));                              \
        VALUE_BE_READED_DO___(this->ReadCallback());                                    \
        ResultType<decltype(this->Data() op data)> result(this->Data() op data);        \
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, #op, data, result));             \
        TRACE_STRING_SAVE____(gt::SetExpress(result, gt::PackWithBracket(*this, #op, data)));\
        return result;                                                                  \
    }                                                                                   \
    \
    template<typename U, template<typename>class DataSource2, typename... Providers2,   \
            typename GType = GuardType<U, DataSource2, Providers2...> >                 \
    const auto operator op (const GuardType<U, DataSource2, Providers2...>& data) const \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(typename GType::LockGuarder guarder2(data));              \
        VALUE_BE_READED_DO___(data.ReadCallback());                                     \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));                              \
        VALUE_BE_READED_DO___(this->ReadCallback());                                    \
        ResultType<decltype(this->Data() op data.Data())> result(this->Data() op data.Data());\
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, #op, data, result));             \
        TRACE_STRING_SAVE____(gt::SetExpress(result, gt::PackWithBracket(*this, #op, data)));\
        return result;                                                                  \
    }
    
    IMPLEMENT_CALC_FUNCTION(*)
    IMPLEMENT_CALC_FUNCTION(/)
    IMPLEMENT_CALC_FUNCTION(+)
    IMPLEMENT_CALC_FUNCTION(-)
    IMPLEMENT_CALC_FUNCTION(%)
    IMPLEMENT_CALC_FUNCTION(^)
    IMPLEMENT_CALC_FUNCTION(&)
    IMPLEMENT_CALC_FUNCTION(|)
    IMPLEMENT_CALC_FUNCTION(<<)
    IMPLEMENT_CALC_FUNCTION(>>)
    
    
#define IMPLEMENT_BOOL_FUNCTION(op)                                                     \
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>     \
    const auto operator op (const U& data) const                                        \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));                              \
        VALUE_BE_READED_DO___(this->ReadCallback());                                    \
        ResultType<decltype(this->Data() op data)> result(this->Data() op data);        \
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, #op, data, result));             \
        TRACE_STRING_SAVE____(gt::SetExpress(result, gt::PackWithBracket(*this, #op, data)));\
        return result;                                                                  \
    }                                                                                   \
    \
    template<typename U, template<typename>class DataSource2, typename... Providers2,   \
            typename GType = GuardType<U, DataSource2, Providers2...> >                 \
    const auto operator op (const GuardType<U, DataSource2, Providers2...>& data) const \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(typename GType::LockGuarder guarder2(data));              \
        VALUE_BE_READED_DO___(data.ReadCallback());                                     \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));                              \
        VALUE_BE_READED_DO___(this->ReadCallback());                                    \
        ResultType<decltype(this->Data() op data.Data())> result(this->Data() op data.Data());\
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, #op, data, result));             \
        TRACE_STRING_SAVE____(gt::SetExpress(result, gt::PackWithBracket(*this, #op, data)));\
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
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>     \
    const GuardType & operator assignOp (const U& data)                                 \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));                              \
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));                      \
        this->Data() assignOp data;                                                     \
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, #assignOp, data, this->Data())); \
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::PackWithBracket(*this, #op, data))); \
        return *this;                                                                   \
    }                                                                                   \
    \
    template<typename U, template<typename>class DataSource2, typename... Providers2,   \
            typename GType = GuardType<U, DataSource2, Providers2...> >                 \
    const GuardType & operator assignOp (const GuardType<U, DataSource2, Providers2...>& data) \
    {                                                                                   \
        ENSURE_THREAD_SAFETY_(typename GType::LockGuarder guarder2(data));              \
        VALUE_BE_READED_DO___(data.ReadCallback());                                     \
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));                              \
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));                      \
        this->Data() assignOp data.Data();                                              \
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, #assignOp, data, this->Data())); \
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::PackWithBracket(*this, #op, data))); \
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
    : DataSource<T>(args...)
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
    }
    
    GuardType(const char* id = gt::defaultId)  noexcept 
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId(id));
    }
    
    // construct from array
    template<typename U, typename... Providers2>
    GuardType(const IndexProvider<U, 1, Providers2...>& data, int n) noexcept 
    : DataSource<T>(data, n)
    {
        if (std::is_base_of<ValueObserverProvider<T>, SelfType>::value) {
            ((ValueObserverProvider<T>*)this)->addr = &this->Data();
        }
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(*this)));
    }
    
    template<typename... Providers2>
    GuardType(const GuardArray<T, 1, Providers2...>& array, int n)
    : DataSource<T>(array, n)
    {
        if (std::is_base_of<ValueObserverProvider<T>, SelfType>::value) {
            ((ValueObserverProvider<T>*)this)->addr = &this->Data();
        }
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    GuardType(U& data)
    : DataSource<T>(data)
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data));
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    GuardType(const U& data)
    : DataSource<T>(data)
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data));
    }
    
    GuardType(GuardType& data)
    : DataSource<T>(static_cast<DataSource<T>&>(data))
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    GuardType(const GuardType& data)
    : DataSource<T>(static_cast<const DataSource<T>&>(data))
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    template<typename U, template<typename>class DataSource2, typename... Providers2>
    GuardType(GuardType<U, DataSource2, Providers2...>& data)
    : DataSource<T>(data.Data())
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    template<typename U, template<typename>class DataSource2, typename... Providers2>
    GuardType(const GuardType<U, DataSource2, Providers2...>& data)
    : DataSource<T>(data.Data())
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    // rvalue constructor
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    GuardType(U&& data)
    : DataSource<T>(std::forward<U>(data))
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    GuardType(const U&& data)
    : DataSource<T>(std::forward<const U>(data))
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    GuardType(GuardType&& data)
    : DataSource<T>(std::forward<DataSource<T> >(data))
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    GuardType(const GuardType&& data)
    : DataSource<T>(std::forward<const DataSource<T> >(data))
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    template<typename U, template<typename>class DataSource2, typename... Providers2>
    GuardType(GuardType<U, DataSource2, Providers2...>&& data)
    : DataSource<T>(std::forward<U>(data))
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    template<typename U, template<typename>class DataSource2, typename... Providers2>
    GuardType(const GuardType<U, DataSource2, Providers2...>&& data)
    : DataSource<T>(std::forward<const U>(data))
    {
        if (std::is_base_of<IDExpressProvider, SelfType>::value && !gt::isTemporaryProvider<SelfType>::value)
            ((IDExpressProvider*)this)->initId(gt::GetNewId());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    const GuardType& operator = (U& data)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = data;
        TRACE_STRING_SAVE____(gt::SetExpress(*this, ""));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    const GuardType& operator = (const U& data)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = data;
        TRACE_STRING_SAVE____(gt::SetExpress(*this, ""));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    const GuardType& operator = (GuardType& data)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder2(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    const GuardType& operator = (const GuardType& data)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder2(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2, typename... Providers2,
            typename GType = GuardType<U, DataSource2, Providers2...> >
    const GuardType& operator = (GuardType<U, DataSource2, Providers2...>& data)
    {
        ENSURE_THREAD_SAFETY_(typename GType::LockGuarder guarder2(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2, typename... Providers2,
            typename GType = GuardType<U, DataSource2, Providers2...> >
    const GuardType& operator = (const GuardType<U, DataSource2, Providers2...>& data)
    {
        ENSURE_THREAD_SAFETY_(typename GType::LockGuarder guarder2(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = data.Data();
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    // rvalue assign operator
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    const GuardType& operator = (U&& data)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = std::forward<U>(data);
        TRACE_STRING_SAVE____(gt::SetExpress(*this, ""));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    const GuardType& operator = (const U&& data)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = std::forward<const U>(data);
        TRACE_STRING_SAVE____(gt::SetExpress(*this, ""));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    const GuardType& operator = (GuardType&& data)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder2(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = std::forward<T>(data.Data());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    const GuardType& operator = (const GuardType&& data)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder2(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = std::forward<const T>(data.Data());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2,
            typename GType = GuardType<U, DataSource2> >
    const GuardType& operator = (GuardType<U, DataSource2>&& data)
    {
        ENSURE_THREAD_SAFETY_(typename GType::LockGuarder guarder2(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = std::forward<U>(data.Data());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    template<typename U, template<typename>class DataSource2, typename... Providers2,
            typename GType = GuardType<U, DataSource2, Providers2...> >
    const GuardType& operator = (const GuardType<U, DataSource2, Providers2...>&& data)
    {
        ENSURE_THREAD_SAFETY_(typename GType::LockGuarder guarder2(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data() = std::forward<const U>(data.Data());
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(data)));
        OUTPUT_TRACE_SWITCH__(gt::OutputOpTrace(*this, "=", data, data.Data()));
        OUTPUT_TRACE_SWITCH__(gt::OutputExpress(*this));
        return *this;
    }
    
    template<typename U>
    decltype(std::declval<T>()[std::declval<U>()]) operator [] (const U& n)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        decltype(std::declval<T>()[std::declval<U>()]) result = this->Data()[n];
        OUTPUT_TRACE_SWITCH__(gt::OutputBracketOpTrace(*this, "[", "]", n));
        return result;
    }
    
    template<typename U>
    decltype(std::declval<const T>()[std::declval<U>()]) operator [] (const U& n) const
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        decltype(std::declval<const T>()[std::declval<U>()]) result = this->Data()[n];
        OUTPUT_TRACE_SWITCH__(gt::OutputBracketOpTrace(*this, "[", "]", n));
        return result;
    }
    
    template<typename ...Args>
    std::enable_if_t<std::is_same<typename std::result_of<T(Args...)>::type, void>::value>
    operator () (Args... args)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(gt::OutputBracketOpTrace(*this, "(", ")", args...));
    }
    
    template<typename ...Args>
    std::enable_if_t<std::is_same<typename std::result_of<T(Args...)>::type, void>::value>
    operator () (Args... args) const
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(gt::OutputBracketOpTrace(*this, "(", ")", args...));
    }
    
    template<typename ...Args>
    std::enable_if_t<!std::is_same<typename std::result_of<T(Args...)>::type, void>::value,
                     typename std::result_of<T(Args...)>::type>
    operator () (Args... args)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        typename std::result_of<T(Args...)>::type result = this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(gt::OutputBracketOpTrace(*this, "(", ")", args...));
        return result;
    }
    
    template<typename ...Args>
    std::enable_if_t<!std::is_same<typename std::result_of<T(Args...)>::type, void>::value,
                     typename std::result_of<T(Args...)>::type>
    operator () (Args... args) const
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        typename std::result_of<T(Args...)>::type result = this->Data()(args...);
        OUTPUT_TRACE_SWITCH__(gt::OutputBracketOpTrace(*this, "(", ")", args...));
        return result;
    }
    
    template<typename U = T, typename = std::enable_if_t<gt::isDereferencable<U>::value>>
    decltype(*(std::declval<U>())) operator* ()
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        decltype(*(std::declval<U>())) result = *(this->Data());
        return result;
    }
    
    template<typename U = T, typename = std::enable_if_t<gt::isDereferencable<U>::value>>
    decltype(*(std::declval<U>())) operator* () const
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        decltype(*(std::declval<U>())) result = *(this->Data());
        return result;
    }
    
    template<typename U = T, typename = std::enable_if_t<gt::isDereferencable<U>::value>>
    auto operator & ()
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        return &this->Data();
    }
    
    template<typename U = T, typename = std::enable_if_t<gt::isDereferencable<U>::value>>
    auto operator & () const
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        return &this->Data();
    }
    
    operator std::conditional_t<gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value, const T, const T&> () const
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_TRACE_READ_SWITCH == true) gt::OutputSingleOpTrace("", *this, ""));
        std::conditional_t<gt::isContainFirstType<ThreadSafetyProvider, Providers...>::value, const T, const T&> result = this->Data();
        return result;
    }
    
    inline FunctionOverGuarder operator -> () noexcept
    {
        return FunctionOverGuarder(*this);
    }
    
    inline const FunctionOverGuarder operator -> () const noexcept
    {
        return FunctionOverGuarder(*this);
    }
    
    const auto operator ! () const
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        OUTPUT_TRACE_SWITCH__(gt::OutputSingleOpTrace("!", GuardType<T, TemporaryProvider>(!this->Data()), ""));
        ResultType<decltype(!this->Data())> result(!this->Data());
        TRACE_STRING_SAVE____(gt::SetExpress(result, "!("+gt::CalcString(*this)+")"));
        return result;
    }
    
    const auto operator ~ () const
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        VALUE_BE_READED_DO___(this->ReadCallback());
        OUTPUT_TRACE_SWITCH__(gt::OutputSingleOpTrace("~", GuardType<T, TemporaryProvider>(~this->Data()), ""));
        ResultType<decltype(~this->Data())> result(~this->Data());
        TRACE_STRING_SAVE____(gt::SetExpress(result, "~("+gt::CalcString(*this)+")"));
        return result;
    }
    
    const GuardType& operator ++()
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        ++this->Data();
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(*this)+"+1"));
        OUTPUT_TRACE_SWITCH__(gt::OutputSingleOpTrace("++", *this, ""));
        return *this;
    }
    
    const auto operator ++(int)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        OUTPUT_TRACE_SWITCH__(gt::OutputSingleOpTrace("", *this, "++"));
        ResultType<decltype(this->Data())> result(this->Data());
        TRACE_STRING_SAVE____(gt::SetExpress(result, gt::CalcString(*this)));
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(*this)+"+1"));
        ++(this->Data());
        return result;
    }
    
    const GuardType& operator --()
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        --this->Data();
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(*this)+"-1"));
        OUTPUT_TRACE_SWITCH__(gt::OutputSingleOpTrace("--", *this, ""));
        return *this;
    }
    
    const auto operator --(int)
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(*this));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(*this));
        OUTPUT_TRACE_SWITCH__(gt::OutputSingleOpTrace("", *this, "--"));
        ResultType<decltype(this->Data())> result(this->Data());
        TRACE_STRING_SAVE____(gt::SetExpress(result, gt::CalcString(*this)));
        TRACE_STRING_SAVE____(gt::SetExpress(*this, gt::CalcString(*this)+"-1"));
        --(this->Data());
        return result;
    }
    
    friend std::istream& operator >> (std::istream &si, GuardType& data) noexcept
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(data));
        OLD_TO_NEW_VALUE_DO__(ValueChangeGuarder vguarder(data));
        if(GuardConfig::_ARRAY_IO_TIP_SWITCH == true && si.rdbuf() == std::cin.rdbuf()) {
            std::cout << "Please input Data ";
            std::cout << gt::Id(data);
            std::cout << ": ";
        }
        si >> data.Data();
        return si;
    }
    
    friend std::ostream& operator << (std::ostream & so, const GuardType& data) noexcept
    {
        ENSURE_THREAD_SAFETY_(LockGuarder guarder(data));
        VALUE_BE_READED_DO___(data.ReadCallback());
        so << data.Data();
        OUTPUT_TRACE_SWITCH__(if(GuardConfig::_OUTPUT_TRACE_SWITCH == true)
                              if(GuardConfig::rule["<<"] == true) {
                                  std::cout << _SPACES << "TRACE: so<< " ;
                                  std::cout << gt::Id(data);
                                  std::cout << " : " << data.Data() << std::endl;});
        return so;
    }
};
    
}

#endif /* GuardType_hpp */
