#include "gt.h"
#include "manual.hpp"
#include "TestUnit.hpp"

void sort(IntArr arr, int length) {
    for(int i = 1; i < length; i++) {
        for(int j = i; j < length; j++) {
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
    manual();
    TestUnit t;
    t.startTest();
	
    int a[] = {3, 1, 3, 63, 11};
    sort(a, 5);
    for(int i=0; i<5; i++) {
        printf("%d  ", a[i]);
	}
    
    return 0;
}
