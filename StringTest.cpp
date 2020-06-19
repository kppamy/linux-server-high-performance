#include <string>
#include <iostream>
using namespace std;
class StringTest
{
public:
    // 3. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s)
    {
        int len = s.length();

        if (len <= 1)
            return len;
        int i = 0;
        int max = 0;
        int j = i + 1;
        for (; j < len; j++)
        {
            int sub = 1;
            for (int k = i; k < j; k++)
            {

                if (s[j] != s[k])
                {
                    sub++;
                }
                else
                {
                    i = k + 1;
                    break;
                }
                if (k == j - 1)
                {
                    max = sub > max ? sub : max;
                }
            }
        }
        return max;
    }

    // Find the length of the longest substring T of a given string (consists of lowercase letters only)
    //  such that every character in T appears no less than k times.
    int lengthOfLongestSubstringWithKRepeates(string s, int k)
    {
        int len = s.length();
        if (k == 1)
        {
            return len;
        }
        else if (len < k)
        {
            return 0;
        }

        int couter[26] = {0};
        int j = 0;

        for (j = 0; j < len; j++)
        {
            int pos = (s[j] - 'a');
            couter[pos]++;
        }
        bool bad[26] = {false};
        for (int i = 0; i < 26; i++)
        {
            if (couter[i] < k)
            {
                bad[i] = 1;
            }
        }
        bool allgood = true;
        int max = 0;
        for (int i = 0; i < len; i++)
        {
            if (bad[s[i] - 'a'])
            {
                allgood = false;
                int sub0 = 0;
                if (i > 0)
                    sub0 = lengthOfLongestSubstringWithKRepeates(s.substr(0, i), k);
                int sub1 = lengthOfLongestSubstringWithKRepeates(s.substr(i + 1), k);
                max = sub0 > sub1 ? sub0 : sub1;
            }
        }
        if (allgood)
            max = max >= len ? max : len;
        return max;
    }

    // 1143. Longest Common Subsequence
    int longestCommonSubstring(string text1, string text2)
    {
        int len1 = text1.length();
        int len2 = text2.length();
        if (len1 * len2 == 0)
        {
            return 0;
        }

        if (text1 == text2)
        {
            return len1;
        }
        int max1 = 0;
        max1 = longestCommonSubsequence(text1.substr(0, len1 - 1), text2);
        int max2 = longestCommonSubsequence(text1.substr(0, len1 - 1), text2.substr(0, len2 - 1));
        max1 = max1 > max2 ? max1 : max2;
        int max3 = longestCommonSubsequence(text1, text2.substr(0, len2 - 1));
        max1 = max1 > max3 ? max1 : max3;
        return max1;
    }

    // 1143. Longest Common Subsequence DP
    int longestCommonSubsequence(string text1, string text2)
    {
        int len1 = text1.length();
        int len2 = text2.length();
        if (len1 * len2 == 0)
        {
            return 0;
        }

        if (text1[len1 - 1] == text2[len2 - 1])
        {
            return (longestCommonSubsequence(text1.substr(0, len1 - 1), text2.substr(0, len2 - 1)) + 1);
        }

        int max1 = 0;
        max1 = longestCommonSubsequence(text1.substr(0, len1 - 1), text2);
        int max3 = longestCommonSubsequence(text1, text2.substr(0, len2 - 1));
        max1 = max1 > max3 ? max1 : max3;
        return max1;
    }

    // 214. Shortest Palindrome
    string shortestPalindrome(const string &s)
    {
        int len = s.length();
        if (len <= 1)
            return s;
        int i = 0;
        int j = len - 1;
        int counter=0;
        string ns = s;
        while (counter < j)
        {
            if (ns[i] != s[j])
                ns = ns.substr(0, i) + s[j] + s.substr(counter,len-counter);
            else
                counter++;
            i++;
            j--;
        }
        return ns;
    }
};

int main(int argc, char const *argv[])
{
    StringTest st;
    string input;
    while (true)
    {
        cin >> input;

        if (input == "q")
        {
            break;
        }
        // cout<< "longest of "<<input<<" is "<<st.lengthOfLongestSubstring(input)<<endl;
        // cout << "lengthOfLongestSubstringWithKRepeates of " << input << " is " << st.lengthOfLongestSubstringWithKRepeates(input, 3) << endl;
        // string input2;
        // cin >> input2;
        // cout << "longestCommonSubsequence of " << input << " and  " << input2 << " is "
        //      << st.longestCommonSubsequence(input, input2) << endl;

        cout << "shortestPalindrome of " << input << " is  " << st.shortestPalindrome(input) << endl;
    }
    return 0;
}
