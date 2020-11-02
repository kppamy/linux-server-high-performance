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

class FizzBuzzC
{
private:
    int n;
    int counter = 0;
    char who = 'n';
    mutex mx;
    condition_variable cv;

public:
    FizzBuzzC(int n)
    {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz)
    {
        int expect = (n / 3 * 3);
        int last = (expect % 15==0) ? (expect-3) : expect;
        while (n >= 3)
        {
            unique_lock<mutex> lk(mx);
            while(who != 'f')
                cv.wait(lk);
            printFizz();
            who = 'n';
            cv.notify_all();
            if (counter == last)
                break;
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz)
    {
        int expect=n / 5 * 5;
        int last = (expect % 15==0) ? (expect-5) : expect;
        while (n >= 5)
        {
            unique_lock<mutex> lk(mx);
            while (who != 'b')
                cv.wait(lk);
            printBuzz();
            who = 'n';
            cv.notify_all();
            if (counter == last)
                break;
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz)
    {
        int last = (n / 15 * 15);
        while (n >= 15)
        {
            unique_lock<mutex> lk(mx);
            while (who != 'o')
                cv.wait(lk);
            printFizzBuzz();
            who = 'n';
            cv.notify_all();
            if (counter == last)
                break;
        }

    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber)
    {
        while (counter < n)
        {
            unique_lock<mutex> lk(mx);
            counter++;
            if (counter % 15 == 0)
            {
                who = 'o';
            }
            else if (counter % 3 == 0)
            {
                who = 'f';
            }
            else if (counter % 5 == 0)
            {
                who = 'b';
            }
            else
            {
                printNumber(counter);
            }
            cv.notify_all();
            while (counter < n && who!='n')
                cv.wait(lk);
        }
    }
};

void testFizzBuzzC()
{
    int n = 32;
    while (n > 0)
    {
        FizzBuzzC fb(n);
        thread t1(bind(&FizzBuzzC::fizz, &fb, printFizz));
        thread t2(bind(&FizzBuzzC::buzz, &fb, printBuzz));
        thread t3(bind(&FizzBuzzC::fizzbuzz, &fb, printFizzBuzz));
        thread t4(bind(&FizzBuzzC::number, &fb, printNumber));
        t3.join();
        t1.join();
        t2.join();
        t4.join();
        // t1.detach();
        // t2.detach();
        // t3.detach();
        // t4.detach();
        cout << endl;
        n--;
    }
}

class FizzBuzzS
{
private:
    int n;

public:
    FizzBuzzS(int n)
    {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz)
    {
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz)
    {
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz)
    {
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber)
    {
    }
};

class FizzBuzzF
{
private:
    int n;

public:
    FizzBuzzF(int n)
    {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz)
    {
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz)
    {
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz)
    {
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber)
    {
    }
};

class FizzBuzz0
{
private:
    int n;

public:
    FizzBuzz0(int n)
    {
        this->n = n;
    }

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz)
    {
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz)
    {
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(function<void()> printFizzBuzz)
    {
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber)
    {
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    // testFizzBuzz();
    testFizzBuzzC();
    return 0;
}
