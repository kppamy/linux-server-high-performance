#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include "../common.h"
using namespace std;

// 1539. Kth Missing Positive Number
// 0 ms, faster than 100.00%
// 9.4 MB, less than 99.10%
int findKthPositive(vector<int> &arr, int k)
{
    int len = arr.size();
    int pre = arr[0];
    int missing = pre - 1;
    if (missing >= k)
        return k;
    for (int i = 1; i < len; i++)
    {
        int cur = arr[i];
        int dif = cur - pre;
        if (dif != 1)
        {
            int more = missing + dif - 1;
            if (more >= k)
            {
                return pre + k - missing;
            }
            missing = more;
        }
        pre = cur;
    }
    return arr[len - 1] + k - missing;
}

// 268. Missing Number
// 16 ms, faster than 91.42%
// 17.8 MB, less than 95.35%
int missingNumber(vector<int> &nums)
{
    int len = nums.size();
    nums.push_back(-1);
    for (int i = 0; i <= len;)
    {
        int cur = nums[i];
        if (cur != -1 && cur != i)
        {
            swap(nums[i], nums[cur]);
        }
        else
        {
            i++;
        }
    }
    for (int i = 0; i <= len; i++)
    {
        if (nums[i] == -1)
        {
            return i;
        }
    }
    return -1;
}

// 784. Letter Case Permutation
// 8 ms, faster than 70.57%
//  9.2 MB, less than 96.53%
vector<string> letterCasePermutation(string S)
{
    auto isLetter = [](char c) {
        return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
    };
    int distance = 'a' - 'A';
    auto trans = [distance](char c) {
        if (c >= 'a')
        {
            return c - distance;
        }
        return c + distance;
    };
    int len = S.size();
    vector<string> ans;
    for (int i = 0; i < len; i++)
    {
        char c = S[i];
        if (isLetter(c))
        {
            if (ans.size() == 0)
            {
                ans.push_back(S);
            }
            int sz = ans.size();
            while (sz > 0)
            {
                string change = ans[sz - 1];
                change[i] = trans(c);
                ans.push_back(change);
                sz--;
            }
        }
    }
    if (ans.size() == 0)
        ans.push_back(S);
    return ans;
}

// 78. Subsets
// 0 ms, faster than 100.00%
// 7 MB, less than 88.15%
vector<vector<int>> subsets(vector<int> &nums)
{
    int sz = nums.size();
    vector<vector<int>> ans;
    ans.push_back({});
    for (int i = 0; i < sz; i++)
    {
        ans.push_back({nums[i]});
        int pre = ans.size() - 1;
        for (int j = 1; j < pre; j++)
        {
            vector<int> sub = ans[j];
            sub.push_back(i);
            ans.push_back(sub);
        }
    }
    return ans;
}

void testSubsets()
{
    vector<int> nums = {1, 2, 3};
}

// 217. Contains Duplicate
bool containsDuplicate(vector<int> &nums)
{
    int different = 0;
    int sz = nums.size();
    for (int i = 0; i < sz; i++)
    {
        int cur = 1 << i;
        if (different & cur != 0)
            return true;
        different = different & cur;
    }
}

// 29. Divide Two Integers
// 0 ms, faster than 100.00%
// 5.9 MB, less than 57.86%
int divide(int dividend, int divisor)
{
    if (dividend == INT_MIN && divisor == -1)
        return INT_MAX;
    if (divisor == 1)
        return dividend;
    int sign = (dividend > 0 ^ divisor > 0) ? -1 : 1;
    long dvd = labs(dividend);
    long dvs = labs(divisor);
    int ans = 0;
    while (dvd >= dvs)
    {
        long temp = dvs, m = 1;
        while (temp << 1 <= dvd)
        {
            temp = temp << 1;
            m = m << 1;
        }
        dvd -= temp;
        ans += m;
    }
    return ans * sign;
}

void testdivi()
{
    cout << "sizeof(long): " << sizeof(long) << endl;
    cout << divide(2147483647, 2) << endl;
    cout << divide(4, 2) << endl;
    cout << divide(3, 2) << endl;
    cout << divide(-7, 3) << endl;
    cout << divide(10, -4) << endl;
    cout << divide(10, 3) << endl;
    cout << divide(20, 11) << endl;
}

// 1630. Arithmetic Subarrays
//  36 ms, faster than 94.73%
// 20.9 MB, less than 94.98%
vector<bool> checkArithmeticSubarrays(vector<int> &nums, vector<int> &l, vector<int> &r)
{
    int n = nums.size(), m = l.size();
    vector<bool> ans(m, true);
    vector<int> tmp(n, 0);
    for (int i = 0; i < m; i++)
    {
        int left = l[i], right = r[i];
        copy(nums.begin() + left, nums.begin() + right + 1, tmp.begin());
        sort(tmp.begin(), tmp.begin() + right - left + 1);
        int dis = tmp[1] - tmp[0];
        int end = right - left;
        for (int j = 1; j < end; j++)
        {
            if (tmp[j + 1] - tmp[j] != dis)
            {
                ans[i] = false;
                break;
            }
        }
    }
    return ans;
}

// 1588. Sum of All Odd Length Subarrays
//  0 ms, faster than 100.00
// 8.2 MB, less than 97.61%
int sumOddLengthSubarrays(vector<int> &arr)
{
    int len = arr.size();
    int ans = 0;
    for (int win = 1; win <= len; win += 2)
    {
        int end = len - win + 1;
        for (int i = 0; i < end; i++)
        {
            int sube = i + win;
            for (int j = i; j < sube; j++)
            {
                ans += arr[j];
            }
        }
    }
    return ans;
}

// 766. Toeplitz Matrix
// 12 ms, faster than 92.93%
// 17.5 MB, less than 69.36%
bool isToeplitzMatrix(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    int i = 0, j = 0;
    while (j < n)
    {
        for (int r = i + 1, c = j + 1; r < m && c < n; r++, c++)
        {
            if (matrix[i][j] != matrix[r][c])
                return false;
        }
        j++;
    }
    j = 0;
    i = 1;
    while (i < m)
    {
        for (int r = i + 1, c = j + 1; r < m && c < n; r++, c++)
        {
            if (matrix[i][j] != matrix[r][c])
                return false;
        }
        i++;
    }
    return true;
}

// 1582. Special Positions in a Binary Matrix
// 16 ms, faster than 96.38%
// 12.9 MB, less than 73.97%
int numSpecial(vector<vector<int>> &mat)
{
    int m = mat.size(), n = mat[0].size();
    if (m == 1 && n == 1)
        return mat[0][0] == 1;
    vector<int> rows(m, 0), cols(n, 0);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j])
            {
                rows[i]++;
                cols[j]++;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] && rows[i] == 1 && cols[j] == 1)
                ans++;
        }
    }

    return ans;
}
// 1576. Replace All ?'s to Avoid Consecutive Repeating Characters
//  4 ms, faster than 38.88%
// 6.1 MB, less than 69.07%
string modifyString(string s)
{
    int i = 0, len = s.size();
    char prev = 'a' - 1;
    char next;
    while (i < len - 1)
    {
        next = s[i + 1];
        if (s[i] == '?' && s[i + 1] != '?')
        {
            if (prev == 'z' && next == 'z')
            {
                s[i] = 'a';
            }
            else if (prev != 'z' && next != 'z')
            {
                s[i] = 'z';
            }
            else
            {
                char nz = prev + next - 'z';
                s[i] = (nz == 'a') ? 'b' : 'a';
            }
            i += 2; // process two characters once 38.88% -->100.00%
            prev = next;
        }
        else if (s[i] == '?')
        {
            s[i] = (prev == 'z') ? 'a' : (prev + 1);
            prev = s[i];
            i++;
        }
        else
        {
            prev = s[i];
            i++;
        }
    }
    if (s[i] == '?')
    {
        s[i] = (prev == 'z') ? 'a' : (prev + 1);
    }
    return s;
}

// 1572. Matrix Diagonal Sum
int diagonalSum(vector<vector<int>> &mat)
{
    int m = mat.size(), n = mat[0].size();
    int p = 0, s = n - 1;
    int ans = 0;
    while (p < n)
    {
        // if(p==s)
        //     ans += mat[p][p];
        // else
        //     ans += mat[p][p] + mat[p][s];

        ans += (p ^ s) ? (mat[p][p] + mat[p][s]) : mat[p][p]; // condition transfer improved from 83.% to 96.55%
        p++;
        s--;
    }
    return ans;
}

void printArr(int *arr, int len)
{
    cout << "output the array:";
    for (int i = 0; i < len; i++)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

void printVector(vector<int> &vec)
{
    cout << "output the vector:";
    for (int x : vec)
    {
        cout << x << ' ';
    }
    cout << endl;
}

void printString(char *input, int size)
{
    cout << " print string: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << *(input + i) << " ";
    }
    cout << endl;
}

// Recursion test
// Write a function that reverses a string. The input string is given as an array of characters char[].
// Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
void reverseString(string input)
{
    if (input.length() == 1)
    {
        cout << input[0] << endl;
        return;
    }
    cout << input[input.length() - 1];
    reverseString(input.substr(0, input.length() - 1));
}

void reverseString(char input[], int size)
{
    char temp;
    printString(input, size);
    for (int i = 0; i < size / 2; i++)
    {
        temp = input[i];
        input[i] = input[size - i - 1];
        input[size - i - 1] = temp;
    }
    printString(input, size);
}

int reverseInteger(int x)
{
    int digits = round(log10(x));
    int res = 0;
    int i = 0;
    while (digits > -1)
    {
        int high = (int)pow(10, digits--);
        res = res + x / high * pow(10, i++);
        x = x - x / high * high;
    }
    return res;
}

// Array test
// Remove Duplicates from Sorted Array, modifying the input array in-place with O(1) extra memory.
//  https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/727/

int removeDup(int arr[], int len)
{
    int j = 0;
    cout << *arr << endl;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] != arr[i + 1])
        {
            j++;
            arr[j] = arr[i + 1];
        }
    }
    printArr(arr, j);
    return j;
}

int removeDup(vector<int> &nums)
{
    int j = 0;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] != nums[i + 1])
        {
            j++;
            nums[j] = nums[i + 1];
        }
    }
    printVector(nums);
    return j;
}

int square(unsigned int start, unsigned int end, unsigned int num)
{
    //recursion faster than iteration ??
    if (start - end == 1)
        return end;
    long long mid = (start + end) / 2;
    if (mid * mid < num)
        //  try x/2, 3/4 x
        return square(mid, end, num);
    else if (mid * mid == num)
        return mid;
    else
    {
        //try x/4,x/2
        return square(start, mid, num);
    }
}

// 69. Sqrt(x)
int mySqrt(int x)
{
    if (x == 1)
        return 1;
    else
        return square(0, x, x);
}

void testSqrt()
{
    cout << "mySqrt of INT64_MAX is " << mySqrt(INT64_MAX) << endl;
    cout << "mySqrt of 1 is " << mySqrt(1) << endl;
    cout << "mySqrt of 4 is " << mySqrt(4) << endl;
    cout << "mySqrt of 6 is " << mySqrt(6) << endl;
    cout << "mySqrt of 8 is " << mySqrt(8) << endl;
    cout << "mySqrt of 9 is " << mySqrt(9) << endl;
}

void testWhat(char **argv)
{
    cout << "begin algo test: " << endl;
    reverseString(argv[1]);
    int arr[7] = {1, 1, 1, 2, 3, 3, 4};
    removeDup(arr, 7);
    vector<int> vec{1, 1, 1, 2, 3, 3, 4, 4, 5, 7, 7};
    removeDup(vec);
    char input[7] = "123456";
    reverseString(input, 6);
    int a = 12345;
    cout << "before operation: " << a << endl;
    int res = reverseInteger(a);
    cout << "after operation: " << res << endl;
}

int main(int argc, char **argv)
{
    // vector<int> nums = {4, 6, 5, 9, 3, 7};
    // vector<int> l = {0, 0, 2};
    // vector<int> r = {2, 3, 5};
    // checkArithmeticSubarrays(nums, l, r);
    testdivi();
    return 0;
}
