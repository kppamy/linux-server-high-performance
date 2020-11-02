#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unistd.h>
#include <map>
#include <stack>
#include <queue>
using namespace std;

#include <mutex>
#include <condition_variable>
#include <atomic>
#include <queue>
#include <time.h>
#include <unistd.h>

string buf = "";

mutex mu;
condition_variable cond;
atomic<int> who{1};
vector<int> qu(128, 0);

void *produce()
{

    while (true)
    {
        mu.lock();
        int t = clock();
        qu.push_back(t);
        cout << " produce: " << t << endl;
        who = 0;
        mu.unlock();
        sleep(5);
    }

    //P empty
    // produce
    // V empty
    //v full
}

void *consume()
{

    while (true)
    {
        mu.lock();
        if (!qu.empty())
        {
            int t = qu.back();
            qu.pop_back();
            cout << " conusme: " << t << endl;
        }
        mu.unlock();
    }
}

void testFunc()
{
    vector<vector<int>> arrs = {

    };
    for (auto &&item : arrs)
    {
    }
}

#include <thread>
int main(int argc, char const *argv[])
{

    thread t1(produce);
    thread t2(consume);
    t1.join();
    t2.join();
    return 0;
}
