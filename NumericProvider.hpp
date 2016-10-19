#ifndef NumericProvider_hpp
#define NumericProvider_hpp

#include <thread>
#include <atomic>
#include <mutex>
#include <map>

//--------------------------------------------------------------------------
//                            class NumericProvider

template<typename T>
class NumericProvider {
    template<typename U>
    friend class NumericProvider;
    
    template<typename U, template<typename>class DataSource>
    friend class GuardType;
    
    using ReadedDOListType = std::multimap<const char*, std::function<void(const T& data)> >;
    using ChangedDOListType = std::multimap<const char*, std::function<void(T& newValue, const T oldValue)> >;
    
public:
    TRACE_STRING_SAVE____(std::string id);
    TRACE_STRING_SAVE____(std::string  calcExpres);
    MULTITHREAD_GUARD____(std::recursive_mutex mWritable);
    T data;
    
public:
    VALUE_BE_READED_DO___(ReadedDOListType readedDoList);
    OLD_TO_NEW_VALUE_DO__(ChangedDOListType changedDoList);
    
public:
    template<typename... Args>
    NumericProvider(Args... args)
    : data(args...) {
    }
    
    NumericProvider(const char* id = GuardConfig::defaultId)
    : data()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    NumericProvider(U& data)
    : data(data)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    NumericProvider(const U& data)
    : data(data)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    NumericProvider(NumericProvider& data)
    : data(data.data)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    NumericProvider(const NumericProvider& data)
    : data(data.data)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(NumericProvider<U>& data)
    : data(data.data) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(const NumericProvider<U>& data)
    : data(data.data) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    // rvalue constructor
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    NumericProvider(U&& data)
    : data(std::forward<U>(data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    NumericProvider(const U&& data)
    : data(std::forward<const U>(data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    NumericProvider(NumericProvider&& data)
    : data(std::forward<T>(data.data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    NumericProvider(const NumericProvider&& data)
    : data(std::forward<const T>(data.data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    void lock_guard() const {
        MULTITHREAD_GUARD____(const_cast<NumericProvider*>(this)->mWritable.lock());
    }
    
    void unlock_guard() const {
        MULTITHREAD_GUARD____(const_cast<NumericProvider*>(this)->mWritable.unlock());
    }
    
    T& Data() {
        return data;
    }
    
    const T& Data() const {
        return data;
    }
    
    void ValueBeReadedDo() const {
        VALUE_BE_READED_DO___(for(auto iter : this->readedDoList){ iter.second(this->data); });
    }
    
    void ValueChangedDo(const T& oldValue) {
        OLD_TO_NEW_VALUE_DO__(for(auto iter : this->changedDoList){ iter.second(this->data, oldValue); });
    }
    
    void addBeReadedDo(const std::function<void(const T&)>& func, const char* functionID = NULL) {
        VALUE_BE_READED_DO___(this->readedDoList.insert(std::make_pair(functionID, func)));
    }
    
    void addChangedDo(const std::function<void(T&)>& func, const char* functionID = NULL) {
        OLD_TO_NEW_VALUE_DO__(this->changedDoList.insert(std::make_pair(functionID, [=](T& newValue, const T oldValue) {
            func(newValue);
        })));
    }
    
    void addChangedDo(const std::function<void(T&,const T)>& func, const char* functionID = NULL) {
        OLD_TO_NEW_VALUE_DO__(this->changedDoList.insert(std::make_pair(functionID, func)));
    }
    
    size_t removeBeReadDo(const char* functionID) {
        VALUE_BE_READED_DO___(return this->readedDoList.erase(functionID));
        return 0;
    }
    
    size_t removeChangedDo(const char* functionID) {
        return this->changedDoList.erase(functionID);
    }
    
    const std::string& Id() const {
        TRACE_STRING_SAVE____(return id);
        return GuardConfig::defaultIdStr;
    }
    
    const std::string CalcString() const {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        TRACE_STRING_SAVE____(if(this->calcExpres != "") return this->calcExpres);
        if(GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
            return this->Id();
        } else {
            return GT::NumericToString(this->data);
        }
    }
    
    void setExpress(const std::string& express) const {
        TRACE_STRING_SAVE____(if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) const_cast<std::string&>(this->calcExpres) = express);
    }
    
    void OutputArray() const {}
};

#endif /* NumericProvider_hpp */
