#include <iostream>
#include <vector>
#include <bitset>
#include <map>
#include <unordered_map>
using namespace std;

// 318. Maximum Product of Word Lengths
// : 36 ms, faster than 97.46%
// 17.2 MB, less than 32.04% 
int maxProduct(vector<string> &words)
{
    int len = words.size();
    unordered_map<int, int> dc;
    int ans = 0;
    for (int i = 0; i < len; i++)
    {
        string wd = words[i];
        int len1 = wd.size();
        int mask = 0;
        for (int j = 0; j < len1; j++)
        {
            mask = mask | (1 << (wd[j] - 'a'));
        }
        int mm = max(dc[mask], len1);
        dc[mask]=mm;
        for (auto &&[bits, len2] : dc)
        {
            if ((bits & mask)==0)
                ans = max(ans, mm * len2);
        }
    }
    return ans;
}

// 342. Power of Four
// 0 ms, faster than 100.00%
// 5.9 MB, less than 80.83%
bool isPowerOfFour(int n)
{

    if (n < 0)
        return false;
    if (n & (n - 1))
        return false;
    long long max4 = 1;
    int sum = 1;
    int cnt = 1;
    while (cnt <= 32)
    {
        max4 = max4 << 2;
        sum += max4;
        if (max4 > n) // from 36.3%->100%
            break;
        cnt += 2;
    }
    return n & sum;
}

int ones(int num)
{
    int cnt = 0;
    while (num)
    {
        if (num % 1)
            cnt++;
        num >>= 1;
    }
    return cnt;
}

bool isPrime(int num)
{
    if (num <= 1)
        return false;
    int i = 2;
    int mid = num / 2;
    while (i <= mid)
    {
        if (num % i == 0)
            return false;
        i++;
    }
    return true;
}

// 762. Prime Number of Set Bits in Binary Representation
int countPrimeSetBits(int L, int R)
{
    int cnt = 0;
    int num = L;
    while (num <= R)
    {
        if (isPrime(ones(num)))
            cnt++;
    }
    return cnt;
}
// 477. Total Hamming Distance
// 56 ms, faster than 73.96%
// 19 MB, less than 94.09%
int totalHammingDistance(vector<int> &nums)
{
    int len = nums.size();
    int cnt = 0;
    int ans = 0;
    while (true)
    {
        int ones = 0;
        int zeros = 0;
        for (int i = 0; i < len; i++)
        {
            int cur = nums[i];
            if (cur == -1)
            {
                zeros++;
                continue;
            }
            if (cur & 1)
                ones++;
            else
                zeros++;
            cur >>= 1;
            if (cur == 0)
            {
                cnt++;
            }
            nums[i] = (cur == 0) ? -1 : cur;
        }
        ans += ones * zeros;
        if (cnt == len)
            break;
    }
    return ans;
}

// 461. Hamming Distance
// 0 ms, faster than 100.00%
// 5.9 MB, less than 53.20%
int hammingDistance(int x, int y)
{
    int dis = 0;
    int dif = x ^ y;
    while (dif)
    {
        if (dif & 1)
        {
            dis++;
        }
        dif >>= 1;
    }
    return dis;
}

// 190. Reverse Bits
// 4 ms, faster than 55.64%
uint32_t reverseBits(uint32_t n)
{
    int ans = 0;
    for (int i = 1; i <= 32 && n > 0; ++i)
    {
        int half = n >> 1;
        int bit = n - (half << 1);
        n = half;
        ans = (ans << 1) + bit;
        if (n == 0)
            ans = ans << (32 - i);
    }
    return ans;
}

void testreverseBits()
{
    vector<uint32_t> cs = {
        // 0000 0010 1001 0100 0001 1110 1001 1100
        0x2941E9C,
        0xFFFFFFFF,
        3,
        0x10000000,
        4294967293};

    for (auto &&num : cs)
    {
        cout << num << "  reverseBits is " << reverseBits(num) << endl;
    }
}

// 191. Number of 1 Bits
//  0 ms, faster than 100.00%
// 6 MB, less than 93.28%
int hammingWeightP(uint32_t n)
{
    return __builtin_popcount(n);
}

// 191. Number of 1 Bits
//  0 ms, faster than 100.00%
// 6 MB, less than 93.28%
int hammingWeightB(uint32_t n)
{
    bitset<32> bs(n);
    return bs.count();
}

// 191. Number of 1 Bits
// 0 ms, faster than 100.00%
// 5.9 MB, less than 93.28%
int hammingWeight(uint32_t n)
{
    int count = 0;
    while (n)
    {
        n &= (n - 1);
        count++;
    }
    return count;
    // int weigh = 0;
    // for (int i = 1; i <= 32 && n > 0; i++)
    // {
    //     int half = n >> 1;
    //     if (n - (half << 1) == 1)
    //         weigh++;
    //     n = half;
    // }
    // return weigh;
}

void testhammingWeight()
{
    vector<uint32_t> cs = {
        11,
        128,
        4294967293};

    for (auto &&num : cs)
    {
        cout << num << "  hammingWeight is " << hammingWeight(num) << endl;
    }
}

// 461. Hamming Distance
//  0 ms, faster than 100.00%
//  5.8 MB, less than 95.80%
int hammingDistanceI(int x, int y)
{
    int dis = 0;
    int dif = x ^ y;
    for (int i = 1; i <= 31 && dif > 0; ++i)
    {
        int half = dif >> 1;
        if (dif - (half << 1) == 1)
            dis++;
        dif = half;
    }
    return dis;
}

void testhammingDistance()
{
    int x = 680142203, y = 1111953568;
    cout << x << " and " << y << " hammingDistance: " << hammingDistance(x, y) << endl;

    x = 1, y = 4;
    cout << x << " and " << y << " hammingDistance: " << hammingDistance(x, y) << endl;

    x = 1, y = 2;
    cout << x << " and " << y << " hammingDistance: " << hammingDistance(x, y) << endl;

    x = 3, y = 3;
    cout << x << " and " << y << " hammingDistance: " << hammingDistance(x, y) << endl;
}

int main(int argc, char const *argv[])
{

    // testhammingDistance();
    // testhammingWeight();
    // testreverseBits();
    cout << isPowerOfFour(16) << endl;
    cout << isPowerOfFour(8) << endl;

    vector<string> ss = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
    cout << maxProduct(ss) << endl;
    return 0;
}
