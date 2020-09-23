#include <string>
#include <stack>
#include <map>
using namespace std;

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
#include "common.h"

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

int main(int argc, char const *argv[])
{
    // testsValid();
    // testMinStack2();
    testMinStack3();
    // testMinStack4();
    // formatCall();
    return 0;
}
