#ifndef ValueObserverProvider_hpp
#define ValueObserverProvider_hpp

#include <functional>
#include "MessageManager.hpp"

namespace gt {

template<typename T>
class ValueObserverProvider
{
    bool alreadSetReadCallback = false;
    bool alreadSetWriteCallback = false;
    void* addr;
    
    template<typename U, template<typename>class DataSource, typename... Providers>
    friend class GuardType;
    
public:
    inline ValueObserverProvider()
    {
        addr = this;
    }
    
    inline static ObjectMessageManager& ReadObserver() noexcept
    {
        static ObjectMessageManager manager;
        return manager;
    }
    
    inline static ObjectMessageManager& WriteObserver() noexcept
    {
        static ObjectMessageManager manager;
        return manager;
    }
    
    inline void AddBeReadedDo(const std::function<void(const T&)>& func, const std::string& functionID = "") noexcept
    {
        ReadObserver().AddMessage(addr, func, functionID);
        alreadSetReadCallback = true;
    }
    
    inline size_t RemoveBeReadDo(const std::string& functionID = "") noexcept
    {
        size_t count = ReadObserver().RemoveMessage(addr, functionID);
        if(ReadObserver().MessageCountByObject(addr) == 0) alreadSetReadCallback = false;
        return count;
    }
    
    inline size_t RemoveBeReadDo() noexcept
    {
        size_t count = ReadObserver().RemoveMessage(addr);
        alreadSetReadCallback = false;
        return count;
    }
    
    inline void AddChangedDo(const std::function<void(T&,const T&)>& func, const std::string& functionID = "") noexcept
    {
        WriteObserver().AddMessage(addr, func, functionID);
        alreadSetWriteCallback = true;
    }
    
    inline void AddChangedDo(const std::function<void(const T&)>& func, const std::string& functionID = "") noexcept
    {
        WriteObserver().AddMessage(addr, std::function<void(T&, const T)>([=](T& newValue, const T oldValue){func(newValue);}), functionID);
        alreadSetWriteCallback = true;
    }
    
    inline size_t RemoveChangedDo(const char* functionID) noexcept
    {
        size_t count = WriteObserver().RemoveMessage(addr, functionID);
        if(WriteObserver().MessageCountByObject(addr) == 0) alreadSetReadCallback = false;
        return count;
    }
    
    inline size_t RemoveChangedDo() noexcept
    {
        size_t count = WriteObserver().RemoveMessage(addr);
        alreadSetWriteCallback = false;
        return count;
    }
    
    inline void CallReadedCallback(const T& data)
    {
        if(!alreadSetReadCallback && addr == this)
            return;
        ReadObserver().CallMessage(addr, data);
    }
    
    inline void CallWroteCallback(T& newValue, const T oldValue)
    {
        if(!alreadSetWriteCallback && addr == this)
            return;
        WriteObserver().CallMessage(addr, newValue, oldValue);
    }
    
    inline ~ValueObserverProvider() noexcept
    {
        if(alreadSetReadCallback && addr == this)
            ReadObserver().RemoveMessage(addr);
        if(alreadSetWriteCallback && addr == this)
            WriteObserver().RemoveMessage(addr);
    }
};

}

#endif /* ValueObserverProvider_hpp */
