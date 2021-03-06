#include "../common.h"
#include "DynamicProgramming.h"
#include <math.h>
#include "../Timer.h"

// 62. Unique Paths
//  0 ms, faster than 100.00%
//  6.4 MB, less than 37.91%
int uniquePaths(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        dp[0][i] = 1;
    }
    for (int i = 0; i < m; i++)
    {
        dp[i][0] = 1;
    }

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

// 64. Minimum Path Sum
// 12 ms, faster than 66.01%
// 10.2 MB, less than 35.67%
int minPathSum(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, 0));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < n; i++)
    {
        dp[0][i] = dp[0][i - 1] + grid[0][i];
    }

    for (int i = 1; i < m; i++)
    {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {

            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }
    return dp[m - 1][n - 1];
}

// 1140. Stone Game II
int stoneGameII(vector<int> &piles)
{
}

// 877. Stone Game
//  20 ms, faster than 40.86%
// 16.5 MB, less than 26.66%
bool stoneGame(vector<int> &piles)
{
    int len = piles.size();
    vector<vector<int>> dp(len, vector<int>(len, 0));
    for (int i = 0; i < len; i++)
    {
        dp[i][i] = -piles[i];
        for (int j = i + 1; j < len; j++)
        {
            int left = dp[i + 1][j];
            int right = dp[i][j - 1];
            if ((j - i + 1) % 2)
            {
                int ls = left - piles[i];
                int rt = right - piles[j];
                dp[i][j] = (ls < rt) ? ls : rt;
            }
            else
            {
                int ls = left + piles[i];
                int rt = right + piles[j];
                dp[i][j] = (ls > rt) ? ls : rt;
            }
        }
    }
    return dp[0][len - 1] > 0;
}

int fnext(vector<int> &piles, vector<vector<int>> &dp, int i, int j)
{
    if (i > j)
    {
        dp[i][j] = 0;
        return 0;
    }
    if (i == j)
    {
        dp[i][j] = -piles[i];
        return -piles[i];
    }
    // cout << "i: " << i << " j: " << j << endl;
    int lsub = dp[i + 1][j];
    if (lsub == INT_MIN)
        lsub = fnext(piles, dp, i + 1, j);
    int rsub = dp[i][j - 1];
    if (rsub == INT_MIN)
        rsub = fnext(piles, dp, i, j - 1);
    int scores = 0;
    if ((j - i + 1) % 2)
    {
        int left = lsub - piles[i];
        int right = rsub - piles[j];
        if (left < right)
        {
            scores = left;
        }
        else
        {
            scores = right;
        }
    }
    else
    {
        int left = lsub + piles[i];
        int right = rsub + piles[j];
        if (left > right)
        {
            scores = left;
        }
        else
        {
            scores = right;
        }
    }
    dp[i][j] = scores;
    return scores;
}

bool stoneGameRec(vector<int> &piles)
{
    int i = 0, len = piles.size(), j = len - 1;
    vector<vector<int>> dp(len, vector<int>(len, INT_MIN));
    return fnext(piles, dp, 0, j) > 0;
}

my2arr testStoneGame()
{
    return {
        {5, 3, 4, 5},
        {7, 7, 12, 16, 41, 48, 41, 48, 11, 9, 34, 2, 44, 30, 27, 12, 11, 39, 31, 8, 23, 11, 47, 25, 15, 23, 4, 17, 11, 50, 16, 50, 38, 34, 48, 27, 16, 24, 22, 48, 50, 10, 26, 27, 9, 43, 13, 42, 46, 24},
        {5, 4, 3, 5}};
}

// 303. Range Sum Query - Immutable
//  24 ms, faster than 87.39%
// 17.2 MB, less than 78.93%
class NumArray
{
public:
    NumArray(vector<int> &nums)
    {
        int len = nums.size();
        dp.resize(len, 0);
        dp[0] = nums[0];
        for (int i = 1; i < len; ++i)
        {
            dp[i] = dp[i - 1] + nums[i];
        }
    }

    int sumRange(int i, int j)
    {
        return dp[j] - dp[i];
    }

private:
    vector<int> dp;
};

// 53. Maximum Subarray
// 4 ms, faster than 97.71%
// 13.2 MB, less than 82.91%
int maxSubArray(vector<int> &nums)
{
    int len = nums.size();
    int ans = INT_MIN;
    int prev = 0;
    for (int i = 0; i < len; ++i)
    {
        int nt = prev + nums[i];
        prev = (nt > nums[i]) ? nt : nums[i];
        ans = (ans > prev) ? ans : prev;
    }
    return ans;
}

my2arr testmaxSubArray()
{
    return {
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},
        {-1},
        {1},
        {-100000},
        {-2, -2, -2},
    };
}

// 1025. Divisor Game
// 0 ms, faster than 100.00%
// 5.9 MB, less than 88.24%
bool divisorGame(int N)
{
    vector<bool> dp(N + 1, false);
    for (int i = 2; i < N + 1; ++i)
    {
        for (int x = 1; x < i; ++x)
        {
            if (i % x == 0 && !dp[i - x])
            {
                dp[i] = true;
            }
        }
    }
    return dp[N];
}

void testdivisorGame()
{
    cout << "divisorGame 2, alice win? " << divisorGame(2) << endl;
    cout << "divisorGame 3, alice win? " << divisorGame(3) << endl;
    cout << "divisorGame 4, alice win? " << divisorGame(4) << endl;
    cout << "divisorGame 5, alice win? " << divisorGame(5) << endl;
    cout << "divisorGame 1000, alice win? " << divisorGame(1000) << endl;
}

int DynamicProgramming::climbStairs(int stairs)
{
    if (stairs == 1)
        return 1;
    else if (stairs == 2)
        return 2;
    return climbStairs(stairs - 1) + climbStairs(stairs - 2);
}

// 70. Climbing Stairs
int climbStairs(int n)
{
    if (n == 1)
        return 1;
    else if (n == 2)
        return 2;
    vector<int> dp(n + 1, 0);

    dp[1] = 1;
    dp[2] = 2;
    for (int i = 3; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

void testClimbStairs()
{
    int n = 1;
    while (n <= 45)
    {
        cout << "ways to climbStairs " << n << " is " << climbStairs(n) << endl;
        n++;
    }
}

// 746. Min Cost Climbing Stairs
//  8 ms, faster than 82.51%
// 13.7 MB, less than 93.69%
int minCostClimbingStairs(vector<int> &cost)
{
    int len = cost.size();
    // vector<int> dp(len + 1,0);
    int dp0 = 0;
    int dp1 = 0;
    int dp2 = 0;
    for (int i = 1; i < len; i++)
    {
        // dp[i + 1] = min(dp[i - 1] + cost[i - 1], dp[i] + cost[i]);
        dp2 = min(dp0 + cost[i - 1], dp1 + cost[i]);
        dp0 = dp1;
        dp1 = dp2;
    }
    // return dp[len];
    return dp2;
}

vector<vector<int>> testminCostClimbingStairs()
{
    return {
        {10, 15, 20},
        {1, 100, 1, 1, 1, 100, 1, 1, 100, 1}};
}

// 198. House Robber
// 4 ms, faster than 46.28% o
// 7.9 MB, less than 97.27%
int rob(vector<int> &nums)
{
    int len = nums.size();
    int dp0 = 0, dp1 = 0, dp2 = 0;
    for (int i = 0; i < len; i++)
    {
        dp2 = (dp0 + nums[i]) >= dp1 ? (dp0 + nums[i]) : dp1;
        dp0 = dp1;
        dp1 = dp2;
    }
    return dp2;
}

my2arr testrob()
{
    return {
        {},
        {1, 2, 3, 1},
        {2, 7, 9, 3, 1}};
}

// 413. Arithmetic Slices
// 0 ms, faster than 100.00%
//  7.7 MB, less than 63.12%
int numberOfArithmeticSlices(vector<int> &A)
{
    int len = A.size();
    if (len < 3)
        return 0;
    int dp0 = 0, dp1 = 0, dp2 = 0;
    for (int i = 2; i < len; i++)
    {
        // no i: dp1, has i--> has i-1 also, has i-1= (has i-1) - (has i-2)
        dp2 = (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) ? (dp1 + 1 + dp1 - dp0) : dp1;
        dp0 = dp1;
        dp1 = dp2;
    }
    return dp2;
}

my2arr testnumberOfArithmeticSlices()
{
    return {
        {1, 2, 3, 8, 9, 10},
        {1, 2, 3, 4},
        {1, 3, 5, 7, 9},
        {1, 3, 5, 7, 9, 11},
        {7, 7, 7, 7},
        {3, -1, -5, -9},
        {1, 1, 2, 5, 7}};
}
void DynamicProgramming::shuffleArray(vector<int> &arr)
{
    int sz = arr.size();
    for (int i = 0; i < sz; i++)
    {
        int swap = randomize(i, sz);
        int tmp = arr[i];
        arr[i] = arr[swap];
        arr[swap] = tmp;
    }
    printVector(arr);
}

vector<int> &DynamicProgramming::resetArray()
{
    return backup;
}

int DynamicProgramming::randomize(int min, int max)
{
    return (rand() % (max - min) + min);
}

int DynamicProgramming::getHammingWeight(int n)
{
    if (n == 0)
        return 0;
    int left = n;
    int count = 0;
    while (left > 0)
    {
        count++;
        left = left - pow(2, floor(log2(left)));
    }
    return count;
}

// knapsack problems
bool canPartition(vector<int> &nums)
{
    return false;
}

// knapsack problems
// 322. Coin Change
int coinChange(vector<int> &coins, int amount)
{
    return 0;
}

// 面试题 08.11. 硬币
int waysToChange(int n)
{
    if (n <= 1)
        return n;
    static int mod = 1000000007;
    static int coins[4] = {25, 10, 5, 1}; //i
    vector<int> res(n + 1, 0);            // res[j] 前i-1 个硬币组成j的方案数, res[0,...,j-1] 表示前i个硬币组成j的方案数
    res[0] = 1;
    for (int i = 0; i <= 3; i++)
    {
        int j;
        for (j = coins[i]; j <= n; j++)
        {
            res[j] = (res[j] + res[j - coins[i]]) % mod;
        }
    }

    return res[n];
}

// 392. 判断子序列
bool isSubsequence(string s, string t)
{
    int m = s.size();
    int n = t.size();
    if (m > n)
        return false;
    // f[i][j] 表示s.sub(0,i) 是t.sub(0,j)的子串
    vector<vector<bool>> f(m, vector<bool>(n, false));
    f[0][0] = 1;
    f[1][0] = 0;
    f[0][1] = 1;

    for (int i = 1; i < m; i++)
    {
        for (int j = i; j < n - m + i + 1; j++)
        {
            if (s[i] == t[j])
            {
                f[i][j] = f[i - 1][j - 1];
            }
            else
            {
                f[i][j] = f[i][j - 1];
            }
        }
    }
    return f[m - 1][n - 1];
}

// 392. 判断子序列
bool isSubsequence(string s, string t, bool two_pointer)
{
    int m = s.size();
    int n = t.size();
    if (m > n)
        return false;
    int i = 0, j = 0;
    while (i < m && j < n)
    {
        if (s[i] == t[j])
        {
            i++;
        }
        j++;
    }
    return i == m;
}

void testwaysToChange()
{
    cout << " ways to change 5  is " << waysToChange(5) << endl;  // 2
    cout << " ways to change 10 is " << waysToChange(10) << endl; // 4
    cout << " ways to change 1 is " << waysToChange(1) << endl;   // 4
}

void testSubSequence()
{
    string s = "abc", t = "ahbgdc";
    // string s = "axc", t = "ahbgdc";
    // string s = "axc", t = "axc";
    cout << s << " is " << (isSubsequence(s, t, true) ? "" : " not ") << "subsequence of " << t << endl;
}

// knapsack problems
// 494. Target Sum
int findTargetSumWays(vector<int> &nums, int S)
{
    int MAX = 0;
    int len = nums.size();
    for (int i = 0; i < len; i++)
        MAX += nums[i];
    if (S > MAX || S < -MAX)
        return 0;
    vector<vector<int>> ways(2, vector<int>(2 * MAX + 1, 0));
    ways[0][nums[0] + MAX] = 1 + ways[0][nums[0] + MAX];
    ways[0][-1 * nums[0] + MAX] = 1 + ways[0][-1 * nums[0] + MAX];
    for (int i = 1; i < len; i++)
    {
        for (int j = -MAX; j <= MAX; j++)
        {

            if ((j - nums[i] + MAX) >= 0 && (j + nums[i]) <= MAX)
                ways[i % 2][j + MAX] = ways[1 - i % 2][j - nums[i] + MAX] + ways[1 - i % 2][j + nums[i] + MAX];
            else if (j - nums[i] + MAX < 0 && (j + nums[i]) <= MAX)
            {
                ways[i % 2][j + MAX] = ways[1 - i % 2][j + nums[i] + MAX];
            }
            else if (j - nums[i] + MAX >= 0 && j + nums[i] > MAX)
            {
                ways[i % 2][j + MAX] = ways[1 - i % 2][j - nums[i] + MAX];
            }
        }
    }

    return ways[(len - 1) % 2][S + MAX];
}

void testFindTargetSumWays()
{

    vector<int> nums2{0, 0, 0, 0, 0, 0, 0, 0, 1};
    // vector<int> nums2{0,0,1};
    printVector(nums2);
    int S = 0;
    while (S < 3)
    {
        int res = findTargetSumWays(nums2, S++);
        cout << "ways to have " << S - 1 << " is " << res << endl;
    }

    vector<int> nums{1, 1, 1, 1, 1};
    printVector(nums);
    S = 3;
    while (S < 7)
    {
        int res = findTargetSumWays(nums, S++);
        cout << "ways to have " << S - 1 << " is " << res << endl;
    }
}

// knapsack problems
// 474. Ones and Zeroes
int findMaxForm(vector<string> &strs, int m, int n)
{
    return 0;
}

void exchange(vector<vector<int>> &intervals, int i, int j)
{
    if (i == j)
    {
        return;
    }
    vector<int> tmp;
    tmp = intervals[i];
    intervals[i] = intervals[j];
    intervals[j] = tmp;
}

void sortBegnings(vector<vector<int>> &intervals, int start, int end)
{
    if (start >= end)
        return;

    int pivot = intervals[end][0];
    int split = start;
    for (int i = start; i < end; i++)
    {
        if (intervals[i][0] < pivot)
        {
            exchange(intervals, i, split);
            split++;
        }
    }
    exchange(intervals, split, end);
    sortBegnings(intervals, start, split - 1);
    sortBegnings(intervals, split + 1, end);
}

// 56. Merge Intervals
vector<vector<int>> merge(vector<vector<int>> &intervals)
{

    // Runtime: 64 ms, faster than 34.76% of C++ online submissions for Merge Intervals.
    // Memory Usage: 17.1 MB, less than 19.05% of C++ online submissions for Merge Intervals.
    //sort beginings
    int len = intervals.size();
    if (len <= 1)
        return intervals;
    sortBegnings(intervals, 0, len - 1);
    for (auto val : intervals)
    {
        printVector(val);
    }
    vector<vector<int>> out;
    vector<int> last = intervals[0];
    out.push_back(last);
    for (int i = 1; i < len; i++)
    {
        if (last[1] < intervals[i][0])
        {
            last = intervals[i];
            out.push_back(last);
        }
        else if (last[1] < intervals[i][1])
        {
            last = {last[0], intervals[i][1]};
            out.pop_back();
            out.push_back(last);
        }
    }
    return out;
}

// 56. Merge Intervals
vector<vector<int>> mergeFast(vector<vector<int>> &intervals)
{
    //sort beginings
    int len = intervals.size();
    if (len <= 1)
        return intervals;
    sortBegnings(intervals, 0, len - 1);
    int merged = 0;
    for (int i = 1; i < len; i++)
    {
        if (intervals[merged][1] < intervals[i][0])
        {
            merged++;
            intervals[merged] = intervals[i];
        }
        else if (intervals[merged][1] < intervals[i][1])
        {
            intervals[merged] = {intervals[merged][0], intervals[i][1]};
        }
    }

    for (int i = len - 1; i > merged; i--)
    {
        intervals.pop_back();
    }
    return intervals;
}

void testMergeIntervals()
{
    // vector<vector<int>> input{{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    // vector<vector<int>> input{{1,3},{2,6},{8,10},{15,18}};
    // vector<vector<int>> input{{1,4},{4,5}};
    // vector<vector<int>> input{{1, 4}, {0, 2}, {3, 5}};
    vector<vector<int>> input{{2, 3}, {2, 2}, {3, 3}, {1, 3}, {5, 7}, {2, 2}, {4, 6}};
    vector<vector<int>> out = mergeFast(input);
    for (auto val : out)
    {
        printVector(val);
    }
}

void testHammingWeight()
{
    DynamicProgramming dp;
    int n = 13;
    for (int i = 0; i < 4; i++)
    {
        cout << "hammingWeight of " << (n + i) << " is " << dp.getHammingWeight(n + i) << endl;
    }
}

void testShuffleArray()
{
    vector<int> arr{2, 3, 4, 5};
    DynamicProgramming dp(arr);
    cout << " shffle: " << endl;
    dp.shuffleArray(arr);
}

int getMaxLinked(vector<vector<int>> ma, int m, int n)
{
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    auto max = [](int a, int b) -> int {
        return (a >= b) ? a : b;
    };
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
            if (ma[i - 1][j - 1] == 1)
            {
                t1 = dp[i - 1][j] + 1;
                t3 = dp[i][j - 1] + 1;
            }
            else
            {
                t2 = dp[i - 1][j];
                t4 = dp[i][j - 1];
            }
            dp[i][j] = max(max(max(t1, t2), t3), t4);
        }
    }

    return dp[m][n];
}

void testML()
{
    vector<vector<int>> input = {{1, 1, 1, 0, 1, 1, 1, 1},
                                 {1, 1, 1, 0, 1, 0, 1, 1},
                                 {1, 1, 0, 1, 1, 0, 1, 1}};
    int len = getMaxLinked(input, 3, 8);
    cout << "getMaxLinked  " << len << endl;
}

int main(int argc, char const *argv[])
{
    // timeit(testMergeIntervals);
    // timeit(testwaysToChange);
    // timeit(testSubSequence);
    // timeit(testFindTargetSumWays);
    // timeit(testML);
    // timeit(testClimbStairs);
    // format_test(minCostClimbingStairs, testminCostClimbingStairs, printInt);
    // format_test(rob, testrob, printInt);
    // format_test(numberOfArithmeticSlices, testnumberOfArithmeticSlices, printInt);
    // format_test(maxSubArray, testmaxSubArray);
    format_test(stoneGame, testStoneGame);
}
