#ifndef MANUAL_HPP
#define MANUAL_HPP
#include "gt.h"
#include "TestUnit.hpp"
using namespace std;
using namespace gt;

/**
 * 算法分析器使用方法
 *
 * 1. 将文件拷贝到工作目录 并在工作文件中 #include "gt.h"
 *
 * 2. using namespace gt;
 *
 * 3. 修改对应的变量定义 例如： int i; 改成 Int i;
 *
 * 示例如下程序
 *
 */


int manual()
{
    //－－－－－－－－－－－－－－－－－－常用示例－－－－－－－－－－－－－－－－－－－－－－
    
    AddId("Pi", "r", "s");      // 为后面的变量命名用于跟踪输出到控制台，函数可以添加任意个参数
    Double Pi = 3.1415926, r=4.1;
    Double s = Pi * (r * r);
    
    Int i("i");                 // 将 int型变量 i 命名为 “i” 用于跟踪输出到控制台
    IntArr a1(5, "a1");         // 定义 int 型一维数组 a1 长度为5 并命名为 “a1” 用于跟踪输出到控制台
    IntArr2D a2(2, 3, "a2");    // 定义 int 型二维数组 a2 第一维长度为2 第二维长度为3  并命名为 “a2”
    
    a1[1]++;
    a2[1][2] *= s;
    i = a1[1] + a2[1][2];
    
    int ax2[2][2] = {
        {1, 2},
        {3, 4}};
    IntArr2D arr2(ax2);          // 构造一个2*2二维数组 arr2，相当于ax2的引用
    
    AddId("array");
    IntArray<2, 3, 4> array = {  // IntArray 的数组维数必须在编译期确定以获取更高构造效率
        {{1, 2, 3, 4},  {8}         },
        {{16},          {20},   {24}}
    };
    array[0][2][3] = 1;
    
    
    // －－－－－－－－－－－－－－－－－－C++ 相关－－－－－－－－－－－－－－－－－－－－－－－－
    
    // GuardConfig::TurnAllGuardOff();           // 关闭所有跟踪
    // GuardConfig::rule["="] = true;            // 开启 “＝” 跟踪，其他符号类似
    // GuardConfig::TurnArrayOutputSwitch(true); // 数组元素变化时，输出整个数组
    // GuardConfig::TurnCalcExpressIdOrNum(false);
    
    GuardConfig::TurnOutputCalcTraceSwitch(true);// 将 TRACE 输出到控制台
    GuardConfig::TurnOutputCalcExpressSwitch(true);// 将 EXPRES 输出到控制台
    GuardConfig::rule["<<"] = false;            // 关闭对 << 符号的跟踪
    GuardConfig::rule[">>"] = false;            // 关闭对 >> 符号的跟踪
    
    cout << a1;                                 // 输出方式 1
    
    for(int i=0; i<a1.size(); ++i) {
        cout << a1[i] << " ";                   // 输出方式 2
    } cout << endl;
    
    GuardType<std::function<void(int)> > f = [](int n){
        cout << "call std::function(" << n << ")" << endl;
    };
    f(1);
    
#if VALUE_BE_READED_DO || OLD_TO_NEW_VALUE_DO
    Int v = 3;
    // 设置回调函数当数值被读取时自动调用
    v.AddBeReadedDo([](int value) {
        cout << "ValueBeReaded: " << value << endl;
    }, "BeReadedCallBack");
    int n = v;
    v.RemoveBeReadDo("BeReadedCallBack");

    // 设置回调函数当数值被修改时自动调用
    v.AddChangedDo([](const int& newValue){
        cout << "Changed to newValue: " << newValue << endl;
    });
    v++;
    
    // 设置回调函数当数值被修改时自动调用
    v.AddChangedDo([](const int& newValue, int oldValue){
        cout << "newValue: " << newValue << " oldValue: " << oldValue << endl;
    });
    v+=v+n;
#endif
    
    // －－－－－－－－－－－－－－－－－－适配自己需要的跟踪类型－－－－－－－－－－－－－－－－－－－
    // 自定义 GT跟踪类型 需要的构造函数
    class GT : public Double
    {
    public :
        GT(const char * id = "defaultId") : Double(id)
        {
        }
        const GT& operator = (const double& data)
        {
            (Double&)*this = data;
            return *this;
        }
    };
    
    // 自定义 Vec跟踪类型 需要的构造函数
    class Vec : public DoubleArr
    {
    public :
        Vec(size_t length, const char* id = "defaultId") :
        DoubleArr(length, id)
        {
        }
    };
    
    // 自定义 Mat跟踪类型 需要的构造函数
    class Mat : public DoubleArr2D
    {
    public :
        Mat(size_t m, size_t n, const char* id = "defaultId") :
        DoubleArr2D(m, n, id)
        {
        }
    };
    
    // 自定义 Mat3d跟踪类型 需要的构造函数
    class Mat3d : public DoubleArr3D
    {
    public :
        Mat3d(size_t m, size_t n, size_t k, const char* id = "defaultId") :
        DoubleArr3D(m, n, k, id)
        { 
        }
    };
    
    Vec axx(3);

    TestUnit t;
    GuardConfig::TurnAllGuardOff();
    t.startTest();
    return 0;
}

#endif // MANUAL_HPP
