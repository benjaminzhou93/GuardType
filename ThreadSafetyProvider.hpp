#ifndef ThreadSafetyProvider_hpp
#define ThreadSafetyProvider_hpp

#include <mutex>

class ThreadSafetyProvider {
    std::recursive_mutex m;
public:
    void thread_lock() const {
        const_cast<std::recursive_mutex&>(m).lock();
    }
    void thread_unlock() const {
        const_cast<std::recursive_mutex&>(m).unlock();
    }
};

class ArrayThreadSafetyProvider {
public:
    template<typename T, typename = typename std::enable_if<GT::isIndexProvider<T>::value>::type>
    void thread_lock(const T& idx){
        idx.array->thread_lock(idx.pos - idx.array->array);
    }
    
    template<typename T, typename = typename std::enable_if<GT::isIndexProvider<T>::value>::type>
    void thread_unlock(const T& idx){
        idx.array->thread_unlock(idx.pos - idx.array->array);
    }
    
    
    template<typename T, typename = typename std::enable_if<!GT::isIndexProvider<T>::value>::type>
    void thread_lock(T data){
    } // for avoid compiler error, never use
    
    template<typename T, typename = typename std::enable_if<!GT::isIndexProvider<T>::value>::type>
    void thread_unlock(T){
    } // for avoid compiler error, never use
};

#endif /* ThreadSafetyProvider_hpp */
