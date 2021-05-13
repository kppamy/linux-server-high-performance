// https://zhuanlan.zhihu.com/p/48157076
int a = 0;
int b = 0
// a, b init to 0.
{
    a = 1;
    b = a + 1;
    assert(b == 2);
}

// thread A running on Core1
void foo(void)
{
    a = 1; // in Core1's Storebuffer
    b = 1; // in Core1's L1 cache
}
​
    // thread B running on Core2, before core1's storebuffer flush
    void
    bar(void)
{
    while (b == 0)
        continue;
    assert(a == 1);
}

// thread A running on Core1
void foo(void)
{
    a = 1; // in Core1's Storebuffer
    // memory barrier ensure to flush all data in storebuffer into L1 cache,
    //   then core's L1 cache will inform other cores
    smp_mb(); // full  emory_barrier
    b = 1;    // in Core1's L1 cache
}

// thread B running on Core2, before core1's storebuffer flush
void bar(void)
{
    while (b == 0)
        continue;
    // if a=1 is in the Core2's invalidateMsgQue, not in the cache yet, but b=1 is already in the
    // cache line
    // memory_barrier here could flush both invalidateMsgQue and storebuffer
    smp_mb(); // full  emory_barrier
    assert(a == 1);
}

{
    atomic<bool> f = false;
    atomic<bool> g = false;
    int n;
    ​
        // thread1
        n = 42;                          // op6
    f.store(true, memory_order_release); // op1
    ​
        // thread2
        while (!f.load(memory_order_acquire)); // op2
    g.store(true, memory_order_release);       // op3
    ​
        // thread3
        while (!g.load(memory_order_acquire)); // op4
    assert(42 == n);                           // op5 always success
}

// thread 1 and thread 2 could enter the critical section
// at the same time as  f1 and f2 are 2 different memory locations
//
{
    atomic<bool> f1 = false;
    atomic<bool> f2 = false;
    ​
        // thread1
        f1.store(true, memory_order_release);
    if (!f2.load(memory_order_acquire))
    {
        // critical section
    }
    // f1.store(true, memory_order_release);
    ​
        // thread2
        f2.store(true, memory_order_release);
    if (!f1.load(memory_order_acquire))
    {
        // critical section
    }
    // f2.store(true, memory_order_release);
}

{
    // relaxed order允序单线程上不同的memory location进行reorder，但是对于同一个memory location不能进行reorder。
    // assert could fail
    atomic<bool> f = false;
    atomic<bool> g = false;
    ​
        // thread1
        f.store(true, memory_order_relaxed);
    g.store(true, memory_order_relaxed);
    ​
        // thread2
        while (!g.load(memory_order_relaxed));
    assert(f.load(memory_order_relaxed));
}

{
    // std::memory_order_relaxed, could work, as thread1 and the main thread use the
    // same location
    // thread1
    void process(){
        while (!stop.load(std::memory_order_relaxed)){}}
    // main
    int main(){
        thread t(process);
stop.store(true, std::memory_order_release);
t.join();
return 0;
}
}

{
    //  单线程，一定是 happens-before：
    // a=42 happens before b=42
    int a, b;

    void foo()
    {
        a = 42;
        b = a;
        assert(b == 42);
    }
}

{
    //  (4)在relax order下可能会失败
    //  但是X86上由于默认的 memory_order_seq_cst 约束，也不会失败
    int data;
    std::atomic_bool flag{false};

    // Execute in thread A
    void producer()
    {
        data = 42;        // (1)
        flag.store(true); // (2)
    }

    // Execute in thread B
    void consume()
    {
        while (!flag.load())
            ;               // (3)
        assert(data == 42); // (4)
    }
}

{
    // (4) will never fail on any machine.
    int data;
    std::atomic_bool flag{false};

    // Execute in thread A
    void producer()
    {
        data = 42;                                   // (1)
        flag.store(true, std::memory_order_release); // (2)
    }

    // Execute in thread B
    void consume()
    {
        while (!flag.load(std::memory_order_acquire))
            ;               // (3)
        assert(data == 42); // (4)
    }
}

struct spinlock
{
    void lock()
    {
        bool expected = false;
        while (!state.compare_exchange_weak(
            expected, true, std::memory_order_acquire, std::memory_order_relaxed))
        {
            expected = false;
        }
    }

    void unlock()
    {
        state.store(false, std::memory_order_release);
    }

private:
    std::atomic_bool state;
};

// https://zhuanlan.zhihu.com/p/24983412

template <typename _Ty>
struct LockFreeStackT
{
    struct Node
    {
        _Ty val;
        Node *next;
    };
    LockFreeStackT() : head_(nullptr) {}
    void push(const _Ty &val)
    {
        Node *node = new Node{val, head_.load()};
        while (!head_.compare_exchange_strong(node->next, node))
        {
        }
    }
    void pop()
    {
        Node *node = head_.load();
    while (node && !head_.compare_exchange_strong(node, node->next) {
    }
    if (node) delete node;
    }
    std::atomic<Node *> head_;
};