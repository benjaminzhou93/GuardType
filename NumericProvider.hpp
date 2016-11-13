#ifndef NumericProvider_hpp
#define NumericProvider_hpp

#include "IDExpressManager.hpp"

//--------------------------------------------------------------------------
//                            class NumericProvider

template<typename T>
class NumericProvider {
    template<typename U>
    friend class NumericProvider;
    
    template<typename U, template<typename>class DataSource, typename... Providers>
    friend class GuardType;
    
public:
    TRACE_STRING_SAVE____(std::string id);
    TRACE_STRING_SAVE____(std::string  calcExpres);
    T data;
    
public:
    template<typename... Args>
    NumericProvider(Args... args)
    : data(args...) {
    }
    
    NumericProvider(const char* id = IDExpressManager::defaultId)
    : data()
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewId(id));
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    NumericProvider(U& data)
    : data(data)
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewId());
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    NumericProvider(const U& data)
    : data(data)
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewId());
    }
    
    NumericProvider(NumericProvider& data)
    : data(data.data)
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewIdByIncreaseId(data.id));
    }
    
    NumericProvider(const NumericProvider& data)
    : data(data.data)
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(NumericProvider<U>& data)
    : data(data.data) {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(const NumericProvider<U>& data)
    : data(data.data) {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewIdByIncreaseId(data.id));
    }
    
    // rvalue constructor
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    NumericProvider(U&& data)
    : data(std::forward<U>(data))
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewId());
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    NumericProvider(const U&& data)
    : data(std::forward<const U>(data))
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewId());
    }
    
    NumericProvider(NumericProvider&& data)
    : data(std::forward<T>(data.data))
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewIdByIncreaseId(data.id));
    }
    
    NumericProvider(const NumericProvider&& data)
    : data(std::forward<const T>(data.data))
    {
        TRACE_STRING_SAVE____(this->id = IDExpressManager::GetNewIdByIncreaseId(data.id));
    }
    
    T& Data() {
        return data;
    }
    
    const T& Data() const {
        return data;
    }
    
    const std::string& Id() const {
        TRACE_STRING_SAVE____(return id);
        return IDExpressManager::defaultIdStr;
    }
    
    const std::string CalcString() const {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        TRACE_STRING_SAVE____(if(this->calcExpres != "") return this->calcExpres);
        if(GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
            return this->Id();
        } else {
            return IDExpressManager::NumericToString(this->data);
        }
    }
    
    void setExpress(const std::string& express) const {
        TRACE_STRING_SAVE____(if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) const_cast<std::string&>(this->calcExpres) = express);
    }
    
    void OutputArray() const {}
};

#endif /* NumericProvider_hpp */
