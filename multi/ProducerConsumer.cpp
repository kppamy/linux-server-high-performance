#include <atomic>
#include <vector>
#include <mutex>
#include <thread>
#include <iostream>
using namespace std;

template <typename T, typename F>
class ProducerConsumer
{
private:
    vector<T> buffer;
    int capacity;
    size_t size{0};
    condition_variable cv;
    mutex mtx;

public:
    ProducerConsumer(int cap) : capacity(cap)
    {
        buffer.resize(cap);
    };
    ~ProducerConsumer(){};
    void produce(const T &val, const chrono::microseconds dur)
    {
        while (true)
        {
            unique_lock<mutex> lck(mtx);
            cv.wait_for(lck, dur, [&]() { return size < capacity; });
            if (size >= capacity)
            {
                cout << "producer timeout, quit" << endl;
                break;
            }
            buffer.emplace_back(val);
            size++;
            cv.notify_all();
        }
    };

    void produce(F fun, const chrono::microseconds dur, const chrono::microseconds interval)
    {
        while (true)
        {
            if (internal > 0)
                this_thread::sleep_for((interval));
            unique_lock<mutex> lck(mtx);
            cv.wait_for(lck, dur, [&]() { return size < capacity; });
            if (size >= capacity)
            {
                cout << "producer timeout, quit" << endl;
                break;
            }
            buffer.emplace_back(fun());
            size++;
            cv.notify_all();
        }
    };
    T &consume(const chrono::milliseconds dur, const chrono::milliseconds interval)
    {
        while (true)
        {
            if (internal > 0)
                this_thread::sleep_for(interval);
            unique_lock<mutex> lck(mtx);
            cv.wait_for(lck, dur, [&]() { return size > 0; });
            if (size <= 0)
            {
                cout << "consumer producer timeout, quit" << endl;
                break;
            }
            T &res = buffer.back();
            buffer.pop_back();
            size--;
            cv.notify_all();
            return res;
        }
    }
    int getSize()
    {
        return size;
    }
};

#include <chrono>
int main(int argc, char const *argv[])
{
    int capacity = 100;
    ProducerConsumer<chrono::steady_clock::time_point, chrono::steady_clock::time_point()> pc(capacity);
    int i = 0;
    auto add = [&]() {
        pc.produce(chrono::steady_clock::now, chrono::milliseconds(100), chrono::milliseconds(10));
    };
    auto sub = [&]() {
        chrono::steady_clock::time_point res = pc.consume(chrono::milliseconds(100), chrono::milliseconds(0));
    };

    vector<thread> producers(1);
    vector<thread> consumers(1);
    for (auto &&p : producers)
    {
        thread th(add);
        p = move(th);
    }
    for (auto &&c : consumers)
    {
        thread consumer(sub);
        c = move(consumer);
    }

    for (auto &&p : producers)
    {
        p.join();
    }
    // cout << "start to consume: " <<pc.getSize()<<endl;

    for (auto &&c : consumers)
    {
        c.join();
    }

    return 0;
}
