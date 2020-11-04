#include<condition_variable>
#include<mutex>
class Semophore
{
private:
    std::condition_variable cv;
    std::mutex mtx;
    int signals;
public:
    Semophore(int capacity):signals(capacity){
    }
    ~Semophore(){}
    void wait(){
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck,[&](){return signals>0;});
        signals--;
    }

    void post(){
        std::unique_lock<std::mutex> lck(mtx);
        signals++;
        cv.notify_all();
    }
   Semophore()=delete;
};

