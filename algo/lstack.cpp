#include <string>
#include <stack>
#include <map>
#include <unordered_map>
#include "../common.h"
#include <queue>
using namespace std;

// 1047. Remove All Adjacent Duplicates In String
// 12 ms, faster than 97.77%
// 10.1 MB, less than 77.96%
string removeDuplicates(string S)
{
    string out;
    out.push_back(S[0]);
    int i = 1, len = S.size();
    while (i < len)
    {
        char cur = S[i];
        if (out.size() > 0 && cur == out.back())
        {
            out.pop_back();
        }
        else
        {
            out.push_back(cur);
        }
        i++;
    }
    return out;
}

// 1047. Remove All Adjacent Duplicates In String
//  16 ms, faster than 89.34%
string removeDuplicatesS(string S)
{
    int len = S.size();
    if (len == 1)
        return S;
    stack<char> sta;
    sta.push(S[0]);
    int i = 1;
    while (i < len)
    {
        char cur = S[i];
        if (!sta.empty() && cur == sta.top())
        {
            sta.pop();
        }
        else
        {
            sta.push(cur);
        }
        i++;
    }
    int sz = sta.size();
    string out(sz, 'A');
    // sz>0 instead of sta.empty(),  downgrade from 43.9% to 23.5% !!!!!!!!,
    //  data relavant is far more expensive than function call
    // while (sz>0)
    while (!sta.empty())
    {
        out[sz - 1] = sta.top();
        sta.pop();
        sz--;
    }
    return out;
}

// 1021. Remove Outermost Parentheses
//  0 ms, faster than 100.00%
// 6.6 MB, less than 94.15%
string removeOuterParentheses(string S)
{
    stack<char> sta;
    sta.push(S[0]);
    int i = 1, len = S.size();
    string out = "";
    while (i < len)
    {
        int sz = sta.size();
        char cur = S[i];
        if (cur == ')')
        {
            if (sz > 1)
            {
                out.push_back(cur);
            }
            sta.pop();
        }
        else
        {
            if (sz >= 1)
            {
                out.push_back(cur);
            }
            sta.push(cur);
        }
        i++;
    }
    return out;
}

void testremoveOuterParentheses()
{
    string S;
    S = "(()())(())(()(()))";
    cout << S << " removeOuterParentheses: " << removeOuterParentheses(S) << endl;

    S = "(()())(())";
    cout << S << " removeOuterParentheses: " << removeOuterParentheses(S) << endl;

    S = "()() ";
    cout << S << " removeOuterParentheses: " << removeOuterParentheses(S) << endl;
}

// 496. Next Greater Element I
// 8 ms, faster than 93.78%
vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
{
    if (nums2.size() * nums1.size() == 0)
        return {};
    stack<int> next;
    unordered_map<int, int> dct;
    for (int i = nums2.size() - 1; i >= 0; --i)
    {
        while (!next.empty() && next.top() < nums2[i])
        {
            next.pop();
        }
        dct[nums2[i]] = next.empty() ? -1 : next.top();
        next.push(nums2[i]);
    }
    vector<int> ans(nums1.size(), -1);
    for (int i = 0; i < nums1.size(); ++i)
    {
        ans[i] = dct[nums1[i]];
    }
    return ans;
}

// 503. Next Greater Element II
// 60 ms, faster than 55.70%
vector<int> nextGreaterElements(vector<int> &nums2)
{
    int len = nums2.size();
    if (len == 0)
        return {};
    vector<int> ans(len, -1);
    stack<int> next;
    for (int i = 2 * len - 1; i >= 0; --i)
    {
        int pos = i % len;
        while (!next.empty() && nums2[next.top()] <= nums2[pos])
        {
            next.pop();
        }
        ans[pos] = next.empty() ? -1 : nums2[next.top()];
        next.push(pos);
    }
    return ans;
}

// 496. Next Greater Element I
// 8 ms, faster than 93.87%
vector<int> nextGreaterElementI(vector<int> &nums1, vector<int> &nums2)
{
    if (nums2.size() * nums1.size() == 0)
        return {};
    unordered_map<int, int> dict;
    stack<int> next;
    for (int i = 0; i < nums2.size() - 1; ++i)
    {
        if (nums2[i] < nums2[i + 1])
        {
            dict[nums2[i]] = nums2[i + 1];
            while (!next.empty())
            {
                int tp = next.top();
                if (tp < nums2[i + 1])
                {
                    dict[tp] = nums2[i + 1];
                    next.pop();
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            next.push(nums2[i]);
        }
    }
    vector<int> ans(nums1.size(), -1);
    for (int i = 0; i < nums1.size(); ++i)
    {
        auto itr = dict.find(nums1[i]);
        if (itr != dict.end())
        {
            ans[i] = (*itr).second;
        }
    }
    return ans;
}

my2arr testnextGreaterElementII()
{
    return {
        {3, 8, 4, 1, 2},
        {1, 2, 1},
        {4, 1, 2},
        {1, 3, 4, 2},
        {2, 4},
        {1, 2, 3, 4}};
}

vector<int> nextGreaterElementWrapper(my2arr &cas)
{
    return nextGreaterElement(cas[0], cas[1]);
}

vector<my2arr> testnextGreaterElement()
{
    return {
        {{4, 1, 2}, {1, 3, 4, 2}},
        {{2, 4}, {1, 2, 3, 4}}};
}

// 739. Daily Temperatures
// 100 ms, faster than 95.00%
vector<int> dailyTemperatures(vector<int> &T)
{
    int len = T.size();
    vector<int> ans(len, 0);
    stack<pair<int, int>> decline;
    for (int i = 0; i < len - 1; ++i)
    {
        if (T[i] < T[i + 1])
        {
            ans[i] = 1;
            while (!decline.empty())
            {
                auto [idx, val] = decline.top();
                if (val < T[i + 1])
                {
                    ans[idx] = i - idx + 1;
                    decline.pop();
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            decline.push(make_pair(i, T[i]));
        }
    }
    return ans;
}

my2arr testdailyTemperatures()
{
    return {
        {73},
        {73, 74, 75, 71, 69, 72, 76, 73}};
}

// 20. Valid Parentheses
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Valid Parentheses.
// Memory Usage: 6.6 MB, less than 5.12% of C++ online submissions for Valid Parentheses.
bool isValid(string s)
{
    int len = s.size();
    if (len % 2)
    {
        return false;
    }
    map<char, char> dc;
    dc['('] = ')';
    dc['['] = ']';
    dc['{'] = '}';
    stack<char> data;
    char top;
    for (char c : s)
    {
        if (dc.find(c) != dc.end())
        {
            data.push(dc[c]);
        }
        else
        {
            if (data.size() == 0)
                return false;
            top = data.top();
            data.pop();
            if (c != top)
            {
                return false;
            }
        }
    }
    if (data.size() == 0)
        return true;
    return false;
}

#include <iostream>
void testsValid()
{
    cout << "()"
         << " is " << (isValid("()") ? "" : " not ") << " valid Parentheses" << endl;
    cout << "(("
         << " is " << (isValid("((") ? "" : " not ") << " valid Parentheses" << endl;
    cout << "()[]{}"
         << " is " << (isValid("()[]{}") ? "" : " not ") << " valid Parentheses" << endl;
    cout << "(]"
         << " is " << (isValid("(]") ? "" : " not ") << " valid Parentheses" << endl;
    cout << "([)]"
         << " is " << (isValid("([)]") ? "" : " not ") << " valid Parentheses" << endl;
    cout << "{[]}"
         << " is " << (isValid("{[]}") ? "" : " not ") << " valid Parentheses" << endl;
}

#include <vector>
#include <algorithm>

// 155. Min Stack
// Runtime: 40 ms, faster than 95.85% of C++ online submissions for Min Stack.
// Memory Usage: 16 MB, less than 94.24% of C++ online submissions for Min Stack.
class MinStack : public Object
{
    DECLARE_CLASS();

private:
    vector<int> data;
    int rear;
    int smallest;
    int size;

public:
    /** initialize your data structure here. */
    MinStack()
    {
        rear = -1;
        size = 0;
        smallest = INT_MAX;
    }

    friend ostream &operator<<(ostream &os, const MinStack &ms)
    {
        if (ms.size == 0)
            return os;
        for (int i = ms.rear - ms.size + 1; i <= ms.rear; i++)
            os << ms.data[i] << " ";
        return os;
    }

    bool isEmpty()
    {
        return (size == 0);
    }

    void push(int x)
    {
        // if use push_back,keep in mind that if we need to use the pop_back as well
        data.push_back(x);
        size++;
        rear++;
        smallest = (x < smallest) ? x : smallest;
        cout << __func__ << " minStack: " << *this << endl;
    }

    void pop()
    {
        if (isEmpty())
            return;
        rear--;
        size--;
        // when use vector to simulate the stack/queue, it's better to keep the storage the same
        // as the pointers, not just move the pointers aroud
        data.pop_back();
        cout << __func__ << " minStack: " << *this << endl;
        if (size == 0)
        {
            smallest = INT_MAX;
            data.resize(0);
        }
        else
        {
            // std::min couldn't iterator over vector's iterator range.
            // there is no such overloaded function, however, the compile doesn't show warning,
            // as it convert the iterator (int*) to int implictly.
            smallest = *min_element(data.begin(), data.begin() + size);
        }
    }

    int top()
    {
        if (!isEmpty())
            return data[rear];
        // must return some value or the leetcode compile will raise compiling error
        return INT_MAX;
    }

    int getMin()
    {
        if (!isEmpty())
            return smallest;
        // must return some value or the leetcode compile will raise compiling error
        return INT_MAX;
    }
};

IMPLEMENT_CLASS("MinStack", MinStack);

void formatCall()
{
    MinStack *obj = dynamic_cast<MinStack *>(Object::CreateObject("MinStack"));
    obj->push(1);
    cout << *obj;
    delete obj;
}

void testMinStack()
{
    MinStack *minStack = new MinStack();
    minStack->push(0);
    minStack->pop();

    minStack->push(-2);
    minStack->push(0);
    minStack->push(-3);
    cout << "minimum: " << minStack->getMin() << endl;

    minStack->pop();
    cout << "minStack->top() " << minStack->top() << endl; // return 0
    cout << "minimum: " << minStack->getMin() << endl;
    minStack->pop();
    cout << "minStack->top() " << minStack->top() << endl; // return 0
    minStack->pop();
    cout << "minStack->top() " << minStack->top() << endl; // return 0
    minStack->pop();
    cout << "minStack->top() " << minStack->top() << endl; // return 0

    // minStack->getMin(); // return -2
    delete minStack;
}

void testMinStack2()
{
    MinStack *minStack = new MinStack();
    minStack->push(2);
    minStack->push(0);
    minStack->push(3);
    minStack->push(0);
    cout << "minimum: " << minStack->getMin() << endl;

    minStack->pop();
    cout << "minimum: " << minStack->getMin() << endl;

    minStack->pop();
    cout << "minimum: " << minStack->getMin() << endl;

    minStack->pop();
    cout << "minimum: " << minStack->getMin() << endl;

    minStack->pop();
    minStack->push(0);

    delete minStack;
}

void testMinStack3()
{
    //     ["MinStack","push","push","push","top","pop","getMin",
    //     [[],[2147483646],[2147483646],[2147483647],[],[],[],

    MinStack *minStack = new MinStack();
    minStack->push(2147483646);
    minStack->push(2147483646);
    minStack->push(2147483647);
    cout << "top: " << minStack->top() << endl;
    minStack->pop();
    cout << "minimum: " << minStack->getMin() << endl;

    // "pop","getMin","pop",
    // [],[],[],
    minStack->pop();
    cout << "minimum: " << minStack->getMin() << endl;
    minStack->pop();

    // "push","top","getMin", "push","top","getMin","pop","getMin"]
    // [2147483647],[],[],[-2147483648],[],[],[],[]]

    minStack->push(2147483647);
    cout << "top: " << minStack->top() << endl;
    cout << "minimum: " << minStack->getMin() << endl;
    minStack->push(-2147483648);
    cout << "top: " << minStack->top() << endl;
    cout << "minimum: " << minStack->getMin() << endl;

    minStack->pop();
    cout << "minStack: " << *minStack << endl;
    cout << "minimum: " << minStack->getMin() << endl;

    delete minStack;
}

void testMinStack4()
{
    //     ["MinStack","push","push","getMin","getMin",
    //     [[],[-10],[14],[],[],

    MinStack *minStack = new MinStack();
    minStack->push(-10);
    minStack->push(14);
    cout << "minimum: " << minStack->getMin() << endl;
    cout << "minimum: " << minStack->getMin() << endl;

    // "push","getMin","getMin",
    // [-20],[],[],
    minStack->push(-20);
    cout << "minimum: " << minStack->getMin() << endl;
    cout << "minimum: " << minStack->getMin() << endl;

    // "top","getMin","pop",
    // [],[],[],
    cout << "top: " << minStack->top() << endl;
    cout << "minimum: " << minStack->getMin() << endl;
    minStack->pop();

    // "push","push","getMin",
    // [10],[-7],[],
    minStack->push(10);
    minStack->push(-7);
    cout << "minimum: " << minStack->getMin() << endl;

    // "push","pop","top","getMin","pop"]
    // [-7],[],[],[],[]]
    minStack->push(-7);
    minStack->pop();
    cout << "top: " << minStack->top() << endl;
    cout << "minimum: " << minStack->getMin() << endl;
    minStack->pop();
}

#include <queue>
// 225. Implement Stack using Queues
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Implement Stack using Queues.
// Memory Usage: 7.1 MB, less than 18.28% of C++ online submissions for Implement Stack using Queues.
class QStack
{
public:
    /** Initialize your data structure here. */
    QStack()
    {
    }

    /** Push element x onto stack. */
    void push(int x)
    {
        data.push(x);
        rear = x;
        size++;
        cout << __func__ << " " << x << " " << endl;
    }

    /** Removes the element on top of the stack and returns that element. */
    int pop()
    {
        if (empty())
            return INT_MAX;
        cout << __func__ << " " << rear << endl;
        int counter = size;
        queue<int> backup;
        int tmp;
        while (counter > 1)
        {
            tmp = data.front();
            backup.push(tmp);
            cout << tmp << " ";
            data.pop();
            counter--;
        }
        cout << endl;
        data = backup;
        int end = rear;
        size--;
        rear = (size > 0) ? tmp : INT_MAX;
        return end;
    }

    /** Get the top element. */
    int top()
    {
        cout << __func__ << " " << rear << endl;
        if (!empty())
            return rear;
        return INT_MAX;
    }

    /** Returns whether the stack is empty. */
    bool empty()
    {
        cout << __func__ << "? size: " << size << endl;
        return size == 0;
    }

private:
    queue<int> data;
    int size = 0;
    int rear;
};

void testQstack()
{
    QStack *stack = new QStack();
    stack->push(1);
    stack->push(2);
    stack->top();   // returns 2
    stack->pop();   // returns 2
    stack->empty(); // returns false
    stack->pop();   // returns 2
    stack->push(3);
    stack->top(); // returns 2
    stack->push(4);
    stack->top(); // returns 2
    stack->push(5);
    stack->top(); // returns 2
    stack->pop(); // returns 2
    stack->pop(); // returns 2
    stack->top(); // returns 2
}

// 331. Verify Preorder Serialization of a Binary Tree
// Runtime: 52 ms, faster than 5.92% of C++ online submissions for Verify Preorder Serialization of a Binary Tree.
// Memory Usage: 38.6 MB, less than 5.03% of C++ online submissions for Verify Preorder Serialization of a Binary Tree.
bool isValidSerialization(string preorder)
{
    stack<string> sta;
    int len = preorder.size();
    auto check = [&](string &&nd) {
        if (nd != "#")
        {
            sta.push(nd);
            return true;
        }
        while (true)
        {
            if (sta.empty())
                return len == 0;
            if (sta.top() == "#")
            {
                sta.pop();
                sta.pop();
            }
            else
            {
                sta.push("#");
                break;
            }
        }
        return true;
    };

    while (true)
    {
        int pos = preorder.find(',');
        if (pos == -1)
        {
            len = 0;
            if (!check(move(preorder)))
                return false;
            break;
        }
        else
        {
            if (!check(preorder.substr(0, pos)))
                return false;
            preorder = preorder.substr(pos + 1);
        }
    }
    return sta.size() == 0;
}

void testisValidSerialization()
{
    vector<string> cases = {
        "9,#,92,#,#",
        "9,#,#",
        "9,3,4,#,#,1,#,#,2,#,6,#,#",
        "#,9,#",
        "1,#",
        "9,#,#,1"};
    for (auto &&str : cases)
    {
        cout << str + "  is" << (isValidSerialization(str) ? "" : " not ") << " valid preorder serialization " << endl;
    }
}

int main(int argc, char const *argv[])
{
    // testsValid();
    // testMinStack2();
    // testMinStack3();
    // testMinStack4();
    // formatCall();
    // testQstack();
    // testisValidSerialization();
    // format_test(dailyTemperatures,testdailyTemperatures);
    // format_test(nextGreaterElementWrapper, testnextGreaterElement);
    // format_test(nextGreaterElement, testnextGreaterElementII);
    testremoveOuterParentheses();
    return 0;
}
