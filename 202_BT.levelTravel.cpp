/*
* 二叉树的层次遍历
*/
#include <iostream>
#include <queue>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left, *right;
    TreeNode(int v = 0) : val(v), left(NULL), right(NULL){}
};

void visit(TreeNode* p){ //访问函数,这里简单只设为是打印
    cout << p->val << " ";
}

void levelTravel(TreeNode *root){
    if(root == NULL) return;
    queue<TreeNode*> Q;
    Q.push(root);

    while(!Q.empty()){
        TreeNode *cur = Q.front();
        Q.pop();
        visit(cur);
        if(cur->left) Q.push(cur->left);
        if(cur->right) Q.push(cur->right);
    }
    return;
}


int main(){
    TreeNode n0(0), n1(1), n2(2), n3(3), n4(4),n5(5), n6(6), n7(7),n8(8), n9(9),n10(10);
    n0.left = &n1; n0.right = &n2;
    n1.left = &n3; n1.right = &n4;
    n2.left = &n5; n2.right = &n6;
    n4.left = &n7; n4.right = &n8;
    n5.left = &n9; n5.right = &n10;

    levelTravel(&n0);
    cout << endl;
}
