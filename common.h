#include <iostream>
#include <vector>
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