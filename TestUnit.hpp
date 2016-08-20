#ifndef TestUnit_hpp
#define TestUnit_hpp

#include "gt.h"
#include <ctime>
#include <iostream>

using namespace std;

#define TEST_UNIT(test)                 \
{                                       \
    time_t begin, end;                  \
    begin = clock();                    \
    for(int i = 0; i < times; i++) {    \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
    }                                   \
    end = clock();                      \
    cout << (1.0*(end-begin)/CLOCKS_PER_SEC - extraRunTime) / 10 << "         " << #test << endl;\
}



#define TEST_COMPARE_UNIT(test)         \
{                                       \
    time_t begin, end;                  \
    double cost1, cost2;                \
    begin = clock();                    \
    for(int i = 0; i < times; i++) {    \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
        {test;}                         \
    }                                   \
    end = clock();                      \
    cost1 = (1.0*(end-begin)/CLOCKS_PER_SEC - extraRunTime) / 10;\
    {                                   \
        volatile int n=1;               \
        volatile long long l=1;         \
        volatile float f=1;             \
        volatile int arr[10];           \
        volatile int arr2[10][10];      \
        volatile int arr3[10][10][10];  \
        begin = clock();                \
        for(int i = 0; i < times; i++) { \
            {test;}                     \
            {test;}                     \
            {test;}                     \
            {test;}                     \
            {test;}                     \
            {test;}                     \
            {test;}                     \
            {test;}                     \
            {test;}                     \
            {test;}                     \
        }                               \
        end = clock();                  \
        cost2 = (1.0*(end-begin)/CLOCKS_PER_SEC - extraRunTime) / 10;\
    }                                   \
    cout << "GT cost: " << cost1 << "    " \
        << " sys cost: " << cost2       \
        << "    rate: " << cost1/cost2 << "     "\
        << #test << endl;               \
}



class TestUnit {
    int times = 1000000 / 10;
    double extraRunTime;
public:
    TestUnit() {
        extraRunTime = runTimeOfFor();
    }
    
    ~TestUnit() {
        
    }
    
    double runTimeOfFor() {
        time_t begin, end;
        begin = clock();
        int counts = times*10;
        for(int i = 0; i < counts; i++);
        end = clock();
        double runTime = 0.1*(end-begin)/CLOCKS_PER_SEC;
        cout << "runTimeOfFor: " << runTime << endl;
        return runTime;
    }
    class Cinner {
    public:
        Cinner(){
            int i; i=1;
        };
    };
    
    void startTest() {
        TEST_UNIT(volatile Cinner c);
        TEST_UNIT(volatile int n; n=1;);
        TEST_UNIT(func0());
        TEST_UNIT(func1(1));
        TEST_UNIT(func2(1, 2));
        
        testInit();
        testCalc();
        testArray();
    }
    
    void func0() {
        
    }
    
    void func1(int i) {
        
    }
    
    void func2(int i, int n) {
        
    }
    
    void testInit() {
        
        TEST_UNIT(volatile int n; n=1;);
        TEST_UNIT(Bool a);
        TEST_UNIT(Char a);
        TEST_UNIT(Short a);
        TEST_UNIT(Int a);
        TEST_UNIT(Long a);
        TEST_UNIT(LLong a);
        TEST_UNIT(Float a);
        TEST_UNIT(Double a);
        TEST_UNIT(string s);
        TEST_UNIT(String s);
        
        TEST_UNIT(int a(0); a=0;);
        TEST_UNIT(Bool a(0));
        TEST_UNIT(Char a(0));
        TEST_UNIT(Short a(0));
        TEST_UNIT(Int a(0));
        TEST_UNIT(Long a(0));
        TEST_UNIT(LLong a(0));
        TEST_UNIT(Float a(0));
        TEST_UNIT(Double a(0));
        TEST_UNIT(string s("s"));
        TEST_UNIT(String s("s"));
        
        Int a, b;
        IntArr arr(10);
        TEST_UNIT(volatile int a[10]; a[0]=0);
        TEST_UNIT(int * p = new int[10]; delete[] p;);
        TEST_UNIT(IntArr arr(10));
        TEST_UNIT(IntArr2D arr(3, 3));
        TEST_UNIT(IntArr3D arr(2, 2, 2));
        TEST_UNIT(auto arr = IntArray(2, 2, 2));
        TEST_UNIT(volatile int a[2][2][2]; a[0][0][0]=0;);
        
    }
    
    void testCalc() {
        Int n;
        IntArr arr(10);
        IntArr2D arr2(10, 10);
        IntArr3D arr3(10, 10, 10);
        
        TEST_COMPARE_UNIT(n=1);
        TEST_COMPARE_UNIT(n++);
        TEST_COMPARE_UNIT(n--);
        TEST_COMPARE_UNIT(n+=1);
        TEST_COMPARE_UNIT(n-=1);
        TEST_COMPARE_UNIT(n*=1);
        TEST_COMPARE_UNIT(n/=1);
        TEST_COMPARE_UNIT(n%=1);
        TEST_COMPARE_UNIT(n^=1);
        TEST_COMPARE_UNIT(n<<=1);
        TEST_COMPARE_UNIT(n>>=1);
        
        TEST_COMPARE_UNIT(n+1);
        TEST_COMPARE_UNIT(n-1);
        TEST_COMPARE_UNIT(n*1);
        TEST_COMPARE_UNIT(n/1);
        TEST_COMPARE_UNIT(n%1);
        TEST_COMPARE_UNIT(n^1);
        TEST_COMPARE_UNIT(n&1);
        TEST_COMPARE_UNIT(~n);
        TEST_COMPARE_UNIT(!n);
        TEST_COMPARE_UNIT(n<<1);
        TEST_COMPARE_UNIT(n>>1);
        
        TEST_COMPARE_UNIT(n&&1);
        TEST_COMPARE_UNIT(n||1);
        
        TEST_COMPARE_UNIT(n<1);
        TEST_COMPARE_UNIT(n>1);
        TEST_COMPARE_UNIT(n<=1);
        TEST_COMPARE_UNIT(n>=1);
        TEST_COMPARE_UNIT(n==1);
        TEST_COMPARE_UNIT(n!=1);
        
        
        
        
        
        TEST_COMPARE_UNIT(n=n);
        TEST_COMPARE_UNIT(n+=n);
        TEST_COMPARE_UNIT(n-=n);
        TEST_COMPARE_UNIT(n*=n);
        TEST_COMPARE_UNIT(n=1;n/=n);
        TEST_COMPARE_UNIT(n=1;n%=n);
        TEST_COMPARE_UNIT(n^=n);
        TEST_COMPARE_UNIT(n<<=n);
        TEST_COMPARE_UNIT(n>>=n);
        
        TEST_COMPARE_UNIT(n+n);
        TEST_COMPARE_UNIT(n-n);
        TEST_COMPARE_UNIT(n*n);
        TEST_COMPARE_UNIT(n=1;n/n);
        TEST_COMPARE_UNIT(n=1;n%n);
        TEST_COMPARE_UNIT(n^n);
        TEST_COMPARE_UNIT(n&n);
        TEST_COMPARE_UNIT(n<<n);
        TEST_COMPARE_UNIT(n>>n);
        
        TEST_COMPARE_UNIT(n&&n);
        TEST_COMPARE_UNIT(n||n);
        
        TEST_COMPARE_UNIT(n<n);
        TEST_COMPARE_UNIT(n>n);
        TEST_COMPARE_UNIT(n<=n);
        TEST_COMPARE_UNIT(n>=n);
        TEST_COMPARE_UNIT(n==n);
        TEST_COMPARE_UNIT(n!=n);
        
        
        
        
        
        
        TEST_COMPARE_UNIT(n=arr[0]);
        TEST_COMPARE_UNIT(n+=arr[0]);
        TEST_COMPARE_UNIT(n-=arr[0]);
        TEST_COMPARE_UNIT(n*=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;n/=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;n%=arr[0]);
        TEST_COMPARE_UNIT(n^=arr[0]);
        TEST_COMPARE_UNIT(n<<=arr[0]);
        TEST_COMPARE_UNIT(n>>=arr[0]);
        
        TEST_COMPARE_UNIT(arr[0]+arr[0]);
        TEST_COMPARE_UNIT(n-arr[0]);
        TEST_COMPARE_UNIT(n*arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;n/arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;n%arr[0]);
        TEST_COMPARE_UNIT(n^arr[0]);
        TEST_COMPARE_UNIT(n&arr[0]);
        TEST_COMPARE_UNIT(~arr[0]);
        TEST_COMPARE_UNIT(!arr[0]);
        TEST_COMPARE_UNIT(n<<arr[0]);
        TEST_COMPARE_UNIT(n>>arr[0]);
        
        TEST_COMPARE_UNIT(n&&arr[0]);
        TEST_COMPARE_UNIT(n||arr[0]);
        
        TEST_COMPARE_UNIT(n<arr[0]);
        TEST_COMPARE_UNIT(n>arr[0]);
        TEST_COMPARE_UNIT(n<=arr[0]);
        TEST_COMPARE_UNIT(n>=arr[0]);
        TEST_COMPARE_UNIT(n==arr[0]);
        TEST_COMPARE_UNIT(n!=arr[0]);
        
        
        
        
        
        
        
        
        
        
        
        TEST_COMPARE_UNIT(arr[0]=arr[0]);
        TEST_COMPARE_UNIT(arr[0]++);
        TEST_COMPARE_UNIT(arr[0]--);
        TEST_COMPARE_UNIT(arr[0]+=arr[0]);
        TEST_COMPARE_UNIT(arr[0]-=arr[0]);
        TEST_COMPARE_UNIT(arr[0]*=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;arr[0]/=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;arr[0]%=arr[0]);
        TEST_COMPARE_UNIT(arr[0]^=arr[0]);
        TEST_COMPARE_UNIT(arr[0]<<=arr[0]);
        TEST_COMPARE_UNIT(arr[0]>>=arr[0]);
        
        TEST_COMPARE_UNIT(arr[0]+arr[0]);
        TEST_COMPARE_UNIT(arr[0]-arr[0]);
        TEST_COMPARE_UNIT(arr[0]*arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;arr[0]/arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;arr[0]%arr[0]);
        TEST_COMPARE_UNIT(arr[0]^arr[0]);
        TEST_COMPARE_UNIT(arr[0]&arr[0]);
        TEST_COMPARE_UNIT(arr[0]<<arr[0]);
        TEST_COMPARE_UNIT(arr[0]>>arr[0]);
        
        TEST_COMPARE_UNIT(arr[0]&&arr[0]);
        TEST_COMPARE_UNIT(arr[0]||arr[0]);
        
        TEST_COMPARE_UNIT(arr[0]<arr[0]);
        TEST_COMPARE_UNIT(arr[0]>arr[0]);
        TEST_COMPARE_UNIT(arr[0]<=arr[0]);
        TEST_COMPARE_UNIT(arr[0]>=arr[0]);
        TEST_COMPARE_UNIT(arr[0]==arr[0]);
        TEST_COMPARE_UNIT(arr[0]!=arr[0]);
        
        
        
        
        
        
        
        
        TEST_COMPARE_UNIT(arr[0]=1);
        TEST_COMPARE_UNIT(arr[0]++);
        TEST_COMPARE_UNIT(arr[0]--);
        TEST_COMPARE_UNIT(arr[0]+=1);
        TEST_COMPARE_UNIT(arr[0]-=1);
        TEST_COMPARE_UNIT(arr[0]*=1);
        TEST_COMPARE_UNIT(arr[0]/=1);
        TEST_COMPARE_UNIT(arr[0]%=1);
        TEST_COMPARE_UNIT(arr[0]^=1);
        TEST_COMPARE_UNIT(arr[0]<<=1);
        TEST_COMPARE_UNIT(arr[0]>>=1);
        
        TEST_COMPARE_UNIT(arr[0]+1);
        TEST_COMPARE_UNIT(arr[0]-1);
        TEST_COMPARE_UNIT(arr[0]*1);
        TEST_COMPARE_UNIT(arr[0]/1);
        TEST_COMPARE_UNIT(arr[0]%1);
        TEST_COMPARE_UNIT(arr[0]^1);
        TEST_COMPARE_UNIT(arr[0]&1);
        TEST_COMPARE_UNIT(arr[0]<<1);
        TEST_COMPARE_UNIT(arr[0]>>1);
        
        TEST_COMPARE_UNIT(arr[0]&&1);
        TEST_COMPARE_UNIT(arr[0]||1);
        
        TEST_COMPARE_UNIT(arr[0]<1);
        TEST_COMPARE_UNIT(arr[0]>1);
        TEST_COMPARE_UNIT(arr[0]<=1);
        TEST_COMPARE_UNIT(arr[0]>=1);
        TEST_COMPARE_UNIT(arr[0]==1);
        TEST_COMPARE_UNIT(arr[0]!=1);
        
        
        
        
        
        
        
        
        TEST_COMPARE_UNIT(1+n);
        TEST_COMPARE_UNIT(1-n);
        TEST_COMPARE_UNIT(1*n);
        TEST_COMPARE_UNIT(n=1;1/n);
        TEST_COMPARE_UNIT(n=1;1%n);
        TEST_COMPARE_UNIT(1^n);
        TEST_COMPARE_UNIT(1&n);
        TEST_COMPARE_UNIT(1<<n);
        TEST_COMPARE_UNIT(1>>n);
        
        TEST_COMPARE_UNIT(1&&n);
        TEST_COMPARE_UNIT(int x=1; x||n);
        
        TEST_COMPARE_UNIT(1<n);
        TEST_COMPARE_UNIT(1>n);
        TEST_COMPARE_UNIT(1<=n);
        TEST_COMPARE_UNIT(1>=n);
        TEST_COMPARE_UNIT(1==n);
        TEST_COMPARE_UNIT(1!=n);
        
        
        
        
        
        
        
        
        TEST_COMPARE_UNIT(1+arr[0]);
        TEST_COMPARE_UNIT(1-arr[0]);
        TEST_COMPARE_UNIT(1*arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;1/arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;1%arr[0]);
        TEST_COMPARE_UNIT(1^arr[0]);
        TEST_COMPARE_UNIT(1&arr[0]);
        TEST_COMPARE_UNIT(1<<arr[0]);
        TEST_COMPARE_UNIT(1>>arr[0]);
        
        TEST_COMPARE_UNIT(1&&arr[0]);
        TEST_COMPARE_UNIT(int x=1; x||arr[0]);
        
        TEST_COMPARE_UNIT(1<arr[0]);
        TEST_COMPARE_UNIT(1>arr[0]);
        TEST_COMPARE_UNIT(1<=arr[0]);
        TEST_COMPARE_UNIT(1>=arr[0]);
        TEST_COMPARE_UNIT(1==arr[0]);
        TEST_COMPARE_UNIT(1!=arr[0]);
        
        
        
        
        
        
        TEST_COMPARE_UNIT(n=n);
        TEST_COMPARE_UNIT(n+=n);
        TEST_COMPARE_UNIT(n-=n);
        TEST_COMPARE_UNIT(n*=n);
        TEST_COMPARE_UNIT(n=1;n/=n);
        TEST_COMPARE_UNIT(n=1;n%=n);
        TEST_COMPARE_UNIT(n^=n);
        TEST_COMPARE_UNIT(n<<=n);
        TEST_COMPARE_UNIT(n>>=n);
        
        TEST_COMPARE_UNIT(n+n);
        TEST_COMPARE_UNIT(n-n);
        TEST_COMPARE_UNIT(n*n);
        TEST_COMPARE_UNIT(n=1;n/n);
        TEST_COMPARE_UNIT(n=1;n%n);
        TEST_COMPARE_UNIT(n^n);
        TEST_COMPARE_UNIT(n&n);
        TEST_COMPARE_UNIT(n<<n);
        TEST_COMPARE_UNIT(n>>n);
        
        TEST_COMPARE_UNIT(n&&n);
        TEST_COMPARE_UNIT(n||n);
        
        TEST_COMPARE_UNIT(n<n);
        TEST_COMPARE_UNIT(n>n);
        TEST_COMPARE_UNIT(n<=n);
        TEST_COMPARE_UNIT(n>=n);
        TEST_COMPARE_UNIT(n==n);
        TEST_COMPARE_UNIT(n!=n);
        
        
        
        
        
        
        TEST_COMPARE_UNIT(n=arr[0]);
        TEST_COMPARE_UNIT(n+=arr[0]);
        TEST_COMPARE_UNIT(n-=arr[0]);
        TEST_COMPARE_UNIT(n*=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;n/=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;n%=arr[0]);
        TEST_COMPARE_UNIT(n^=arr[0]);
        TEST_COMPARE_UNIT(n<<=arr[0]);
        TEST_COMPARE_UNIT(n>>=arr[0]);
        
        TEST_COMPARE_UNIT(arr[0]+arr[0]);
        TEST_COMPARE_UNIT(n-arr[0]);
        TEST_COMPARE_UNIT(n*arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;n/arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;n%arr[0]);
        TEST_COMPARE_UNIT(n^arr[0]);
        TEST_COMPARE_UNIT(n&arr[0]);
        TEST_COMPARE_UNIT(~arr[0]);
        TEST_COMPARE_UNIT(!arr[0]);
        TEST_COMPARE_UNIT(n<<arr[0]);
        TEST_COMPARE_UNIT(n>>arr[0]);
        
        TEST_COMPARE_UNIT(n&&arr[0]);
        TEST_COMPARE_UNIT(n||arr[0]);
        
        TEST_COMPARE_UNIT(n<arr[0]);
        TEST_COMPARE_UNIT(n>arr[0]);
        TEST_COMPARE_UNIT(n<=arr[0]);
        TEST_COMPARE_UNIT(n>=arr[0]);
        TEST_COMPARE_UNIT(n==arr[0]);
        TEST_COMPARE_UNIT(n!=arr[0]);
        
        
        
        
        
        
        
        
        
        
        
        TEST_COMPARE_UNIT(arr[0]=arr[0]);
        TEST_COMPARE_UNIT(arr[0]++);
        TEST_COMPARE_UNIT(arr[0]--);
        TEST_COMPARE_UNIT(arr[0]+=arr[0]);
        TEST_COMPARE_UNIT(arr[0]-=arr[0]);
        TEST_COMPARE_UNIT(arr[0]*=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;arr[0]/=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;arr[0]%=arr[0]);
        TEST_COMPARE_UNIT(arr[0]^=arr[0]);
        TEST_COMPARE_UNIT(arr[0]<<=arr[0]);
        TEST_COMPARE_UNIT(arr[0]>>=arr[0]);
        
        TEST_COMPARE_UNIT(arr[0]+arr[0]);
        TEST_COMPARE_UNIT(arr[0]-arr[0]);
        TEST_COMPARE_UNIT(arr[0]*arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;arr[0]/arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;arr[0]%arr[0]);
        TEST_COMPARE_UNIT(arr[0]^arr[0]);
        TEST_COMPARE_UNIT(arr[0]&arr[0]);
        TEST_COMPARE_UNIT(arr[0]<<arr[0]);
        TEST_COMPARE_UNIT(arr[0]>>arr[0]);
        
        TEST_COMPARE_UNIT(arr[0]&&arr[0]);
        TEST_COMPARE_UNIT(arr[0]||arr[0]);
        
        TEST_COMPARE_UNIT(arr[0]<arr[0]);
        TEST_COMPARE_UNIT(arr[0]>arr[0]);
        TEST_COMPARE_UNIT(arr[0]<=arr[0]);
        TEST_COMPARE_UNIT(arr[0]>=arr[0]);
        TEST_COMPARE_UNIT(arr[0]==arr[0]);
        TEST_COMPARE_UNIT(arr[0]!=arr[0]);
        
        
        
        
        
        
        
        
        TEST_COMPARE_UNIT(arr[0]=1);
        TEST_COMPARE_UNIT(arr[0]++);
        TEST_COMPARE_UNIT(arr[0]--);
        TEST_COMPARE_UNIT(arr[0]+=1);
        TEST_COMPARE_UNIT(arr[0]-=1);
        TEST_COMPARE_UNIT(arr[0]*=1);
        TEST_COMPARE_UNIT(arr[0]/=1);
        TEST_COMPARE_UNIT(arr[0]%=1);
        TEST_COMPARE_UNIT(arr[0]^=1);
        TEST_COMPARE_UNIT(arr[0]<<=1);
        TEST_COMPARE_UNIT(arr[0]>>=1);
        
        TEST_COMPARE_UNIT(arr[0]+1);
        TEST_COMPARE_UNIT(arr[0]-1);
        TEST_COMPARE_UNIT(arr[0]*1);
        TEST_COMPARE_UNIT(arr[0]/1);
        TEST_COMPARE_UNIT(arr[0]%1);
        TEST_COMPARE_UNIT(arr[0]^1);
        TEST_COMPARE_UNIT(arr[0]&1);
        TEST_COMPARE_UNIT(arr[0]<<1);
        TEST_COMPARE_UNIT(arr[0]>>1);
        
        TEST_COMPARE_UNIT(arr[0]&&1);
        TEST_COMPARE_UNIT(arr[0]||1);
        
        TEST_COMPARE_UNIT(arr[0]<1);
        TEST_COMPARE_UNIT(arr[0]>1);
        TEST_COMPARE_UNIT(arr[0]<=1);
        TEST_COMPARE_UNIT(arr[0]>=1);
        TEST_COMPARE_UNIT(arr[0]==1);
        TEST_COMPARE_UNIT(arr[0]!=1);
        
        
        
        
        
        
        
        
        TEST_COMPARE_UNIT(1+n);
        TEST_COMPARE_UNIT(1-n);
        TEST_COMPARE_UNIT(1*n);
        TEST_COMPARE_UNIT(n=1;1/n);
        TEST_COMPARE_UNIT(n=1;1%n);
        TEST_COMPARE_UNIT(1^n);
        TEST_COMPARE_UNIT(1&n);
        TEST_COMPARE_UNIT(1<<n);
        TEST_COMPARE_UNIT(1>>n);
        
        TEST_COMPARE_UNIT(1&&n);
        TEST_COMPARE_UNIT(int x=1; x||n);
        
        TEST_COMPARE_UNIT(1<n);
        TEST_COMPARE_UNIT(1>n);
        TEST_COMPARE_UNIT(1<=n);
        TEST_COMPARE_UNIT(1>=n);
        TEST_COMPARE_UNIT(1==n);
        TEST_COMPARE_UNIT(1!=n);
        
        
        
        
        
        
        
        
        TEST_COMPARE_UNIT(1+arr[0]);
        TEST_COMPARE_UNIT(1-arr[0]);
        TEST_COMPARE_UNIT(1*arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;1/arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;1%arr[0]);
        
        TEST_COMPARE_UNIT(1&&arr[0]);
        TEST_COMPARE_UNIT(int x=1; x||arr[0]);
        
        TEST_COMPARE_UNIT(1<arr[0]);
        TEST_COMPARE_UNIT(1>arr[0]);
        TEST_COMPARE_UNIT(1<=arr[0]);
        TEST_COMPARE_UNIT(1>=arr[0]);
        TEST_COMPARE_UNIT(1==arr[0]);
        TEST_COMPARE_UNIT(1!=arr[0]);
        
        
        
        LLong l=1;
        TEST_COMPARE_UNIT(l+n);
        TEST_COMPARE_UNIT(l-n);
        TEST_COMPARE_UNIT(l*n);
        TEST_COMPARE_UNIT(n=1;l/n);
        TEST_COMPARE_UNIT(n=1;l%n);
        TEST_COMPARE_UNIT(l^n);
        TEST_COMPARE_UNIT(l&n);
        TEST_COMPARE_UNIT(l<<n);
        TEST_COMPARE_UNIT(l>>n);
        
        TEST_COMPARE_UNIT(l&&n);
        TEST_COMPARE_UNIT(l||n);
        
        TEST_COMPARE_UNIT(l<n);
        TEST_COMPARE_UNIT(l>n);
        TEST_COMPARE_UNIT(l<=n);
        TEST_COMPARE_UNIT(l>=n);
        TEST_COMPARE_UNIT(l==n);
        TEST_COMPARE_UNIT(l!=n);
        
        
        
        
        Float f=1;
        TEST_COMPARE_UNIT(f=arr[0]);
        TEST_COMPARE_UNIT(f+=arr[0]);
        TEST_COMPARE_UNIT(f-=arr[0]);
        TEST_COMPARE_UNIT(f*=arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;f/=arr[0]);
        
        TEST_COMPARE_UNIT(f-arr[0]);
        TEST_COMPARE_UNIT(f*arr[0]);
        TEST_COMPARE_UNIT(arr[0]=1;f/arr[0]);
        TEST_COMPARE_UNIT(~arr[0]);
        TEST_COMPARE_UNIT(!arr[0]);
        
        TEST_COMPARE_UNIT(f&&arr[0]);
        TEST_COMPARE_UNIT(f||arr[0]);
        
        TEST_COMPARE_UNIT(f<arr[0]);
        TEST_COMPARE_UNIT(f>arr[0]);
        TEST_COMPARE_UNIT(f<=arr[0]);
        TEST_COMPARE_UNIT(f>=arr[0]);
        TEST_COMPARE_UNIT(f==arr[0]);
        TEST_COMPARE_UNIT(f!=arr[0]);
    }
    
    void testArray() {
        IntArr arr(10);
        IntArr2D arr2(10, 10);
        IntArr3D arr3(10, 10, 10);
        GuardArray<int, 4> arr4(10, 10, 10, 10);
        
        TEST_COMPARE_UNIT(int x = arr[0]+arr[1]);
        TEST_COMPARE_UNIT(int x = arr[0]+arr[1]+arr[2]);
        TEST_COMPARE_UNIT(int x = arr[0]+arr[1]+arr[2]+arr[3]);
        TEST_COMPARE_UNIT(int x = arr[0]+arr[1]+arr[2]+arr[3]+arr[4]);
		
        TEST_COMPARE_UNIT(int x = arr2[0][0]+arr2[1][1]);
        TEST_COMPARE_UNIT(int x = arr2[0][0]+arr2[1][1]+arr2[2][2]);
        TEST_COMPARE_UNIT(int x = arr2[0][0]+arr2[1][1]+arr2[2][2]+arr2[3][3]);
        TEST_COMPARE_UNIT(int x = arr2[0][0]+arr2[1][1]+arr2[2][2]+arr2[3][3]+arr2[4][4]);
        
        TEST_COMPARE_UNIT(int x = arr3[0][0][0]+arr3[1][1][1]);
        TEST_COMPARE_UNIT(int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]);
        TEST_COMPARE_UNIT(int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]+arr3[3][3][3]);
        TEST_COMPARE_UNIT(int x = arr3[0][0][0]+arr3[1][1][1]+arr3[2][2][2]+arr3[3][3][3]+arr3[4][4][4]);
        
    }

};

#endif // TestUnit_hpp