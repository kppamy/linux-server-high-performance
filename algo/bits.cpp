#include <iostream>
using namespace std;

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

    testhammingDistance();
    return 0;
}
