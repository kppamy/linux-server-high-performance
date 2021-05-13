
#include <iostream>
#include <memory>
using namespace std;
class Strategy
{
public:
    virtual ~Strategy()
    {
        cout << "father delete" << endl;
    }
    virtual void implement()
    {
        cout << "father strategy" << endl;
    }
};

class StrategyA : public Strategy
{
public:
    ~StrategyA()
    {
        cout << "childA delete" << endl;
    }
    void implement()
    {
        cout << "child A strategy" << endl;
    }
};

class Context
{
private:
    unique_ptr<Strategy> sta;

public:
    Context(unique_ptr<Strategy> s) : sta(move(s)) {}
    void algo()
    {
        sta->implement();
    }
};

int main(int argc, char const *argv[])
{
    Context c(make_unique<Strategy>());
    c.algo();
    Context c1(make_unique<StrategyA>());
    c1.algo();
    return 0;
}
