#ifndef ValueObserverProvider_hpp
#define ValueObserverProvider_hpp

#include <functional>
#include "MessageManager.hpp"


template<typename T>
class ValueObserverProvider {
    bool alreadSetReadCallback = false;
    bool alreadSetWriteCallback = false;
    static ObjectMessageManager readObserver;
    static ObjectMessageManager writeObserver;
    
public:
    void AddBeReadedDo(std::function<void(const T&)> func, const char* functionID = NULL) {
        readObserver.AddMessage(this, func, functionID);
        alreadSetReadCallback = true;
    }
    
    size_t RemoveBeReadDo(const char* functionID) {
        size_t count = readObserver.RemoveMessage(this, functionID);
        if(readObserver.MessageCountByObject(this) == 0) alreadSetReadCallback = false;
        return count;
    }
    
    size_t RemoveBeReadDo() {
        size_t count = readObserver.RemoveMessage(this);
        alreadSetReadCallback = false;
        return count;
    }
    
    void AddChangedDo(const std::function<void(T&,const T&)>& func, const char* functionID = NULL) {
        writeObserver.AddMessage(this, func, functionID);
        alreadSetWriteCallback = true;
    }
    
    void AddChangedDo(const std::function<void(const T&)>& func, const char* functionID = NULL) {
        writeObserver.AddMessage(this, std::function<void(T&, const T)>([=](T& newValue, const T oldValue){func(newValue);}), functionID);
        alreadSetWriteCallback = true;
    }
    
    size_t RemoveChangedDo(const char* functionID) {
        size_t count = writeObserver.RemoveMessage(this, functionID);
        if(writeObserver.MessageCountByObject(this) == 0) alreadSetReadCallback = false;
        return count;
    }
    
    size_t RemoveChangedDo() {
        size_t count = writeObserver.RemoveMessage(this);
        alreadSetWriteCallback = false;
        return count;
    }
    
    void CallReadedCallback(const T& data) {
        if(!alreadSetReadCallback) return;
        readObserver.CallMessage(this, data);
    }
    
    void CallWroteCallback(T& newValue, const T oldValue) {
        if(!alreadSetWriteCallback) return;
        writeObserver.CallMessage(this, newValue, oldValue);
    }
};

template<typename T>
ObjectMessageManager ValueObserverProvider<T>::readObserver;

template<typename T>
ObjectMessageManager ValueObserverProvider<T>::writeObserver;

#endif /* ValueObserverProvider_hpp */
