#ifndef MANUAL_HPP
#define MANUAL_HPP
#include <numeric>
#include "gt.h"
using namespace std;

/**
 * 算法分析器使用方法
 *
 * 1.将 GT.h 文件拷贝到工作目录 并在工作文件中 #include "gt.h"
 *
 * 2.修改对应的变量定义 例如： int i; 改成 Int i;
 *
 * 示例如下程序
 *
 */


int manual() {
    //－－－－－－－－－－－－－－－－－－常用示例－－－－－－－－－－－－－－－－－－－－－－
    
    Int i("i");                 // 将 int型变量 i 命名为 “i” 用于跟踪输出到控制台
    IntArr a1(5, "a1");         // 定义 int 型一维数组 a1 长度为5 并命名为 “a1” 用于跟踪输出到控制台
    IntArr2D a2(2, 3, "a2");     // 定义 int 型二维数组 a2 第一维长度为2 第二维长度为3  并命名为 “a2” 用于跟踪输出到控制台
    
    AddId("array");
    auto array = IntArray(1, 2, 3, 4, 5, 6, 7, 8, 9);
    
    AddId("Pi", "r");           // 为后面的变量命名用于跟踪输出到控制台，函数可以添加任意个参数
    Double Pi = 3.1415926, r=4.1;
    2 * Pi * r;
    
    a1[i]++;
    a2[1][2] *= i;
    for(int i=0; i<5; i++) {
        a1[i] = 5-i;
    }
    
    int ax2[2][2] = {
        {1, 2},
        {3, 4}};
    IntArr2D arr2(ax2);          // 构造一个2*2二维数组 arr2，相当于ax2的引用
    
    IntPtr p = a1;              // 定义 p 为 int 型指针(类似于 int * p;) 并将数组首地址复制给指针
    *(p+1) = 9;                 // 等价于 a1[1] = 9;
    
    
    
    // －－－－－－－－－－－－－－－－－－C++ 相关－－－－－－－－－－－－－－－－－－－－－－－－
    
    //GuardConfig::TurnAllGuardOff();             // 关闭所有跟踪
    
    //GuardConfig::rule["="] = true;              // 开启 “＝” 跟踪，其他符号类似
    
    //GuardConfig::TurnArrayOutPutSwitch(true);   // 数组元素变化时，输出整个数组
    
    TurnTrace(true);            // 将 TRACE 输出到控制台
    TurnExpres(true);           // 将 EXPRES 输出到控制台
    GTRule["<<"] = false;       // 关闭对 << 符号的跟踪
    GTRule[">>"] = false;       // 关闭对 >> 符号的跟踪
    
    cout << a1;                                 // 输出方式 1
    
    for(size_t i=0; i<a1.size(); i++) {
        cout << a1[i] << " ";                   // 输出方式 2
    } cout << endl;
    
    for(IntArr::iterator iter=a1.begin(); iter != a1.end(); iter++) {
        cout << *iter << " ";                   // 输出方式 3
    } cout << endl;
    
    copy(a1.begin(), a1.end(), ostream_iterator<int>(cout, " "));// 输出方式 4
    cout << endl;
    
    // 排序
    std::sort(a1.begin(), a1.end());
    cout << a1;
    
    // 以 0 为初始值 计算累加和
    Int result = accumulate(a1.begin(), a1.end(), 0);
    cout << "accumulate result: " << result << endl;
    
    
    Int v = 3;
    VALUE_BE_READED_DO___(
                          v.ValueBeReadedDoing = [](int data) {
                              std::cout << "ValueBeReaded: " << data << std::endl;
                          };)
    VALUE_CHANGED_DO_____(
                          v.ValueChangedDoing = [](int &data) {
                              std::cout << "ValueChanged: " << data << std::endl;
                          };)
    OLD_TO_NEW_VALUE_DO__(
                          v.ValueChangedDoingWithOldAndNewValue = [](int oldValue, int &newValue) {
                              std::cout << "oldValue: " << oldValue << ", newValue: " << newValue << std::endl;
                          };)
    v++;
    
    
    // －－－－－－－－－－－－－－－－－－适配自己需要的跟踪类型－－－－－－－－－－－－－－－－－－－
    
    // 用 MyInt 类型定义数据, 实际操作的数据类型为 int
    // 并且 自动生成了 一维数组 MyIntArr, 二维数组 MyIntArr2, 三维数组 MyIntArr3
    GT_TYPE(int, MyInt);
    
    
    // 自定义 GT跟踪类型 需要的构造函数
    class GT : public Double {
        public :
        GT(const char * id = "defaultId") : Double(id){ }
        const GT& operator = (const double& data) {
            (Double&)*this = data;
            return *this;
        }
    };
    
    // 自定义 Vec跟踪类型 需要的构造函数
    class Vec : public DoubleArr {
        public :
        Vec(size_t length, const char* id = "defaultId") :
        DoubleArr(length, id){ }
    };
    
    // 自定义 Mat跟踪类型 需要的构造函数
    class Mat : public DoubleArr2D {
        public :
        Mat(size_t m, size_t n, const char* id = "defaultId") :
        DoubleArr2D(m, n, id){ }
    };
    
    // 自定义 Mat3d跟踪类型 需要的构造函数
    class Mat3d : public DoubleArr3D {
        public :
        Mat3d(size_t m, size_t n, size_t k, const char* id = "defaultId") :
        DoubleArr3D(m, n, k, id){ }
    };
    
    Vec axx(3);
    
    return 0;
}

#endif // MANUAL_HPP
