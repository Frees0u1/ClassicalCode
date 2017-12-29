/*
* 二叉树的先序遍历 --- 非递归版与递归版
*/


#include <iostream>
#include <stack>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left, *right;
    TreeNode(int v = 0) : val(v), left(NULL), right(NULL){}
};

void visit(TreeNode* p){ //访问函数,这里简单只设为是打印
    cout << p->val << " ";
}

/*******************************************
*               前序遍历
********************************************/
void BT_PreOrder(TreeNode* root){
    if(root == NULL) return;
    stack<TreeNode*> S;
    S.push(root);

    while(!S.empty()){
        TreeNode* cur = S.top();
        S.pop();
        visit(cur); //访问
        if(cur->right) S.push(cur->right);
        if(cur->left) S.push(cur->left);
    }
    return;
}


/*******************************************
*               中序遍历
********************************************/
void BT_InOrder(TreeNode *root){
    stack<TreeNode* > S;
    TreeNode *cur = root;
    while(true){
        while(cur){
            S.push(cur); cur = cur->left;
        }
        if(S.empty()) break;

        cur = S.top();
        visit(cur);
        S.pop();
        cur = cur->right;
    }
}

/*******************************************
*               后序遍历
********************************************/

void findFirst(stack<TreeNode*> &S); //找到以栈顶节点为根的子树其第一个应该输出的节点   
 //即按照自己-右节点-左节点的顺序压栈

void BT_PostOrder(TreeNode* root){
    if(root == NULL) return;
    
    stack<TreeNode *> S;
    TreeNode *cur = root;
    S.push(root);
    while(!S.empty()){
        if(S.top()->left != cur && S.top()->right != cur){ //当前节点不是栈顶节点的子节点
        //这里的当前节点指的是上一个输出的节点
        //这种关系表示上一个输出节点是左节点,而栈顶是右节点,因为右节点可能有未输出的子树,因此需要进行FindFirst的操作
            findFirst(S); 
        }
        visit(cur = S.top());
        S.pop();
    }
    
}
void findFirst(stack<TreeNode*> &S) {
    //找到以栈顶节点为根的子树其第一个应该输出的节点
    while (TreeNode* x = S.top()) {
        if (x->left) { //一句话总结,有左先右再左,无左只压右
            if (x->right) S.push(x->right);
            S.push(x->left);
        }
        else {
            S.push(x->right);
        }
    }
    S.pop(); //删掉栈顶的空指针
}


/*
0
|
+ 2 ----- 6
|   +---- 5 ---- 10
|         + ---- 9
+ 1 ----- 4 ---- 8
          + ---- 7
    +---- 3       
*/

int main(){
    TreeNode n0(0), n1(1), n2(2), n3(3), n4(4),n5(5), n6(6), n7(7),n8(8), n9(9),n10(10);
    n0.left = &n1; n0.right = &n2;
    n1.left = &n3; n1.right = &n4;
    n2.left = &n5; n2.right = &n6;
    n4.left = &n7; n4.right = &n8;
    n5.left = &n9; n5.right = &n10;

    BT_PreOrder(&n0);
    cout << endl;

    BT_InOrder(&n0);
    cout << endl;

    BT_PostOrder(&n0);
    cout << endl;
}
