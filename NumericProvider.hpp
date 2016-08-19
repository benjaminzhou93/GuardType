#ifndef NumericProvider_hpp
#define NumericProvider_hpp


//--------------------------------------------------------------------------
//                            class NumericProvider

template<typename T>
class NumericProvider {
    template<typename U>
    friend class NumericProvider;
    
    TRACE_STRING_SAVE____(std::string id);
    T data;
    
public:
    NumericProvider(const char* id = GuardConfig::defaultId)
    : data()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
    }
    
#define NumericProviderConstructN(type)             \
    NumericProvider(const type& data)               \
    : data(data)                                      \
    {                                               \
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());\
    }

    EXPAND_NUMERIC_MACRO(NumericProviderConstructN)
    
    
    NumericProvider(const NumericProvider& data)
    : data(data.data)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(const NumericProvider<U>& data)
    : data(data.data) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    T& Data() const {
        return const_cast<T&>(data);
    }
    
    const std::string& Id() const {
        TRACE_STRING_SAVE____(return id);
        return GuardConfig::defaultIdStr;
    }
    
    void OutPutArray() const {}
};

#endif /* NumericProvider_hpp */
