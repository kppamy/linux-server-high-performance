

// struct block
// {
//     char *data;
//     block(size_t sze) : size(sz)
//     {
//         data = malloc(size * sizeof(char))
//     }

//     ~block()
//     {
//         delete data;
//     }

// private:
//     constexpr size_t size;
// };

// block *myallocate(size_t size);

#include <vector>
using namespace std;
struct Node
{
    int val;
    vector<Node *> children;

public:
    Node(int _val, int forks)
    {
        val = _val;
        children.resize(forks);
    }
};

Node *buildNaryNode(int n, int m)
{
    if (n <= 0)
        return nullptr;
    int len = n;
    Node *root = new Node(len, m);
    vector<Node *> child(m);
    for (int i = 0; i < m; i++)
    {
        Node *node = buildNaryNode(len - i, m);
        child.emplace_back(node);
    }
    root->children = child;
    return root;
}

#include<iostream>
class A{
    private:
    int a{0};
    public:
    virtual void print(){
        cout<< "I am father "<< a<<endl;
    }
    virtual ~A(){};
};

class B:public A{
    private:
    int a{1};
     virtual void print(){
        cout<< "I am child "<< a<<endl;
    }
};

int main(int argc, char const *argv[])
{
    // Node *tree = buildNaryNode(3, 1);
    // unique_ptr<A> p= make_unique<new B[10]>;
    A* p=new B[10];
    p->print();
    delete[] p;
    return 0;
}
