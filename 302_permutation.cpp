/*
* 全排列
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//不含重复元素的递归实现
class Solution1{
public:
	vector<string> permutation(string s){
		vector<string> result;
		helper(result, s, 0);
		return result;
	}
	void helper(vector<string> &result, string &s, int idx){
		//将字符串S[idx, n)部分进行全排序, 并将结果保存在result 中
		int n = s.length();
		if(idx == n) return;
		if(idx == n - 1){
			result.push_back(s);
			return;
		}
		for(int k = idx; k < n; k++){ //遍历范围内的所有值作为首字符的排列方式
			swap(s[k], s[idx]);
			helper(result, s, idx + 1);
			swap(s[k], s[idx]);
		}
		return;
	}

};


//含重复元素的递归实现, 仅仅是排序后多加一行判定,但要注意此时不传引用,要传值,因此不用回溯
class Solution2 {
public:
    void recursion(string s, int i, vector<string > &res) {
		int j = s.size();
        if (i == j-1) {
            res.push_back(s);
            return;
        }
        for (int k = i; k < j; k++) {
            if (i != k && s[i] == s[k]) continue;
            swap(s[i], s[k]);
            recursion(s, i+1, res);
        }
    }
    vector<string > permuteUnique(string &s) {
        sort(s.begin(), s.end());
        vector<string >res;
        recursion(s, 0, res);
        return res;
    }
};


int main(int argc, char **argv){
	if(argc != 2){
		cout << "usage: " << argv[0] <<" <str>" << endl;
		return -1; 
	}
	string s(argv[1]);

	vector<string> svec;
	Solution2 sol;

	svec = sol.permuteUnique(s);

	for(auto sx : svec){
		cout << sx << endl;
	}
	cout << svec.size() << "种排列" << endl;
	return 0;
}