/*
* 程序功能: 将字符串按照某一特定字符分裂成子串数组,常见应用: 将一段话按照空格分裂成单词数组
* 接口: (string , char ) -> vector
* Author: free50u1 Date: 2018/1/20
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> StrSplit(string& text, char sep = ' '){ //默认为空格
    vector<string> segs;
    int lo = 0, hi = 0; //每一个[lo, hi)区间组成一个seg

    text.push_back(sep); //在最后添一个哨兵
    
    string seg;
    while( hi < text.size() ){
        if(text[hi] == sep){ //发现一个新的分隔符
            seg = text.substr(lo, hi - lo);
            segs.push_back(seg);
            lo = hi + 1;
        }
        ++hi;
    }

    text.pop_back(); //去掉哨兵,不更改原句.
    return segs;
} 


int main(){
    string s = "Harry Potter is The Boy Who Lived, singled out by Lord Voldemort at birth to be his greatest rival, and our hero.";
    vector<string> segs = std::move(StrSplit(s));
    for(auto seg : segs){
        cout << seg << endl;
    }

    return 0;
}
