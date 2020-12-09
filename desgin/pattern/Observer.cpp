#include <iostream>
using namespace std;
#include <vector>
class Observer;
class Subject
{
private:
    vector<shared_ptr<Observer>> observers;

public:
    void subscribe(shared_ptr<Observer> &&observer)
    {
        observers.push_back(observer);
    }

    void push();
    virtual int getState() const { return -1; };
    virtual void setState(int state){};
    virtual ~Subject() {}
};

class ConcreteSubject : public Subject
{
private:
    int state{0};

public:
    void setState(int a)
    {
        if (a != state)
        {
            state = a;
            push();
        }
        else
        {
            cout << "sate not changed, no need to notify observers" << endl;
        }
    }

    // hidden overloaded virtual function 'Subject::getState' declared here: different qualifiers (const vs none)
    // int getState()
    int getState() const
    {
        return state;
    };
};

class Observer
{
public:
    virtual ~Observer() {}
    virtual void update(const Subject &s) {}
};

void Subject::push()
{
    for (auto &&i : observers)
    {
        // i: member access into incomplete type 'element_type' (aka 'Observer')
        i->update(*this);
    }
}
class ObserverA : public Observer
{
public:
    void update(const Subject &s) override
    {
        cout << "observerA get notice " << s.getState() << endl;
    }
};

class ObserverB : public Observer
{
public:
    void update(const Subject &s) override
    {
        cout << "observerB get notice" << s.getState() << endl;
    }
};

int main(int argc, char const *argv[])
{
    // ConcreteSubject s;
    shared_ptr<Subject> s(make_shared<ConcreteSubject>());
    // unique_ptr<Subject> s(move(make_unique<ConcreteSubject>()));
    s->subscribe(make_shared<ObserverA>());
    s->subscribe(make_shared<ObserverB>());
    s->setState(0);
    s->setState(1);
    return 0;
}
