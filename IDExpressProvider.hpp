#ifndef IDExpressProvider_hpp
#define IDExpressProvider_hpp

#include "IDExpressManager.hpp"

namespace gt {

//--------------------------------------------------------------------------
//                            class IDExpressProvider

class IDExpressProvider
{
public:
    inline IDExpressProvider() noexcept
    {
    }
    
    inline IDExpressProvider(const IDExpressProvider& express) noexcept
    {
        this->id = gt::GetNewIdByIncreaseId(express.Id());
    }
    
    inline void initId(const std::string& id) noexcept
    {
        this->id = id;
    }

    inline const std::string& Id() const noexcept
    {
        return id;
    }
    
    inline const std::string& Express() const noexcept
    {
        return calcExpress;
    }
    
    inline void setExpress(const std::string& express) noexcept
    {
        calcExpress = express;
    }
    
protected:
    
    std::string id;
    std::string calcExpress;
};

}

#endif /* IDExpressProvider_hpp */
