#include <deque>

using namespace std;

// 1670. Design Front Middle Back Queue
// 36 ms, faster than 79.13%
//  20.8 MB, less than 32.85%
class FrontMiddleBackQueue
{
public:
    FrontMiddleBackQueue()
    {
    }
    void balance()
    {
        int s1 = q1.size();
        int s2 = q2.size();
        while (s1 - s2 > 1)
        {
            q2.push_front(q1.back());
            q1.pop_back();
            s1--;
            s2++;
        }

        while (s2 - s1 > 0)
        {
            q1.push_back(q2.front());
            q2.pop_front();
            s1++;
            s2--;
        }
    }

    void pushFront(int val)
    {
        q1.push_front(val);
        balance();
    }

    void pushMiddle(int val)
    {
        if (q1.size() > q2.size())
        {
            q2.push_front(q1.back());
            q1.pop_back();
        }
        q1.push_back(val);
        balance();
    }

    void pushBack(int val)
    {
        q2.push_back(val);
        balance();
    }

    int popFront()
    {
        int ft = -1;
        if (!q1.empty())
        {
            ft = q1.front();
            q1.pop_front();
        }
        balance();
        return ft;
    }

    int popMiddle()
    {
        int mid = -1;
        if (!q1.empty())
        {
            mid = q1.back();
            q1.pop_back();
        }
        balance();
        return mid;
    }

    int popBack()
    {
        int back = -1;
        if (!q2.empty())
        {
            back = q2.back();
            q2.pop_back();
        }
        else if (!q1.empty())
        {
            back = q1.back();
            q1.pop_back();
        }
        balance();
        return back;
    }

private:
    deque<int> q1;
    deque<int> q2;
};