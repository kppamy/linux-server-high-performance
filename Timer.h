#ifndef _TIMER_H_
#define _TIMER_H_

#include<time.h>
#include <iostream>
class Timer
{
private:
    /* data */
    long sta;
    int end;
public:
    Timer(/* args */):sta(0),end(0){}
    ~Timer(){};
    void start(){
            sta = clock();
    };
    void stop(){
        end=clock();
    };
    double miniSeconds(){
     double elaps = ((static_cast<float>(end - sta)) / CLOCKS_PER_SEC)*1000;
    return elaps ;
    };
};
#endif
