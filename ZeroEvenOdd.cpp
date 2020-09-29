#include <mutex>
#include <atomic>
#include <iostream>
using namespace std;

// 1116. Print Zero Even Odd
// Runtime: 48 ms, faster than 60.12% of C++ online submissions for Print Zero Even Odd.
// Memory Usage: 7.1 MB, less than 15.91% of C++ online submissions for Print Zero Even Odd.
class ZeroEvenOdd
{
private:
    int n;
    atomic<int> progress;
    mutex mutZ;
    mutex mutE;
    mutex mutO;

public:
    ZeroEvenOdd(int n)
    {
        this->n = n;
        mutZ.lock();
        mutE.lock();
        mutO.lock();
        progress = 0;
    }

    ~ZeroEvenOdd()
    {
        mutZ.unlock();
        mutE.unlock();
        mutO.unlock();
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber)
    {
        // print
        while (progress < n)
        {
            printNumber(0);
            progress++;
            if (progress % 2)
            {
                mutO.unlock();
            }
            else
            {
                mutE.unlock();
            }
            if (progress < n)
                mutZ.lock();
        }
    }

    void odd(function<void(int)> printNumber)
    {

        // if n==0, we should't lock at all, or odd thread will block here for ever
        while (progress <= n && n != 0)
        {

            mutO.lock();
            printNumber(progress);

            cout << " ";
            // quit when there is only one task remaing, as it would never  be handled by myself
            // and remember to signal zero thread to continue
            if (n - progress <= 1)
            {
                mutZ.unlock();
                break;
            }
            // before signal zero thread, should guarantee the atomic of (n-progress)
            mutZ.unlock();
        }
    }

    void even(function<void(int)> printNumber)
    {
        // if n==0 or n==1, I should never run at all , or i will block at mutE forever.
        while (progress <= n && n > 1)
        {
            mutE.lock();
            printNumber(progress);
            cout << " ";
            // quit when there is only one task remaing, as it would never  be handled by myself
            // and remember to signal zero thread to continue
            if (n - progress <= 1)
            {
                mutZ.unlock();
                break;
            }
            // before signal zero thread, should guarantee the atomic of (n-progress)
            mutZ.unlock();
        }
    }
};

void printN(int num)
{
    cout << num;
}

#include <thread>
void testZeroEvenOdd()
{
    int cases = 1000; //time cost: 7434.13 ms
    while (cases >= 0)
    {
        ZeroEvenOdd test(cases);
        thread t1(bind(&ZeroEvenOdd::zero, &test, &printN));
        thread t2(bind(&ZeroEvenOdd::odd, &test, &printN));
        thread t3(bind(&ZeroEvenOdd::even, &test, &printN));
        t1.join();
        t2.join();
        t3.join();
        cases--;
        cout << endl;
    }
}

#include <condition_variable>
// 1116. Print Zero Even Odd using Condition variable
class ZeroEvenOddC
{
private:
    int n;
    mutex mutO;
    mutex mutE;
    condition_variable ec;
    condition_variable oc;
    condition_variable zc;
    int counter = 0;
    // atomic<int> who{0};
    int who=0;

public:
    ZeroEvenOddC(int n)
    {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber)
    {
        while (counter < n)
        {
            printNumber(0);
            counter++;
            unique_lock<mutex> lck;
            if (counter % 2)
            {
                lck = unique_lock<mutex>(mutO);
                who = 1;
                oc.notify_one();
            }
            else
            {
                lck = unique_lock<mutex>(mutE);
                who = 2;
                ec.notify_one(); 
            }
            if (counter < n)
                zc.wait(lck);
        }
    }

    void odd(function<void(int)> printNumber)
    {
        int last = (n % 2) ? n : n - 1;
        while (n >= 1)
        {
            unique_lock<mutex> lck(mutO);
            if (who != 1)
                oc.wait(lck);
            // lck.unlock(); //ondition_variable wait failed: 
            printNumber(counter);
            who = 0;
            zc.notify_one();
            if (counter == last)
                break;
        }
    }

    void even(function<void(int)> printNumber)
    {
        int last = (n % 2) ? n - 1 : n;
        while (n >= 2)
        {
            unique_lock<mutex> lck(mutE);
            if (who != 2)
                ec.wait(lck);
            // lck.unlock(); //ondition_variable wait failed: 
            printNumber(counter);
            who = 0;
            zc.notify_one();
            if (counter == last){
                break;
            }
        }
    }
};

void testZeroEvenOddC()
{
    int cases = 30;//6863.16 ms
    while (cases >= 0)
    {
        ZeroEvenOddC test(cases);
        thread t1(bind(&ZeroEvenOddC::zero, &test, &printN));
        thread t2(bind(&ZeroEvenOddC::odd, &test, &printN));
        thread t3(bind(&ZeroEvenOddC::even, &test, &printN));
        t1.join();
        t2.join();
        t3.join();
        cases--;
        cout << endl;
    }
}

// 1116. Print Zero Even Odd using semphore
class ZeroEvenOddS
{
private:
    int n;

public:
    ZeroEvenOddS(int n)
    {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber)
    {
    }

    void odd(function<void(int)> printNumber)
    {
    }

    void even(function<void(int)> printNumber)
    {
    }
};

// 1116. Print Zero Even Odd using futhure
class ZeroEvenOddF
{
private:
    int n;

public:
    ZeroEvenOddF(int n)
    {
        this->n = n;
    }

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber)
    {
    }

    void odd(function<void(int)> printNumber)
    {
    }

    void even(function<void(int)> printNumber)
    {
    }
};

#include "common.h"
int main(int argc, char const *argv[])
{
    //  timeit(testZeroEvenOdd);
    timeit(testZeroEvenOddC);
    return 0;
}