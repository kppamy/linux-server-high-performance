#include<iostream>
using namespace std;

int global_v0;
int global_val = 0;

const int const_global_val = 0; // no symbol generated ?

class test
{
private:
    int val;
};

class subtest:test{

};



class B
{
protected:
int i=0;
public:
    void f1() {cout<<"normal function"<<endl; }
    virtual void f3() {cout<<"virtual function in base"<<endl; }
};

class A: public B
{
public:
    virtual void f2() final {cout<<"virtual function "<<endl;} 
};
class C: public B
{
public:
    virtual void f2() final {cout<<"virtual function "<< i<< endl;} 
};

void testVirtual(){

    B *b = nullptr;
    b->f1();
    // b->f3(); // crash!  null ptr access implict member: vptr to find vitual function in runtime, dynamic binding

    A *a = nullptr;
    a->f1();
    a->f2(); // okay!!!!  virtual function is final, the function's address is settle down in complile time, static binding

    C *c = nullptr;
    c->f1();
    c->f2(); // crash! final virtual function is okay, but access private memory i. access address 0x0---> crash!!

}

class  AA{
    public:
    int i=0;
    virtual void f1() {cout<<"AA f1 "<<endl; }
    virtual void f2() {cout<<"AA f2"<<endl; }
};

class  BB:public AA{
    public:
        virtual void f2() {cout<<"BB f2"<<endl; }
    virtual void f1() {cout<<"BB f1 "<<endl; }
};


void testVtable(){
    AA* a;
    a=new AA();
    cout<<"AA f1 "<<&AA::f1<<endl;
    cout<<"AA f2 "<<&AA::f2<<endl;
    BB* b=new BB();
    cout<<"BB f1 "<<&BB::f1<<endl;
    cout<<"BB f2 "<<&BB::f2<<endl;
    a=b;
    a->f1();
}


class OneF{
    public:
    void foo(){};
};

void testClassSize(){
    cout<<"size of one function class "<<sizeof(OneF)<<endl;
    OneF of;
    cout<<"size of one function class "<<sizeof(of)<<endl;
}

void testAlign(){
    test tt;  // no symbol generated ?
    test t2=tt;  // no symbol generated ?
    int val=sizeof(tt);  // no symbol generated ?
    printf(" global_val %d\n", global_val);
    printf(" sizeof(int) %d\n", sizeof(int));
    printf(" sizeof(long) %d\n", sizeof(long));
    printf(" sizeof(float) %d\n", sizeof(float));
    printf(" sizeof(double) %d\n", sizeof(double));
    printf(" sizeof(long long) %d\n", sizeof(long long));
    // cout<<"size test "<<sizeof(test)<<endl;
    // std::cout<<"size test instance "<<sizeof(tt)<<std::endl;
}

int main(int argc, char const *argv[])
{
    // testAlign();
    // testVirtual();
    testVtable();
    return 0;
}
