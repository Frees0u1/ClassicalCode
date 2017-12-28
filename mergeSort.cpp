#include <vector>
#include <iostream>
using namespace std;

void merge(vector<int>& nums, int lo, int mid, int hi){
    vector<int> B(nums.begin() + lo, nums.begin()  + mid);
    int i = 0, j = mid;
    int k = lo;
    while(i < B.size() && j < hi){
        if(B[i] < nums[j]) nums[k++] = B[i++];
        else nums[k++] = nums[j++];
    }
    while(i < B.size()) nums[k++] = B[i++];
    //else 后半部分还有,但是已经就地了,无需处理
    return;
}


void mergeSort(vector<int> &nums, int lo, int hi){
    if(hi < lo + 2) return;
    int mid = lo + ((hi - lo) >> 1);
    mergeSort(nums, lo, mid);
    mergeSort(nums, mid, hi);
    merge(nums, lo, mid, hi);
}


int main(){
    vector<int> nums{16,4,10,14,7,9,3,2,8,1};
    mergeSort(nums, 0, nums.size());

    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << " ";
    }
    cout << endl;

    return 0;
}