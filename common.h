#include <iostream>
#include <vector>
#include <time.h>
#include <limits.h>
#include <random>
#include "Timer.h"

typedef vector<vector<int>> my2arr;


void timeit(std::function<void()> func)
{
    Timer t;
    t.start();
    func();
    t.stop();
    std::cout << "time cost: " << t.miniSeconds() << " ms" << endl;
}

void printVector(std::vector<int> &input)
{

    for_each(input.begin(), input.end(), [](int i) {
        cout << i << " ";
    });
    cout << endl;
}

void printInput(int input[], int len)
{
    {
        for (int i = 0; i < len; i++)
        {
            cout << input[i] << " ";
        }
        cout << endl;
    }
}


vector<int> generateArray(int num, int max)
{
    vector<int> arr(num);

    // C random generators
    // for(int i=0;i<=num;i++){
    //     arr[i]=(rand()%max);
    // }

    // C++ 11 random generations
    //  http://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1.0, 10.0);

    for (int i = 0; i < num; ++i)
    {
        arr[i] = dist(mt);
    }
    return arr;
}