#include "common.h"
#include "DynamicProgramming.h"
#include <math.h>

int DynamicProgramming::climbStairs(int stairs){
    if(stairs == 1)
    return 1;
    else if(stairs == 2)
    return 2;
    return climbStairs(stairs-1) + climbStairs(stairs - 2);
}


void DynamicProgramming::shuffleArray(vector<int> &arr){
    int sz = arr.size();
    for(int i=0;i<sz;i++){
        int swap = randomize(i,sz);
        int tmp = arr[i];
        arr[i] = arr[swap];
        arr[swap] = tmp;
    }
    printVector(arr);
}

vector<int>& DynamicProgramming::resetArray(){
     return backup;
}

int DynamicProgramming::randomize(int min, int max){
    return (rand()%(max - min) + min) ;
}

int DynamicProgramming::getHammingWeight(int n){
    if(n==0)
    return 0;
    int left = n ;
    int count = 0;
    while(left > 0){
        count ++;
        left = left - pow(2,floor(log2(left)));
    }
    return count;
}

int main(int argc, char const *argv[])
{
    /* code */
    DynamicProgramming dp;
    // int stairs = 5;
    // int ways = dp.climbStairs(stairs);
    // cout<< ways<<" ways to climb "<<stairs<<" steps"<<endl;
    // vector<int> arr{2, 3, 4, 5};
    // DynamicProgramming dp(arr);
    // cout<<" shffle: "<<endl;
    // dp.shuffleArray(arr);
    int n = 13;
    for(int i=0;i<4;i++){
        cout<<"hammingWeight of "<<(n+i)<<" is "<<dp.getHammingWeight(n+i)<<endl;
    }

}
