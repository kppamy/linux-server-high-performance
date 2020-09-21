
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

// 622. Design Circular Queue
class MyCircularQueue
{
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) : capacity(k)
    {
        data.resize(k);
    }

    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value)
    {
        if (isFull())
        {
            return false;
        }
        size++;
        rear++;
        if(rear>=capacity){
            rear=0;
        }
        data[rear] = value;
        return true;
    }

    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue()
    {
        if (isEmpty())
        {
            return false;
        }
        size--;
        front++;
        if (size==0)
        {
            front = 0;
            rear = 0;
        }
        if(front==capacity){
            front=0;
        }
        return true;
    }

    /** Get the front item from the queue. */
    int Front()
    {
        if(isEmpty())
        return -1;
        return data[front];
    }

    /** Get the last item from the queue. */
    int Rear()
    {
        if(isEmpty())
            return -1;
        return data[rear];
    }

    /** Checks whether the circular queue is empty or not. */
    bool isEmpty()
    {
        return size == 0;
    }

    /** Checks whether the circular queue is full or not. */
    bool isFull()
    {
        return size == capacity;
    }

private:
    vector<int> data;
    const int capacity;
    int front = 0;
    int size = 0;
    int rear = -1;
};

void testCircularQueue()
{
    MyCircularQueue *circularQueue = new MyCircularQueue(3); // set the size to be 3
    // circularQueue->enQueue(1);                               // return true
    cout << "circularQueue->enQueue(1)" << ((circularQueue->enQueue(1)) ? "" : " not ") << "success" << endl;

    // circularQueue->Rear();                                   // return 1
    cout << "circularQueue->Rear() " << circularQueue->Rear() << endl;

    // circularQueue->Front();                                   // return 1
    cout << "circularQueue->Front() " << circularQueue->Front() << endl;

    // circularQueue->deQueue();                                // return true
    cout << "circularQueue->deQueue()" << ((circularQueue->deQueue()) ? "" : " not ") << "success" << endl;
    // circularQueue->Rear();                                   // return 1
    cout << "circularQueue->Rear() " << circularQueue->Rear() << endl;

    // circularQueue->Front();                                   // return 1
    cout << "circularQueue->Front() " << circularQueue->Front() << endl;

    // circularQueue->enQueue(2);                               // return true
    cout << "circularQueue->enQueue(2)" << ((circularQueue->enQueue(2)) ? "" : " not ") << "success" << endl;

    // circularQueue->enQueue(3);                               // return true
    cout << "circularQueue->enQueue(3)" << ((circularQueue->enQueue(3)) ? "" : " not ") << "success" << endl;

    // circularQueue->enQueue(4);                               // return true
    cout << "circularQueue->enQueue(4)" << ((circularQueue->enQueue(4)) ? "" : " not ") << "success" << endl;

 // circularQueue->enQueue(5);                               // return false, the queue is full
    cout << "circularQueue->enQueue(5)" << ((circularQueue->enQueue(5)) ? "" : " not ") << "success" << endl;


    // circularQueue->Rear();                                   // return 3
    cout << "circularQueue->Rear() " << circularQueue->Rear() << endl;

    // circularQueue->isFull();                                 // return true
    cout << "circularQueue->isFull()" << ((circularQueue->isFull()) ? " YES " : " NO ") << endl;

        // circularQueue->deQueue();                                // return true
    cout << "circularQueue->deQueue()" << ((circularQueue->deQueue()) ? "" : " not ") << "success" << endl;
    // circularQueue->Rear();                                   // return 1
    cout << "circularQueue->Rear() " << circularQueue->Rear() << endl;

    // circularQueue->Front();                                   // return 1
    cout << "circularQueue->Front() " << circularQueue->Front() << endl;

    // circularQueue->deQueue();                                // return true
    cout << "circularQueue->deQueue()" << ((circularQueue->deQueue()) ? "" : " not ") << "success" << endl;

    // circularQueue->enQueue(4);                               // return true
    cout << "circularQueue->enQueue(4)" << ((circularQueue->enQueue(4)) ? "" : " not ") << "success" << endl;

    // circularQueue->Rear();                                   // return 4
    cout << "circularQueue->Rear() " << circularQueue->Rear() << endl;
}

int main(int argc, char const *argv[])
{
    /* code */
    // testRecentCounter();
    testCircularQueue();
    return 0;
}
