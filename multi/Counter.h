#include<atomic>
class Counter
{
private:
    std::atomic<int> cnt{0};
    std::atomic_bool  stopped{false};
public:
    Counter(/* args */)=default;
    ~Counter()=default;
    void  reset(){
        cnt.store(0);
        stopped.store(false);
    }
    void increment(){
        cnt.fetch_add(1);
    }
    void start(){
        while(!stopped.load()){
            increment();
        }
    }
    void  stop(){
        stopped.store(true);
    }
    int  get(){
        return cnt.load();
    }
};
