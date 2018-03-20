/*
* 二叉树的先序遍历 --- 非递归版与递归版
*/


#include <iostream>
#include <stack>
#include <vector>
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

// 注意注意 --- 前方高能!!!
// 下面是二叉树前中后序遍历的奇技淫巧!
// 非常有效,而且对前中后序遍历均有效,
// 即模拟递归栈的思路, 下面对三种中最难的后序遍历序列给出原生版本和精简版本

// 原生版本
class Solution1 {
    typedef struct Command{
        string cmd_; //go or print
        TreeNode* node_;
        Command(string cmd, TreeNode* node) : cmd_(cmd), node_(node) {}
    }Command;
    
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == nullptr) return res;        
        stack<Command> stk;
        stk.push(Command("go", root));
        while(!stk.empty()) {
            Command command = stk.top(); stk.pop();
            if(command.cmd_ == "print") res.push_back(command.node_->val);
            else { // cmd == go
                stk.push(Command("print", command.node_));
                if(command.node_->right) 
                    stk.push(Command("go", command.node_->right));
                if(command.node_->left) 
                    stk.push(Command("go", command.node_->left));
            }
        }
        return res;
    }
};

// 精简版本 -- 将Command精简为pair,并多存一个bool位
class Solution2 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> res;
        if(root == nullptr) return res;        
        stack<pair<bool, TreeNode*> > stk; //pair的第一位bool值表示是否需要往下访问，1为需要，0为不需要
        stk.push({1, root});
        
        while(!stk.empty()) {
            pair<bool, TreeNode*> p = stk.top(); stk.pop();
            TreeNode* cur = p.second;
            if(cur == nullptr) continue;  // 递归版本里，这个就是递归基
            else {
                if(p.first) { //需要先访问子树
                    stk.push({0, cur});
                    if(cur->right) stk.push({1, cur->right});
                    if(cur->left) stk.push({1, cur->left});
                }
                else
                    res.push_back(cur->val);
            }   
        }
        return res;  
    }
};





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
