#include <functional>
#include <tuple>
#include <pthread.h>
#include <iostream>
using namespace std;
class Foo {
public:
    Foo() {
        
    }

    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
 
        printSecond();
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }


};
    pthread_mutex_t lock1,lock2;
    pthread_cond_t cond,cond2;
    void* first(void *) {
        // printFirst() outputs "first". Do not change or remove this line.
        cout<<" printFirst()"<<endl;
        pthread_cond_signal(&cond);
    }

    void* second(void *) {
                pthread_mutex_lock(&lock1);
        pthread_cond_wait(&cond,&lock1);
        // printFirst() outputs "first". Do not change or remove this line.
        cout<<" printSecond()"<<endl;
        pthread_cond_signal(&cond2);
    }

    void* third(void *) {
        pthread_mutex_lock(&lock2);
        pthread_cond_wait(&cond2,&lock2);
        // printFirst() outputs "first". Do not change or remove this line.
        cout<<" printThird()"<<endl;
    }



    // 1114. Print in Order
void testPrintInOrder(){
    // std::tuple<int,int,int> tu =make_tuple(1,2,3);
    // auto tu =make_tuple(1,2,3);
    auto tu = make_tuple(1, 3, 2);
    void *(*fun[3])(void *) = {first, second, third};

    pthread_mutex_init(&lock1, nullptr);
    pthread_mutex_init(&lock2, nullptr);

    pthread_cond_init(&cond, nullptr);
    pthread_cond_init(&cond2, nullptr);

    pthread_t ft;
    pthread_create(&ft, nullptr, fun[get<0>(tu) - 1], nullptr);

    pthread_t sd;
    pthread_create(&sd, nullptr, fun[get<1>(tu) - 1], nullptr);

    pthread_t td;
    pthread_create(&td, nullptr, fun[get<2>(tu) - 1], nullptr);

    pthread_join(ft, nullptr);
    pthread_join(sd, nullptr);
    pthread_join(td, nullptr);

    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);

    pthread_cond_destroy(&cond);
    pthread_cond_destroy(&cond2);
}

int main(int argc, char const *argv[])
{
    /* code */
    testPrintInOrder();
    
    return 0;
}
