#ifndef NumericProvider_hpp
#define NumericProvider_hpp


//--------------------------------------------------------------------------
//                            class NumericProvider

template<typename T>
class NumericProvider {
    template<typename U>
    friend class NumericProvider;
    
    template<typename U>
    using enable_if_original_t = typename std::enable_if<GT::isOriginalType<U>::value>::type;
    
private:
    TRACE_STRING_SAVE____(std::string id);
    T data;
    
public:
    NumericProvider(const char* id = GuardConfig::defaultId)
    : data()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
    }
    
    template<typename U>
    NumericProvider(const U& data, enable_if_original_t<U>* = 0)
    : data(data)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    
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
    
    // const rvalue constructor
    template<typename U>
    NumericProvider(const U&& data, enable_if_original_t<U>* = 0)
    : data(std::forward<const U>(data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    
    NumericProvider(const NumericProvider&& data)
    : data(std::forward<const T>(data.data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(const NumericProvider<U>&& data)
    : data(std::forward<const U>(data.data)) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    // rvalue constructor
    template<typename U>
    NumericProvider(U&& data, enable_if_original_t<U>* = 0)
    : data(std::forward<U>(data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    
    NumericProvider(NumericProvider&& data)
    : data(std::forward<T>(data.data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(NumericProvider<U>&& data)
    : data(std::forward<U>(data.data)) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    T& Data() const {
        return const_cast<T&>(data);
    }
    
    const std::string& Id() const {
        TRACE_STRING_SAVE____(return id);
        return GuardConfig::defaultIdStr;
    }
    
    void OutputArray() const {}
};

#endif /* NumericProvider_hpp */
