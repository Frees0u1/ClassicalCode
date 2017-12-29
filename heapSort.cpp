/* 
*  批量建堆以及堆排序  Floyd算法 1964
*/
#include <vector>
#include <iostream>
using namespace std;

void percolateDown(vector<int>& nums, int n, int i){ //将nums[i]进行下滤 此时堆的边界为n
    int j;
    while(true){
        int lc = 2*i+1, rc = 2*i +2;
        j = i; //j为下一个该下滤的节点
        //以下两条if语句执行完毕后,j指向i/lc/rc三者中值最大者
        if(lc < n && nums[lc] > nums[j]) j = lc;
        if(rc < n && nums[rc] > nums[j]) j = rc;
        if(j == i) break; //无需下滤
        swap(nums[i], nums[j]);
        i = j;
    }
    return;
}


void buildHeap(vector<int>& nums){
    int n = nums.size();
    int lastInternal = (n - 2) >> 1; // 节点i的父节点为 (i-1)>>1, 最后一个内节点即为末节点的父亲
    for(int i = lastInternal; i >= 0; i--){
        percolateDown(nums, nums.size(), i); //对每一个节点进行下滤
    }
    return;
}

void heapSort(vector<int>& nums){
    buildHeap(nums); //初始建堆

    int hi = nums.size();
    while(hi > 1){
        swap(nums[0], nums[hi - 1]);
        percolateDown(nums, --hi, 0);
    }
    return;
}


int main(){
    vector<int> nums{16,4,10,14,7,9,3,2,8,1};
    heapSort(nums);

    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}