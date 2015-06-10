#include "gt.h"
#include "manual.hpp"

const unsigned int N = 4;                       // 下面数组的长度
const unsigned int SellNum[N] = {11, 7, 3, 1};  // 最后一个数值必须是 1



// IntPtr can only construct from array and other IntPtr
void ShellSort(IntPtr arr, int length) {
    for(int n=0; n<N; n++) {
        int increase=SellNum[n];
        for(int i=0; i<increase; i++) {
            for(int j=i+increase; j<length; j+=increase) {
                for(int k=j; arr[k-increase]>arr[k]; k-=increase) {
                    int temp = arr[k];
                    arr[k] = arr[k-increase];
                    arr[k-increase] = temp;
                    if(k-2*increase < 0)break;
                }
            }
        }
    }
}

int main(void)
{
    TurnTrace(ON);
    int a[] = {3, 1, 3, 63, 11,2, 5,23, 51};
    ShellSort(a, 9);
    for(int i=0; i<9; i++) {
        printf("%d  ", a[i]);
    }
    return 0;
}
