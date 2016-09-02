#ifndef TemporaryProvider_hpp
#define TemporaryProvider_hpp

#include <thread>
#include <atomic>
#include <mutex>

//--------------------------------------------------------------------------
//                            class TemporaryProvider

template<typename T>
class TemporaryProvider {
    template<typename U>
    friend class TemporaryProvider;
    
    template<typename U>
    using enable_if_original_t = typename std::enable_if<GT::isOriginalType<U>::value>::type;
    
protected:
    TRACE_STRING_SAVE____(std::string  calcExpres);
    T data;
    
public:
    template<typename U>
    TemporaryProvider(const U& data, bool)
    : data(data)
    {
    }
    
    
    TemporaryProvider(const TemporaryProvider& data)
    : data(data.data)
    {
    }
    
    template<typename U>
    TemporaryProvider(const TemporaryProvider<U>& data)
    : data(data.data) {
    }
    
    void lock_guard() const {
    }
    
    void unlock_guard() const {
    }
    
    T& Data() {
        return data;
    }
    
    const T& Data() const {
        return data;
    }
    
    void ValueBeReadedDo() const {
    }
    
    const std::string& Id() const {
        return GuardConfig::defaultIdStr;
    }
    
    const std::string CalcString() const {
        if(GuardConfig::GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        TRACE_STRING_SAVE____(if(this->calcExpres != "") return this->calcExpres);
        return GT::NumericToString(this->data);
    }
    
    void setExpress(const std::string& express) const {
        TRACE_STRING_SAVE____(if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) const_cast<std::string&>(this->calcExpres) = express);
    }
    
    void OutputArray() const {}
};

#endif /* TemporaryProvider_hpp */
