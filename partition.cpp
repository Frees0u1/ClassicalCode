#include <iostream>
#include <vector>
#include <stdlib.h>
#include <assert.h>
using namespace std;

//[lo, hi) : 构造轴点，轴点前的所有元素都不大于轴点值，反之都不小于轴点值
int partition(vector<int>&nums, int lo, int hi){ 
    assert(hi - lo >= 2); //partition给定的区间必须至少包含两个元素

    int p = lo + rand() % (hi - lo);
    swap(nums[lo], nums[p]);
    int mi = lo;
    for(int i = lo + 1; i < hi; ++i){
        if(nums[i] < nums[lo])
            swap(nums[++mi], nums[i]);
    }
    swap(nums[lo], nums[mi]);
    return mi; 
}

void quicksort(vector<int>&nums, int lo, int hi){
    //将nums[lo, hi)内的所有元素进行排序
    if(hi - lo < 2) return;

    int mi = partition(nums, lo, hi);
    quicksort(nums, lo, mi);
    quicksort(nums, mi + 1, hi);
    return;
}



int main(){
    srand(time(NULL));
    vector<int> tst;
    for(int i = 0; i < 1000; i++){
        tst.push_back(rand() % 1000);
    }


    for(auto x : tst) cout << x << " ";
    cout << endl;

    quicksort(tst, 0, tst.size());

    for(auto x : tst) cout << x << " ";
    cout << endl;


    return 0;
}