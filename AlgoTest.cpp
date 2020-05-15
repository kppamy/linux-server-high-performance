#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

void printArr(int *arr, int len){
  cout<<"output the array:";
   for(int i=0;i<len;i++){
       cout<<arr[i]<<' ';
   }
   cout<<endl;
}

void printVector(vector<int> &vec){
  cout<<"output the vector:";
   for(int x : vec){
       cout<<x<<' ';
   }
   cout<<endl;
}

void printString(char* input, int size){
    cout<<" print string: "<<endl;
    for(int i=0;i<size;i++){
        cout<<*(input+i)<<" ";
    }
    cout<<endl;
}

// Recursion test
// Write a function that reverses a string. The input string is given as an array of characters char[].
// Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
void reverseString(string input){
 if(input.length() == 1){
     cout<<input[0]<<endl;
     return;
 }
 cout<<input[input.length()-1];
 reverseString(input.substr(0, input.length()-1));
}

void reverseString(char input[], int size){
    char temp;
    printString(input, size);
    for(int i=0; i < size/2;i++){
        temp = input[i];
        input[i] = input[size-i-1];
        input[size-i-1] = temp;
    }
    printString(input, size);
}

int reverseInteger(int x){
   int digits = round(log10(x));
   int res = 0;
   int i=0;
   while(digits > -1){
       int high = (int) pow(10,digits--);
       res = res + x/high * pow(10, i++);
       x = x - x/high * high;
   }
   return res;
}






// Array test
// Remove Duplicates from Sorted Array, modifying the input array in-place with O(1) extra memory.
//  https://leetcode.com/explore/featured/card/top-interview-questions-easy/92/array/727/

int removeDup(int arr[], int len){
    int j=0;
    cout<<*arr<<endl;
    for(int i=0; i<len;i++){
        if(arr[i] != arr[i+1]){
           j++;
           arr[j]=arr[i+1];
        }
    }
    printArr(arr, j);
    return j;
}

int removeDup(vector<int> &nums){
 int j=0;
 for(int i=0; i< nums.size(); i++){
     if(nums[i] != nums[i+1]){
       j++;
       nums[j]=nums[i+1];
     }
 }
 printVector(nums);
 return j;
}







int main(int argc, char** argv){
    cout<<"begin algo test: "<<endl;
    // reverseString(argv[1]);
    // int arr[7] = {1,1,1,2,3,3,4};
    // removeDup(arr, 7);
    // vector<int> vec{1,1,1,2,3,3,4,4, 5, 7,7};
    // removeDup(vec);
    // char input[7]="123456";
    // reverseString(input,6);
    int a=12345;
    cout<<"before operation: "<<a<<endl;
    int res=reverseInteger(a);
    cout<<"after operation: "<<res<<endl;
    return 0;
}

