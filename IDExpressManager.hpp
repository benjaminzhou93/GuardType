#ifndef IDExpressManager_hpp
#define IDExpressManager_hpp

#include <set>
#include <sstream>
#include "TemplateTools.hpp"

namespace gt {

    static const char defaultId[] = "gt";
    static const std::string defaultIdStr = defaultId;
    static std::ostream& so = std::cout;
    static std::queue<std::string> idArray;


    std::string GetNewId() noexcept
    {
        if(!idArray.empty()) {
            std::string id = idArray.front();
            idArray.pop();
            return id;
        } else {
            return defaultIdStr;
        }
    }
    
    std::string GetNewId(const char* userDef) noexcept
    {
        if(userDef != defaultId) {
            return userDef;
        } else {
            return GetNewId();
        }
    }
    
    const std::string GetNewIdByIncreaseId(const std::string& id) noexcept
    {
        std::string getId = GetNewId();
        if(getId != defaultId) return getId;
        std::istringstream s(id);
        int n = 0;
        s >> getId >> n;
        return getId + "#" + std::to_string(++n);
    }

    template<typename T>
    void SetExpress(T&, const std::string&) noexcept
    {
    }

    template<typename T, template<typename>class DataSource, typename... Providers,
            typename = std::enable_if_t<gt::isContainFirstType<IDExpressProvider, Providers...>::value > >
    void SetExpress(GuardType<T, DataSource, Providers...>& data, const std::string& s) noexcept
    {
        data.setExpress(s);
    }
    
    template<typename T, typename = std::enable_if_t<!gt::isStringable<typename gt::type_traits<T>::value_type>::value> >
    std::string NumericToString(const T& data, int=0) noexcept
    {
        return typeid(T).name();
    }
    
    template<typename T, typename = std::enable_if_t<gt::isStringable<typename gt::type_traits<T>::value_type>::value> >
    std::string NumericToString(const T& data) noexcept
    {
        std::ostringstream s;
        s << data;
        return s.str();
    }
    
    template<typename T, template<typename>class DataSource, typename... Providers,
            typename = std::enable_if_t<gt::isStringable<typename gt::type_traits<T>::value_type>::value> >
    std::string NumericToString(const GuardType<T, DataSource, Providers...>& data) noexcept
    {
        std::ostringstream s;
        s << data.Data();
        return s.str();
    }

    template<typename T>
    std::string Id(const T& data) noexcept
    {
        return NumericToString(data);
    }

    template<typename T, template<typename>class DataSource, typename... Providers,
            typename = std::enable_if_t<gt::isContainFirstType<IDExpressProvider, Providers...>::value
                                        || gt::isExistArrayId<DataSource<T> >::value>  >
    std::string Id(const GuardType<T, DataSource, Providers...>& source) noexcept
    {
        auto id = source.Id();
        return id != "" ? id : NumericToString(source);
    }
    
    template<typename T,
            typename = std::enable_if_t<gt::isOriginalType<T>::value>,
            typename = std::enable_if_t<!gt::isStringable<typename gt::type_traits<T>::value_type>::value> >
    std::string CalcString(const T data) noexcept
    {
        return NumericToString(data);
    }

	template<typename T,
		typename = std::enable_if_t<gt::isOriginalType<T>::value>,
		typename = std::enable_if_t<gt::isStringable<typename gt::type_traits<T>::value_type>::value> >
    std::string CalcString(const T& data) noexcept
    {
		std::ostringstream s;
		s << data;
		return s.str();
	}

    template<typename U>
    std::string Express(const U& data) noexcept
    {
        return typeid(U).name();
    }

    template<typename T, template<typename>class DataSource, typename... Providers,
            typename = std::enable_if_t<gt::isContainFirstType<IDExpressProvider, Providers...>::value> >
    std::string Express(const GuardType<T, DataSource, Providers...>& data) noexcept
    {
        return data.Express();
    }

	template<typename T, template<typename>class DataSource, typename... Providers>
    std::string CalcString(const GuardType<T, DataSource, Providers...>& data) noexcept
    {
		if (!gt::isContainFirstType<IDExpressProvider, Providers...>::value) {
            if (GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
                if (gt::isExistArrayId<DataSource<T> >::value)
                    return Id(data);
                else
                    return CalcString(data.Data());
            }
            return NumericToString(data);
		}
		else {
			if (GuardConfig::_OUT_PUT_EXPRES_SWITCH == false)
				return "";

			if (Express(data) != "")
				return Express(data);

			if (GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
				return Id(data);
			}
			else {
				return NumericToString(data.Data());
			}
			return "";
		}
	}
    
    int PriorityOfSymbol(const std::string& symbol) noexcept
    {
        if(symbol == "(" || symbol == ")")
            return 19;
        else if(symbol == "++" || symbol == "--" || symbol == "!" || symbol == "~")
            return 17;
        else if(symbol == "*" || symbol == "/" || symbol == "%")
            return 15;
        else if(symbol == "+" || symbol == "-")
            return 13;
        else if(symbol == "<<" || symbol == ">>")
            return 11;
        else if(symbol == "<" || symbol == ">" || symbol == "<=" || symbol == ">=")
            return 9;
        else if(symbol == "==" || symbol == "!=")
            return 7;
        else if(symbol == "&" || symbol == "|" || symbol == "^")
            return 5;
        else if(symbol == "&&" || symbol == "||")
            return 3;
        return 999;
    }
    
    const std::string NextCalculateOp(std::string::iterator& current,
                                      const std::string::iterator& end) noexcept
    {
        static std::string calcSymbolsTemp[25] = {
            "(", ")", "=", "+", "++", "-", "--", "*", "/", "%", "<", ">", "<=", ">=",
            "==", "!=", "&&", "||", "!", "&", "|", "~", "^", "<<", ">>"};
        static std::set<std::string> calcSymbols(calcSymbolsTemp,calcSymbolsTemp+25);
        
        std::string op="";
        while(current != end && calcSymbols.find(op) == calcSymbols.end()) {
            op = *current++;
        }
        if(calcSymbols.find(op) != calcSymbols.end()) {
            if(current != end && calcSymbols.find(op + *current) != calcSymbols.end()) {
                return op + *current++;
            }
            else
                return op;
        }else {
            return "";
        }
    }
    
    int MinCalcPriorityOf(const std::string& calcExpression) noexcept
    {
        int minPriorityOfData2 = 999;
        int tempPriority;
        std::string& calcExpress = const_cast<std::string&>(calcExpression);
        std::string::iterator iter = calcExpress.begin();
        std::string opTemp = NextCalculateOp(iter, calcExpress.end());
        while(iter != calcExpress.end()) {
            if(opTemp == "(") {
                int l=1, r=0;
                opTemp = NextCalculateOp(iter, calcExpress.end());
                while(opTemp != "" && l!=r) {
                    if(opTemp == "(")
                        ++l;
                    else if(opTemp == ")") {
                        ++r;
                    }
                    opTemp = NextCalculateOp(iter, calcExpress.end());
                }
            } else {
                tempPriority = PriorityOfSymbol(opTemp);
                if(tempPriority < minPriorityOfData2)
                    minPriorityOfData2 = tempPriority;
            }
            opTemp = NextCalculateOp(iter, calcExpress.end());
        }
        return minPriorityOfData2;
    }

    template<typename U, typename V>
    std::string PackWithBracket(const U& data1,
                                const char* op,
                                const V& data2) noexcept
    {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false)
            return "";
        std::string opStr(op);
        std::string calcExpress;
        std::string data1CalcString = CalcString(data1);
        std::string data2CalcString = CalcString(data2);
        if(MinCalcPriorityOf(data1CalcString) < PriorityOfSymbol(opStr))
            calcExpress = "("+data1CalcString+")" + opStr;
        else
            calcExpress = data1CalcString + opStr;
        
        if(PriorityOfSymbol(opStr) >= MinCalcPriorityOf(data2CalcString))
            calcExpress += "("+data2CalcString+")";
        else
            calcExpress += data2CalcString;
        return calcExpress;
    }
    
    std::ostream& Output()
    {
        return so;
    }
    
    template<typename T, typename ...Args>
    std::ostream& Output(const T& a) noexcept
    {
        return so << a;
    }
    
    template<typename T, typename ...Args>
    std::ostream& Output(const T& a, const Args&... args) noexcept
    {
        so << a << ", ";
        return Output(args...);
    }

    template<typename T, template<typename>class DataSource, typename... Providers>
    void OutputExpress(const GuardType<T, DataSource, Providers...>& data) noexcept
    {
        if(gt::isTemporaryProvider<decltype(data)>::value)
            return;
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH)
            so << _SPACES << "EXPRES:"
            << Id(data) << " = "
            << CalcString(data) << std::endl;
    }

    template<typename T, template<typename>class DataSource, typename... Providers>
    void OutputSingleOpTrace(const char* frontOp,
                             const GuardType<T, DataSource, Providers...>& result,
                             const char* backOp) noexcept
    {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false)
            return;
        if (GuardConfig::_OUTPUT_TRACE_SWITCH == false)
            return;
        if(GuardConfig::rule[frontOp] == false
           && GuardConfig::rule[backOp] == false)
            return;
        so << _SPACES << "TRACE: ";
        so << frontOp;
        so << Id(result);
        so << backOp << " = ";
        so << NumericToString(result.Data()) << std::endl;
    }

    template<typename T, typename ...Args>
    void OutputBracketOpTrace(const T& data, const char* opLeft, const char* opRight, Args... args) noexcept
    {
        if (GuardConfig::_OUTPUT_TRACE_SWITCH == false)
            return;
        so << _SPACES << "TRACE: ";
        so << "Called " + gt::Id(data) + opLeft;
        Output(args...);
        so << opRight;
        so << std::endl;
    }

    template<typename U, typename V, typename W>
    void OutputOpTrace(const U& data1,
                       const char* op,
                       const V& data2,
                       const W& result) noexcept
    {
        if (gt::isTemporaryProvider<U>::value && *op == '=')
            return;
        if (GuardConfig::_OUTPUT_TRACE_SWITCH == false)
            return;
        if (gt::isIndexProvider<U>::value && GuardConfig::_ARRAY_OUT_PUT_SWITCH == false)
            return;
        if(GuardConfig::rule[op] == false)
            return;
        so << _SPACES << "TRACE: ";
        so << Id(data1);
        so << " " << op << " ";
        so << Id(data2);
        if(*op != '=') {
            so << " = ";
            so << NumericToString(result);
        }
        so << std::endl;
    }

    template<typename T>
    void OutputArray(T) noexcept
    {
    }

    template<typename T, template<typename>class DataSource, typename... Providers,
        typename = std::enable_if_t<gt::isIndexProvider<DataSource<T> >::value>  >
    void OutputArray(const GuardType<T, DataSource, Providers...>& source) noexcept
    {
        if (GuardConfig::_ARRAY_OUT_PUT_SWITCH == false)
            return;
        source.OutputArray();
    }

}


template<typename... T>
int printf(const char * s, const T&... arg1) noexcept
{
    return std::printf(s, static_cast<typename gt::type_traits<T>::value_type>(arg1)...);
}

template<typename T>
void AddId(const T& id) noexcept
{
    gt::idArray.push(id);
}

template<typename T, typename ...U>
void AddId(const T& id, const U&...ids) noexcept
{
    gt::idArray.push(id);
    AddId(ids...);
}


#endif /* IDExpressManager_hpp */
