#include <iostream>
#include <vector>
using namespace std;

class DynamicProgramming
{
private:
    vector<int> backup;
    /* data */
public:
    DynamicProgramming(vector<int> &input);
    DynamicProgramming();
    ~DynamicProgramming();

    static int climbStairs(int stairs);
    static void shuffleArray(vector<int> &arr);
    vector<int>& resetArray();
    static int randomize(int min, int max);
    int getHammingWeight(int n);
};

DynamicProgramming::DynamicProgramming(vector<int> &input)
{
    backup = input;
}

DynamicProgramming::DynamicProgramming()
{
}

DynamicProgramming::~DynamicProgramming()
{
}
