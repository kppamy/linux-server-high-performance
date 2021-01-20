#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

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
int hammingDistance(int x, int y)
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
    testreverseBits();
    return 0;
}
