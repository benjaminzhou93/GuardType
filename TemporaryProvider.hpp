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
    
protected:
    T data;
    TRACE_STRING_SAVE____(std::string  calcExpres);
    
public:
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    TemporaryProvider(U& data)
    : data(data)
    {
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    TemporaryProvider(const U& data)
    : data(data)
    {
    }
    
    TemporaryProvider(TemporaryProvider& data)
    : data(data.data)
    {
    }
    
    TemporaryProvider(const TemporaryProvider& data)
    : data(data.data)
    {
    }
    
    template<typename U>
    TemporaryProvider(TemporaryProvider<U>& data)
    : data(data.data) {
    }
    
    template<typename U>
    TemporaryProvider(const TemporaryProvider<U>& data)
    : data(data.data) {
    }
    
    // rvalue constructor
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    TemporaryProvider(U&& data)
    : data(std::forward<U>(data))
    {
    }
    
    template<typename U, typename = typename std::enable_if<GT::isOriginalType<U>::value>::type>
    TemporaryProvider(const U&& data)
    : data(std::forward<const U>(data))
    {
    }
    
    TemporaryProvider(TemporaryProvider&& data)
    : data(std::forward<T>(data.data))
    {
    }
    
    TemporaryProvider(const TemporaryProvider&& data)
    : data(std::forward<const T>(data.data))
    {
    }
    
    T& Data() {
        return data;
    }
    
    const T& Data() const {
        return data;
    }
    
    const std::string Id() const {
        return "";
    }
    
    const std::string CalcString() const {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        TRACE_STRING_SAVE____(if(this->calcExpres != "") return this->calcExpres);
        return IDExpressManager::NumericToString(this->data);
    }
    
    void setExpress(const std::string& express) const {
        TRACE_STRING_SAVE____(if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) const_cast<std::string&>(this->calcExpres) = express);
    }
    
    void OutputArray() const {}
};

#endif /* TemporaryProvider_hpp */
