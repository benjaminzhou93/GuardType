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
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId(id)))
    data() {
    }
    
    template<typename U>
    NumericProvider(const U& data)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewId()))
    data(data) {
    }
    
    template<typename U>
    NumericProvider(const NumericProvider<U>& data)
    : TRACE_STRING_SAVE_DECLARE(id(GT::GetNewIdByIncreaseId(data.id)))
    data(data.data) {
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
