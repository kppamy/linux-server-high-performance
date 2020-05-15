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
    if(index_s == -1  ){
        if(prices[end] > prices[index_b])
            index_s = end;
        else if(prices[end] < prices[index_b])
            index_b = end;
        return 0;
    }else if (prices[end] > prices[index_s])
    {
        index_s = end;
        return (subMaxProfit(prices, end - 1, index_b, index_s) + (prices[end] - prices[index_s]));
    }else {
        return subMaxProfit(prices, end - 1, index_b, index_s);
    }
}

// buy and sell only once
void maxProfitBF(vector<int> &prices)
{
    int max=INT_MIN;
    for(int i=0;i<prices.size()-1;++i){
        for(int j=i+1;j<prices.size();++j){
            if(prices[j]-prices[i]>max){
                max = prices[j]-prices[i];
            }
        }
    }

    cout<<" max profit "<< max<<endl;
}

// buy and sell only once
void maxProfit1P(vector<int> &prices)
{
    int min=INT_MAX;
    int prf=0;
    for(int i=0;i<prices.size();++i){
        if(prices[i]< min){
            min = prices[i];
        }else if(prices[i] - min > prf ){
            prf = prices[i] - min;
        }
    }
    cout<<" max profit "<<prf<<endl;
}


int main(int argc, char const *argv[])
{
    /* code */
    ArrayTest at;
    // vector<int> prices{7, 1, 5, 3, 6, 4};
    vector<int> prices = generateArray(10, 10);
    // int max = at.maxProfit(prices);
    // cout<<" max profit is: "<<max<<endl;
    // cout << "before rotate:" << endl;
    // printVector(prices);
    // int k = 5;
    // cout << "after rotate " << k << " k" << endl;
    // at.rotateArraySwitch(prices, k);
    printVector(prices);

    maxProfitBF(prices);

    return 0;
}
