#include <vector>
#include "../common.h"
#include <iostream>
#include <deque>
using namespace std;

// 395. Longest Substring with At Least K Repeating Characters
//  4 ms, faster than 77.54%
//  6.6 MB, less than 87.19%
int longestSubstring(string s, int k)
{
    int len = s.size();
    if (k == 1)
        return len;
    vector<int> lettersm(26, 0);
    int maxUnique = 0;
    for (int i = 0; i <= len - 1; ++i)
    {
        if (lettersm[s[i] - 'a'] == 0)
            maxUnique++;
        lettersm[s[i] - 'a']++;
    }
    lettersm.clear();
    int ans = 0;
    for (int unique = 1; unique <= maxUnique; ++unique)
    {
        int start = 0, end = -1, uni = 0;
        vector<int> letters(26, 0);
        int counterAtLeastK = 0;
        while (end < len)
        {
            // expand
            if (uni <= unique)
            {
                end++;
                if (end == len)
                    break;
                if (letters[s[end] - 'a'] == 0)
                {
                    uni++;
                }
                letters[s[end] - 'a']++;
                if (letters[s[end] - 'a'] == k)
                    counterAtLeastK++;
            }
            else // shrink
            {
                if (letters[s[start] - 'a'] == 1)
                {
                    uni--;
                }
                letters[s[start] - 'a']--;
                if (letters[s[start] - 'a'] == k - 1)
                    counterAtLeastK--;
                start++;
            }
            if (uni == unique && counterAtLeastK == unique)
            {
                ans = max(ans, end - start + 1);
            }
        }
    }
    return ans;
}

void testlongestSubstring()
{
    string s = "";
    int k = 0;
    s = "abababbdabcabc", k = 2;
    cout << "longestSubstring of " << s << " with at least " << k << " Repeating Characters is " << longestSubstring(s, k) << endl;

    s = "aaabb", k = 3;
    cout << "longestSubstring of " << s << " with at least " << k << " Repeating Characters is " << longestSubstring(s, k) << endl;

    s = "ababbc", k = 2;
    cout << "longestSubstring of " << s << " with at least " << k << " Repeating Characters is " << longestSubstring(s, k) << endl;
}

// 239. Sliding Window Maximum
// : 424 ms, faster than 46.16%
// 115 MB, less than 41.40% o
vector<int> maxSlidingWindow(vector<int> &nums, int k)
{
    deque<int> win;
    vector<int> ans(nums.size() - k + 1, 0);
    for (int i = 0; i < nums.size(); i++)
    {
        while (!win.empty() && (i - win.front() + 1 > k))
        {
            win.pop_front();
        }
        while (!win.empty() && nums[i] > nums[win.back()])
        {
            win.pop_back();
        }
        win.push_back(i);
        if (i >= k - 1)
            ans[i - k + 1] = nums[win.front()];
    }
    return ans;
}

vector<int> maxSlidingWindowWrapper(my2arr &nums)
{
    return maxSlidingWindow(nums[0], nums[1][0]);
}

my2DCases testmaxSlidingWindow()
{
    return {
        {{1, 3, 1, 2, 0, 5}, {3}},
        {{1, 3, -1, -3, 5, 3, 6, 7}, {3}},
        {{1}, {1}},
        {{1, -1}, {1}},
        {{9, 11}, {2}},
        {{4, -2}, {2}},
    };
}

int main(int argc, char const *argv[])
{
    // testlongestSubstring();
    format_test(maxSlidingWindowWrapper, testmaxSlidingWindow);
    return 0;
}
