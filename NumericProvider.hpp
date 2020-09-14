#ifndef NumericProvider_hpp
#define NumericProvider_hpp

#include "IDExpressManager.hpp"

namespace gt {

//--------------------------------------------------------------------------
//                            class NumericProvider

template<typename T>
class NumericProvider
{
    template<typename U>
    friend class NumericProvider;
    
protected:
    T data;
    
public:
    template<typename... Args>
    inline NumericProvider(Args... args) noexcept
    : data(args...)
    {
    }
    
    inline NumericProvider(const char* id = gt::defaultId) noexcept
    : data()
    {
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    inline NumericProvider(U& data) noexcept
    : data(data)
    {
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    inline NumericProvider(const U& data) noexcept
    : data(data)
    {
    }
    
    inline NumericProvider(NumericProvider& data) noexcept
    : data(data.data)
    {
    }
    
    inline NumericProvider(const NumericProvider& data) noexcept
    : data(data.data)
    {
    }
    
    template<typename U>
    inline NumericProvider(NumericProvider<U>& data) noexcept
    : data(data.data)
    {
    }
    
    template<typename U>
    inline NumericProvider(const NumericProvider<U>& data) noexcept
    : data(data.data)
    {
    }
    
    // rvalue constructor
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    inline NumericProvider(U&& data) noexcept
    : data(std::forward<U>(data))
    {
    }
    
    template<typename U, typename = std::enable_if_t<gt::isOriginalType<U>::value>>
    inline NumericProvider(const U&& data) noexcept
    : data(std::forward<const U>(data))
    {
    }
    
    inline NumericProvider(NumericProvider&& data) noexcept
    : data(std::forward<T>(data.data))
    {
    }
    
    inline NumericProvider(const NumericProvider&& data) noexcept
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

#endif /* NumericProvider_hpp */
