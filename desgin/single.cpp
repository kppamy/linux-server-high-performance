#include <iostream>
#include <mutex>
using namespace std;
class lazySingle
{
private:
    static mutex mut;
    static lazySingle *instance;

private:
    lazySingle()
    {
        cout << "create lazy single instance" << endl;
    };

public:
    static lazySingle *getInstance()
    {
        lock_guard<mutex> lck(mut);
        if (instance == nullptr)
        {
            instance = new lazySingle();
        }
        return instance;
    }
};

mutex lazySingle::mut;
lazySingle* lazySingle::instance;

class hungrySingle
{
private:
    static hungrySingle *instance;
    hungrySingle()
    {
        cout << "create hungry single instance" << endl;
    };

public:
    static hungrySingle *getInstance()
    {
        return instance;
    }
};

hungrySingle * hungrySingle::instance=new hungrySingle();

int main(int argc, char const *argv[])
{
    lazySingle *single=lazySingle::getInstance();
    cout << "lazySingle: " << single << endl;

    hungrySingle *hungry=hungrySingle::getInstance();
        cout << "hungrySingle: " << hungry << endl;

    return 0;
}
