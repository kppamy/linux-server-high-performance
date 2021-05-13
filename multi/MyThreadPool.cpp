
#include <memory>
#include <thread>
#include <mutex>
#include <queue>
using namespace std;
class Task
{
private:
    /* data */
public:
    Task(/* args */){};
    void run(){};
    ~Task(){};
};

class MyThreadPool
{
private:
    /* data */
    static unique_ptr<MyThreadPool> pool;
    mutex mut;
    queue<Task> tasks;
    int coreNum{0};
    int capacity{0};
    condition_variable cv;
    bool stopping{false};
    atomic<int> runningThreads{0};
    atomic<int> size{0};

private:
    MyThreadPool(int coreThreadNum, int taskQueueCapacity){

    };

public:
    static unique_ptr<MyThreadPool> &getPool(int coreThreadNum, int taskQueueCapacity)
    {
        unique_lock<mutex> lck(mut);
        if (pool == nullptr)
        {
            pool = make_unique<MyThreadPool>(coreThreadNum, taskQueueCapacity);
        }
        return pool;
    }

    void execute()
    {
        while (true)
        {
            unique_lock lck(mut);
            if (tasks.empty())
            {
                cv.wait(lck);
            }
            else if (stopping)
            {
                break;
            }
            else
            {
                Task ta = move(tasks.front());
                tasks.pop();
                size--;
                ta.run();
            }
        }
    }
    void enque(Task &&task)
    {
        unique_lock<mutex> lck(mut);
        cv.wait(lck, [this]() {
            return tasks.size()< capacity;
        });

        tasks.push(move(task));
        if (runningThreads < coreNum)
        {
            thread th(execute);
            th.detach();
        }
        cv.notify_all();
    }

    auto &deque(Task task)
    {
    }

    void start()
    {
    }

    void stop()
    {
    }

    ~MyThreadPool(){

    };
    MyThreadPool() = delete;
};
