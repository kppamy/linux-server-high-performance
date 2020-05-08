#include "TreeTest.h"
#include <iomanip>

TreeNode *buildTree()
{
    int val;
    cin >> val;
    if (val == -1)
        return NULL;
    TreeNode *root = new TreeNode(val);
    root->left = buildTree();
    root->right = buildTree();
    return root;
}

int TreeTest::maxDepth(TreeNode *root)
{
    if (root->left == NULL && root->right == NULL)
        return 1;
    else if (root->left == NULL)
        return (maxDepth(root->right)+1);
    else if (root->right == NULL)
        return (maxDepth(root->left)+1);
    else
    {
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return (left >= right ? (left + 1) : (right + 1));
    }
}

void getLine(const TreeNode *root, int depth, vector<int> &vals)
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

void printRow(const TreeNode *p, const int height, int depth)
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
                    cout << "/"<< "   ";
                else
                    cout << "\\"<< "   ";
            }
            toggle = !toggle;
        }
        cout << endl;
        cout << setw((height - depth) * 2);
    }
    for (int v : vec)
    {
        if (v != -2)
            cout << v << "   ";
    }
    cout << endl;
}

// create a pretty vertical tree
void prettyPrintTree(TreeNode *p, int hgt)
{
    //   int height = getHeight(p) * 2;
    int height = hgt;
    for (int i = 0; i < height; i++)
    {
        printRow(p, height, i);
    }
}

int main(int argc, char const *argv[])
{
    cout << "please input the tree nodes" << endl;
    // right tree: 1 -1 2 -1 3 -1 4 -1 5 6 -1 7 -1 -1 -1
    // left tree: 1 -1 2 -1 3 -1 4 -1 5 6 -1 7 -1 -1 -1
    TreeNode *root = buildTree();
    TreeTest tt;
    int dpt= tt.maxDepth(root);
    prettyPrintTree(root,dpt);
    cout<< "depth of the tree: " <<dpt<< endl;
    return 0;
}
