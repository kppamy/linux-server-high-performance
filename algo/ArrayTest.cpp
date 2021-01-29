#include "ArrayTest.h"
#include "../common.h"

using namespace std;

// 1480. Running Sum of 1d Array
//  0 ms, faster than 100.00% 
//   8.6 MB, less than 78.36%
vector<int> runningSum(vector<int> &nums)
{
    int len = nums.size();
    if (len == 1)
        return nums;
    vector<int> ans(len, INT_MIN);
    ans[0] = nums[0];
    for (int i = 1; i < len; ++i)
    {
        ans[i] = ans[i - 1] + nums[i];
    }
    return move(ans);
}

void ArrayTest::rotateArray(vector<int> &input, int k)
{
    // extra k steps
    vector<int> back;
    int len = input.size();
    for (int i = len - k; i < len; i++)
        back.push_back(input[i]);
    for (int i = len - k - 1; i >= 0; i--)
        input[i + k] = input[i];
    for (int i = 0; i < k; i++)
        input[i] = back[i];
}

void ArrayTest::rotateArraySwitch(vector<int> &input, int k)
{
    vector<int> back;
    int len = input.size();
    int tmp;
    for (int i = 0; i < k; i++)
    {
        tmp = input[len - 1];
        input.pop_back();
        input.insert(input.begin(), tmp);
    }
}

void ArrayTest::rotateRecus(vector<int> &input, int k)
{
    if (k == 1)
    {
        rotateOne(input);
    }
    else if (k > 1)
    {
        rotateArray(input, k);
        k = k - 1;
    }
}

void ArrayTest::rotateOne(vector<int> &input)
{
    int len = input.size();
    int tmp = input[len - 1];
    for (int i = len - 2; i >= 0; i--)
    {
        input[i + 1] = input[i];
    }
    tmp = input[0];
}

// 1248. Count Number of Nice Subarrays
int numberOfSubarrays(vector<int> &nums, int k)
{
    //count pre-sub
    int len = nums.size();
    if (len < k)
        return 0;
    vector<int> counter(len + 2, 0);
    int sum = 0;
    counter[0] = 1;
    int res = 0;
    for (auto val : nums)
    {
        if (val % 2)
            sum++;
        counter[sum]++;
        if (sum >= k)
            res += counter[sum - k];
    }
    return res;
}

void testNiceArray()
{
    vector<int> input{1, 1, 2, 1, 1};
    int k = 0;
    //  vector<int> input{2,4,6};
    // int k = 1;
    //  vector<int> input{2,2,2,1,2,2,1,2,2,2};
    // int k = 2;
    printVector(input);
    cout << "numberOfSubarrays:  " << numberOfSubarrays(input, k) << endl;
}

void testRotateArray()
{
    ArrayTest at;
    vector<int> prices = generateArray(10, 10);
    cout << "before rotate:" << endl;
    printVector(prices);
    int k = 5;
    cout << "after rotate " << k << " k" << endl;
    at.rotateArraySwitch(prices, k);
    printVector(prices);
}

// |     11. Container With Most Water
// |
// |     two pointers.
// |     c++: 32 ms  python: 116 ms
int maxArea(vector<int> &height)
{
    int left = 0;
    int right = height.size() - 1;
    int maxa = 0;
    auto area = [&](int i, int j) {
        return ((j - i) * min(height[i], height[j]));
    };
    while (left < right)
    {
        maxa = max(area(left, right), maxa);
        if (height[left] < height[right])
            left++;
        else
            right--;
    }
    return maxa;
}

void testMaxArea()
{
    vector<int> arr1 = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    printVector(arr1);
    cout << "max area: " << maxArea(arr1) << endl;

    arr1 = {1, 3, 2, 4};
    printVector(arr1);
    cout << "max area: " << maxArea(arr1) << endl;
}

int main(int argc, char const *argv[])
{

    // timeit(testNiceArray);
    // testNiceArray();
    timeit(testMaxArea);
    return 0;
}
