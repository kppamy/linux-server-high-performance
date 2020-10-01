

// 1518. Water Bottles
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Water Bottles.
// Memory Usage: 6.2 MB, less than 5.68% of C++ online submissions for Water Bottles.
int numWaterBottles(int numBottles, int numExchange)
{
    int sum = numBottles;
    int begin = numBottles;
    while (begin >= numExchange)
    {
        int chg = begin / numExchange;
        int left = begin % numExchange;
        sum += chg;
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

// 1221. Split a String in Balanced Strings
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Split a String in Balanced Strings.
// Memory Usage: 6.5 MB, less than 5.09% of C++ online submissions for Split a String in Balanced Strings.
int balancedStringSplit(string s)
{
    int counter = 0;
    int sum = 0;
    for (auto &&c : s)
    {
        sum += (c == 'L' ? 1 : -1);
        if (sum == 0)
            counter++;
    }
    return counter;
}

void testbalancedStringSpli()
{
    cout << " balancedStringSplit "
         << " RLRRLLRLRL " << balancedStringSplit("RLRRLLRLRL") << endl;
    cout << " balancedStringSplit "
         << " RLLLLRRRLR " << balancedStringSplit("RLLLLRRRLR") << endl;
    cout << " balancedStringSplit "
         << " LLLLRRRR " << balancedStringSplit("LLLLRRRR") << endl;
    cout << " balancedStringSplit "
         << " RLRRRLLRLL " << balancedStringSplit("RLRRRLLRLL") << endl;
}

// 944. Delete Columns to Make Sorted
// Runtime: 52 ms, faster than 94.37% of C++ online submissions for Delete Columns to Make Sorted.
// Memory Usage: 12.5 MB, less than 12.60% of C++ online submissions for Delete Columns to Make Sorted.
int minDeletionSize(vector<string> &A)
{

    int len = A.size();
    int wid = A[0].size();
    auto sorted = [&](int i) -> bool {
        for (int j = 0; j < len - 1; j++)
        {
            if (A[j][i] > A[j + 1][i])
                return false;
        }
        return true;
    };
    int del = 0;
    for (int i = 0; i < wid; i++)
    {
        if (!sorted(i))
            del++;
    }
    return del;
}

void testminDeletionSize()
{
    vector<vector<string>> cases = {
        {"cba", "daf", "ghi"},
        {"a", "b"},
        {"zyx", "wvu", "tsr"}};
    for (auto &&cs : cases)
    {
        for (auto &&item : cs)
            cout << item << ", ";
        cout << endl;
        cout << "minDeletionSize: " << minDeletionSize(cs) << endl;
    }
}

// 1403. Minimum Subsequence in Non-Increasing Order
// Runtime: 16 ms, faster than 76.28% of C++ online submissions for Minimum Subsequence in Non-Increasing Order.
// Memory Usage: 10.9 MB, less than 13.92% of C++ online submissions for Minimum Subsequence in Non-Increasing Order.
vector<int> minSubsequence(vector<int> &nums)
{
    int sum = 0;
    for (int val : nums)
    {
        sum += val;
    }
    int sz = nums.size();
    vector<int> out;
    int sum2 = 0;
    sort(nums.begin(), nums.end());
    while (sz > 0)
    {
        out.push_back(nums[sz - 1]);
        sum2 += nums[sz - 1];
        if (sum2 > sum - sum2)
            return out;
        sz--;
    }
    return out;
}

my2arr testminSubsequenc()
{
    return {
        {4, 3, 10, 9, 8},
        {4, 4, 7, 6, 7},
        {6}};
}

// 392. Is Subsequence
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Is Subsequence.
// Memory Usage: 6.7 MB, less than 25.13% of C++ online submissions for Is Subsequence.
bool isSubsequence(string s, string t)
{
    int ls = s.size();
    if (ls == 0)
        return true;
    int lt = t.size();
    int i = 0, j = 0;
    while (i < ls && j < lt)
    {
        if (s[i] == t[j])
        {
            i++;
        }
        j++;
    }
    return (i == ls);
}

void testisSubsequence()
{
    string s = "abc", t = "ahbgdc";
    cout << s << " is " << (isSubsequence(s, t) ? "" : " not ") << "Subsequence of " << t << endl;

    s = "axc", t = "ahbgdc";
    cout << s << " is " << (isSubsequence(s, t) ? "" : " not ") << "Subsequence of " << t << endl;
}

int largestSumAfterKNegations(vector<int> &A, int K)
{
    sort(A.begin(), A.end());
    for (auto &&val : A)
    {
        if (K > 0 && val < 0)
        {
            val = -1 * val;
            K--;
        }
        if (K == 0)
            break;
    }
    sort(A.begin(), A.end());
    int sum = 0;
    for (int val : A)
    {
        if (K > 0 && val >= 0)
        {
            if (K % 2)
            {
                val = -1 * val;
            }
            K = 0;
        }
        sum += val;
    }
    return sum;
}

void testlargestSumAfterKNegation()
{
    vector<int> A = {4, 2, 3};
    int K = 1;
    printVector(A);
    cout << "largestSumAfter " << K << " Negations: " << largestSumAfterKNegations(A, K) << endl;

    A = {2, -3, -1, 5, -4}, K = 2;
    printVector(A);
    cout << "largestSumAfter " << K << " Negations: " << largestSumAfterKNegations(A, K) << endl;

    A = {-8, 3, -5, -3, -5, -2}, K = 6;
    printVector(A);
    cout << "largestSumAfter " << K << " Negations: " << largestSumAfterKNegations(A, K) << endl;

    A = {1, 3, 2, 6, 7, 9}, K = 3;
    printVector(A);
    cout << "largestSumAfter " << K << " Negations: " << largestSumAfterKNegations(A, K) << endl;

    A = {3, -1, 0, 2}, K = 3;
    printVector(A);
    cout << "largestSumAfter " << K << " Negations: " << largestSumAfterKNegations(A, K) << endl;

    A = {2, -3, -1, 5, -4}, K = 2;
    printVector(A);
    cout << "largestSumAfter " << K << " Negations: " << largestSumAfterKNegations(A, K) << endl;
}

int main(int argc, char const *argv[])
{
    // testnumWaterBottles();
    // testbalancedStringSpli();
    // testminDeletionSize();
    // testArray(minSubsequence, "minSubsequence", testminSubsequenc, printVector);
    // testisSubsequence();
    testlargestSumAfterKNegation();
    return 0;
}
