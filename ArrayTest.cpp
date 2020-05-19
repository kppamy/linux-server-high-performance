#include "ArrayTest.h"
#include "common.h"

// buy and sell multiple times
int ArrayTest::maxProfit(vector<int> &prices)
{
    int len = prices.size();
    int max = 0;
    for (int i = 0; i < len; i++)
    {
        if (prices[i + 1] > prices[i])
        {
            max = max + (prices[i + 1] - prices[i]);
        }
    }
    return max;
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

int subMaxProfit(vector<int> &prices, int end, int &index_b, int &index_s)
{
    if (end == 1)
    {
        if (prices[1] >= prices[0])
        {
            index_b = 0;
            index_s = 1;
            return (prices[1] - prices[0]);
        }
        else
        {
            index_b = 1;
            index_s = -1;
            return 0;
        }
    }
    if (index_s == -1)
    {
        if (prices[end] > prices[index_b])
            index_s = end;
        else if (prices[end] < prices[index_b])
            index_b = end;
        return 0;
    }
    else if (prices[end] > prices[index_s])
    {
        index_s = end;
        return (subMaxProfit(prices, end - 1, index_b, index_s) + (prices[end] - prices[index_s]));
    }
    else
    {
        return subMaxProfit(prices, end - 1, index_b, index_s);
    }
}

// buy and sell only once
void maxProfitBF(vector<int> &prices)
{
    int max = INT_MIN;
    for (int i = 0; i < prices.size() - 1; ++i)
    {
        for (int j = i + 1; j < prices.size(); ++j)
        {
            if (prices[j] - prices[i] > max)
            {
                max = prices[j] - prices[i];
            }
        }
    }

    cout << " max profit " << max << endl;
}

// buy and sell only once
void maxProfit1P(vector<int> &prices)
{
    int min = INT_MAX;
    int prf = 0;
    for (int i = 0; i < prices.size(); ++i)
    {
        if (prices[i] < min)
        {
            min = prices[i];
        }
        else if (prices[i] - min > prf)
        {
            prf = prices[i] - min;
        }
    }
    cout << " max profit " << prf << endl;
}

// buy and sell for k chances
void maxProfitDP(vector<int> &prices, int k)
{
    int nums = prices.size();
    vector<vector<int>> profits(k + 1, vector<int>(nums, 0));
    for (int kk = 1; kk < k + 1; kk++)
    {
        int g = 0;
        int i = 1;
        int j = 0;
        for (i = 1; i < nums; ++i)
        {
            for (j = 0; j < i; ++j)
            {
                g = max(g, profits[kk - 1][j] + prices[i] - prices[j]);
            }
            profits[kk][i] = max(profits[kk][i - 1], g);
        }
    }
    // max profit for 2 chances is: 16 elaps: 121518 ms
    cout << "max profit for " << k << " chances"
         << " is: " << profits[k][nums - 1];

    //input size: 10W, 2*10 20w loops
    //  ++i,i++ difference ~1s
    // create i,j inside the loop or not: diff ~0.5s

    // ++i,++j, create i,j inside the loop
    // "max profit for 2 chances is: 16elaps: 120787 ms\r\n"

    // i++, j++ dont create i,j inside the loop
    // @"max profit for 2 chances is: 16elaps: 121053 ms\r\n"

    // i++,j++, create i,j inside the loop
    // max profit for 2 chances is: 16 elaps: 121518 ms
}

// buy and sell for k chances
void maxProfit2chances(vector<int> &prices)
{
    int i = 0;
    int b1 = INT_MAX, b2 = INT_MAX;
    int s1 = INT_MIN, s2 = INT_MIN;
    for (; i < prices.size(); i++)
    {
        b1 = min(b1, prices[i]);
        s1 = max(s1, prices[i] - b1);
        b2 = min(b2, prices[i] - s1);
        s2 = max(s2, prices[i] - b2);
    }
    // max profit for 2 chances is: 16 elaps: 121518 ms
    cout << "max profit for 2 chances"
         << " is: " << s2;
}

void maxProfitCoolDown(const vector<int> &prices)
{
    int len = prices.size();
    if (len <= 1)
        return;
    vector<int> prf(len, 0);
    prf[1] = max(prices[1] - prices[0], 0);
    if (len == 2)
    {
        cout << "max profit for unlimited trasactions but cooldown 1d "
             << " is: " << prf[len - 1] << endl;
        return;
    }
    prf[2] = max(prf[1], prf[1] + prices[2] - prices[1]);
    int i = 3, j = 2;
    int g = 0;
    for (; i < len; ++i)
    {
        for (j = 2; j < i; ++j)
        {
            g = max(g, prf[j - 2] + prices[i] - prices[j]);
            g = max(g, prf[j - 1] + prices[i] - prices[j]);
        }
        prf[i] = max(prf[i - 1], g);
    }

    cout << "max profit for unlimited trasactions but cooldown 1d "
         << " is: " << prf[len - 1] << endl;
}

void maxProfitCoolDownSM(const vector<int> &prices)
{
    int len = prices.size();
    vector<int> bought(len, 0);
    vector<int> sold(len, 0);
    vector<int> cooldown(len, 0);
    bought[0] = -prices[0];
    sold[0] = 0;
    cooldown[0] = 0;
    int i;
    for (i = 1; i < len; ++i)
    {
        bought[i] = max(cooldown[i - 1] - prices[i], bought[i - 1]);
        sold[i] = max(bought[i - 1] + prices[i], sold[i - 1]);
        cooldown[i] = max(max(sold[i - 1], bought[i - 1]), cooldown[i - 1]);
    }

    cout << "max profit for unlimited trasactions but cooldown 1d "
         << " is: " << max(sold[len - 1], cooldown[len - 1]) << endl;
}

int main(int argc, char const *argv[])
{
    /* code */
    ArrayTest at;
    // vector<int> prices{4 ,3, 8, 9 ,3 ,7, 7 ,4 ,9 ,1};
    vector<int> prices = generateArray(10, 10);
    // int max = at.maxProfit(prices);
    // cout<<" max profit is: "<<max<<endl;
    // cout << "before rotate:" << endl;
    // printVector(prices);
    // int k = 5;
    // cout << "after rotate " << k << " k" << endl;
    // at.rotateArraySwitch(prices, k);
    printVector(prices);
    int start = clock();

    // maxProfitDP(prices, 2);
    // maxProfit2chances(prices);
    maxProfitCoolDownSM(prices);

    int end = clock();
    double elaps = (static_cast<float>(end - start)) / CLOCKS_PER_SEC;
    cout << "elaps: " << elaps * 1000 << " ms" << endl;
    return 0;
}
