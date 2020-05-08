#include "ArrayTest.h"
#include "common.h"

int ArrayTest::maxProfit(vector<int> &prices){
    int len = prices.size();
    int max = 0;
    for(int i=0;i<len;i++){
        if(prices[i+1]>prices[i]){
            max = max + (prices[i+1] - prices[i]);
        }
    }
    return max;
}

void ArrayTest::rotateArray(vector<int> &input, int k){
    // extra k steps
    vector<int> back;
    int len = input.size();
    for(int i=len-k;i<len;i++)
        back.push_back(input[i]);
    for(int i=len-k-1; i>=0;i--)
        input[i+k] = input[i];
    for(int i=0;i<k;i++)
        input[i]=back[i];
}


void ArrayTest::rotateArraySwitch(vector<int> &input, int k){
    vector<int> back;
    int len = input.size();
    int tmp;
    for(int i=0;i<k;i++){
        tmp = input[len-1];
        input.pop_back();
        input.insert(input.begin(), tmp);
    }
}

void ArrayTest::rotateRecus(vector<int> &input, int k){
    if (k == 1){
        rotateOne(input);
    }else if(k > 1){
        rotateArray(input,k);
        k = k-1;    
    }
}

void ArrayTest::rotateOne(vector<int> &input){
    int len = input.size();
    int tmp=input[len-1];
    for(int i=len-2;i>=0;i--){
        input[i+1]=input[i];
    }
    tmp=input[0];
}


int main(int argc, char const *argv[])
{
    /* code */
    ArrayTest at;
    vector<int> prices{7,1,5,3,6,4};
    // int max = at.maxProfit(prices);
    // cout<<" max profit is: "<<max<<endl;
    cout<<"before rotate:"<<endl;
    printVector(prices);
    int k = 5;
    cout<<"after rotate "<<k<<" k"<<endl;
    at.rotateArraySwitch(prices,k);
    printVector(prices);
    return 0;
}

