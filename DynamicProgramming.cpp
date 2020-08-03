#include "common.h"
#include "DynamicProgramming.h"
#include <math.h>
#include "Timer.h"

int DynamicProgramming::climbStairs(int stairs)
{
    if (stairs == 1)
        return 1;
    else if (stairs == 2)
        return 2;
    return climbStairs(stairs - 1) + climbStairs(stairs - 2);
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
}

// knapsack problems
// 322. Coin Change
int coinChange(vector<int> &coins, int amount)
{
  
}

// 面试题 08.11. 硬币
int waysToChange(int n)
{    
    if (n <= 1)
        return n;
    static int mod = 1000000007;
    static int coins[4]={25, 10, 5, 1};//i
    vector<int> res(n+1,0);// res[j] 前i-1 个硬币组成j的方案数, res[0,...,j-1] 表示前i个硬币组成j的方案数
    res[0] = 1;
    for (int i = 0; i<=3 ; i++)
    {
        int j;
        for (j = coins[i]; j <= n; j++)
        {
            res[j] =(res[j] + res[j - coins[i]])%mod;
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
    int i,j=0;
    while(i<m && j<n){
        if(s[i]==t[j]){
            i++;
        }
        j++;
    }
    return i==m;
}

void testwaysToChange(){
      cout<<" ways to change 5  is "<< waysToChange(5)<<endl; // 2
      cout<<" ways to change 10 is "<< waysToChange(10)<<endl;// 4
      cout<<" ways to change 1 is "<< waysToChange(1)<<endl;// 4
}

void testSubSequence(){
    string s = "abc", t = "ahbgdc";
    // string s = "axc", t = "ahbgdc";
    // string s = "axc", t = "axc";
    cout <<s<<" is "<< (isSubsequence(s,t,true)?"":" not ")<< "subsequence of " << t<<endl;
}

// knapsack problems
// 494. Target Sum
int findTargetSumWays(vector<int> &nums, int S)
{
}

// knapsack problems
// 474. Ones and Zeroes
int findMaxForm(vector<string> &strs, int m, int n)
{
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
            intervals[merged] =  intervals[i];
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

void testClimbStairs()
{
    DynamicProgramming dp;
    int stairs = 5;
    int ways = dp.climbStairs(stairs);
    cout << ways << " ways to climb " << stairs << " steps" << endl;
}

int main(int argc, char const *argv[])
{
    // timeit(testMergeIntervals);
    // timeit(testwaysToChange);
    timeit(testSubSequence);
}
