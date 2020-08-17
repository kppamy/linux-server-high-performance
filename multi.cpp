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
        who = 2;
    }

    void second(function<void()> printSecond)
    {

        while(who!=2)
            usleep(0);
        // printSecond() outputs "printSecond". Do not change or remove this line.
        printSecond();
        who=3;
    }

    void third(function<void()> printThird)
    {
        while(who!=3)
            usleep(0);
        // printThird() outputs "printThird". Do not change or remove this line.
        printThird();
    }

private:
    int who=0;
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
    Foo *foo = (Foo *)ptr;
    foo->first(pFirst);
}

void *second(void *ptr)
{
    Foo *foo = (Foo *)ptr;
    foo->second(pSecond);
}

void *third(void *ptr)
{
    Foo *foo = (Foo *)ptr;
    foo->third(pThird);
}

// 1114. Print in Order
void testPrintInOrderModernWay()
{
    // auto tu = make_tuple(1, 3, 2);
    // auto tu = make_tuple(3, 2, 1);
    auto tu = make_tuple(1, 2, 3);
    void *(*fun[3])(void *) = {first, second, third};
    Foo foo;
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

int main(int argc, char const *argv[])
{
    /* code */
    // testPrintInOrder();
    timeit(testPrintInOrderModernWay);
    return 0;
}
