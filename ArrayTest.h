#include <stdio.h>
#include <vector>
using namespace std;
class ArrayTest
{
private:
    /* data */
public:
    ArrayTest(/* args */);
    int maxProfit(vector<int> &prices);
    // rotate the array by k steps
    void rotateArray(vector<int> &input, int steps);
    void rotateArraySwitch(vector<int> &input, int k);
    void rotateRecus(vector<int> &input, int steps);
    void rotateOne(vector<int> &input);
    ~ArrayTest();
};

ArrayTest::ArrayTest(/* args */)
{
}

ArrayTest::~ArrayTest()
{
}
