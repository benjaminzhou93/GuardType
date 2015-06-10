#ifndef GUARDCONFIG_H
#define GUARDCONFIG_H
#include <queue>
#include <map>
#include <string>
#include <iostream>

#define _SPACES "\t\t\t\t"              // 数据读写的提示位置

// 作为基类只有一个实例对象作为配置
class GuardConfig
{
    GuardConfig();
    template<typename T>
    friend class GuardType;
public:
    struct AddNewId;
    friend struct AddNewId;
public:
    // 预先为要定义的变量赋予名字
    static struct AddNewId PushNewId(std::string newId);

    // 开启所有跟踪
    static void TurnAllGuardOff();
    // 关闭所有跟踪
    static void TurnAllGuardOn();

    // 读取单元素跟踪开关   GT: 99 （读取 GT 内容为 99）
    static void TurnReadSwitch(bool yes);
    // 算数运算跟踪开关     +, -, *, /, %, ^, &,|, ~, <<, >>
    static void TurnMathSwitch(bool yes);
    // 逻辑运算跟踪开关     !, &&, ||
    static void TurnLogicSwitch(bool yes);
    // 比较运算跟踪开关     <, >, <=, >=, !=, ==
    static void TurnCompareSwitch(bool yes);
    // 赋值运算跟踪开关     =, ++, --, +=, -=, *=, /=, %=, ^=, <<=, >>=
    static void TurnAssignSwitch(bool yes);
    static void TurnOutPutCalcTraceSwitch(bool yes);
    static void TurnOutPutCalcExpressSwitch(bool yes);

    static void TurnIOTipSwitch(bool yes);         // 从键盘读取数据时提示开关
    static void TurnArrayOutPutSwitch(bool yes);   // 输出整行数组跟踪开关
    static void TurnCalcExpressIdOrNum(bool yes);  // 输出计算表达式yes为Id,no为num
    static void SetArrayOutPutInterval(int n);     // 调整数组元素之间的输出间隔

    static bool _TRACE_READ_SWITCH;                // 读取单元素跟踪开关
    static bool _OUT_PUT_TRACE_SWITCH;             // 输出计算过程跟踪开关
    static bool _OUT_PUT_EXPRES_SWITCH;            // 输出计算表达式跟踪开关
    static bool _OUT_PUT_EXPRES_ID_OR_NUM_SWITCH;  // 设置Expres表达方式为输出纯id还是纯num
    static bool _ARRAY_IO_TIP_SWITCH;              // 从键盘读取数据时提示开关
    static bool _ARRAY_OUT_PUT_SWITCH;             // 输出数组跟踪开关
    static int  _ARRAY_OUT_PUT_INTERVAL;           // 输出的数组元素之间的间隔
    const static bool defaultGuard;                // 默认跟踪全部开启
public :
    static std::ostream& so;                       // 默认跟踪输出到 std::cout
    static std::queue<std::string> idArray;
    static std::map<std::string, bool> rule;
    
    struct AddNewId {
        public :
        struct AddNewId operator () (std::string name) {
            GuardConfig::idArray.push(name);
            return AddNewId();
        }
    };
};

#endif // GUARDCONFIG_H
