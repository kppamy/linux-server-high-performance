#include <functional>
#include <mutex>
#include <vector>
#include <iostream>
using namespace std;

// 1226. The Dining Philosophers
class DiningPhilosophers
{
public:
    static int counts;
    DiningPhilosophers()
    {
        // forks = vector<mutex>(5);
    }

    DiningPhilosophers(int n) : rounds(n)
    {
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork)
    {
        while (rounds > 0)
        {
            // this->print.lock();
            // cout << philosopher << " wantsToEat  " << rounds << endl;
            //  this->print.unlock();
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

            rounds--;
            counts++;
        }
    }

private:
    static vector<mutex> forks;
    static mutex print;
    int rounds;
};
mutex DiningPhilosophers::print;
vector<mutex> DiningPhilosophers::forks = vector<mutex>(5);
int DiningPhilosophers::counts = 0;

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
    DiningPhilosophers dp(n);
    DiningPhilosophers dp1(n);
    DiningPhilosophers dp2(n);
    DiningPhilosophers dp3(n);
    DiningPhilosophers dp4(n);
    thread t0(bind(&DiningPhilosophers::wantsToEat, &dp, 0, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
    thread t1(bind(&DiningPhilosophers::wantsToEat, &dp1, 1, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
    thread t2(bind(&DiningPhilosophers::wantsToEat, &dp2, 2, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
    thread t3(bind(&DiningPhilosophers::wantsToEat, &dp3, 3, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
    thread t4(bind(&DiningPhilosophers::wantsToEat, &dp4, 4, &pickLeftFork, &pickRightFork, &eat, &putLeftFork, &putRightFork));
    t0.join();
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    cout << "*********************  eating " << DiningPhilosophers::counts << endl;
}

int main(int argc, char const *argv[])
{
    testDiningPhilosophers();
    return 0;
}
