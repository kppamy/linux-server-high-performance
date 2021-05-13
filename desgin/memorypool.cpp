
#include<mm_malloc.h>
#include<memory.h>
#include<iostream>
using namespace std;

struct block
{
    char *chunk{nullptr};

    void allocate(size_t size){
        chunk = (char*)malloc(size); 
        cout<<"allocate(chunk);    "<<endl;
    }

    void myfree(){
        free(chunk);
        cout<<"free(chunk);    "<<endl;
    }

};


void testAllocator(){
    block blk;
    blk.allocate(10);
    memset(blk.chunk,2,10);
    //  cout<<blk.chunk<<endl;
    blk.myfree();
}


#include <vector>
template <typename T>
struct Node
{
    T val;
    vector<Node *> children;

public:
    Node(T _val, int cap)
    {
        val = _val;
        children.resize(cap, nullptr);
    }

    ~Node()
    {
        for (auto &&nd : children)
        {
            if (nd)
            {
                delete nd;
                nd = nullptr;
            }
        }
    }
};

using myNode = Node<int>;

#include <queue>
myNode *buildNaryNode(int n, int m)
{

    if (n <= 0)
        return nullptr;
    myNode *root = new myNode(1, m);
    vector<myNode *> child(m);
    queue<myNode *> que;
    que.push(root);
    int i = 1;
    while (!que.empty() && i < n)
    {
        myNode *tp = que.front();
        que.pop();
        int j = 1;
        for (; j <= m; j++)
        {
            if (i + j <= n)
            {
                myNode *nd = new myNode(i + j, m);
                tp->children[j - 1] = nd;
                que.push(nd);
            }
            else
                break;
        }
        i = i + j - 1;
    }
    return root;
}

class A
{
private:
    int a{0};

public:
    virtual void print()
    {
        cout << "I am father " << a << endl;
    }
    virtual ~A(){};
};

class B : public A
{
private:
    int a{1};
    virtual void print()
    {
        cout << "I am child " << a << endl;
    }
};

int main(int argc, char const *argv[])
{
    // myNode *tree = buildNaryNode(7, 4);
    // vector<myNode *> child = tree->children;
    // delete tree;
    // tree = nullptr;

    testAllocator();
    // unique_ptr<A> p= make_unique<new B[10]>;

    // A *p = new B[10];
    // p->print();
    // delete[] p;

    // char *pc = (char *)malloc(sizeof(char) * 10);
    // cout << pc << endl;
    // free(pc);

    return 0;
}
