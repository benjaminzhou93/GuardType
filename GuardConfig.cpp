#include "GuardConfig.h"

std::ostream& GuardConfig::so = std::cout;      // 默认将跟踪信息输出到 std::cout

const bool GuardConfig::defaultGuard        = true;
bool GuardConfig::_TRACE_READ_SWITCH        = false;
bool GuardConfig::_OUT_PUT_TRACE_SWITCH     = false;
bool GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH = false;
bool GuardConfig::_OUT_PUT_EXPRES_SWITCH    = GuardConfig::defaultGuard;
bool GuardConfig::_ARRAY_IO_TIP_SWITCH      = GuardConfig::defaultGuard;
bool GuardConfig::_ARRAY_OUT_PUT_SWITCH     = GuardConfig::defaultGuard;
int GuardConfig::_ARRAY_OUT_PUT_INTERVAL    = 2;
std::queue<std::string> GuardConfig::idArray;
std::map<std::string, bool> GuardConfig::rule;

GuardConfig::GuardConfig()
{
    rule.insert(std::pair<std::string, bool>("+", defaultGuard));
    rule.insert(std::pair<std::string, bool>("-", defaultGuard));
    rule.insert(std::pair<std::string, bool>("*", defaultGuard));
    rule.insert(std::pair<std::string, bool>("/", defaultGuard));
    rule.insert(std::pair<std::string, bool>("%", defaultGuard));
    rule.insert(std::pair<std::string, bool>("^", defaultGuard));
    rule.insert(std::pair<std::string, bool>("&", defaultGuard));
    rule.insert(std::pair<std::string, bool>("|", defaultGuard));
    rule.insert(std::pair<std::string, bool>("~", defaultGuard));
    rule.insert(std::pair<std::string, bool>("<<", defaultGuard));
    rule.insert(std::pair<std::string, bool>(">>", defaultGuard));
    rule.insert(std::pair<std::string, bool>("!", defaultGuard));
    rule.insert(std::pair<std::string, bool>("&&", defaultGuard));
    rule.insert(std::pair<std::string, bool>("||", defaultGuard));
    rule.insert(std::pair<std::string, bool>("<", defaultGuard));
    rule.insert(std::pair<std::string, bool>(">", defaultGuard));
    rule.insert(std::pair<std::string, bool>("<=", defaultGuard));
    rule.insert(std::pair<std::string, bool>(">=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("==", defaultGuard));
    rule.insert(std::pair<std::string, bool>("!=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("+=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("-=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("*=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("/=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("%=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("^=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("<<=", defaultGuard));
    rule.insert(std::pair<std::string, bool>(">>=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("++", defaultGuard));
    rule.insert(std::pair<std::string, bool>("--", defaultGuard));
    rule.insert(std::pair<std::string, bool>("=", defaultGuard));
    rule.insert(std::pair<std::string, bool>("", true));
}

struct GuardConfig::AddNewName GuardConfig::PushNewName(std::string newName) {
    idArray.push(newName);
    return GuardConfig::AddNewName();
}

void GuardConfig::TurnAllGuardOff() {
    TurnReadSwitch(false);
    TurnMathSwitch(false);
    TurnLogicSwitch(false);
    TurnCompareSwitch(false);
    TurnAssignSwitch(false);
    TurnIOTipSwitch(false);
    TurnArrayOutPutSwitch(false);
    TurnOutPutCalcTraceSwitch(false);
    TurnOutPutCalcExpressSwitch(false);
}

void GuardConfig::TurnAllGuardOn() {
    TurnReadSwitch(true);
    TurnMathSwitch(true);
    TurnLogicSwitch(true);
    TurnCompareSwitch(true);
    TurnAssignSwitch(true);
    TurnIOTipSwitch(true);
    TurnArrayOutPutSwitch(true);
    TurnOutPutCalcTraceSwitch(true);
    TurnOutPutCalcExpressSwitch(true);
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

void GuardConfig::TurnArrayOutPutSwitch(bool yes) {
    _ARRAY_OUT_PUT_SWITCH = yes;
}

void GuardConfig::TurnOutPutCalcTraceSwitch(bool yes) {
    _OUT_PUT_TRACE_SWITCH = yes;
}

void GuardConfig::TurnOutPutCalcExpressSwitch(bool yes) {
    _OUT_PUT_EXPRES_SWITCH = yes;
}

void GuardConfig::TurnCalcExpressIdOrNum(bool yes) {
    _OUT_PUT_EXPRES_ID_OR_NUM_SWITCH = yes;
}

void GuardConfig::SetArrayOutPutInterval(int n) {
    _ARRAY_OUT_PUT_INTERVAL = n;
}
