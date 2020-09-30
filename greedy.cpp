

// 1518. Water Bottles
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Water Bottles.
// Memory Usage: 6.2 MB, less than 5.68% of C++ online submissions for Water Bottles.
int numWaterBottles(int numBottles, int numExchange)
{
    int sum=numBottles;
    int begin = numBottles;
    while (begin >= numExchange)
    {
        int chg = begin / numExchange;
        int left = begin % numExchange;
        sum +=  chg;
        begin = left + chg;   
    }
    return sum;
}

#include "common.h"
void testnumWaterBottles()
{
    int numBottles = 9, numExchange = 3;
    cout << "numWaterBottles  numBottles = 9, numExchange = 3 " << numWaterBottles(numBottles, numExchange) << endl;

    numBottles = 15, numExchange = 4;
    cout << "numWaterBottles  numBottles = 15, numExchange = 4 " << numWaterBottles(numBottles, numExchange) << endl;

    numBottles = 5, numExchange = 5;
    cout << "numWaterBottles  numBottles = 5, numExchange = 5 " << numWaterBottles(numBottles, numExchange) << endl;

    numBottles = 2, numExchange = 3;
    cout << "numWaterBottles  numBottles = 2, numExchange = 3 " << numWaterBottles(numBottles, numExchange) << endl;
}

int main(int argc, char const *argv[])
{
    testnumWaterBottles();
    return 0;
}
