#include <stddef.h>
#include <vector>
#include <iostream>
using namespace std;
template <typename T>
struct TreeNode
{
    T val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int val, TreeNode *l, TreeNode *r) : val(0), left(l), right(r) {}
};

class Tree
{
public:
    int maxDepth(const TreeNode<int> *node);
    bool validateBST(TreeNode<int> *root);
};

class BinaryTree : Tree
{
public:
    void printBinaryTree(const TreeNode<int> *root);
    void printNode(const TreeNode<int> *root, int dept, vector<vector<string>> &out);
    void preOrder(const TreeNode<int> *root) const;
    void midOrder(const TreeNode<int> *root) const;
    const TreeNode<int>* nextValInMidOrder(const TreeNode<int> *root, int val) const;
    void postOrder(const TreeNode<int> *root) const;
};

template <typename T>
class BSTree : public BinaryTree
{
public:
    void insert(TreeNode<T> *&tree, T val);
    int  find(T val);
    void del(TreeNode<T> *&root, T val);
};