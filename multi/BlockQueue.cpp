
#include <atomic>
#include <queue>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <thread>
#include<cassert>
template <typename T>
class BlockQueueLockFreeSPSC
{
    using TIME_TYPE = std::chrono::milliseconds;

private:
    /* data */
    int _capacity;
    std::atomic<size_t> _size;
    std::deque<T> _data;

public:
    BlockQueueLockFreeSPSC(const int capacity) : _capacity(capacity)
    {
        _data.resize(capacity);
    };
    ~BlockQueueLockFreeSPSC() = default;

    
    void push(T &&val) noexcept
    {
        wait(_capacity);
        assert(_size<_capacity);
        // rvalue reference => move
        _data.emplace_back(std::move(val));
        _size.fetch_add(1);
    }

    T &&top()
    {
         int i = 0;
        int old = _size.load();
        do {
            assert(_size==0);
            i++;
            if (i == 100)
                std::this_thread::yield();
        }while (_size==0)
        ;
        return _data.front();
    }

    void wait(int val)
    {
        int i = 0;
        while (_size.load() == val)
        {
            assert(_size==val);
            i++;
            if (i == 100)
                std::this_thread::yield();
        };
    }
    void pop()
    {
        wait(0);
        assert(_size>0);
        _data.pop_front();
        _size.fetch_sub(1);
    }
};

template <typename T>
class BlockingQueueMPMC
{
private:
    /* data */
    int _capacity;
    size_t _size;
    std::deque<T> _data;
    std::mutex mtx;
    std::condition_variable cv;

public:
    BlockingQueueMPMC(const int capacity) : _capacity(capacity)
    {
        _data.resize(capacity);
    };
    ~BlockingQueueMPMC() = default;

    void push(const T &&val)
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [&]() { return _size < _capacity; });
        _data.push_back();
        _size++;
    }

    T &&top()
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [&]() { return _size > 0; });
        return _data.front();
    }

    void pop()
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, [&]() { return _size > 0; });
        _data.pop_front();
        _size--;
    }
};

#include<future>
void testSPSCLockFree(){
    BlockQueueLockFreeSPSC<int> lf(100);
    const int outputs=500000;
    auto produce=[&](){
        for(int i=0;i<outputs;i++){
            lf.push(std::move(i));
        }
    };

    auto consume=[&](){
        for(int i=0;i<outputs;i++){
            lf.pop();
        }
    };

    auto pf=std::async(std::launch::async,produce);
    auto cf=std::async(std::launch::async,consume);
      
}

void testSPSCLocked(){

}

#include "../common.h"
int main(int argc, char const *argv[])
{
    timeit(testSPSCLockFree);
    return 0;
}
