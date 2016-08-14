#ifndef Tools_hpp
#define Tools_hpp

#include <assert.h>
#include <set>
#include "GuardConfig.hpp"

//--------------------------------------------------------------------------
//                             GT tools

#define ASSERT(yes, outPut)\
if(! (yes) ) GuardConfig::so << outPut << std::endl;\
assert(yes);

namespace GT {
    
    const std::string GetNewId() {
        if(!GuardConfig::idArray.empty()) {
            std::string newId = GuardConfig::idArray.front();
            GuardConfig::idArray.pop();
            return newId;
        } else {
            return GuardConfig::defaultId;
        }
    }
    
    const std::string GetNewId(std::string userDef) {
        if(userDef != GuardConfig::defaultId) {
            return userDef;
        } else {
            return GetNewId();
        }
    }
    
    const std::string GetNewIdByIncreaseId(const std::string& id) {
        std::string getName = (id == "" ? GT::GetNewId() : id);
        if(getName == GuardConfig::defaultId) return getName;
        std::string newName = id;
        if(newName == "") newName = GuardConfig::defaultId;
        int num = 0;
        while(newName.length() != 0
              && ('0' <= newName[newName.length()-1])
              && (newName[newName.length()-1] <= '9')) {
            num = num*10 + atoi(&newName[newName.length()-1]);
            newName.erase(newName.length()-1);
        }
        ++num;
        char str_num[4];
        sprintf(str_num, "%d", num);
        newName += str_num;
        return newName;
    }
    
    int PriorityOfSymbol(const std::string& symbol) {
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
    
    const std::string NextCalculateOp(std::string::iterator& current,
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
    
    int MinCalcPriorityOf(const std::string& calcExpression) {
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
    
}

#endif /* Tools_hpp */