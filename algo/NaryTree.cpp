#include <vector>
#include <queue>
using namespace std;
// Definition for a Node.

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

int main(int argc, char const *argv[])
{
    /* code */
    // testNaryTree(maxDepth,"maxDepth",printInt);
    testNaryTree(preorder, "preorder", printVector);
    return 0;
}
