#include <functional>
#include <mutex>
#include <vector>
#include <iostream>
using namespace std;

// 1226. The Dining Philosophers
// 184 ms, faster than 63.16% 
class DiningPhilosophers
{
public:
    static int counts;
    DiningPhilosophers()
    {
        forks = vector<mutex>(5);
    }

    DiningPhilosophers(int n) : DiningPhilosophers()
    {
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork)
    {
        if (philosopher == 0)
        {
            forks[philosopher].lock();
            forks[4].lock();
            pickLeftFork();
            pickRightFork();
            eat();
            putRightFork();
            putLeftFork();
            forks[4].unlock();
            forks[philosopher].unlock();
        }
        else
        {
            forks[philosopher - 1].lock();
            pickRightFork();
            forks[philosopher].lock();
            pickLeftFork();
            eat();
            putRightFork();
            putLeftFork();
            forks[philosopher - 1].unlock();
            forks[philosopher].unlock();
        }
    }

private:
    vector<mutex> forks;
};

void pickLeftFork()
{
    cout << "pickLeftFork" << endl;
}

void eat()
{
    cout << "eating ....." << endl;
}

void pickRightFork()
{
    cout << "pickRightFork" << endl;
}
void putLeftFork()
{
    cout << "putLeftFork" << endl;
}
void putRightFork()
{
    cout << "putRightFork" << endl;
}

#include <thread>
// Runtime: 76 ms, faster than 95.99% of C++ online submissions for The Dining Philosophers.
// Memory Usage: 11.5 MB, less than 5.16% of C++ online submissions for The Dining Philosophers.
void testDiningPhilosophers()
{
    int n = 5;
    DiningPhilosophers dp;
    while (n)
    {
        thread t0(bind(&DiningPhilosophers::wantsToEat, &dp, 0, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        thread t1(bind(&DiningPhilosophers::wantsToEat, &dp, 1, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        thread t2(bind(&DiningPhilosophers::wantsToEat, &dp, 2, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        thread t3(bind(&DiningPhilosophers::wantsToEat, &dp, 3, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        thread t4(bind(&DiningPhilosophers::wantsToEat, &dp, 4, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        t0.join();
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        n--;
    }
}

// 1226. The Dining Philosophers
// 200 ms, faster than 44.26% 
#include "Semophore.h"
class DiningPhilosophersSem
{
public:
    DiningPhilosophersSem()
    {
        sem = new Semophore(4);
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork)
    {
        sem->wait();
        cout << "philosopher: " << philosopher << " gets to eat" << endl;
        pickLeftFork();
        pickRightFork();
        eat();
        putLeftFork();
        putRightFork();
        cout << "philosopher: " << philosopher << " finished " << endl;
        sem->post();
    }

private:
    Semophore *sem;
};

void testDiningPhilosophersSem()
{
    int n = 35;
    DiningPhilosophersSem dp;
    while (n)
    {
        thread t0(bind(&DiningPhilosophersSem::wantsToEat, &dp, 0, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        thread t1(bind(&DiningPhilosophersSem::wantsToEat, &dp, 1, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        thread t2(bind(&DiningPhilosophersSem::wantsToEat, &dp, 2, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        thread t3(bind(&DiningPhilosophersSem::wantsToEat, &dp, 3, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        thread t4(bind(&DiningPhilosophersSem::wantsToEat, &dp, 4, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
        t0.join();
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        n--;
    }
}
int main(int argc, char const *argv[])
{
    // testDiningPhilosophers();
    testDiningPhilosophersSem();
    return 0;
}
