#ifndef GuardConfig_hpp
#define GuardConfig_hpp

#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <cstring>

//---------------------------------------------------------------------------
//                              GuardConfig



#define ENSURE_MULTITHREAD_SAFETY           0 // 0

#define OUT_OF_INDEX_DETECT                 1 // 0

#define VALUE_BE_READED_DO                  1 // 0

#define OLD_TO_NEW_VALUE_DO                 1 // 0

#define SAVE_EXPRES_SLOWER_SPEED            1 // 0
#define OUTPUT_TRACE_SWITCH                 1 // 0
#define TRACE_STRING_SAVE                   1 // 0

#define _SPACES "\t\t\t\t"



class GuardConfig
{
    GuardConfig();
    GuardConfig(GuardConfig&);
public:
    
    static void TurnAllGuardOff();
    static void TurnAllGuardOn();
    
    static void TurnReadSwitch(bool yes);
    // +, -, *, /, %, ^, &,|, ~, <<, >>
    static void TurnMathSwitch(bool yes);
    // !, &&, ||
    static void TurnLogicSwitch(bool yes);
    // <, >, <=, >=, !=, ==
    static void TurnCompareSwitch(bool yes);
    // =, ++, --, +=, -=, *=, /=, %=, ^=, <<=, >>=
    static void TurnAssignSwitch(bool yes);
    static void TurnOutputCalcTraceSwitch(bool yes);
    static void TurnOutputCalcExpressSwitch(bool yes);
    
    static void TurnIOTipSwitch(bool yes);
    static void TurnArrayOutputSwitch(bool yes);
    static void TurnCalcExpressIdOrNum(bool yes);
    static void SetArrayOutputInterval(int n);
    
    static bool _TRACE_READ_SWITCH;
    static bool _OUTPUT_TRACE_SWITCH;
    static bool _OUT_PUT_EXPRES_SWITCH;
    static bool _OUT_PUT_EXPRES_ID_OR_NUM_SWITCH;
    static bool _ARRAY_IO_TIP_SWITCH;
    static bool _ARRAY_OUT_PUT_SWITCH;
    static int  _ARRAY_OUT_PUT_INTERVAL;
    const static bool defaultGuard;
public:
    static std::map<const char*, bool> rule;
    static GuardConfig config;
};

const bool GuardConfig::defaultGuard        = true;
bool GuardConfig::_TRACE_READ_SWITCH        = false;
bool GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH = false;
bool GuardConfig::_OUTPUT_TRACE_SWITCH      = GuardConfig::defaultGuard;
bool GuardConfig::_OUT_PUT_EXPRES_SWITCH    = GuardConfig::defaultGuard;
bool GuardConfig::_ARRAY_IO_TIP_SWITCH      = GuardConfig::defaultGuard;
bool GuardConfig::_ARRAY_OUT_PUT_SWITCH     = GuardConfig::defaultGuard;
int  GuardConfig::_ARRAY_OUT_PUT_INTERVAL   = 2;


std::map<const char*, bool> GuardConfig::rule;
GuardConfig GuardConfig::config;

GuardConfig::GuardConfig()
{
    rule.insert(std::make_pair("+", defaultGuard));
    rule.insert(std::make_pair("-", defaultGuard));
    rule.insert(std::make_pair("*", defaultGuard));
    rule.insert(std::make_pair("/", defaultGuard));
    rule.insert(std::make_pair("%", defaultGuard));
    rule.insert(std::make_pair("^", defaultGuard));
    rule.insert(std::make_pair("&", defaultGuard));
    rule.insert(std::make_pair("|", defaultGuard));
    rule.insert(std::make_pair("~", defaultGuard));
    rule.insert(std::make_pair("<<", defaultGuard));
    rule.insert(std::make_pair(">>", defaultGuard));
    rule.insert(std::make_pair("!", defaultGuard));
    rule.insert(std::make_pair("&&", defaultGuard));
    rule.insert(std::make_pair("||", defaultGuard));
    rule.insert(std::make_pair("<", defaultGuard));
    rule.insert(std::make_pair(">", defaultGuard));
    rule.insert(std::make_pair("<=", defaultGuard));
    rule.insert(std::make_pair(">=", defaultGuard));
    rule.insert(std::make_pair("==", defaultGuard));
    rule.insert(std::make_pair("!=", defaultGuard));
    rule.insert(std::make_pair("+=", defaultGuard));
    rule.insert(std::make_pair("-=", defaultGuard));
    rule.insert(std::make_pair("*=", defaultGuard));
    rule.insert(std::make_pair("/=", defaultGuard));
    rule.insert(std::make_pair("%=", defaultGuard));
    rule.insert(std::make_pair("^=", defaultGuard));
    rule.insert(std::make_pair("<<=", defaultGuard));
    rule.insert(std::make_pair(">>=", defaultGuard));
    rule.insert(std::make_pair("++", defaultGuard));
    rule.insert(std::make_pair("--", defaultGuard));
    rule.insert(std::make_pair("=", defaultGuard));
    rule.insert(std::make_pair("", true));
}

void GuardConfig::TurnAllGuardOff() {
    TurnReadSwitch(false);
    TurnMathSwitch(false);
    TurnLogicSwitch(false);
    TurnCompareSwitch(false);
    TurnAssignSwitch(false);
    TurnIOTipSwitch(false);
    TurnArrayOutputSwitch(false);
    TurnOutputCalcTraceSwitch(false);
    TurnOutputCalcExpressSwitch(false);
}

void GuardConfig::TurnAllGuardOn() {
    TurnReadSwitch(true);
    TurnMathSwitch(true);
    TurnLogicSwitch(true);
    TurnCompareSwitch(true);
    TurnAssignSwitch(true);
    TurnIOTipSwitch(true);
    TurnArrayOutputSwitch(true);
    TurnOutputCalcTraceSwitch(true);
    TurnOutputCalcExpressSwitch(true);
}

void GuardConfig::TurnMathSwitch(bool yes) {
    rule["+"] = yes;
    rule["-"] = yes;
    rule["*"] = yes;
    rule["/"] = yes;
    rule["%"] = yes;
    rule["^"] = yes;
    rule["&"] = yes;
    rule["|"] = yes;
    rule["~"] = yes;
    rule["<<"] = yes;
    rule[">>"] = yes;
}

void GuardConfig::TurnLogicSwitch(bool yes) {
    rule["!"] = yes;
    rule["&&"] = yes;
    rule["||"] = yes;
}

void GuardConfig::TurnCompareSwitch(bool yes) {
    rule["<"] = yes;
    rule[">"] = yes;
    rule["<="] = yes;
    rule[">="] = yes;
    rule["=="] = yes;
    rule["!="] = yes;
}

void GuardConfig::TurnAssignSwitch(bool yes) {
    rule["="] = yes;
    rule["++"] = yes;
    rule["--"] = yes;
    rule["+="] = yes;
    rule["-="] = yes;
    rule["*="] = yes;
    rule["/="] = yes;
    rule["%="] = yes;
    rule["/="] = yes;
    rule["^="] = yes;
    rule["<<="] = yes;
    rule[">>="] = yes;
}

void GuardConfig::TurnReadSwitch(bool yes) {
    rule[""] = yes;
    _TRACE_READ_SWITCH = yes;
}

void GuardConfig::TurnIOTipSwitch(bool yes) {
    _ARRAY_IO_TIP_SWITCH = yes;
}

void GuardConfig::TurnArrayOutputSwitch(bool yes) {
    _ARRAY_OUT_PUT_SWITCH = yes;
}

void GuardConfig::TurnOutputCalcTraceSwitch(bool yes) {
    _OUTPUT_TRACE_SWITCH = yes;
}

void GuardConfig::TurnOutputCalcExpressSwitch(bool yes) {
    _OUT_PUT_EXPRES_SWITCH = yes;
}

void GuardConfig::TurnCalcExpressIdOrNum(bool yes) {
    _OUT_PUT_EXPRES_ID_OR_NUM_SWITCH = yes;
}

void GuardConfig::SetArrayOutputInterval(int n) {
    _ARRAY_OUT_PUT_INTERVAL = n;
}

void TurnTrace(bool yes) {
    GuardConfig::TurnOutputCalcTraceSwitch(yes);
}

void TurnExpres(bool yes) {
    GuardConfig::TurnOutputCalcExpressSwitch(yes);
}



#if OUT_OF_INDEX_DETECT
#define OUT_OF_INDEX_DETECT__(detect)       detect
#else
#define OUT_OF_INDEX_DETECT__(detect)
#endif



#if OUTPUT_TRACE_SWITCH
#define OUTPUT_TRACE_SWITCH__(trace)        trace
#else
#define OUTPUT_TRACE_SWITCH__(trace)
#endif



#if TRACE_STRING_SAVE
#define TRACE_STRING_SAVE____(calcString)   calcString
#else
#define TRACE_STRING_SAVE____(calcString)
#endif



#if VALUE_BE_READED_DO
#define VALUE_BE_READED_DO___(calcString)   calcString
#else
#define VALUE_BE_READED_DO___(calcString)
#endif



#if OLD_TO_NEW_VALUE_DO
#define OLD_TO_NEW_VALUE_DO__(calcString)   calcString
#else
#define OLD_TO_NEW_VALUE_DO__(calcString)
#endif



#endif /* GuardConfig_hpp */
