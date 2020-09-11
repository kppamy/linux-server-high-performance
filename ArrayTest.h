#include <vector>
class ArrayTest
{
private:
    /* data */
public:
    ArrayTest(/* args */){};
    // rotate the array by k steps
    void rotateArray(std::vector<int> &input, int steps);
    void rotateArraySwitch(std::vector<int> &input, int k);
    void rotateRecus(std::vector<int> &input, int steps);
    void rotateOne(std::vector<int> &input);
    ~ArrayTest(){};
};
