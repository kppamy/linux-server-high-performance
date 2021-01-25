#include <stddef.h>
#include <vector>
#include <iostream>
#include "../common.h"

using namespace std;
template <typename T=int>
struct TreeNodeT
{
    T val;
    TreeNodeT *left;
    TreeNodeT *right;
    TreeNodeT(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNodeT() : val(0), left(nullptr), right(nullptr) {}
    TreeNodeT(int val, TreeNodeT *l, TreeNodeT *r) : val(0), left(l), right(r) {}
};
//use TreeNodeT<> tn;



class Tree
{
public:
    int maxDepth(const TreeNode *node);
    bool validateBST(TreeNode *root);
};

class BinaryTree : Tree
{
public:
    void printBinaryTree(const TreeNode*root);
    void printNode(const TreeNode*root, int dept, vector<vector<string>> &out);
    void preOrder(const TreeNode*root) const;
    void midOrder(const TreeNode*root) const;
    const TreeNode* nextValInMidOrder(const TreeNode*root, int val) const;
    void postOrder(const TreeNode*root) const;
};

template <typename T>
class BSTree : public BinaryTree
{
public:
    void insert(TreeNodeT<T> *&tree, T val);
    int  find(T val);
    void del(TreeNodeT<T> *&root, T val);
};


void build(TreeNode *pare, int i, const vector<int> &arr, int len)
{
    pare->val = arr[i];
    int li = 2 * i + 1;
    if (li <= len - 1 && arr[li] != -1)
    {
        TreeNode *left = new TreeNode();
        pare->left = left;
        build(left, li, arr, len);
    }
    int ri = 2 * i + 2;
    if (ri <= len - 1 && arr[ri] != -1)
    {
        TreeNode *right = new TreeNode();
        pare->right = right;
        build(right, ri, arr, len);
    }
};


// build tree from arr storage, BFS storage
TreeNode *buildTree(const vector<int> &arr)
{
    int len = arr.size();
    if (len == 0)
        return NULL;
    TreeNode *root = new TreeNode();
    build(root, 0, arr, len);
    return root;
}

// 104. Maximum Depth of Binary Tree
// Runtime: 16 ms, faster than 44.65% of C++ online submissions for Maximum Depth of Binary Tree.
// Memory Usage: 19.5 MB, less than 6.95% of C++ online submissions for Maximum Depth of Binary Tree.
int maxDepth(TreeNode *root)
{
    if (!root)
        return 0;
    int left = 0;
    if (root->left)
        left = maxDepth(root->left);
    int right = 0;
    if (root->right)
        right = maxDepth(root->right);
    return (max(left, right) + 1);
}


void getLine(TreeNode *root, int depth, std::vector<int> &vals)
{
    if (depth <= 0 && root != nullptr)
    {
        vals.push_back(root->val);
        return;
    }
    if (root->left != nullptr)
        getLine(root->left, depth - 1, vals);
    else if (depth - 1 <= 0)
        vals.push_back(-2);
    if (root->right != nullptr)
        getLine(root->right, depth - 1, vals);
    else if (depth - 1 <= 0)
        vals.push_back(-2);
}

#include<iomanip>
void printRow(TreeNode *p, const int height, int depth)
{
    vector<int> vec;
    getLine(p, depth, vec);
    cout << setw((height - depth) * 2); // scale setw with depth
    bool toggle = true;                 // start with left
    if (vec.size() > 1)
    {
        for (int v : vec)
        {
            if (v != -2)
            {
                if (toggle)
                    cout << "/"
                         << "   ";
                else
                    cout << "\\"
                         << "   ";
            }
            else
            {
                cout << "   ";
            }
            toggle = !toggle;
        }
        cout << endl;
        cout << setw((height - depth) * 2);
    }
    for (int v : vec)
    {
        if (v != -2)
        {
            cout << v << "   ";
        }
        else
            cout << "   ";
    }
    cout << endl;
}

// create a pretty vertical tree
// after this function, the p changed
void prettyPrintTree(TreeNode *p, int hgt)
{
    //   int height = getHeight(p) * 2;
    int height = hgt;
    for (int i = 0; i < height; i++)
    {
        printRow(p, height, i);
    }
}