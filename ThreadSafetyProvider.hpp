#ifndef ThreadSafetyProvider_hpp
#define ThreadSafetyProvider_hpp

#include <mutex>

namespace gt {

class ThreadSafetyProvider
{
    std::recursive_mutex m;
public:
    inline void thread_lock() const noexcept
    {
        const_cast<std::recursive_mutex&>(m).lock();
    }
    
    inline void thread_unlock() const noexcept
    {
        const_cast<std::recursive_mutex&>(m).unlock();
    }
};

}

#endif /* ThreadSafetyProvider_hpp */
