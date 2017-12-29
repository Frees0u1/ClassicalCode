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
		helper(result, s, 0, s.size());
		return result;
	}
	void helper(vector<string> &result, string &s, int i, int j){
		//将字符串S[i, j)部分进行全排序, 并将结果保存在result 中
		if(i == j) return;
		if(i == j - 1){
			result.push_back(s);
			return;
		}
		for(int k = i; k < j; k++){
			swap(s[k], s[i]);
			helper(result, s, i + 1, j);
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