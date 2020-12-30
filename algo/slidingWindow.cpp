#include <vector>
#include "../common.h"
#include<iostream>
using namespace std;

// 395. Longest Substring with At Least K Repeating Characters
    int longestSubstring(string s, int k) {
        
    }

    void testlongestSubstring(){
        string s="";
        int k=0;

        s = "aaabb", k = 3;
        cout<<"longestSubstring of "<<s << " with at least "<<k <<" Repeating Characters is "<<longestSubstring(s,k)<<endl;

       s = "ababbc", k = 2;
        cout<<"longestSubstring of "<<s << " with at least "<<k <<" Repeating Characters is "<<longestSubstring(s,k)<<endl;

    }



// 239. Sliding Window Maximum
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
}

vector<int> maxSlidingWindowWrapper(my2arr &nums)
{
    maxSlidingWindow(nums[0], nums[1][0]);
}

my2DCases testmaxSlidingWindow()
{
    return {
        {{1, 3, -1, -3, 5, 3, 6, 7}, {3}},
        {{1}, {1}},
        {{1, -1}, {1}},
        {{9, 11}, {2}},
        {{4, -2}, {2}},
    };
}

int main(int argc, char const *argv[])
{
    format_test(maxSlidingWindowWrapper,testmaxSlidingWindow);
    return 0;
}
