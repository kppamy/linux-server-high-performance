#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include "../common.h"
using namespace std;

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
    if (end - start == 1)
        return start;
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

    return 0;
}
