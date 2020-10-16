#include <iostream>
using namespace std;
class Product
{
public:
    virtual void eat()
    {
        cout << "Product eat" << endl;
    }
    virtual ~Product(){};
};

class Factory
{
public:
    virtual ~Factory(){};
    virtual Product *createProduct()=0;
};

class ConcreteProduct : public Product
{
public:
// not necessary use virtual as well, 
// In the derived class the function is virtual by way of having the ¹same type as the base class function.
// override helps maintainance
    void eat() override
    {
        cout << "ConcreteProduct eat" << endl;
    }
};

class ConcreteFactory : public Factory
{
public:
// not necessary use virtual as well
// override helps maintainance
    ConcreteProduct *createProduct() override
    {
        ConcreteProduct* cp=new ConcreteProduct();
        cp->eat();
        return cp;
    }
};


#include<memory>
int main(int argc, char const *argv[])
{
    unique_ptr<Factory> fm(new ConcreteFactory());
    unique_ptr<Product> pro(fm->createProduct());
    return 0;
}
