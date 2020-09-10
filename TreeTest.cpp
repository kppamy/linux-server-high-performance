#include "TreeTest.h"
#include <iomanip>
#include <math.h>
#include "common.h"

void getLine(TreeNode *root, int depth, vector<int> &vals)
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

TreeNode *buildTree()
{
    int r;
    cin >> r;
    if (r == -1)
        return NULL;
    TreeNode *root = new TreeNode(r);
    root->left = buildTree();
    root->right = buildTree();
    return root;
}

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

// build tree from arr storage, for parent i, left:2i+1, right:2i+2
TreeNode *buildTree(const vector<int> &arr)
{
    int len = arr.size();
    if (len == 0)
        return NULL;
    TreeNode *root = new TreeNode();
    build(root, 0, arr, len);
    return root;
}

int Tree::maxDepth(const TreeNode *root)
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

bool validate(TreeNode *node, int parentv, bool isroot, bool isleft)
{
    if (!node)
        return true;

    if (!node->left && !node->right)
    {
        if (isleft && node->val >= parentv)
        {
            return false;
        }
        else if (!isleft && node->val <= parentv)
        {
            return false;
        }
        return true;
    }

    if (!node->left)
        return validate(node->right, node->val, false, false);
    if (!node->right)
        return validate(node->left, node->val, false, true);
    if ((node->val <= node->left->val) || node->val >= node->right->val)
        return false;
    if (isroot)
        return true;
    if (isleft && parentv <= node->right->val)
        return false;
    if (!isleft && parentv >= node->left->val)
        return false;
    return true;
}

void midOrder(TreeNode *node, vector<int> &sorted)
{
    if (!node)
        return;
    midOrder(node->left, sorted);
    sorted.push_back(node->val);
    midOrder(node->right, sorted);
}



// 98. Validate Binary Search Tree
// Runtime: 20 ms, faster than 67.28% of C++ online submissions for Validate Binary Search Tree.
    // Memory Usage: 22.1 MB, less than 5.47% of C++ online submissions for Validate Binary Search Tree.

bool isValidBST(TreeNode *root)
{
    // out mid order
    vector<int> sorted;
    midOrder(root, sorted);
    // check if sorted
    for (int i = 1; i < sorted.size(); i++)
    {
        if (sorted[i] <= sorted[i - 1])
            return false;
    }
    return true;
}


#include <list>
void midOrder(TreeNode *node, list<int> &sorted)
{
    if (!node)
        return;
    midOrder(node->left, sorted);
    sorted.push_back(node->val);
    midOrder(node->right, sorted);
}

// 98. Validate Binary Search Tree
// using list, no memory optimization observed
bool isValidBSTList(TreeNode *root)
{
    // out mid order
    list<int> sorted;
    midOrder(root, sorted);
    // check if sorted
    list<int>::iterator itr = sorted.begin(), fitr = sorted.begin();
    ++fitr;
    for (; itr != sorted.end(); ++itr)
    {
        if (fitr != sorted.end() && *itr >= *(fitr))
            return false;
        ++fitr;
    }
    return true;
}

void testIsValidBST()
{
    //     2
    //    / \
    //   1   3
    vector<int> tr1 = {2, 1, 3}; //true
    printVector(tr1);
    TreeNode *root = buildTree(tr1);
    prettyPrintTree(root, 2);
    cout << " is " << (isValidBST(root) ? "" : " not ") << "valid BST" << endl;
    cout << endl;

    //     5
    //    / \
    //   1   4
    //      / \
    //     3   6
    vector<int> tr2 = {5, 1, 4, -1, -1, 3, 6}; //false
    printVector(tr2);
    root = buildTree(tr2);
    prettyPrintTree(root, 3);
    cout << " is " << (isValidBST(root) ? "" : " not ") << "valid BST" << endl;
    cout << endl;

    //     10
    //    /   \   
    //    5   15
    //       /   \   
    //       6   20
    vector<int> tr3 = {10, 5, 15, -1, -1, 6, 20}; //false
    printVector(tr3);
    root = buildTree(tr3);
    prettyPrintTree(root, 3);
    cout << " is " << (isValidBST(root) ? "" : " not ") << "valid BST" << endl;
    cout << endl;

    vector<int> tr4 = {1, 1}; //false
    printVector(tr4);
    root = buildTree(tr4);
    prettyPrintTree(root, 2);
    cout << " is " << (isValidBST(root) ? "" : " not ") << "valid BST" << endl;
    cout << endl;
}

void BinaryTree::printBinaryTree(const TreeNode *root)
{
    int dept = maxDepth(root);
    vector<vector<string>> out(dept, vector<string>(pow(2, dept) - 1, " "));
    printNode(root, dept, out);
    cout << "Print  binary tree: " << endl;
    for (int i = 0; i < dept; i++)
    {
        for (string root : out[i])
            cout << root;
        cout << endl;
    }
}

void BinaryTree::printNode(const TreeNode *root, int dept, vector<vector<string>> &out)
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

const TreeNode *BinaryTree::nextValInMidOrder(const TreeNode *root, int val) const
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

void BinaryTree::midOrder(const TreeNode *root) const
{
    if (!root)
        return;
    midOrder(root->left);
    cout << " " << root->val << " ";
    midOrder(root->right);
}

template <typename T>
void BSTree<T>::insert(TreeNodeT<T> *&tree, T root)
{
    TreeNodeT<T> *parent = NULL;
    TreeNodeT<T> *temp = tree;

    //寻找插入点
    while (temp != NULL)
    {
        parent = temp;
        if (root > temp->val)
            temp = temp->right;
        else
            temp = temp->left;
    }
    // z->_parent = parent;
    TreeNodeT<T> *nd = new TreeNodeT<T>(root);
    if (parent == NULL) //如果树本来就是空树，则直接把z节点插入根节点
        tree = nd;
    else if (root > parent->val) //如果z的值大于其双亲，则z为其双亲的右孩
        parent->right = nd;
    else
        parent->left = nd;
}

template <typename T>
void BSTree<T>::del(TreeNodeT<T> *&root, T val)
{
    TreeNodeT<T> *parent = root;
    TreeNodeT<T> *tmp = root;
    TreeNodeT<T> *target = nullptr;
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
        TreeNode *next = nextValInMidOrder(target, target->val);
    }
    else
    {
        TreeNodeT<T> *root = nullptr;
        if (target->right)
        {
            root = target->right;
        }
        else if (target->left)
        {
            root = target->left;
        }
        if (val > parent->val)
            parent->right = root;
        else if (val < parent->val)
        {
            parent->left = root;
        }
        delete target;
    }
}

int square(unsigned int start, unsigned int end, unsigned int num)
{
    //recursion faster than iteration ??
    if (end - start == 1)
        return start;
    long long mid = (start + end) / 2;
    if (mid * mid < num)
        //  try x/2, 3/4 x
        return square(mid, end, num);
    else if (mid * mid == num)
        return mid;
    else
    {
        //try x/4,x/2
        return square(start, mid, num);
    }
}

// 69. Sqrt(x)
int mySqrt(int x)
{
    if (x == 1)
        return 1;
    else
        return square(0, x, x);
}

void testSqrt()
{
    cout << "mySqrt of INT64_MAX is " << mySqrt(INT64_MAX) << endl;
    cout << "mySqrt of 1 is " << mySqrt(1) << endl;
    cout << "mySqrt of 4 is " << mySqrt(4) << endl;
    cout << "mySqrt of 6 is " << mySqrt(6) << endl;
    cout << "mySqrt of 8 is " << mySqrt(8) << endl;
    cout << "mySqrt of 9 is " << mySqrt(9) << endl;
}

// 167. Two Sum II - Input array is sorted
// two sum
vector<int> twoSum(vector<int> &numbers, int target)
{
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
    // cout << "is BST ? " << tt.isValidBST(root) << endl;
    // BinaryTree bt;

    // bt.printBinaryTree(root);
    // int a = 0;
    // cout << ((a = 0) == 0) << endl;
    // BSTree<int> bst;
    // TreeNode *root;
    // // vector<int> nodes{7, 2, 4, 6, 3, 1, 5};
    // vector<int> nodes{4, 2, 1, 3, 6, 5, 7};
    // for (int val : nodes)
    // {
    //     bst.insert(root, val);
    // }
    // bst.printBinaryTree(root);
    // testSqrt();

    testIsValidBST();
    return 0;
}