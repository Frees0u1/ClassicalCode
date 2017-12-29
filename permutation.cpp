/*
* 全排列
*/

#include <iostream>
#include <vector>
using namespace std;

//不含重复元素的递归实现
class Solution{
public:
	vector<string> all_arrange(string s){
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
		}
		return;
	}

};


int main(int argc, char **argv){
	if(argc != 2){
		cout << "usage: " << argv[0] <<" <str>" << endl;
		return -1; 
	}
	string s(argv[1]);

	vector<string> svec;
	Solution sol;

	svec = sol.all_arrange(s);

	for(auto sx : svec){
		cout << sx << endl;
	}
	cout << svec.size() << "种排列" << endl;
	return 0;
}