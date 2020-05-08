#include <stddef.h>
#include <vector>
#include <iostream>
using namespace std;
struct TreeNode
{
   int val;
   TreeNode* left;
   TreeNode* right;
   TreeNode(int x): val(x),left(NULL),right(NULL){}
};



class TreeTest{
    public:
        TreeTest(){};
        ~TreeTest(){};
        int maxDepth(TreeNode* node);

};
