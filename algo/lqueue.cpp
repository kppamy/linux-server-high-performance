
#include <queue>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

// 641. Design Circular Deque
// 36 ms, faster than 82.92%
// 17.2 MB, less than 21.74%
class MyCircularDeque
{
public:
    /** Initialize your data structure here. Set the size of the deque to be k. */
    MyCircularDeque(int k) : capacity(k)
    {
        data.resize(k, -1);
    }

    /** Adds an item at the front of Deque. Return true if the operation is successful. */
    bool insertFront(int value)
    {
        if (size == capacity)
            return false;
        front = (capacity + front - 1) % capacity;
        data[front] = value;
        size++;
        if (size == 1)
            rear = front;
        cout << "insertFront " << value << endl;
        cout << this;
        return true;
    }

    /** Adds an item at the rear of Deque. Return true if the operation is successful. */
    bool insertLast(int value)
    {
        if (size == capacity)
            return false;
        rear = (rear + 1) % capacity;
        data[rear] = value;
        size++;
        if (size == 1)
            front = rear;
        cout << "insertLast " << value << endl;
        cout << this;
        return true;
    }

    /** Deletes an item from the front of Deque. Return true if the operation is successful. */
    bool deleteFront()
    {
        if (size == 0)
            return false;
        data[front] = -1;
        size--;
        if (size == 0)
        {
            rear = -1;
            front = 0;
        }
        else
            front = (front + 1) % capacity;
        cout << "deleteFront " << endl;
        cout << this;
        return true;
    }

    /** Deletes an item from the rear of Deque. Return true if the operation is successful. */
    bool deleteLast()
    {
        if (size == 0)
            return false;
        data[rear] = -1;
        size--;
        if (size == 0)
        {
            rear = -1;
            front = 0;
        }
        else
        {
            rear = (rear - 1 + capacity) % capacity;
        }
        cout << "deleteLast " << endl;
        cout << this;
        return true;
    }

    /** Get the front item from the deque. */
    int getFront()
    {
        if (size == 0)
            return -1;
        return data[front];
    }

    /** Get the last item from the deque. */
    int getRear()
    {
        if (size == 0)
            return -1;
        return data[rear];
    }

    /** Checks whether the circular deque is empty or not. */
    bool isEmpty()
    {
        return size == 0;
    }

    /** Checks whether the circular deque is full or not. */
    bool isFull()
    {
        return size == capacity;
    }

    friend ostream &operator<<(ostream &out, MyCircularDeque *myqueue)
    {
        out << "( " << myqueue->front << " , " << myqueue->rear << " ) = " << myqueue->size << endl;
        for (int j = 0, i = myqueue->front; j < myqueue->size; i = (i + 1) % myqueue->capacity, ++j)
        {
            out << myqueue->data[i] << "  ";
        };
        out << endl;
        return out;
    }

private:
    vector<int> data;
    int capacity = 0;
    int front = 0;
    int rear = -1;
    size_t size = 0;
};

void testMyCircularDeque()
{
    {
        vector<string> cmds{"MyCircularDeque",
                            "insertLast", "getRear", "getFront", "insertLast", "getRear",
                            "getFront", "insertLast", "getRear", "getFront", "insertLast",
                            "insertFront", "deleteLast", "deleteFront", "getRear", "getFront",
                            "deleteFront", "getRear", "getFront"};
        vector<vector<int>> parameters{{3},
                                       {1},
                                       {},
                                       {},
                                       {2},
                                       {},
                                       {},
                                       {3},
                                       {},
                                       {},
                                       {4},
                                       {5},
                                       {},
                                       {},
                                       {},
                                       {},
                                       {},
                                       {},
                                       {}};
        vector<int> results{-1,
                            true, 1, 1, true, 2,
                            1, true, 3, 1, false,
                            false, true, true, 2, 2,
                            true, -1, -1};
        MyCircularDeque *circularDeque = new MyCircularDeque(parameters[0][0]);
        for (int i = 1; i < cmds.size(); i++)
        {
            if (cmds[i] == "insertLast")
            {
                assert(circularDeque->insertLast(parameters[i][0]) == results[i]);
            }
            else if (cmds[i] == "insertFront")
            {
                assert(circularDeque->insertFront(parameters[i][0]) == results[i]);
            }
            else if (cmds[i] == "getRear")
            {
                assert(circularDeque->getRear() == results[i]);
            }
            else if (cmds[i] == "getFront")
            {
                assert(circularDeque->getFront() == results[i]);
            }
            else if (cmds[i] == "deleteFront")
            {
                assert(circularDeque->deleteFront() == results[i]);
            }

            else if (cmds[i] == "deleteLast")
            {
                assert(circularDeque->deleteLast() == results[i]);
            }
            else if (cmds[i] == "isEmpty")
            {
                assert(circularDeque->isEmpty() == results[i]);
            }
            else if (cmds[i] == "isFull")
            {
                assert(circularDeque->isFull() == results[i]);
            }
        }
        cout << "test successfull" << endl;
    }

    {
        MyCircularDeque *circularDeque = new MyCircularDeque(3); // set the size to be 3
        assert(circularDeque->insertLast(1));                    // return true
        assert(circularDeque->insertLast(2));                    // return true
        assert(circularDeque->insertFront(3));                   // return true
        assert(!circularDeque->insertFront(4));                  // return false, the queue is full
        assert(circularDeque->getRear() == 2);                   // return 2
        assert(circularDeque->isFull());                         // return true
        assert(circularDeque->deleteLast());                     // return true
        assert(circularDeque->insertFront(4));                   // return true
        assert(circularDeque->getFront() == 4);                  // return 4
    }
}

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
// Runtime: 56 ms, faster than 36.42% of C++ online submissions for Design Circular Queue.
// Memory Usage: 16.8 MB, less than 46.43% of C++ online submissions for Design Circular Queue.

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
        if (rear == capacity)
        {
            rear = 0;
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
        if (size == 0)
        {
            front = 0;
            rear = -1;
        }
        if (front == capacity)
        {
            front = 0;
        }
        return true;
    }

    /** Get the front item from the queue. */
    int Front()
    {
        if (isEmpty())
            return -1;
        return data[front];
    }

    /** Get the last item from the queue. */
    int Rear()
    {
        if (isEmpty())
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
    cout << "circularQueue->enQueue(6)" << ((circularQueue->enQueue(6)) ? "" : " not ") << "success" << endl;

    // circularQueue->Rear();                                   // return 4
    cout << "circularQueue->Rear() " << circularQueue->Rear() << endl;
}

int main(int argc, char const *argv[])
{
    /* code */
    // testRecentCounter();
    // testCircularQueue();
    testMyCircularDeque();
    return 0;
}
