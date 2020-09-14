#include "gt.h"
#include "manual.hpp"

using namespace gt;


void sort(IntArr arr, int length) {
    for(int i = 1; i < length; ++i) {
        for(int j = 1; j <= length-i; ++j) {
            if(arr[j-1] > arr[j]) {
                int swap = arr[j-1];
                arr[j-1] = arr[j];
                arr[j] = swap;
            }
        }
    }
}

int main(void)
{
    int a[] = {3, 5, 1, 11, 7};
    
    sort(a, 5);
    for(int i=0; i<5; ++i) {
        printf("%d  ", a[i]);
    }
    printf("\n");
    
    manual();
}
