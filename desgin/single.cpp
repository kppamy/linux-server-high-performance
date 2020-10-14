#include <iostream>
#include <mutex>
using namespace std;
class lazySingle
{
private:
    static mutex mut;
    static lazySingle *instance;
    string val = "lazy";

private:
    lazySingle(string name) : val(name){};

public:
    lazySingle() = delete;
    lazySingle(lazySingle &other) = delete;
    void operator=(const lazySingle &other) = delete;
    static lazySingle *getInstance(string name)
    {
        lock_guard<mutex> lck(mut);
        if (instance == nullptr)
        {
            instance = new lazySingle(name);
        }
        return instance;
    }
    string getVal()
    {
        return val;
    }
    ~lazySingle()
    {
        delete instance;
        instance = nullptr;
        cout << "singleton deconstructor" << endl;
    }
};

mutex lazySingle::mut;
lazySingle *lazySingle::instance = nullptr;

class hungrySingle
{
private:
    static hungrySingle *instance;
    hungrySingle()
    {
        cout << "create hungry single instance" << endl;
    };

public:
    hungrySingle(hungrySingle &other) = delete;
    hungrySingle operator=(hungrySingle &other) = delete;
    static hungrySingle *getInstance()
    {
        return instance;
    }
};

hungrySingle *hungrySingle::instance = new hungrySingle();

#include <thread>
string threadFoo()
{
    std::this_thread::sleep_for(chrono::microseconds(1000));
    lazySingle *ls = lazySingle::getInstance("Foo");
    return ls->getVal();
}

string threadBar()
{
    std::this_thread::sleep_for(chrono::microseconds(1000));
    lazySingle *ls = lazySingle::getInstance("Bar");
    return ls->getVal();
}

int testAsync(int val)
{
    cout << val << endl;
    return val;
}

#include <future>
void testMySingleton()
{
    int n = 10000;
    while (n-- > 0)
    {
        future<string> foo = async(std::launch::async | std::launch::deferred, threadFoo); // default of async
        future<string> bar = async(threadBar);                                             // the same as above.
        string fs = foo.get();
        string bs = bar.get();
        if (fs != bs)
        {
            cout << "!!!!!!!!!!!!!!!oops, singleton not sigleton" << endl;
        }
        // foo.get(); crash
    }
}

#include <utility>
template <class T>
class SingleTon
{
public:
    static T &GetInstance(string name)
    {
        static T ins(name);
        return ins;
    }
    SingleTon(const SingleTon &) = delete;
    SingleTon &operator=(const SingleTon &) = delete;
    virtual ~SingleTon() {}

protected: // why protected?
    SingleTon() {}
};

class Foo
{
public:
    string val = "single";
    Foo(string name) : val(name) {}
};

string tstSig(string name)
{
    Foo f = SingleTon<Foo>::GetInstance(name);
    return f.val;
}
void testBeauty()
{
    int n = 100000;
    while (n-- > 0)
    {
        future<string> foo = async(std::launch::async | std::launch::deferred, tstSig, "Foo"); // default of async
        future<string> bar = async(tstSig, "Bar");                                             // the same as above.
        string fs = foo.get();
        string bs = bar.get();
        if (fs != bs)
        {
            cout << "!!!!!!!!!!!!!!!oops, singleton not sigleton" << endl;
        }
        // foo.get(); crash
    }
}
int main(int argc, char const *argv[])
{
    testBeauty();
    return 0;
}
