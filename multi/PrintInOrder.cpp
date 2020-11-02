#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <functional>
#include <future>
#include <unistd.h> //for sleep
#include <iostream>

using namespace std;
class FooM
{
public:
    FooM()
    {
    }

    void first(function<void()> printFirst)
    {

        unique_lock<mutex> lck(mtx); //(4)
        // printFirst() outputs "printFirst". Do not change or remove this line.
        printFirst();
        sv = 2; //(2)
        cv.notify_one();
    }

    void second(function<void()> printSecond)
    {
        unique_lock<mutex> lck(mtx);
        while (sv != 2) // (1)
        {
            // (3)
            cv.wait(lck);
        }
        // printSecond() outputs "printSecond". Do not change or remove this line.
        printSecond();
        sv = 3;
        cv.notify_one();
    }

    void third(function<void()> printThird)
    {
        unique_lock<mutex> lck(mtx);
        while (sv != 3)
            cv.wait(lck);
        // printThird() outputs "printThird". Do not change or remove this line.
        printThird();
    }

private:
    mutex mtx;
    condition_variable cv;
    atomic<int> sv{1};
};

class FooFP
{
public:
    FooFP()
    {
    }

    void first(function<void()> printFirst)
    {

        //    sleep(1);
        // printFirst() outputs "printFirst". Do not change or remove this line.
        printFirst();
        p.set_value(2);
    }

    void second(function<void()> printSecond)
    {
        // sleep(0.5);
        int val = fu.get();
        // printSecond() outputs "printSecond". Do not change or remove this line.
        printSecond();
        p2.set_value(3);
    }

    void third(function<void()> printThird)
    {

        fu2.get();
        // printThird() outputs "printThird". Do not change or remove this line.
        printThird();
    }

private:
    promise<int> p;
    future<int> fu = p.get_future();

    promise<int> p2;
    future<int> fu2 = p2.get_future();
};

void pFirst()
{
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " 1 ";
}

void pSecond()
{
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " 2 ";
}

void pThird()
{
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " 3" << endl;
}

void pTest(function<void()> fun)
{
    fun();
}

void testPrintOrderM()
{
    auto tu = make_tuple(1, 2, 3);
    FooM fm;
    auto fun = {bind(&FooM::first, &fm, pFirst),
                bind(&FooM::second, &fm, pSecond),
                bind(&FooM::third, &fm, pThird)};

    thread th1(bind(&FooM::third, &fm, pThird));
    thread th2(bind(&FooM::second, &fm, pSecond));
    thread th3(bind(&FooM::first, &fm, pFirst));
    // function<void()> tt[1]={pThird};
    function<void(function<void()>)> tt2 = {pTest};
    // thread th4(*tt);
    // thread th5(tt2);//fail why?

    th1.join();
    th2.join();
    th3.join();
}

void testPrintOrderFP()
{
    auto tu = make_tuple(1, 2, 3);
    FooFP fm;
    thread th1(bind(&FooFP::third, &fm, pThird));
    thread th2(&FooFP::second, &fm, pSecond);
    thread th3(&FooFP::first, &fm, pFirst);

    th1.join();
    th2.join();
    th3.join();
}

#include "Semophore.h"
class FooSem
{
public:
    FooSem()
    {
    }

    void first(function<void()> printFirst)
    {

        //    sleep(1);
        // printFirst() outputs "printFirst". Do not change or remove this line.
        printFirst();
        s1.post();
    }

    void second(function<void()> printSecond)
    {
        s1.wait();
        // printSecond() outputs "printSecond". Do not change or remove this line.
        printSecond();
        s2.post();
    }

    void third(function<void()> printThird)
    {
        s2.wait();
        // printThird() outputs "printThird". Do not change or remove this line.
        printThird();
    }

private:
    Semophore s1{0};
    Semophore s2{0};
};

void testPrintInOrderSem()
{
    int n = 30;
    while (n-- > 0)
    {
        FooSem sf;
        thread t1(bind(&FooSem::first, &sf, pFirst));
        thread t2(bind(&FooSem::second, &sf, pSecond));
        thread t3(bind(&FooSem::third, &sf, pThird));
        t1.join();
        t2.join();
        t3.join();
    }
}

#include <atomic>
// 332 ms
class Foo0Lck
{
public:
    Foo0Lck()
    {
    }

    void first(function<void()> printFirst)
    {

        // printFirst() outputs "printFirst". Do not change or remove this line.
        printFirst();
        who = 2;
    }

    void second(function<void()> printSecond)
    {
        while (who != 2)
        {
            this_thread::yield();
        }
        // printSecond() outputs "printSecond". Do not change or remove this line.
        printSecond();
        who = 3;
    }

    void third(function<void()> printThird)
    {
        while (who != 3)
        {
            this_thread::yield();
        }
        // printThird() outputs "printThird". Do not change or remove this line.
        printThird();
        who = 1;
    }

private:
    atomic<int> who{1};
};

void testPrintInOrder0Lck()
{
    int n = 30;
    while (n-- > 0)
    {
        Foo0Lck sf;
        thread t1(bind(&Foo0Lck::first, &sf, pFirst));
        thread t2(bind(&Foo0Lck::second, &sf, pSecond));
        thread t3(bind(&Foo0Lck::third, &sf, pThird));
        t1.join();
        t2.join();
        t3.join();
    }
}

int main(int argc, char const *argv[])
{
    // testPrintInOrderSem();
    testPrintInOrder0Lck();
    return 0;
}
