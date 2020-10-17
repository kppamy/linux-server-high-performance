#include <stddef.h>
#include <vector>
#include <iostream>
#include "common.h"

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