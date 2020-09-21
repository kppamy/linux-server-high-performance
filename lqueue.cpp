
#include <queue>
using namespace std;
// 933. Number of Recent Calls
// Runtime: 292 ms, faster than 68.67% of C++ online submissions for Number of Recent Calls.
// Memory Usage: 57.5 MB, less than 68.90% of C++ online submissions for Number of Recent Calls.
class RecentCounter
{
public:
    RecentCounter()
    {
    }

    int ping(int t)
    {
        calls.push(t);
        while (!calls.empty())
        {
            if (t - calls.front() > 3000)
            {
                calls.pop();
            }
            else
            {
                break;
            }
        }
        return calls.size();
    }

private:
    queue<int> calls;
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */

#include <iostream>
#include <vector>
void testRecentCounter()
{
    RecentCounter *obj = new RecentCounter();
    vector<int> times = {1, 100, 3001, 3002};
    for (int tk : times)
    {
        cout << "ping: " << tk << " recent calls: " << obj->ping(tk) << endl;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    testRecentCounter();
    return 0;
}
