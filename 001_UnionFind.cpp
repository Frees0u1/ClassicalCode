#include <unordered_map>
#include <vector>
#include <assert.h>
#include <iostream>
using namespace std;

template<typename T>
class UnionFind{
public:
    UnionFind(vector<T> nodes) {
        for(T x : nodes) {
            mp.insert({x, x});
        }
    }

    T find(T x){
        assert(mp.find(x) != mp.end());

        if(mp[x] == x) {
            return x;
        }
        int f = find(mp[x]);
        mp[x] = f;

        return f;
    }

    void unite(T x, T y) {
        assert(mp.find(x) != mp.end());
        assert(mp.find(y) != mp.end());

        T f_x = find(x);
        T f_y = find(y);

        if(f_x != f_y) {
            mp[f_x] = f_y;
        }
    }

    bool isSame(T x, T y){
        assert(mp.find(x) != mp.end());
        assert(mp.find(y) != mp.end());

        return mp[x] == mp[y];
    }

private:
    unordered_map<T, T> mp;
};

int main(){
    vector<int> nums{1,2,3,4,5,6};
    UnionFind<int> uf(nums);

    uf.unite(1, 2); uf.unite(1, 3);
    uf.unite(4, 5); uf.unite(5, 6);

    for(int x : nums){
        cout << x << ": " << uf.find(x) << endl;
    }
}