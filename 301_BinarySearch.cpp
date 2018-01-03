#include <iostream>
#include <cstdio>
using namespace std;

/*===== 速记口诀 =====
*   lower小于, upper小等
*   return lo
*/

//二分查找版本一
//找到nums[lo, hi)大于等于key值的第一个元素位置
int lower_bound(int nums[], int lo, int hi, int key ){
    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        if(nums[mid] < key){ //中位数小于key值,key值在后半部分
            lo = mid + 1;
        }else{
            hi = mid;
        }
    }
    return lo;
}

//二分查找二
//找到严格大于key值的第一个元素
int upper_bound(int nums[], int lo, int hi, int key){
    while(lo < hi){
        int mid = lo + (hi - lo) / 2;
        if(nums[mid] <= key){
             lo = mid + 1;
        }
        else
            hi = mid;
    }
    return lo;
}


int main(int argc, char *argv[]){
    int nums[] = {1,1,2,2,4,4,4,5,5};
    int key = atoi(argv[1]);
    cout << "index of first >= key: " << lower_bound(nums, 0, 9, key) << endl;
    cout << "index of first > key: " << upper_bound(nums, 0, 9, key) << endl;
}