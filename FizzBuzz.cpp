#include <functional>
#include <thread>
#include <mutex>
#include <iostream>
#include <atomic>
using namespace std;

// 1195. Fizz Buzz Multithreaded
// Runtime: 24 ms, faster than 79.74% of C++ online submissions for Fizz Buzz Multithreaded.
// Memory Usage: 7.1 MB, less than 6.57% of C++ online submissions for Fizz Buzz Multithreaded.

class FizzBuzz
{
private:
    int n;
    mutex fz;
    mutex bz;
    mutex fb;
    mutex num;
    int counter = 1;

public:
    FizzBuzz(int n)
    {
        this->n = n;
        fz.lock();
        bz.lock();
        fb.lock();
        num.lock();
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz)
    {
        int last = (n / 3) * 3;
        if (last % 15 == 0)
        {
            last = last - 3;
        }
        while (n >= 3)
        {
            fz.lock();
            printFizz();

            if (counter >= last)
            {
                num.unlock();
                break;
            }
            num.unlock();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz)
    {
        int last = (n / 5) * 5;
        if (last % 15 == 0)
        {
            last = last - 5;
        }
        while (n >= 5)
        {
            bz.lock();
            printBuzz();
            if (counter >= last)
            {
                num.unlock();
                break;
            }
            num.unlock();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz)
    {
        while (n >= 15)
        {
            fb.lock();
            printFizzBuzz();
            if (n - counter < 15)
            {
                num.unlock();
                break;
            }
            num.unlock();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber)
    {
        while (counter <= n)
        {
            if (counter % 3 == 0 && counter % 5 == 0)
            {
                // fizzbuzz
                fb.unlock();
                num.lock();
            }
            else if (counter % 3 == 0)
            {
                // fizz
                fz.unlock();
                num.lock();
            }
            else if (counter % 5 == 0)
            {
                // buz
                bz.unlock();
                num.lock();
            }
            else
            {
                printNumber(counter);
            }
            counter++;
        }
    }
};

void printNumber(int n)
{
    cout << n << ", ";
}

void printFizz()
{
    cout << "fizz, ";
}

void printBuzz()
{
    cout << "Buzz, ";
}

void printFizzBuzz()
{
    cout << "FizzBuzz, ";
}

void testFizzBuzz()
{
    int n = 32;
    while (n > 0)
    {
        FizzBuzz fb(n);
        thread t1(bind(&FizzBuzz::fizz, &fb, printFizz));
        thread t2(bind(&FizzBuzz::buzz, &fb, printBuzz));
        thread t3(bind(&FizzBuzz::fizzbuzz, &fb, printFizzBuzz));
        thread t4(bind(&FizzBuzz::number, &fb, printNumber));
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        cout << endl;
        n--;
    }
}

int main(int argc, char const *argv[])
{
    /* code */
    testFizzBuzz();
    return 0;
}
