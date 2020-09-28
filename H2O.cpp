#include <functional>
#include <thread>
#include <mutex>
#include <iostream>
#include <time.h>
#include "common.h"
#include <vector>
using namespace std;
// 1117. Building H2O
// Runtime: 212 ms, faster than 46.32% of C++ online submissions for Building H2O.
// Memory Usage: 9 MB, less than 53.41% of C++ online submissions for Building H2O.
class H2O
{
private:
    atomic<int> hyd{0};
    mutex hlock;
    mutex olock;
public:
    H2O()
    {
    }

    void hydrogen(function<void()> releaseHydrogen)
    {
        hlock.lock();
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        hyd++;
        if (hyd == 2) // (1)
        {
            olock.unlock();
        }
        else if (hyd < 2)
        {
            hlock.unlock();
        }
    }

    void oxygen(function<void()> releaseOxygen)
    {
        olock.lock();
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        if (hyd == 2)
        {
            hyd = 0;
            hlock.unlock();
        }
    }
};

void releaseHydrogen()
{
    cout << "H";
}

void releaseOxygen()
{
    cout << "O";
}

void testH2O()
{
    H2O ho;
    // string arr = "HOH";
    // string arr = "OOHHHH";
    string arr = "HOHOHOHHH";
    int n = 100;
    while (n > 0)
    {
        for (char c : arr)
        {
            if (c == 'H')
            {
                thread hh(bind(&H2O::hydrogen, &ho, releaseHydrogen));
                hh.detach();
            }
            else if (c == 'O')
            {
                thread oo(bind(&H2O::oxygen, &ho, releaseOxygen));
                oo.detach();
            }
        }
        cout << endl;
        n--;
    }
}

int main(int argc, char const *argv[])
{
    testH2O();
    return 0;
}
