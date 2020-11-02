#include <vector>
#include <queue>
using namespace std;
// Definition for a Node.
class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

// 559. Maximum Depth of N-ary Tree
// Runtime: 28 ms, faster than 98.54% of C++ online submissions for Maximum Depth of N-ary Tree.
// Memory Usage: 11 MB, less than 15.36% of C++ online submissions for Maximum Depth of N-ary Tree.
#include <algorithm>
int maxDepth(Node *root)
{
    if (!root)
        return 0;
    if (root->children.size() == 0)
        return 1;
    int dep = 0;
    for (Node *child : root->children)
    {
        dep = max(maxDepth(child), dep);
    }
    return dep + 1;
}

Node *buildNaryNode(vector<int> &bfs_storage)
{
    int len = bfs_storage.size();
    if (len == 0)
        return nullptr;
    Node *root = nullptr;
    queue<Node *> prelevel;
    queue<Node *> nextlevel;
    vector<Node *> children;
    auto update = [&]() {
        if (!prelevel.empty())
        {
            Node *parent = prelevel.front();
            parent->children = children;
            prelevel.pop();
        }
        children.clear();
        if (prelevel.size() == 0)
        {
            prelevel = nextlevel;
            nextlevel = queue<Node *>();
        }
    };

    for (int node : bfs_storage)
    {
        if (node == -1)
        {
            update();
            continue;
        }
        Node *nd = new Node(node);
        if (!root)
            root = nd;
        children.push_back(nd);
        nextlevel.push(nd);
    }
    update();
    return root;
}

#include <stack>
// 589. N-ary Tree Preorder Traversal
// Runtime: 36 ms, faster than 98.13% of C++ online submissions for N-ary Tree Preorder Traversal.
// Memory Usage: 11.4 MB, less than 24.08% of C++ online submissions for N-ary Tree Preorder Traversal.
vector<int> preorder(Node *root)
{
    if (!root)
        return {};
    stack<Node *> data;
    data.push(root);
    vector<int> ordered;
    while (!data.empty())
    {
        Node *tp = data.top();
        ordered.push_back(tp->val);
        data.pop();
        int sz = tp->children.size();
        for (int i = sz - 1; i >= 0; i--)
        {
            data.push(tp->children[i]);
        }
    }
    return ordered;
}

#include "common.h"
template <typename f, typename u>
void testNaryTree(f fuc, string name, u print = nullptr)
{
    my2arr cases = {
        {1, -1, 3, 2, 4, -1, 5, 6},
        {1, -1, 2, 3, 4, 5, -1, -1, 6, 7, -1, 8, -1, 9, 10, -1, -1, 11, -1, 12, -1, 13, -1, -1, 14}};

    for (auto &&test : cases)
    {
        printVector(test);
        Node *root = buildNaryNode(test);
        // prettyPrintTree(root, maxDepth(root));
        cout << name + ": ";
        auto &&res = fuc(root);
        print(res);
        cout << endl;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    // testNaryTree(maxDepth,"maxDepth",printInt);
    testNaryTree(preorder, "preorder", printVector);
    return 0;
}
