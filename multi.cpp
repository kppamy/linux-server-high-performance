#include <functional>
#include <tuple>
#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include "common.h"

using namespace std;
class Foo
{
public:
    Foo()
    {
    }

    void first(function<void()> printFirst)
    {

        // printFirst() outputs "printFirst". Do not change or remove this line.
        printFirst();
        sv = 2;
    }

    void second(function<void()> printSecond)
    {

        while (sv != 2)
            usleep(0);
        // printSecond() outputs "printSecond". Do not change or remove this line.
        printSecond();
        sv = 3;
    }

    void third(function<void()> printThird)
    {
        while (sv != 3)
            usleep(0);
        // printThird() outputs "printThird". Do not change or remove this line.
        printThird();
    }

private:
    int sv = 0;
};

#include <semaphore.h>
class FooSEM
{
public:
    FooSEM()
    {
        sem_init(&sem, 0, 0);
        sem_init(&sem2, 0, 0);
    }

    void first(function<void()> printFirst)
    {

        // printFirst() outputs "printFirst". Do not change or remove this line.
        printFirst();
        sem_post(&sem);
    }

    void second(function<void()> printSecond)
    {

        sem_wait(&sem);
        // printSecond() outputs "printSecond". Do not change or remove this line.
        printSecond();
        sem_post(&sem2);
    }

    void third(function<void()> printThird)
    {
        sem_wait(&sem2);
        // printThird() outputs "printThird". Do not change or remove this line.
        printThird();
    }

private:
    sem_t sem;
    sem_t sem2;
};

pthread_mutex_t lock1, lock2;
pthread_cond_t cond, cond2;
void *printFirst(void *)
{
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " printFirst()" << endl;
    pthread_cond_signal(&cond);
}

void *printSecond(void *)
{
    pthread_mutex_lock(&lock1);
    pthread_cond_wait(&cond, &lock1);
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " printSecond()" << endl;
    pthread_cond_signal(&cond2);
}

void *printThird(void *)
{
    pthread_mutex_lock(&lock2);
    pthread_cond_wait(&cond2, &lock2);
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " printThird()" << endl;
}

void pFirst()
{
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " printFirst()" << endl;
}

void pSecond()
{
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " printSecond" << endl;
}

void pThird()
{
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << " printThird" << endl;
}

void *first(void *ptr)
{
    // Foo *foo = (Foo *)ptr;
    FooSEM *foo = (FooSEM *)ptr;
    foo->first(pFirst);
}

void *second(void *ptr)
{
    // Foo *foo = (Foo *)ptr;
    FooSEM *foo = (FooSEM *)ptr;
    foo->second(pSecond);
}

void *third(void *ptr)
{
    // Foo *foo = (Foo *)ptr;
    FooSEM *foo = (FooSEM *)ptr;
    foo->third(pThird);
}

// 1114. Print in Order
void testPrintInOrderModernWay()
{
    // auto tu = make_tuple(1, 3, 2);
    auto tu = make_tuple(3, 2, 1);
    // auto tu = make_tuple(1, 2, 3);
    void *(*fun[3])(void *) = {first, second, third};
    // Foo foo;
    FooSEM foo;
    pthread_t ft;
    pthread_create(&ft, nullptr, fun[get<0>(tu) - 1], (void *)&foo);
    pthread_t ft2;
    pthread_create(&ft2, nullptr, fun[get<1>(tu) - 1], (void *)&foo);
    pthread_t ft3;
    pthread_create(&ft3, nullptr, fun[get<2>(tu) - 1], (void *)&foo);

    pthread_join(ft, nullptr);
    pthread_join(ft2, nullptr);
    pthread_join(ft3, nullptr);
}

// 1114. Print in Order
void testPrintInOrder()
{
    // std::tuple<int,int,int> tu =make_tuple(1,2,3);
    // auto tu =make_tuple(1,2,3);
    auto tu = make_tuple(1, 3, 2);
    void *(*fun[3])(void *) = {printFirst, printSecond, printThird};

    pthread_mutex_init(&lock1, nullptr);
    pthread_mutex_init(&lock2, nullptr);

    pthread_cond_init(&cond, nullptr);
    pthread_cond_init(&cond2, nullptr);

    pthread_t ft;
    pthread_create(&ft, nullptr, fun[get<0>(tu) - 1], nullptr);

    pthread_t sd;
    pthread_create(&sd, nullptr, fun[get<1>(tu) - 1], nullptr);

    pthread_t td;
    pthread_create(&td, nullptr, fun[get<2>(tu) - 1], nullptr);

    pthread_join(ft, nullptr);
    pthread_join(sd, nullptr);
    pthread_join(td, nullptr);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    pthread_cond_destroy(&cond);
    pthread_cond_destroy(&cond2);
}

#include <thread>
#include <condition_variable>
#include <atomic>
#include <mutex>

class FooBar
{
private:
    condition_variable cv;
    mutex mtx;
    atomic<int> who{1};
    int n;

public:
    FooBar(int n)
    {
        this->n = n;
    }

    void foo(function<void()> printFoo)
    {

        for (int i = 0; i < n; i++)
        {

            // printFoo() outputs "foo". Do not change or remove this line.
            while (who != 1)
            {
                usleep(0.1);
            }
            unique_lock<mutex> lck(mtx);
            printFoo();
            who = 2;
            cv.notify_one();
        }
    }

    void bar(function<void()> printBar)
    {

        for (int i = 0; i < n; i++)
        {

            // printBar() outputs "bar". Do not change or remove this line.
            unique_lock<mutex> lck(mtx);
            while (who != 2)
                cv.wait(lck);
            printBar();
            who = 1;
        }
    }
};

class FooBar0Lck
{
private:
    int n;
    atomic<bool> who{true};

public:
    FooBar0Lck(int n)
    {
        this->n = n;
    }

    void foo(function<void()> printFoo)
    {

        for (int i = 0; i < n; i++)
        {

            // printFoo() outputs "foo". Do not change or remove this line.
            if (who.load(memory_order_acquire))
            {
                printFoo();
                who.store(false, memory_order_release);
            }
            else
                this_thread::yield();
        }
    }

    void bar(function<void()> printBar)
    {

        for (int i = 0; i < n; i++)
        {

            // printBar() outputs "bar". Do not change or remove this line.
            if (!who.load(memory_order_acquire))
            {
                printBar();
                who.store(true, memory_order_release);
            }
            else
                this_thread::yield();
        }
    }
};

void pFoo()
{
    cout << "Foo";
}

void pBar()
{
    // printFirst() outputs "printFirst". Do not change or remove this line.
    cout << "Bar" << endl;
}

// 1115. Print FooBar Alternately
void testPrintFooBar()
{
    FooBar fb(1000);
    cout << "sizeof mutex " << sizeof(mutex) << endl;
    cout << "sizeof condition_variable " << sizeof(condition_variable) << endl;
    cout << "sizeof atomic<int> who{1} " << sizeof(atomic<int>) << endl;
    cout << "sizeof FooBar " << sizeof(FooBar) << endl;
    thread t1(bind(&FooBar::foo, &fb, &pFoo));
    thread t2(bind(&FooBar::bar, &fb, &pBar));
    t1.join();
    t2.join();
}
// 1115. Print FooBar Alternately using pure atomic doesn't work
void testPrintFooBar0lck()
{
    FooBar0Lck fb(100000);
    cout << "sizeof mutex " << sizeof(mutex) << endl;
    cout << "sizeof condition_variable " << sizeof(condition_variable) << endl;
    cout << "sizeof atomic<int> who{1} " << sizeof(atomic<int>) << endl;
    cout << "sizeof FooBar0Lck " << sizeof(FooBar0Lck) << endl;
    thread t1(bind(&FooBar0Lck::foo, &fb, &pFoo));
    thread t2(bind(&FooBar0Lck::bar, &fb, &pBar));
    t1.join();
    t2.join();
}

void printN(int num)
{
    cout << num;
}

// 1116. Print Zero Even Odd
class ZeroEvenOdd
{
private:
    int n;
    int progress;
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
        progress=0;
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
        while (n > 0)
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
            // cout << "\n zero lock " << endl;
            mutZ.lock();
            // cout << "\n zero unlock " << endl;
        }
    }

    void odd(function<void(int)> printNumber)
    {

        // print
        while (n > 0)
        {
            // cout << "\n odd lock " << endl;
            mutO.lock();
            // cout << "\n odd unlock " << endl;
            printNumber(progress);
            cout << " ";
            n--;
            mutZ.unlock();
            if (n == 1 && (progress + 1) % 2 == 0)
            {
                break;
            }
        }
    }

    void even(function<void(int)> printNumber)
    {

        while (n > 0)
        {
            // cout << "\n even lock " << endl;
            mutE.lock();
            // cout << "\n even unlock " << endl;
            printNumber(progress);
            cout << " ";
            n--;
            mutZ.unlock();
            if (n == 1 && (progress + 1) % 2 == 1)
            {
                break;
            }
        }
    }
};

void testZeroEvenOdd()
{
    int cases = 100;
    while (cases > 0)
    {
        ZeroEvenOdd test(cases);
        thread t1(bind(&ZeroEvenOdd::zero, &test, &printN));
        thread t2(bind(&ZeroEvenOdd::odd, &test, &printN));
        thread t3(bind(&ZeroEvenOdd::even, &test, &printN));
        t1.join();
        t2.join();
        t3.join();
        cases--;
        cout<<endl;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    // testPrintInOrder();
    // timeit(testPrintInOrderModernWay);
    // timeit(testPrintFooBar);
    // timeit(testPrintFooBar0lck);
    testZeroEvenOdd();
    return 0;
}
