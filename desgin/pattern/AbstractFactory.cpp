#include <iostream>
using namespace std;
class ProductA
{
public:
    virtual void say() = 0;
    virtual ~ProductA(){};
};
class GreenProductA : public ProductA
{
    void say()
    {
        cout << "i am GreenProductA" << endl;
    }
    ~GreenProductA(){
                cout << "destroy GreenProductA" << endl;
    }
};

class RedProductA : public ProductA
{
    public:
    void say()
    {
        cout << "i am RedProductA" << endl;
    }

    RedProductA(){
                cout << " construct RedProductA" << endl;
    }

     ~RedProductA(){
                cout << " destroy RedProductA" << endl;
    }
};

class ProductB
{
public:
    virtual void say() = 0;
    virtual ~ProductB(){};
};

class GreenProductB : public ProductB
{
    void say()
    {
        cout << "i am GreenProductB" << endl;
    }
     ~GreenProductB(){
                cout << "destroy GreenProductB" << endl;
    }
};

class RedProductB : public ProductB
{
    void say()
    {
        cout << "i am RedProductB" << endl;
    }
    ~RedProductB(){
                cout << " destroy RedProductB" << endl;
    }
};

class AbstractFactory
{
public:
    virtual ~AbstractFactory(){};
    virtual ProductA *createProductA() = 0;
    virtual ProductB *createProductB() = 0;
};

class GreeFactory : public AbstractFactory
{
public:
    GreenProductA *createProductA() override
    {
        return new GreenProductA();
    };
    GreenProductB *createProductB() override
    {
        return new GreenProductB();
    };
};

class RedFactory : public AbstractFactory
{
public:
    RedProductA *createProductA() override
    {
        return new RedProductA();
    };
    RedProductB *createProductB() override
    {
        return new RedProductB();
    };
};

class Builder
{
public:
    virtual ProductA *buildProductA() = 0;
    virtual ProductB *buildProductB() = 0;
    virtual ~Builder(){};
};

class RedBuilder : public Builder
{
public:
    RedProductA *buildProductA() override
    {
        return new RedProductA();
    };
    RedProductB *buildProductB() override
    {
        return new RedProductB();
    };
    ~RedBuilder(){
        cout<<"~RedBuilder"<<endl;
    }
};

class Director
{
private:
    shared_ptr<Builder> worker;
public:
    Director(shared_ptr<Builder> builder) : worker(builder){};
    std::pair<ProductA*, ProductB*> construct()
    {
        ProductA *a = worker->buildProductA();
        ProductB *b = worker->buildProductB();
        return std::make_pair(a, b);
    }
};

int main(int argc, char const *argv[])
{
    shared_ptr<AbstractFactory> gfactory(new GreeFactory());
    shared_ptr<ProductA> pa(gfactory->createProductA());
    shared_ptr<ProductB> pb(gfactory->createProductB());
    pa->say();
    pb->say();

    shared_ptr<AbstractFactory> rfactory(new RedFactory());
    shared_ptr<ProductA> ra(rfactory->createProductA());
    shared_ptr<ProductB> rb(rfactory->createProductB());
    ra->say();
    rb->say();

    cout<<"============== Builder pattern ==========="<<endl;
    Director worker(shared_ptr<Builder>(new RedBuilder()));
    auto [ba,bb]=worker.construct();
    ba->say();
    bb->say();
    delete ba;
    delete bb;
}
