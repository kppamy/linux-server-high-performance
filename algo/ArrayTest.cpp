#include "ArrayTest.h"
#include "../common.h"

using namespace std;

// 852. Peak Index in a Mountain Array
// 16 ms, faster than 65.96%
// 11.5 MB, less than 77.90%
int peakIndexInMountainArray(vector<int> &arr)
{
    int len = arr.size();
    int left = 0, right = len - 1;
    while (left < right)
    {
        int mid = (right + left) >> 1;
        int mn = arr[mid];
        if (arr[left] > mn)
        {
            right = mid - 1;
        }
        else if (mn < arr[right])
        {
            left = mid + 1;
        }
        else
        {
            if (mid == left)
                return mid;
            left += 1;
            right -= 1;
        }
    }
    return left;
}

// 1351. Count Negative Numbers in a Sorted Matrix
// 12 ms, faster than 98.07%
// 10.9 MB, less than 10.33%
int countNegatives(vector<vector<int>> &grid)
{
    int ans = 0;
    for (auto row : grid)
    {
        reverse(row.begin(), row.end());
        ans += upper_bound(row.begin(), row.end(), -1) - row.begin(); // all right >-1
        // rev +=  lower_bound(row.begin(), row.end(), -1)-row.begin(); // all left <-1
    }
    return ans;
}

my2DCases testcountNega()
{
    return {
        {{4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}},
        {{3, 2}, {1, 0}},
        {{1, -1}, {-1, -1}},
        {{-1}}};
}

// 1732. Find the Highest Altitude
//  0 ms, faster than 100.00%
//  8.2 MB, less than 6.47%
int largestAltitude(vector<int> &gain)
{
    int len = gain.size();
    vector<int> pts(len + 1, INT_MAX);
    pts[0] = 0;
    int largest = 0;
    for (int i = 1; i <= len; ++i)
    {
        pts[i] = pts[i - 1] + gain[i - 1];
        largest = (pts[i] > largest) ? pts[i] : largest;
    }
    return largest;
}

// 561. Array Partition I
// 100 ms, faster than 70.83%
// 28.2 MB, less than 84.01%
int arrayPairSum(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int len = nums.size();
    int ans = 0;
    for (int i = 0; i < len - 1; i += 2)
    {
        ans += min(nums[i], nums[i + 1]);
    }
    return ans;
}

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
    // timeit(testMaxArea);
    format_test(countNegatives, testcountNega);
    return 0;
}
