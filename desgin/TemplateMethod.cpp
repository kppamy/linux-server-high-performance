
#include <iostream>
using namespace std;
class TemplateMethod
{
public:
    void methodArchitecture()
    {
        primitiveOper1();
        primitiveOper2();
    }

    virtual void primitiveOper1()
    {
        cout << " fater primitiveOper1" << endl;
    }

    virtual void primitiveOper2()
    {
        cout << " fater primitiveOper2" << endl;
    }
    virtual ~TemplateMethod() {}
};

class TMchildA : public TemplateMethod
{
public:
    void primitiveOper1() final
    {
        cout << " override primitiveOper1" << endl;
    }
};

class TMchildB : public TemplateMethod
{
public:
    virtual void primitiveOper2() final
    {
        cout << " override  primitiveOper2 from B" << endl;
    }
};

int main(int argc, char const *argv[])
{
    unique_ptr<TemplateMethod> p(make_unique<TMchildA>());
    unique_ptr<TemplateMethod> p2(make_unique<TMchildB>());
    auto p3(make_unique<TMchildB>());
    p->methodArchitecture();
    p2->methodArchitecture();
    p3->methodArchitecture();
    return 0;
}
