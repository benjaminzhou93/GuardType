#ifndef MANUAL_HPP
#define MANUAL_HPP
#include <numeric>
#include "gt.h"
using namespace std;

/**
 * @brief 算法分析器使用方法
 *
 * 1.将文件解压到工作目录 并在工作文件中 #include "gt.h"
 *
 * 2.修改对应的变量定义 例如： int i; 改成 Int i;
 *
 * 示例如下程序
 *
 * @return
 */



// 函数传递数组的三种方式
// 方式一通过指针传递 IntPtr p 类似于 int * p;
void func(IntPtr p) {
    for(int i=0; i<3; i++)
        p[i] = i;
}

// 通过 C++ 引用传递数组
void func2(IntArr& arr) { // 注意这里的 “&”
    // 这里数组的改变将会被传递到函数外部，就好像是在使用数组指针
    arr[1] = 1;
}


int manual() {
    //－－－－－－－－－－－－－－－－－－常用示例－－－－－－－－－－－－－－－－－－－－－－
    
    Int i("i");                 // 将 int型变量 i 命名为 “i” 用于跟踪输出到控制台
    IntArr a1(5, "a1");         // 定义 int 型一维数组 a1 长度为5 并命名为 “a1” 用于跟踪输出到控制台
    IntArr2 a2(2, 3, "a2");     // 定义 int 型二维数组 a2 第一维长度为2 第二维长度为3  并命名为 “a2” 用于跟踪输出到控制台
    IntArr3 a3(2, 3, 4, "a3");  // 定义 int 型三维数组 a3 第一维长度为2 第二维长度为3 第三维长度为4  并命名为 “a3” 用于跟踪输出到控制台
    // 除了 Int 之外 GT.h 中还定义了 Char, Short, Double, LongDouble, String 等类型 和 对应的数组类型 可以直接用来使用
    
    AddId("id_Pi")("id_r");     // 为后面的变量命名用于跟踪输出到控制台，函数后面可以添加任意个参数
    Double Pi = 3.1415926, r;
    r = 4.1;
    
    AddId("id_perimeter")("id_area");   // 为后面的变量命名用于跟踪输出到控制台
    Double perimeter, area;
    perimeter = 2 * Pi * r;
    area = Pi * pow(r, 2);
    
    a1[i]++;
    a2[1][2] *= i;
    a3[1][2][3] <= i;

    a3[1][1][1] = 1;
    for(int i=0; i<5; i++) {
        a1[i] = 5-i;
    }

    //printf("int ＝ %d\n 请输入下一个数值\n", i);
    //scanf("%d", &i);

    
    int ax[] = {1, 2, 3, 4, 5};
    IntArr arr1(ax);            // 构造一个一维数组 arr1 并且把 ax 全部元素复制到 arr
    
    ax[1] = 1;                  // 这里不会改变 ax 的值
    int ax2[2][2] = {
        {1, 2},
        {3, 4}};
    IntArr2 arr2(ax2);          // 构造一个2*2二维数组 arr2 并且把 ax2 全部元素复制到 arr2
    
    
    
    // －－－－－－－－－－－－－－－－－－指针的用法－－－－－－－－－－－－－－－－－－－－－－－

    IntPtr p = a1;              // 定义 p 为 int 型指针(类似于 int * p;) 并将数组首地址复制给指针
    *(p+1) = 9;                 // 等价于 a1[1] = 9;
    IntPtr2 p2 = a2;            // 定义 p2 为 int 型二级指针(类似于 int ** p;) 并将二维数组首地址复制给指针
    **p2 = 9;                   // 等价于 a2[0][0] = 9;

    

    // －－－－－－－－－－－－－－－－－－C++ 相关－－－－－－－－－－－－－－－－－－－－－－－－

    //GuardConfig::TurnAllGuardOff();             // 关闭所有跟踪

    //GuardConfig::rule["="] = true;              // 开启 “＝” 跟踪，其他符号类似

    //GuardConfig::TurnArrayOutPutSwitch(true);   // 数组元素变化时，输出整个数组
    
    TurnTrace(ON);              // 将 TRACE 输出到控制台
    TurnExpres(ON);             // 将 EXPRES 输出到控制台
    
    Double j = 3;
    j.SetId("j");

    cout << a1;                                 // 输出方式 1

    for(size_t i=0; i<a1.size(); i++) {
        cout << a1[i] << " ";                   // 输出方式 2
    } cout << endl;

    for(IntArr::iterator iter=a1.begin(); iter != a1.end(); iter++) {
        cout << *iter << " ";                   // 输出方式 3
    } cout << endl;

    copy(a1.begin(), a1.end(), ostream_iterator<IntArr::value_type>(cout, " "));// 输出方式 4

    // 排序
    std::sort(a1.begin(), a1.end());
    
    // 以 0 为初始值 计算累加和
    Int result = accumulate(a1.begin(), a1.end(), 0);
    cout << "accumulate result: " << result << endl;



    // －－－－－－－－－－－－－－－－－－适配自己需要的跟踪类型－－－－－－－－－－－－－－－－－－－

    // 用 MyInt 类型定义数据, 实际操作的数据类型为 int
    // 并且 自动生成了 一维数组 MyIntArr, 二维数组 MyIntArr2, 三维数组 MyIntArr3
    GT_TYPE(int, MyInt);


    // 自定义 GT跟踪类型 需要的构造函数
    class GT : public Double {
    public :
        GT(const std::string& id = "") : Double(id){ }
        const GT& operator = (const double& data) {
            (Double&)*this = data;
            return *this;
        }
    };

    // 自定义 Vec跟踪类型 需要的构造函数
    class Vec : public DoubleArr {
    public :
        Vec(size_t length, const std::string& id = "") :
            DoubleArr(length, id){ }
    };

    // 自定义 Mat跟踪类型 需要的构造函数
    class Mat : public DoubleArr2 {
    public :
        Mat(size_t m, size_t n, const std::string& id = "") :
            DoubleArr2(m, n, id){ }
    };

    // 自定义 Mat3d跟踪类型 需要的构造函数
    class Mat3d : public DoubleArr3 {
    public :
        Mat3d(size_t m, size_t n, size_t k, const std::string& id = "") :
            DoubleArr3(m, n, k, id){ }
    };
    
    return 0;
}

#endif // MANUAL_HPP