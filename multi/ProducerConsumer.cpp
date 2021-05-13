#include <atomic>
#include <vector>
#include <mutex>
#include <thread>
#include <iostream>
#include <chrono>
#include "../common.h"
using namespace std;

// template <typename T, typename F>
class ProducerConsumer
{
private:
    // std::vector<T> buffer;
    std::vector<int> buffer;
    int capacity{0};
    int output{0};
    size_t size{0};
    std::condition_variable cv;
    std::mutex mtx;

public:
    ProducerConsumer(int op, int cap) : capacity(cap), output(op)
    {
        buffer.resize(cap);
    };
    ~ProducerConsumer(){};
    void produce()
    {
        while (true)
        {
            unique_lock<mutex> lck(mtx);
            cv.wait_for(lck, std::chrono::milliseconds(1000), [&]() { return size < capacity; });
            if (size >= capacity)
            {
                std::cout << "finsh produce products on timeout" << std::endl;
                break;
            }
            size++;
            buffer.emplace_back(output--);
            std::cout << "produce " << size << " products" << std::endl;
            cv.notify_all();
            if (output == 0)
            {
                std::cout << "finsh produce products" << std::endl;
                break;
            }
        }
    };

    void consume()
    {
        while (true)
        {
            unique_lock<mutex> lck(mtx);
            cv.wait_for(lck, std::chrono::milliseconds(1000), [&]() { return size > 0; });
            if (size <= 0)
            {
                std::cout << "finsh produce consume on timeout" << std::endl;
                break;
            }
            int res = buffer.back();
            buffer.pop_back();
            size--;
            // if (i % 1000 == 0)
            std::cout << ".... consume  products: " << res << std::endl;
            cv.notify_all();
            if (res <= 0)
            {
                std::cout << "finsh consume  products" << std::endl;
                break;
            }
        }
    }

    // void produce(int productions, F fun, const std::chrono::milliseconds dur, const std::chrono::milliseconds interval)
    // {
    //     int i = 0;
    //     while (true)
    //     {
    //         if (internal > 0)
    //             std::this_thread::sleep_for((interval));
    //         unique_lock<mutex> lck(mtx);
    //         // cv.wait_for(lck, dur, [&]() { return size < capacity; });
    //         // if (size >= capacity)
    //         // {
    //         //     std::cout << "producer timeout, quit" << std::endl;
    //         //     break;
    //         // }
    //         cv.wait(lck, [&]() { return size < capacity; });
    //         buffer.emplace_back(fun());
    //         size++;
    //         i++;
    //         if (i == productions)
    //         {
    //             std::cout << "finsh produce" << productions << " products" << std::endl;
    //             break;
    //         }
    //         cv.notify_all();
    //     }
    // };
    // T &consume(const std::chrono::milliseconds dur, const std::chrono::milliseconds interval)
    // {
    //     while (true)
    //     {
    //         if (internal > 0)
    //             std::this_thread::sleep_for(interval);
    //         unique_lock<mutex> lck(mtx);
    //         cv.wait_for(lck, dur, [&]() { return size > 0; });
    //         if (size <= 0)
    //         {
    //             std::cout << "consumer timeout, quit" << std::endl;
    //             break;
    //         }
    //         T &res = buffer.back();
    //         buffer.pop_back();
    //         size--;
    //         cv.notify_all();
    //         return res;
    //     }
    // }

    int getSize()
    {
        return size;
    }
};

#include <cassert>
#include "cocurrent.h"
class SProducerSConsumerLockFree
{
private:
    std::vector<int> buffer;
    int capacity{0};
    int output{0};
    // atomic<int> wx{0};
    int wx{0};
    // atomic<int> rx{0};
    int rx{0};
    atomic<size_t> size{0};

public:
    SProducerSConsumerLockFree(int op, int cap) : capacity(cap), output(op)
    {
        buffer.resize(cap);
    };
    SProducerSConsumerLockFree(const SProducerSConsumerLockFree &) = delete;
    void operator=(const SProducerSConsumerLockFree &) = delete;
    ~SProducerSConsumerLockFree(){};
    void produce()
    {
        int i = 0;
        while (i < output)
        {
            if (size.load(memory_order_acquire) < capacity)
            {
                buffer[wx] = i;
                wx++;
                size.fetch_add(1, memory_order_release);
                i++;
                if (wx == capacity)
                    wx = 0;
                // std::cout << "produce " << i << " products" << std::endl;
            }
            else
            {
                this_thread::yield();
            }
        }
    };

    void consume()
    {
        int j = 0;
        while (j < output)
        {
            int sz = size.load(memory_order_acquire);
            if (sz > 0)
            {
                int res = buffer[rx];
                assert(sz < output);
                rx++;
                size.fetch_sub(1, memory_order_release);
                if (rx == capacity)
                    rx = 0;
                j++;
                if (j == output)
                    std::cout << ".... consume  products: " << res << std::endl;
            }
            else
            {
                this_thread::yield();
            }
        }
    }
};

class SProducerSConsumerSpin
{
private:
    std::vector<int> buffer;
    int capacity{0};
    int output{0};
    // SpinLockCAS lck;
    SpinLockTAS lck; //486.814 ms
    // std::mutex lck;  //4993.43 ms
    std::atomic<int> size{0};

public:
    SProducerSConsumerSpin(int op, int cap) : capacity(cap), output(op)
    {
        buffer.resize(cap);
    };
    SProducerSConsumerSpin(const SProducerSConsumerSpin &) = delete;
    void operator=(const SProducerSConsumerSpin &) = delete;
    ~SProducerSConsumerSpin(){};
    void produce()
    {
        int i = 0;
        while (i < output)
        {
            lck.lock();
            if (size.load(std::memory_order_acquire) < capacity)
            {
                buffer[size] = i;
                size.fetch_add(1, memory_order_release);
                i++;
                // std::cout << "produce " << i << " products" << std::endl;
            }
            else
            {
                assert(size >= capacity);
            }
            lck.unlock();
        }
    };

    void consume()
    {
        int j = 0;
        while (j < output)
        {
            lck.lock();
            if (size.load(std::memory_order_release) > 0)
            {
                assert(size > 0);
                int res = buffer[size - 1];
                size.fetch_sub(1, std::memory_order_release);
                j++;
                if (j == output)
                    std::cout << ".... consume  products: " << res << std::endl;
            }
            else
            {
                assert(size <= 0);
            }
            lck.unlock();
        }
    }
};

void testSPSCLockFreeSpin()
{
    int capacity = 100;
    SProducerSConsumerSpin pc(500000, capacity);
    std::thread p(&SProducerSConsumerSpin::produce, &pc);
    std::thread c(&SProducerSConsumerSpin::consume, &pc);
    p.join();
    c.join();
}

int testMPMC(int argc, char const *argv[])
{
    int capacity = 100;
    ProducerConsumer pc(500000, capacity);
    auto add = [&]() {
        pc.produce();
    };
    auto sub = [&]() {
        pc.consume();
    };

    auto testPC = [&](int M, int N) {
        std::vector<std::thread> producers(M);
        std::vector<std::thread> consumers(N);
        for (auto &&p : producers)
        {
            std::thread th(add);
            p = move(th);
        }
        for (auto &&c : consumers)
        {
            std::thread consumer(sub);
            c = move(consumer);
        }

        for (auto &&p : producers)
        {
            p.join();
        }
        // std::cout << "start to consume: " <<pc.getSize()<<std::endl;

        for (auto &&c : consumers)
        {
            c.join();
        }
    };
    // timeit(testPC,1,1);//10700.9 ms
    double t(0);
    // t=timeit(testPC,2,1);//15817.8 ms, 15751.6 ms
    // t=timeit(testPC,2,2);//10560 ms
    t = timeit(testPC, 4, 4); //10615.7 ms

    return 0;
}

#include "readerwriterqueue.h"
void testSPSCTextBook()
{
    using namespace moodycamel;

    ReaderWriterQueue<int> q(100);
    const int OUTPUTS = 500000;
    int i = OUTPUTS, j = OUTPUTS;
    std::thread p([&]() {
        while (i > 0)
        {
            q.enqueue(i);
            // q.enqueue(std::chrono::steady_clock::now().time_since_epoch().count());
            i--;
            // std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        }
    });

    std::thread c([&]() {
        while (j > 0)
        {
            std::cout << "consume: " << *(q.peek()) << std::endl;
            q.pop();
            j--;
            // if (j == 0)
            //     std::cout << "consume: " << *(q.peek())<< std::endl;
            // std::this_thread::sleep_for(std::chrono::nanoseconds(1000));
        }
    });
    p.join();
    c.join();
}

#include "concurrentqueue.h"
// https://zhuanlan.zhihu.com/p/55583561
void testMPMCLockFree()
{
    using namespace moodycamel;
    ConcurrentQueue<int> q(100);
    std::thread threads[20];
    // Producers
    for (int i = 0; i != 5; ++i)
    {
        threads[i] = std::thread([&](int i) {
            for (int j = 0; j != 10000 * 5; ++j)
            {
                q.enqueue(i * 10 + j);
                std::this_thread::sleep_for(std::chrono::nanoseconds(1000)); //10064.6 ms
            }
        },
                                 i);
    }

    // Consumers
    for (int i = 5; i != 10; ++i)
    {
        threads[i] = std::thread([&]() {
            int item;
            for (int j = 0; j != 10000 * 5; ++j)
            {
                if (q.try_dequeue(item))
                {
                    std::cout << item << std::endl;
                }
                std::this_thread::sleep_for(std::chrono::nanoseconds(1000)); //10064.6 ms, no sleep slowerrrrrrrrrrrr: 12178.5 ms
            }
        });
    }

    // Wait for all threads
    for (int i = 0; i != 10; ++i)
    {
        threads[i].join();
    }
}

void testSPSCLockFreeMy()
{
    int capacity = 100;
    SProducerSConsumerLockFree pc(500000, capacity);
    std::thread p(&SProducerSConsumerLockFree::produce, &pc);
    std::thread c(&SProducerSConsumerLockFree::consume, &pc);
    p.join();
    c.join();
}

#include<shared_mutex>

class SProducerMConsumer
{
private:
    std::vector<int> buffer;
    int capacity{0};
    int output{0};
    // ReadWriteLock lck;
    std::shared_mutex stx;
    std::atomic<int> size{0};
    std::scoped_lock slck;

public:
    SProducerMConsumer(int op, int cap) : capacity(cap), output(op)
    {
        buffer.resize(cap);
    };
    SProducerMConsumer(const SProducerMConsumer &) = delete;
    void operator=(const SProducerMConsumer &) = delete;
    ~SProducerMConsumer(){};
    void produce()
    {
        int i = 0;
        auto start = chrono::system_clock::now();
        while (i < output)
        {
            // lck.lockWrite();
            std::unique_lock<std::shared_mutex> wlck(stx);
            if (size.load(std::memory_order_acquire) < capacity)
            {
                buffer[size] = i;
                size.fetch_add(1, memory_order_release);
                i++;
                if (i % 10000 == 0)
                    Log::info("produce ", i, " products");
                // std::cout << "produce " << i << " products" << std::endl;
            }
            else
            {
                assert(size >= capacity);
                this_thread::yield();
                // size.store(0, memory_order_acquire);

            }
            // lck.unlockWrite();
        }
        auto end = chrono::system_clock::now();
        Log::info(this_thread::get_id(), "Writer consumes " + std::to_string((end - start).count() / 1000) + " ms");
    };

    void consume()
    {
        int j = 0;
        auto start = chrono::system_clock::now();
        while (j < output)
        {
            // lck.lockRead();
            std::shared_lock<std::shared_mutex> rlck(stx);
            int rx=size.load(std::memory_order_release) - 1;
            if ( rx >= 0)
            {
                assert(size > 0);
                int res = buffer[rx];
                size --;
                j++;
                if (j % 10000 == 0)
                {
                    Log::info(".... consume  products: ", res);
                }
            }
            else
            {
                assert(size <= 0);
                this_thread::yield();
            }
            // lck.unlockRead();
        }
        auto end = chrono::system_clock::now();
        Log::info(this_thread::get_id(), "Reader consumes " + std::to_string((end - start).count() / 1000) + " ms");
    }
};

void testReadWriteLock()
{
    int capacity = 100;
    SProducerMConsumer pc(500000, capacity);
    auto add = [&]() {
        pc.produce();/k.nkl,. l]hhl=]-\- -b v n ,};
    auto sub = [&]() {
        pc.consume();
    };

    auto testPC = [&](int M, int N) {
        std::vector<std::thread> producers(M);
        std::vector<std::thread> consumers(N);
        for (auto &&p : producers)
        {
            std::thread th(add);
            p = move(th);
        }
        for (auto &&c : consumers)
        {
            std::thread consumer(sub);
            c = move(consumer);
        }

        for (auto &&p : producers)
        {
            p.join();
        }
        // std::cout << "start to consume: " <<pc.getSize()<<std::endl;

        for (auto &&c : consumers)
        {
            c.join();
        }
    };
    // timeit(testPC,2,2);
    testPC(2, 2);
}

int main(int argc, char const *argv[])
{
    double summary(0.0);
    int times = 20;
    int i = 0;
    while (i < times)
    {
        // timeit(testSPSCTextBook);//1326.73 ms
        // timeit(testMPMCLockFree); // 12178.5 ms, 5 producers, 5 consumers
        // summary += timeit(testSPSCTextBook); // averag time cost: 122.192ms
        // summary += timeit(testSPSCLockFreeMy); //averag time cost: 169.619ms? , 6242.29 ms(seq_cst+yield), 6476.18ms (seq_cst+busy wait), 6887.83ms(acquire_release+yield)
        // summary += timeit(testSPSCLockFreeSpin); //averag time cost: 178.081 ms, 178.538 ms, standard mutex 4993.43 ms
        summary += timeit(testReadWriteLock);
        i++;
        std::cout << "averag time cost: " << summary / i << std::endl; //
    }
    std::cout << "averag time cost: " << summary / times << std::endl;
    return 0;
}