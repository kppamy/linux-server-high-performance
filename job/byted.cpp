#include <vector>
#include "../common.h"
#include <stack>
#include <queue>
using namespace std;

// 449. Serialize and Deserialize BST
class Codec
{
private:
    const string SPLIT = " ";
    const string EMPTY = "99999";

public:
    int str2int(string str)
    {
        int ans = 0;
        int len = str.size();
        for (int i = 0; i < len; i++)
        {
            ans += 10 * ans + str[i] - '0';
        }
        return ans;
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode *root)
    {
        if (!root)
            return "";
        string ans = "";
        queue<TreeNode *> sta;
        sta.push(root);
        while (!sta.empty())
        {
            TreeNode *tp = sta.front();
            sta.pop();
            if (!tp)
            {
                if (sta.size() > 0)
                    ans += EMPTY + SPLIT;
            }
            else
            {
                ans += to_string(tp->val) + SPLIT;
                if (tp->left || tp->right)
                {
                    sta.push(tp->left);
                    sta.push(tp->right);
                }
            }
        }
        return ans;
    }

    // Decodes your encoded data to tree.
    TreeNode *deserialize(string data)
    {
        int len = data.size();
        if (len == 0)
            return nullptr;
        vector<string> da = split(data, SPLIT);
        TreeNode *root = new TreeNode(str2int(da[0]));
        queue<TreeNode *> que;
        que.push(root);
        int i = 0, sz = da.size();
        while (!que.empty())
        {
            TreeNode *tp = que.front();
            que.pop();
            if (i >= sz - 1)
                break;
            int li = i + 1;
            string lval = da[li];
            if (lval != EMPTY)
            {
                TreeNode *left = new TreeNode(str2int(lval));
                tp->left = left;
                que.push(left);
            }
            i++;
            if (i >= sz - 1)
                break;
            int ri = i + 1;
            string rval = da[ri];
            if (rval != EMPTY)
            {
                TreeNode *right = new TreeNode(str2int(rval));
                tp->right = right;
                que.push(right);
            }
            i++;
        }
        return root;
    }
};

// TreeNode *buildTree(const vector<int> &arr)
// {
//     int len = arr.size();
// }

// #include <iostream>
// #include <vector>
// using namespace std;

// struct Tree
// {
//     int val;
//     Tree *left;
//     Tree *right;
//     Tree(int v) : val(v)
//     {
//     }
// };

// Tree *deSerial(const vector<int> &arr)
// {
//     int sz = arr.size(), len = sz / 2;
//     if (sz == 1 && arr[0])
//         return new Tree(arr[0]);
//     else if (sz == 0 || arr[0] == 0)
//         return nullptr;
//     Tree *root = nullptr;
//     for (int i = 0; i < len; ++i)
//     {
//         Tree *parent = new Tree(arr[i]);
//         if (!root)
//             root = parent;
//         int left = arr[2 * i + 1];
//         parent->left = new Tree(left);
//         int right = arr[2 * i + 2];
//         parent->right = new Tree(right);
//     }
//     return root;
// }

// #include <stack>
// void preOrder(Tree *root)
// {
//     if (!root)
//         return;
//     cout << root->val << " ";
//     preOrder(root->left);
//     preOrder(root->right);
// }

// 3th interview
// 168. Excel Sheet Column Title
//  0 ms, faster than 100.00%
// 6 MB, less than 50.26%
string convertToTitle(int columnNumber)
{
    string ans = "";
    while (columnNumber)
    {
        int a = columnNumber % 26;
        int b = columnNumber / 26;
        if (a == 0)
        {
            a = 26;
            b = b - 1;
        }
        ans += 'A' + a - 1;
        columnNumber = b;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void testSeriDeser()
{
    {
        string tree = "2 1 99999 3 99999 4";
        Codec des;
        Codec ser;
        TreeNode *root = des.deserialize(tree);
        string out = ser.serialize(root);
        cout << out << endl;
    }

    {
        string tree = "2 99999 1 99999 3 99999 4";
        Codec des;
        Codec ser;
        TreeNode *root = des.deserialize(tree);
        string out = ser.serialize(root);
        cout << out << endl;
    }

    {
        string tree = "2 1 3 99999 4 5 99999 6";
        Codec des;
        Codec ser;
        TreeNode *root = des.deserialize(tree);
        string out = ser.serialize(root);
        cout << out << endl;
    }

    Codec cod;
    {
        string tree = "1";
        TreeNode *root = cod.deserialize(tree);
        string out = cod.serialize(root);
        cout << out << endl;
    }

    {
        string tree = "1 2";
        TreeNode *root = cod.deserialize(tree);
        string out = cod.serialize(root);
        cout << out << endl;
    }

    {
        string tree = "2 1 3";
        Codec des;
        Codec ser;
        TreeNode *root = des.deserialize(tree);
        string out = ser.serialize(root);
        cout << out << endl;
    }

    {
        string tree = "1 2 3 4 5";
        TreeNode *root = cod.deserialize(tree);
        string out = cod.serialize(root);
        cout << out << endl;
    }
}

class A{
    private:
    int val=0;
    public:
    void func(){
        cout<<"I am okay func"<<endl;
    }
    int getVal(){
        return val;
    }
    virtual void vfunc(){
                cout<<"I am okay virtual func"<<endl;
    }
};

void testMemFunc(){
    A* ptr = new A();
    delete ptr;
    ptr->func();
    // ptr->getVal(); // crash
    // ptr->vfunc(); //crash

    ptr=nullptr;
    ptr->func();
    ptr->vfunc();
}

int main()
{
    testMemFunc();
    return 0;
}
