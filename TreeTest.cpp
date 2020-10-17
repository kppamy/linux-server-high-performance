#include "TreeTest.h"
#include <iomanip>
#include <math.h>

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

// 167. Two Sum II - Input array is sorted
// two sum
vector<int> twoSum(vector<int> &numbers, int target)
{
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
        int half = 0;
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
void testTree(f fuc, string name, u print = nullptr)
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

int main(int argc, char const *argv[])
{
    // testTree(isValidBST,"isValidBST",printInt);
    // testTree(maxDepth,"maxDepth",printInt);
    // testTree(minDepth,"minDepth",printInt);
    // testTree(isBalanced,"isBalanced",printInt);
    // testTree(postorderTraversal, "postorderTraversal", printVector);
    // testTree(isSymmetric, "isSymmetric", printInt);
    // testTree(levelOrderBottom, "levelOrderBottom", print2Vector);
    testTree(tree2str, "tree2str", [](string res) { cout << res << endl; });
    return 0;
}