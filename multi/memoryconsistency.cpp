// #include<memory>
// #include<atomic>
#include<assert.h>
#include<thread>

using namespace std;
bool flag=false;
int  x=0;
void test_store(){
    x=1;
    // std::atomic_thread_fence(std::memory_order_release);
    __ATOMIC_RELEASE;
    flag=true;
}

void test_load(){
    while (!flag);
    // std::atomic_thread_fence(std::memory_order_acquire);
    __ATOMIC_ACQUIRE;
    assert(x==1);
}

#include<unistd.h>
int main(int argc, char const *argv[])
{
    while (true)
    {
        thread t1(test_store);
        thread t2(test_load);
        t1.join();
        t2.join();
        // usleep(100);
    }
    return 0;
}


