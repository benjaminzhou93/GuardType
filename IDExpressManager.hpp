#ifndef IDExpressManager_hpp
#define IDExpressManager_hpp

#include <set>
#include <sstream>
#include "TemplateTools.hpp"

class IDExpressManager {
public:
    static const char defaultId[];
    static const std::string defaultIdStr;
    static std::ostream& so;
    static std::queue<std::string> idArray;

    static const std::string GetNewId() {
        if(!IDExpressManager::idArray.empty()) {
            std::string newId = IDExpressManager::idArray.front();
            IDExpressManager::idArray.pop();
            return newId;
        } else {
            return IDExpressManager::defaultId;
        }
    }
    
    static const std::string GetNewId(const char* userDef) {
        if(userDef != IDExpressManager::defaultId) {
            return userDef;
        } else {
            return GetNewId();
        }
    }
    
    static const std::string GetNewIdByIncreaseId(const std::string& id) {
        std::string getId = GetNewId();
        if(getId != IDExpressManager::defaultId) return getId;
        std::istringstream s(id);
        int n = 0;
        s >> getId >> n;
        return getId + " " + std::to_string(++n);
    }
    
    static int PriorityOfSymbol(const std::string& symbol) {
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
        return 9999;
    }
    
    static const std::string NextCalculateOp(std::string::iterator& current,
                                      const std::string::iterator& end)
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
    
    static int MinCalcPriorityOf(const std::string& calcExpression) {
        int minPriorityOfData2 = 9999;
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
    
    template<typename T
    , typename = typename std::enable_if<! GT::isStringable<T>::value>::type>
    static const std::string NumericToString(T) {
        return typeid(T).name();
    }
    
    template<typename T, template<typename>class DataSource, typename... Providers>
    static const std::string NumericToString(const GuardType<T, DataSource, Providers...>& data
                                      ,typename std::enable_if<! GT::isStringable<T>::value>::type* = 0)
    {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        return data.Id();
    }
    
    template<typename T
    , typename = typename std::enable_if<GT::isStringable<T>::value>::type>
    static const std::string NumericToString(const T& data) {
        std::ostringstream s;
        s << data;
        return s.str();
    }
    
    template<typename T, template<typename>class DataSource
    , typename = typename std::enable_if<GT::isStringable<T>::value>::type, typename... Providers>
    static const std::string NumericToString(const GuardType<T, DataSource, Providers...>& data) {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        std::string idIndex = data.Id();
        if(idIndex == "") {
            return NumericToString(static_cast<const T&>(data));
        } else {
            return idIndex;
        }
    }
    
    template<typename T
    , typename = typename std::enable_if<! GT::isStringable<T>::value>::type>
    static std::string CalcString(T) {
        return typeid(T).name();
    }
    
    template<typename T, template<typename>class DataSource, typename... Providers>
    static std::string CalcString(const GuardType<T, DataSource, Providers...>& data
                           ,typename std::enable_if<! GT::isStringable<T>::value>::type* = 0)
    {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        return data.Id();
    }
    
    template<typename T
    , typename = typename std::enable_if<GT::isStringable<T>::value>::type>
    static std::string CalcString(const T& data) {
        std::ostringstream s;
        s << data;
        return s.str();
    }
    
    template<typename T, template<typename>class DataSource
    , typename = typename std::enable_if<GT::isStringable<T>::value>::type, typename... Providers>
    static std::string CalcString(const GuardType<T, DataSource, Providers...>& data) {
        return data.CalcString();
    }
    
    template<typename U, typename V>
    static const std::string PackWithBracket(const U& data1,
                                      const char* ops,
                                      const V& data2) {
        if(GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        std::string opStr(ops);
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
    
    static std::ostream& Output() {
        return so;
    }
    
    template<typename T, typename ...Args>
    static std::ostream& Output(const T& a) {
        return so << a;
    }
    
    template<typename T, typename ...Args>
    static std::ostream& Output(const T& a, const Args&... args) {
        so << a << ", ";
        return Output(args...);
    }
};


const char IDExpressManager::defaultId[] = "GT";
std::ostream& IDExpressManager::so = std::cout;
std::queue<std::string> IDExpressManager::idArray;
const std::string IDExpressManager::defaultIdStr = std::string(IDExpressManager::defaultId);

#endif /* IDExpressManager_hpp */
