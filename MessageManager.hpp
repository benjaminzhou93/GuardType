#ifndef MessageManager_hpp
#define MessageManager_hpp

#include <map>
#include <functional>
#include <memory>

namespace gt {

template<int N, typename...Args>
struct Types;


template<int N, typename T, typename...Args>
struct Types<N, T, Args...>
{
    using FirstType = T;
};

template<>
struct Types<0>
{
    using FirstType = void;
};


template<typename... Args>
class CallbackFunction;

template<typename T, typename... Args>
struct PackRest
{
    using type = CallbackFunction<Args...>;
};


template<typename... Args>
class CallbackFunction;

template<int N, typename ArgPacker, typename...Args>
struct RefNoCVPacker
{
    using PackerArgsFirstType = typename ArgPacker::FirstArgsType;
    using FristNoRef = typename std::remove_reference<PackerArgsFirstType>::type;
    using FirstNoCV = typename std::remove_cv<FristNoRef>::type;
    using FirstRefNoCV = FirstNoCV&;
    using type = typename RefNoCVPacker<N-1, typename ArgPacker::NextPacker, Args..., FirstRefNoCV>::type;
};

template<typename ArgPacker, typename...Types>
struct RefNoCVPacker<0, ArgPacker, Types...>
{
    using type = CallbackFunction<Types...>;
};





class MessageCallback
{
public:
    template<typename... Args>
    bool Callback(Args... args)
    {
        auto f = dynamic_cast<typename RefNoCVPacker<sizeof...(Args), CallbackFunction<Args...> >::type* >(this);
        if(f != NULL) {
            f->func(args...);
            return true;
        }
        return false;
    }
    
    inline virtual ~MessageCallback() noexcept {}
};

template<typename... Args>
class CallbackFunction : public MessageCallback
{
public:
    
    using FirstArgsType = typename Types<sizeof...(Args), Args...>::FirstType;
    using NextPacker = typename PackRest<Args...>::type;
    
    std::function<void(Args...)> func;
    
    inline CallbackFunction(const std::function<void(Args...)>& func) noexcept : func(func)
    {
    }
};


class MessageManager {
private:
    MessageManager() {}
    MessageManager(MessageManager&) {}
    
    std::multimap<std::string, std::shared_ptr<MessageCallback> > messages;
    
    friend class ObjectMessageManager;
public:
    using Iterator = std::multimap<std::string, std::shared_ptr<MessageCallback> >::iterator;
    
    inline static MessageManager& instance() noexcept
    {
        static MessageManager manager;
        return manager;
    }
    
    template<typename... Args>
    inline Iterator AddMessage(const std::function<void(Args...)>& message, const std::string& msgName = "") noexcept
    {
        MessageCallback* callBack = new typename RefNoCVPacker<sizeof...(Args), CallbackFunction<Args...> >::type(message);
        return messages.insert(std::make_pair(msgName, std::shared_ptr<MessageCallback>(callBack)));
    }
    
    inline size_t RemoveMessage(const std::string& msgName = "") noexcept
    {
        size_t count = 0;
        auto range = messages.equal_range(msgName);
        for(auto iter = range.first, end = range.second; iter != end;) {
            auto temp = iter++;
            messages.erase(temp);
            ++count;
        }
        return count;
    }
    
    template<typename... Args>
    inline size_t CallMessage(const std::string& msgName, Args... args)
    {
        size_t count = 0;
        auto range = messages.equal_range(msgName);
        for(auto iter = range.first, end = range.second; iter != end; ++iter) {
            if(iter->second->Callback<Args...>(args...)) {
                ++count;
            }
        }
        return count;
    }
};



class ObjectMessageManager
{
private:
    ObjectMessageManager(ObjectMessageManager&) {}
    
    std::multimap<void*, MessageManager::Iterator> objMsgMap;
    
    std::recursive_mutex mutex;
    
    ObjectMessageManager() {}
    
    template<typename T>
    friend class ValueObserverProvider;
    
public:
    inline ObjectMessageManager& instance() noexcept
    {
        static ObjectMessageManager manager;
        return manager;
    }
    
    template<typename... Args>
    void AddMessage(void* obj, const std::function<void(Args...)>& message, const std::string& msgName = "") noexcept
    {
        std::lock_guard<std::recursive_mutex> guard(mutex);
        objMsgMap.insert(std::make_pair(obj, MessageManager::instance().AddMessage(message, msgName)));
    }
    
    size_t RemoveMessage(void* obj) noexcept
    {
        size_t count = 0;
        std::lock_guard<std::recursive_mutex> guard(mutex);
        auto range = objMsgMap.equal_range(obj);
        for(auto iter = range.first, end = range.second; iter != end;) {
            MessageManager::instance().messages.erase(iter->second);
            auto temp = iter++;
            objMsgMap.erase(temp);
            ++count;
        }
        return count;
    }
    
    size_t RemoveMessage(void* obj, const std::string& msgName) noexcept
    {
        size_t count = 0;
        std::lock_guard<std::recursive_mutex> guard(mutex);
        auto range = objMsgMap.equal_range(obj);
        for(auto iter = range.first, end = range.second; iter != end;) {
            if(msgName == iter->second->first) {
                MessageManager::instance().messages.erase(iter->second);
                auto temp = iter++;
                objMsgMap.erase(temp);
                ++count;
            }else {
                ++iter;
            }
        }
        return count;
    }
    
    template<typename... Args>
    size_t CallMessage(void* obj, Args... args)
    {
        size_t count = 0;
        std::lock_guard<std::recursive_mutex> guard(mutex);
        auto range = objMsgMap.equal_range(obj);
        for(auto iter = range.first, end = range.second; iter != end; ++iter) {
            if(iter->second->second->Callback<Args...>(args...)) {
                ++count;
            }
        }
        return count;
    }
    
    template<typename... Args>
    size_t CallMessage(const std::string& msgName, void* obj, Args... args)
    {
        size_t count = 0;
        std::lock_guard<std::recursive_mutex> guard(mutex);
        auto range = objMsgMap.equal_range(obj);
        for(auto iter = range.first, end = range.second; iter != end; ++iter) {
            if(msgName == iter->second->first) {
                if(iter->second->second->Callback<Args...>(args...)) {
                    ++count;
                }
            }
        }
        return count;
    }
    
    size_t MessageCountByObject(void * obj) noexcept
    {
        std::lock_guard<std::recursive_mutex> guard(mutex);
        return objMsgMap.count(obj);
    }
};

}

#endif /* MessageManager_hpp */
