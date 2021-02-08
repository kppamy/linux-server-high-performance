#include "TreeTest.h"
#include <iomanip>
#include <math.h>
#include <stack>
#include <queue>
#include <iostream>
#include <set>
using namespace std;

// 617. Merge Two Binary Trees
//  40 ms, faster than 81.67%
// 32.7 MB, less than 99.33%
TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
{
    if (!root1)
        return root2;
    if (!root2)
        return root1;
    queue<TreeNode *> bfs1;
    bfs1.push(root1);
    queue<TreeNode *> bfs2;
    bfs2.push(root2);
    while (!bfs1.empty())
    {
        TreeNode *tp1 = bfs1.front();
        bfs1.pop();
        TreeNode *tp2 = bfs2.front();
        bfs2.pop();
        if (tp1 == tp2)
            continue;
        tp1->val += tp2->val;
        if (tp1->left && tp2->left)
        {
            bfs1.push(tp1->left);
            bfs2.push(tp2->left);
        }
        else
        {
            tp1->left = tp1->left ? tp1->left : tp2->left;
            if (tp1->left)
            {

                bfs1.push(tp1->left);
                bfs2.push(tp1->left);
            }
        }

        if (tp1->right && tp2->right)
        {
            bfs1.push(tp1->right);
            bfs2.push(tp2->right);
        }
        else
        {
            tp1->right = tp1->right ? tp1->right : tp2->right;
            if (tp1->right)
            {
                bfs1.push(tp1->right);
                bfs2.push(tp1->right);
            }
        }
    }

    return root1;
}

// 1022. Sum of Root To Leaf Binary Numbers
//  4 ms, faster than 91.33%
//  9.6 MB, less than 100.00%
int sumRootToLeaf(TreeNode *root)
{
    stack<TreeNode *> sta;
    sta.push(root);
    int ans = 0;
    set<TreeNode *> nleaf;
    while (!sta.empty())
    {
        TreeNode *tp = sta.top();
        if (!tp->left && !tp->right)
        {
            if (nleaf.find(tp) == nleaf.end())
                ans += tp->val;
            sta.pop();
        }
        else
        {
            if (tp->left)
            {
                tp->left->val = (tp->val << 1) + tp->left->val;
                nleaf.insert(tp);
                sta.push(tp->left);
                tp->left = nullptr;
            }
            if (tp->right)
            {
                tp->right->val = (tp->val << 1) + tp->right->val;
                nleaf.insert(tp);
                sta.push(tp->right);
                tp->right = nullptr;
            }
        }
    }
    return ans;
}

void testsumRootToLeaf()
{
    my2arr cases = {
        {1, 0, 1, 0, 1, 0, 1}};

    for (auto &&test : cases)
    {
        printVector(test);
        TreeNode *root = buildTree(test);
        prettyPrintTree(root, maxDepth(root));
        cout << "sumRootToLeaf: " << endl;
        auto &&res = sumRootToLeaf(root);
        print(res);
        cout << endl;
    }
}

// 938. Range Sum of BST
// 96 ms, faster than 99.90%
// 54.6 MB, less than 99.23%
int rangeSumBST(TreeNode *root, int low, int high)
{
    vector<int> mid;
    stack<TreeNode *> sta;
    sta.push(root);
    while (!sta.empty())
    {
        TreeNode *tp = sta.top();
        sta.pop();
        if (!tp->right && !tp->left)
        {
            mid.push_back(tp->val);
        }
        else
        {
            if (tp->right)
            {
                sta.push(tp->right);
                tp->right = nullptr;
            }
            sta.push(tp);
            if (tp->left)
            {
                sta.push(tp->left);
                tp->left = nullptr;
            }
        }
    }
    int i = 0, len = mid.size(), j = len - 1;
    while (i < len)
    {
        if (mid[i] < low)
            i++;
        else
            break;
    }
    while (j > 0)
    {
        if (mid[j] > high)
            j--;
        else
            break;
    }

    int ans = 0;
    for (; i <= j; i++)
    {
        ans += mid[i];
    }
    return ans;
}

void testrangeSumBST()
{
    vector<int> ta;
    int low, high;
    TreeNode *root;

    low = 7, high = 15;
    ta = {10, 5, 15, 3, 7, 13, 18, 1, -1, 6};
    root = buildTree(ta);
    prettyPrintTree(root, maxDepth(root));
    cout << "rangeSumBST: " << low << "..." << high << " " << rangeSumBST(root, low, high) << endl;

    low = 6, high = 10;
    ta = {10, 5, 15, 3, 7, -1, 18};
    root = buildTree(ta);
    prettyPrintTree(root, maxDepth(root));
    cout << "rangeSumBST: " << low << "..." << high << " " << rangeSumBST(root, low, high) << endl;
}

// 437. Path Sum III
int pathSumIII(TreeNode *root, int sum)
{
    return 0;
}

// 113. Path Sum II
// 12 ms, faster than 72.81%
// 12.4 MB, less than 99.77%
vector<vector<int>> pathSum(TreeNode *root, int targetSum)
{
    if (!root)
        return {};
    stack<TreeNode *> sta;
    sta.push(root);
    map<TreeNode *, bool> isLeaf;
    vector<vector<int>> ans;
    auto getPath = [](stack<TreeNode *> sta) {
        int sz = sta.size();
        int len = sz;
        vector<int> path(sz, INT_MAX);
        while (!sta.empty())
        {
            TreeNode *tp = sta.top();
            path[sz - 1] = tp->val;
            sz--;
            sta.pop();
        }
        for (int i = len - 1; i > 0; --i)
        {
            path[i] -= path[i - 1];
        }
        return path;
    };
    while (!sta.empty())
    {
        TreeNode *tp = sta.top();
        if (!tp->left && !tp->right)
        {
            if (isLeaf.find(tp) == isLeaf.end() && tp->val == targetSum)
            {
                vector<int> path = getPath(sta);
                ans.push_back(path);
            }
            sta.pop();
            continue;
        }
        isLeaf[tp] = false;
        if (tp->left)
        {
            tp->left->val += tp->val;
            sta.push(tp->left);
            tp->left = nullptr;
        }
        else
        {
            tp->right->val += tp->val;
            sta.push(tp->right);
            tp->right = nullptr;
        }
    }
    return ans;
}

void testPathSum()
{
    vector<int> tarr = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1};
    TreeNode *root = buildTree(tarr);
    prettyPrintTree(root, maxDepth(root));
    int targetsum = 22;
    my2arr paths = pathSum(root, targetsum);
    cout << "paths has sum: " << targetsum << endl;
    print(paths);

    tarr = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1};
    root = buildTree(tarr);
    prettyPrintTree(root, maxDepth(root));
    targetsum = 27;
    paths = pathSum(root, targetsum);
    cout << "paths has sum: " << targetsum << endl;
    print(paths);
}

// 112. Path Sum
// 8 ms, faster than 96.15%
// 12.5 MB, less than 99.70%
bool hasPathSum(TreeNode *root, int targetSum)
{
    if (!root)
        return false;
    stack<TreeNode *> sta;
    sta.push(root);
    map<TreeNode *, bool> isLeaf;
    while (!sta.empty())
    {
        TreeNode *tp = sta.top();
        if (!tp->left && !tp->right)
        {
            if (isLeaf.find(tp) == isLeaf.end() && tp->val == targetSum)
                return true;
            sta.pop();
            continue;
        }
        isLeaf[tp] = false;
        if (tp->left)
        {
            tp->left->val += tp->val;
            sta.push(tp->left);
            tp->left = nullptr;
        }
        else
        {
            tp->right->val += tp->val;
            sta.push(tp->right);
            tp->right = nullptr;
        }
    }
    return false;
}

void testhasPathSum()
{
    vector<int> tarr = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1};
    TreeNode *root = buildTree(tarr);
    prettyPrintTree(root, maxDepth(root));
    int targetsum = 22;
    cout << " tree has path sum : " << targetsum << "  " << hasPathSum(root, targetsum) << endl;

    tarr = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1};
    root = buildTree(tarr);
    prettyPrintTree(root, maxDepth(root));
    targetsum = 17;
    cout << " tree has path sum : " << targetsum << "  " << hasPathSum(root, targetsum) << endl;

    tarr = {5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1};
    root = buildTree(tarr);
    prettyPrintTree(root, maxDepth(root));
    targetsum = 20;
    cout << " tree has path sum : " << targetsum << "  " << hasPathSum(root, targetsum) << endl;

    tarr = {1, 2, 3};
    root = buildTree(tarr);
    prettyPrintTree(root, maxDepth(root));
    targetsum = 5;
    cout << " tree has path sum : " << targetsum << "  " << hasPathSum(root, targetsum) << endl;

    tarr = {1, 2};
    root = buildTree(tarr);
    prettyPrintTree(root, maxDepth(root));
    targetsum = 0;
    cout << " tree has path sum : " << targetsum << "  " << hasPathSum(root, targetsum) << endl;
    ;
}

int height(TreeNode *root, int &ans)
{
    if (!root)
        return 0;
    int left = height(root->left, ans);
    int right = height(root->right, ans);
    ans = max(ans, left + right);
    return max(left, right) + 1;
}

// 543. Diameter of Binary Tree
//  8 ms, faster than 86.03%
// 20.2 MB, less than 91.34%
int diameterOfBinaryTree(TreeNode *root)
{
    if (!root)
        return 0;
    int ans = 0;
    height(root, ans);
    return ans;
}

// 100. Same Tree
//  4 ms, faster than 48.02%
// 8.9 MB, less than 100.00%
bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (!p && !q)
        return true;
    if (!p || !q)
        return false;
    queue<TreeNode *> psta;
    psta.push(p);
    queue<TreeNode *> qsta;
    qsta.push(q);
    while (!psta.empty() && !qsta.empty())
    {
        TreeNode *ptop = psta.front();
        psta.pop();
        TreeNode *qtop = qsta.front();
        qsta.pop();
        if (ptop->val != qtop->val)
            return false;
        if (ptop->left != nullptr && qtop->left != nullptr)
        {
            psta.push(ptop->left);
            ptop->left = nullptr;
            qsta.push(qtop->left);
            qtop->left = nullptr;
        }
        else if (ptop->left || qtop->left)
        {
            return false;
        }
        if (ptop->right != nullptr && qtop->right != nullptr)
        {
            psta.push(ptop->right);
            ptop->right = nullptr;
            qsta.push(qtop->right);
            qtop->right = nullptr;
        }
        else if (ptop->right || qtop->right)
        {
            return false;
        }
    }
    return psta.empty() && qsta.empty();
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

// 111. Minimum Depth of Binary Tree
// Runtime: 20 ms, faster than 41.10% of C++ online submissions for Minimum Depth of Binary Tree.
// Memory Usage: 20.1 MB, less than 53.37% of C++ online submissions for Minimum Depth of Binary Tree
int minDepth(TreeNode *root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    int left = INT_MAX;
    if (root->left)
        left = minDepth(root->left);
    int right = INT_MAX;
    if (root->right)
        right = minDepth(root->right);
    return (min(left, right) + 1);
}

int maxDifference(TreeNode *root)
{
    if (!root)
        return 0;
    int left = 0;
    if (root->left)
        left = maxDifference(root->left);
    int right = 0;
    if (root->right)
        right = maxDifference(root->right);
    if (left == -1 || right == -1)
        return -1;
    if (abs(left - right) > 1)
        return -1;
    return (max(left, right) + 1);
}

// 110. Balanced Binary Tree
// Runtime: 20 ms, faster than 65.17% of C++ online submissions for Balanced Binary Tree.
// Memory Usage: 21.5 MB, less than 87.45% of C++ online submissions for Balanced Binary Tree.
bool isBalanced(TreeNode *root)
{
    if (maxDifference(root) == -1)
        return false;
    return true;
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
    return nullptr;
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
        // TreeNode *next = nextValInMidOrder(target, target->val);
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

// 167. Two Sum II - Input array is sorted
// two sum
vector<int> twoSum(vector<int> &numbers, int target)
{
    return {};
}

#include <stack>
// 145. Binary Tree Postorder Traversal
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Binary Tree Postorder Traversal.
// Memory Usage: 8.5 MB, less than 69.18% of C++ online submissions for Binary Tree Postorder Traversal.
vector<int> postorderTraversal(TreeNode *root)
{
    if (!root)
        return {};
    stack<TreeNode *> nodes;
    nodes.push(root);
    vector<int> post;
    TreeNode *tmp = root;
    stack<TreeNode *> parents;
    while (true)
    {
        if (!parents.empty() && tmp == parents.top())
        {
            nodes.pop();
            post.push_back(tmp->val);
            parents.pop();
        }
        else
        {
            if (tmp->right)
                nodes.push(tmp->right);
            if (tmp->left)
                nodes.push(tmp->left);
            if (!tmp->left && !tmp->right)
            {
                nodes.pop();
                post.push_back(tmp->val);
            }
            else
            {
                parents.push(tmp);
            }
        }
        if (nodes.empty())
        {
            break;
        }
        tmp = nodes.top();
    }
    return post;
}

#include <queue>
// 101. Symmetric Tree
// Runtime: 4 ms, faster than 92.07% of C++ online submissions for Symmetric Tree.
// Memory Usage: 18.5 MB, less than 5.00% of C++ online submissions for Symmetric Tree.
bool isSymmetric(TreeNode *root)
{
    queue<TreeNode *> nodes;
    stack<int> line;
    nodes.push(root);
    auto getval = [&](TreeNode *nd) {
        return (nd ? nd->val : INT_MAX);
    };

    auto deline = [&](TreeNode *nd) {
        if (line.empty())
            return true;
        if (getval(nd) != line.top())
            return false;
        else
            line.pop();
        return true;
    };
    while (!nodes.empty())
    {
        queue<TreeNode *> next;
        int sz = nodes.size();
        int count = 0;
        while (!nodes.empty())
        {
            TreeNode *ft = nodes.front();
            if (count < sz / 2)
            {
                line.push(getval(ft));
            }
            else
            {
                if (!deline(ft))
                    return false;
            }
            if (ft)
            {
                next.push(ft->left);
                next.push(ft->right);
            }

            count++;
            nodes.pop();
        }
        if (!line.empty())
        {
            return false;
        }
        nodes = next;
    }
    return true;
}

template <typename f, typename u>
void testTree(f fuc, string name, u print)
{
    my2arr cases = {
        {1, 2, 3, 4},
        {1, 2, 3, -1, 4},
        {1, -1, 2},
        {},
        {1},
        {1, 1},
        {1, 2},
        {2, 1, 3},
        {3, 1, 2},
        {1, -1, 2, 3},
        {1, 2, -1, -1, 3},
        {5, 1, 4, -1, -1, 3, 6},
        {10, 5, 15, -1, -1, 6, 20},
        {3, 9, 20, -1, -1, 15, 7},
        {1, 2, 2, 3, 3, -1, -1, 4, 4},
        {10, 5, 15, -1, -1, 6, 20},
        {2, 3, 3, 4, 5, 5, 4, -1, -1, 8, 9, -1, -1, 9, 8},
        {1, 2, 2, 3, -1, -1, 3, 4, -1, -1, 4},
        {1, 2, 2, 3, 4, 4, 3},
        {1, 2, 2, -1, 3, -1, 3},
    };

    for (auto &&test : cases)
    {
        printVector(test);
        TreeNode *root = buildTree(test);
        prettyPrintTree(root, maxDepth(root));
        cout << name + ": " << endl;
        auto &&res = fuc(root);
        print(res);
        cout << endl;
    }
}

template <typename f>
void testTree(f fuc, string name)
{
    my2arr cases = {
        {4, -7, -3, -1, -1, -9, -3, 9, -7, -4, -1, 6, -1, -6, -6, -1, -1, 0, 6, 5, -1, 9, -1, -1, -1, -4, -1, -1, -1, -2},
        {1, 2, 3, 4},
        {1, 2, 3, -1, 4},
        {1, -1, 2},
        {},
        {1},
        {1, 1},
        {1, 2},
        {2, 1, 3},
        {3, 1, 2},
        {1, -1, 2, 3},
        {1, 2, -1, -1, 3},
        {5, 1, 4, -1, -1, 3, 6},
        {10, 5, 15, -1, -1, 6, 20},
        {3, 9, 20, -1, -1, 15, 7},
        {1, 2, 2, 3, 3, -1, -1, 4, 4},
        {10, 5, 15, -1, -1, 6, 20},
        {2, 3, 3, 4, 5, 5, 4, -1, -1, 8, 9, -1, -1, 9, 8},
        {1, 2, 2, 3, -1, -1, 3, 4, -1, -1, 4},
        {1, 2, 2, 3, 4, 4, 3},
        {1, 2, 2, -1, 3, -1, 3},
    };

    for (auto &&test : cases)
    {
        printVector(test);
        TreeNode *root = buildTree(test);
        prettyPrintTree(root, maxDepth(root));
        cout << name + ": " << endl;
        auto &&res = fuc(root);
        print(res);
        cout << endl;
    }
}

template <typename f, typename u>
void test2Tree(f fuc, string name, u print = nullptr)
{
    vector<my2arr> cases = {
        {{1, 2, 3}, {1, -1, 3}},
        {{}, {}},
        {{1, 2}, {1, -1, 2}},
        {{1, 2, 1}, {1, 1, 2}},
        {{1, 2, 3}, {1, 2, 3}}};
    for (auto &&test : cases)
    {
        cout << "====================new case====================" << endl;
        printVector(test);
        TreeNode *root = buildTree(test[0]);
        cout << "The first tree: " << endl;
        prettyPrintTree(root, maxDepth(root));
        cout << "The second tree: " << endl;
        TreeNode *root1 = buildTree(test[1]);
        prettyPrintTree(root1, maxDepth(root1));
        cout << name + ": " << endl;
        auto &&res = fuc(root, root1);
        print(res);
        cout << endl;
    }
}

// 107. Binary Tree Level Order Traversal II
// Runtime: 8 ms, faster than 50.37% of C++ online submissions for Binary Tree Level Order Traversal II.
// Memory Usage: 13.9 MB, less than 18.22% of C++ online submissions for Binary Tree Level Order Traversal II.
vector<vector<int>> levelOrderBottom(TreeNode *root)
{
    if (!root)
        return {};
    stack<vector<int>> data;
    queue<TreeNode *> qu;
    qu.push(root);
    data.push({root->val});
    while (!qu.empty())
    {
        vector<int> level;
        queue<TreeNode *> next;
        while (!qu.empty())
        {
            TreeNode *parent = qu.front();
            qu.pop();
            if (parent->left)
            {
                level.push_back(parent->left->val);
                next.push(parent->left);
            }
            if (parent->right)
            {
                level.push_back(parent->right->val);
                next.push(parent->right);
            }
        }
        if (!level.empty())
        {
            data.push(level);
            qu = next;
        }
    }

    vector<vector<int>> out;
    while (!data.empty())
    {
        out.push_back(data.top());
        data.pop();
    }
    return out;
}

// 606. Construct String from Binary Tree
// Runtime: 36 ms, faster than 55.54% of C++ online submissions for Construct String from Binary Tree.
// Memory Usage: 66.8 MB, less than 6.32% of C++ online submissions for Construct String from Binary Tree.
string tree2str(TreeNode *t)
{
    string out = "";
    if (!t)
        return out;
    out += to_string(t->val);
    string left = "(";
    left += tree2str(t->left);
    left += ')';
    string right = "(";
    right += tree2str(t->right);
    right += ')';
    if (right == "()")
    {
        if (left == "()")
            return out;
        else
            return out + left;
    }
    else
        return out + left + right;
}

// 94. Binary Tree Inorder Traversal
// 4 ms, faster than 50.41%
vector<int> inorderTraversal(TreeNode *root)
{
    if (!root)
        return {};
    stack<TreeNode *> sta;
    sta.push(root);
    vector<int> out;
    while (!sta.empty())
    {
        TreeNode *top = sta.top();
        if (!top->left && !top->right)
        {
            out.push_back(top->val);
            sta.pop();
        }
        else
        {
            if (top->left)
            {
                sta.push(top->left);
                top->left = nullptr;
            }
            else if (top->right)
            {
                out.push_back(top->val);
                sta.pop();
                sta.push(top->right);
            }
        }
    }
    return out;
}

int main(int argc, char const *argv[])
{
    // testTree(isValidBST,"isValidBST",printInt);
    // testTree(maxDepth,"maxDepth",printInt);
    // testTree(minDepth,"minDepth",printInt);
    // testTree(isBalanced,"isBalanced",printInt);
    // testTree(postorderTraversal, "postorderTraversal", printVector);
    // testTree(isSymmetric, "isSymmetric", printInt);
    // testTree(levelOrderBottom, "levelOrderBottom", print2Vector);
    // testTree(tree2str, "tree2str", [](string res) { cout << res << endl; });
    // testTree(inorderTraversal, "inorderTraversal");
    // test2Tree(isSameTree, "isSameTree", [](bool result) {
    //     cout << (result ? " true " : " false ") << endl;
    // });
    // testTree(diameterOfBinaryTree, "diameterOfBinaryTree");
    // testhasPathSum();
    // testPathSum();
    // testrangeSumBST();
    testsumRootToLeaf();
    return 0;
}