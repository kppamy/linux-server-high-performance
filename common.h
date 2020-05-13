#include <iostream>
#include <vector>
#include <time.h>
#include <limits.h>
using namespace std;

void printVector(vector<int> &input){
    for(int v:input){
        cout<<v<<" ";
    }
    cout<<endl;
}

void printInput(int input[], int len){
{
    for (int i = 0; i < len; i++)
    {
        cout << input[i] << " ";
    }
    cout << endl;
}
}

vector<int> generateArray(int num, int max){
    vector<int> arr(num);
    for(int i=0;i<=num;i++){
        arr[i]=(rand()%max);
    }
    return arr;
}