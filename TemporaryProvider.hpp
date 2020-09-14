#ifndef TemporaryProvider_hpp
#define TemporaryProvider_hpp

#include <thread>
#include <atomic>

namespace gt {

//--------------------------------------------------------------------------
//                            class TemporaryProvider

template<typename T>
class TemporaryProvider
{
    template<typename U>
    friend class TemporaryProvider;
    
protected:
    T data;
    
public:
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    inline TemporaryProvider(U& data) noexcept
    : data(data)
    {
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    inline TemporaryProvider(const U& data) noexcept
    : data(data)
    {
    }
    
    inline TemporaryProvider(TemporaryProvider& data) noexcept
    : data(data.data)
    {
    }
    
    inline TemporaryProvider(const TemporaryProvider& data) noexcept
    : data(data.data)
    {
    }
    
    template<typename U>
    inline TemporaryProvider(TemporaryProvider<U>& data) noexcept
    : data(data.data)
    {
    }
    
    template<typename U>
    inline TemporaryProvider(const TemporaryProvider<U>& data) noexcept
    : data(data.data)
    {
    }
    
    // rvalue constructor
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    inline TemporaryProvider(U&& data) noexcept
    : data(std::forward<U>(data))
    {
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    inline TemporaryProvider(const U&& data) noexcept
    : data(std::forward<const U>(data))
    {
    }
    
    inline TemporaryProvider(TemporaryProvider&& data) noexcept
    : data(std::forward<T>(data.data))
    {
    }
    
    inline TemporaryProvider(const TemporaryProvider&& data) noexcept
    : data(std::forward<const T>(data.data))
    {
    }
    
    inline T& Data() noexcept
    {
        return data;
    }
    
    inline const T& Data() const noexcept
    {
        return data;
    }
};

}

#endif /* TemporaryProvider_hpp */
