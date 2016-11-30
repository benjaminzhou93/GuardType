#ifndef ValueObserverProvider_hpp
#define ValueObserverProvider_hpp

#include <functional>
#include "MessageManager.hpp"


template<typename T>
class ValueObserverProvider {
    bool alreadSetReadCallback = false;
    bool alreadSetWriteCallback = false;
    
public:
    static ObjectMessageManager& ReadObserver() {
        static ObjectMessageManager manager;
        return manager;
    }
    
    static ObjectMessageManager& WriteObserver() {
        static ObjectMessageManager manager;
        return manager;
    }
    
    void AddBeReadedDo(const std::function<void(const T&)>& func, const char* functionID = NULL) {
        ReadObserver().AddMessage(this, func, functionID);
        alreadSetReadCallback = true;
    }
    
    size_t RemoveBeReadDo(const char* functionID) {
        size_t count = ReadObserver().RemoveMessage(this, functionID);
        if(ReadObserver().MessageCountByObject(this) == 0) alreadSetReadCallback = false;
        return count;
    }
    
    size_t RemoveBeReadDo() {
        size_t count = ReadObserver().RemoveMessage(this);
        alreadSetReadCallback = false;
        return count;
    }
    
    void AddChangedDo(const std::function<void(T&,const T&)>& func, const char* functionID = NULL) {
        WriteObserver().AddMessage(this, func, functionID);
        alreadSetWriteCallback = true;
    }
    
    void AddChangedDo(const std::function<void(const T&)>& func, const char* functionID = NULL) {
        WriteObserver().AddMessage(this, std::function<void(T&, const T)>([=](T& newValue, const T oldValue){func(newValue);}), functionID);
        alreadSetWriteCallback = true;
    }
    
    size_t RemoveChangedDo(const char* functionID) {
        size_t count = WriteObserver().RemoveMessage(this, functionID);
        if(WriteObserver().MessageCountByObject(this) == 0) alreadSetReadCallback = false;
        return count;
    }
    
    size_t RemoveChangedDo() {
        size_t count = WriteObserver().RemoveMessage(this);
        alreadSetWriteCallback = false;
        return count;
    }
    
    void CallReadedCallback(const T& data) {
        if(!alreadSetReadCallback) return;
        ReadObserver().CallMessage(this, data);
    }
    
    void CallWroteCallback(T& newValue, const T oldValue) {
        if(!alreadSetWriteCallback) return;
        WriteObserver().CallMessage(this, newValue, oldValue);
    }
    
    ~ValueObserverProvider() {
        if(alreadSetReadCallback)
            ReadObserver().RemoveMessage(this);
        if(alreadSetWriteCallback)
            WriteObserver().RemoveMessage(this);
    }
};

#endif /* ValueObserverProvider_hpp */
