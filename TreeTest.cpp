#include "TreeTest.h"
#include "BinaryTree.h"
#include <iomanip>
#include <math.h>

TreeNode<int> *buildTree()
{
    int node;
    cin >> node;
    if (node == -1)
        return NULL;
    TreeNode<int> *root = new TreeNode<int>(node);
    root->left = buildTree();
    root->right = buildTree();
    return root;
}

int Tree::maxDepth(const TreeNode<int> *root)
{
    if (root->left == NULL && root->right == NULL)
        return 1;
    else if (root->left == NULL)
        return (maxDepth(root->right) + 1);
    else if (root->right == NULL)
        return (maxDepth(root->left) + 1);
    else
    {
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return (left >= right ? (left + 1) : (right + 1));
    }
}

bool Tree::validateBST(TreeNode<int> *node)
{
    if (node == NULL)
        return true;
    if ((node->left != NULL) && node->val < node->left->val)
    {
        return false;
    }
    else if (node->right != NULL && node->val > node->right->val)
    {
        return false;
    }
    if (!validateBST(node->left))
        return false;
    if (!validateBST(node->right))
        return false;
    return true;
}

void getLine(const TreeNode<int> *root, int depth, vector<int> &vals)
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

void printRow(const TreeNode<int> *p, const int height, int depth)
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
void prettyPrintTree(TreeNode<int> *p, int hgt)
{
    //   int height = getHeight(p) * 2;
    int height = hgt;
    for (int i = 0; i < height; i++)
    {
        printRow(p, height, i);
    }
}

void BinaryTree::printBinaryTree(const TreeNode<int> *root)
{
    int dept = maxDepth(root);
    vector<vector<string>> out(dept, vector<string>(pow(2, dept) - 1, " "));
    printNode(root, dept, out);
    cout << "Print  binary tree: " << endl;
    for (int i = 0; i < dept; i++)
    {
        for (string node : out[i])
            cout << node;
        cout << endl;
    }
}

void BinaryTree::printNode(const TreeNode<int> *root, int dept, vector<vector<string>> &out)
{
    int rp = static_cast<int>(pow(2, dept - 1)) - 1;
    int distance = static_cast<int>(pow(2, dept)) - 1;
    static int cur = 0;
    static bool left = true;
    if (left)
    {
        out[cur][rp] = to_string(root->val);
    }
    else
    {
        out[cur][rp + distance + 1] = to_string(root->val);
    }
    if (root->left != nullptr || root->right != nullptr)
    {
        cur++;
    }
    if (root->left != nullptr)
    {
        left = true;
        printNode(root->left, dept - 1, out);
    }

    if (root->right != nullptr)
    {
        left = false;
        printNode(root->right, dept - 1, out);
    }
}

const TreeNode<int> *BinaryTree::nextValInMidOrder(const TreeNode<int> *root, int val) const
{
    static bool begin = false;
    if (root)
    {
        midOrder(root->left);
        if (begin)
        {
            return root;
        }
        cout << " " << root->val << " ";
        if (root->val == val)
        {
            begin = true;
            cout << " find " << val << " at " << root << endl;
        }

        midOrder(root->right);
    }
}

void BinaryTree::midOrder(const TreeNode<int> *root) const
{
    if (!root)
        return;
    midOrder(root->left);
    cout << " " << root->val << " ";
    midOrder(root->right);
}

template <typename T>
void BSTree<T>::insert(TreeNode<T> *&tree, T node)
{
    TreeNode<T> *parent = NULL;
    TreeNode<T> *temp = tree;

    //寻找插入点
    while (temp != NULL)
    {
        parent = temp;
        if (node > temp->val)
            temp = temp->right;
        else
            temp = temp->left;
    }
    // z->_parent = parent;
    TreeNode<T> *nd = new TreeNode<T>(node);
    if (parent == NULL) //如果树本来就是空树，则直接把z节点插入根节点
        tree = nd;
    else if (node > parent->val) //如果z的值大于其双亲，则z为其双亲的右孩
        parent->right = nd;
    else
        parent->left = nd;
}

template <typename T>
void BSTree<T>::del(TreeNode<T> *&root, T val)
{
    TreeNode<T> *parent = root;
    TreeNode<T> *tmp = root;
    TreeNode<T> *target = nullptr;
    while (tmp)
    {
        parent = tmp;
        if (val > tmp->val)
        {
            parent = tmp->right;
        }
        else if (val < tmp->val)
        {
            parent = tmp->left;
        }
        else if (val == tmp->val)
        {
            target = tmp;
        }
    }

    if (target == nullptr)
    {
        return;
    }
    if (!target->left && !target->right)
    {
        delete target;
    }
    else if (target->left && target->right)
    {

        //   next val in midOder
        TreeNode<int>* next=nextValInMidOrder(target,target->val);
    }
    else
    {
        TreeNode<T> *node = nullptr;
        if (target->right)
        {
            node = target->right;
        }
        else if (target->left)
        {
            node = target->left;
        }
        if (val > parent->val)
            parent->right = node;
        else if (val < parent->val)
        {
            parent->left = node;
        }
        delete target;
    }
}

int main(int argc, char const *argv[])
{
    cout << "please input the tree nodes" << endl;
    // right tree: 1 -1 2 -1 3 -1 4 -1 5 6 -1 7 -1 -1 -1
    // left tree: 1 -1 2 -1 3 -1 4 -1 5 6 -1 7 -1 -1 -1
    // 3 1 -1 -1 5 4 -1 -1 1 -1 -1
    // 1 2 -1 -1 -1
    // 1 2 -1 4 -1 -1 3 -1 -1
    // TreeNode *root = buildTree();
    // Tree tt;
    // int dpt = tt.maxDepth(root);
    // prettyPrintTree(root, dpt);
    // cout << "depth of the tree: " << dpt << endl;
    // cout << "is BST ? " << tt.validateBST(root) << endl;
    // BinaryTree bt;

    // bt.printBinaryTree(root);
    int a=0;
    cout<<((a=0)==0)<<endl;
    BSTree<int> bst;
    TreeNode<int> *root;
    // vector<int> nodes{7, 2, 4, 6, 3, 1, 5};
    vector<int> nodes{4, 2, 1, 3, 6, 5, 7};
    for (int val : nodes)
    {
        bst.insert(root, val);
    }
    bst.printBinaryTree(root);
    return 0;
}