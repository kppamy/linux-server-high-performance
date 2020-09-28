#include <functional>
#include <thread>
#include <mutex>
#include <iostream>
#include <time.h>
#include "common.h"
#include <vector>
using namespace std;
class H2O
{
private:
    atomic<int> hyd{0};
    mutex hlock;
    mutex olock;
    vector<long> otime;
    vector<long> htime;

public:
    H2O()
    {
        hlock.lock();
    }

    void hydrogen(function<void()> releaseHydrogen)
    {

        if (hyd == 2) // (1)
        {
            cout << " ....  ";
            hlock.lock();
        }
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        // htime.push_back(clock());
        releaseHydrogen();
        hyd++;
        if (hyd == 2)
        {
            cout << " ..2..  ";
            olock.unlock();
        }
    }

    void oxygen(function<void()> releaseOxygen)
    {
        olock.lock();
        // releaseOxygen() outputs "O". Do not change or remove this line.
        // otime.push_back(clock());
        releaseOxygen();
        if (hyd == 2)
        {
            // wait for H
            hyd = 0;
            cout << " ****  ";
            hlock.unlock();
        }
    }
};

#include <unistd.h>
mutex mut;
void releaseHydrogen()
{
    // mut.lock();
    cout << "H";
    // mut.unlock();
}

void releaseOxygen()
{
    // mut.lock();
    cout << "O";
    // mut.unlock();
}

void testUnlockAfterThreadQuit()
{
    thread t1(releaseHydrogen);
    t1.join();
    thread t2(releaseOxygen);
    t2.join();
}

void testH2O()
{
    H2O ho;
    string arr = "OOHHHH";
    int n = 10;
    while (n > 0)
    {
        thread oo(bind(&H2O::oxygen, &ho, releaseOxygen));
        thread oo2(bind(&H2O::oxygen, &ho, releaseOxygen));
        thread hh(bind(&H2O::hydrogen, &ho, releaseHydrogen));
        thread hh2(bind(&H2O::hydrogen, &ho, releaseHydrogen));
        thread hh3(bind(&H2O::hydrogen, &ho, releaseHydrogen));
        thread hh4(bind(&H2O::hydrogen, &ho, releaseHydrogen));
        oo.detach();
        oo2.detach();
        hh2.detach();
        hh.detach();
        hh3.detach();
        hh4.detach();
        cout << endl;
        n--;
        sleep(1);
    }
}

int main(int argc, char const *argv[])
{
    testH2O();
    // testUnlockAfterThreadQuit();
    return 0;
}
