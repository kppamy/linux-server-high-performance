#include <string>
#include <iostream>
#include <vector>
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
        vector<vector<int>> lcs(len1, vector<int>(len2, 0));

        for (int j = 0; j < len2 - 1; j++)
        {
            if (text1[0] == text2[j])
            {
                lcs[0][j] = 1;
            }
            lcs[0][j + 1] = lcs[0][j];
        }

        for (int j = 0; j < len1 - 1; j++)
        {
            if (text1[j] == text2[0])
            {
                lcs[j][0] = 1;
            }
            lcs[j + 1][0] = lcs[j][0];
        }

        for (int i = 1; i < len1; i++)
        {
            for (int j = 1; j < len2; j++)
            {
                if (text1[i] == text2[j])
                    lcs[i][j] = lcs[i - 1][j - 1] + 1;
                else
                {
                    lcs[i][j] = lcs[i - 1][j] > lcs[i][j - 1] ? lcs[i - 1][j] : lcs[i][j - 1];
                }
            }
        }

        return lcs[len1 - 1][len2 - 1];

        // if (text1[len1 - 1] == text2[len2 - 1])
        // {
        //     return (longestCommonSubsequence(text1.substr(0, len1 - 1), text2.substr(0, len2 - 1)) + 1);
        // }

        // int max1 = 0;
        // max1 = longestCommonSubsequence(text1.substr(0, len1 - 1), text2);
        // int max3 = longestCommonSubsequence(text1, text2.substr(0, len2 - 1));
        // max1 = max1 > max3 ? max1 : max3;
        // return max1;
    }

    void testlongestCommonSubsequence()
    {
        StringTest st;
        string text1 = "ylqpejqbalahwr", text2 = "yrkzavgdmdgtqpg";
        cout << "longestCommonSubsequence of " << text1 << " and  " << text2 << " is "
             << st.longestCommonSubsequence(text1, text2) << endl;
        // cout << "longestCommonString of " << text1 << " and  " << text2 << " is "
        //     << st.longestCommonSubstring(text1, text2) << endl;

        text1 = "bl", text2 = "yby";

        cout << "longestCommonSubsequence of " << text1 << " and  " << text2 << " is "
             << st.longestCommonSubsequence(text1, text2) << endl;

        text1 = "abcde", text2 = "ace";
        cout << "longestCommonSubsequence of " << text1 << " and  " << text2 << " is "
             << st.longestCommonSubsequence(text1, text2) << endl;
        // cout << "longestCommonString of " << text1 << " and  " << text2 << " is "
        //     << st.longestCommonSubstring(text1, text2) << endl;

        text1 = "abc", text2 = "abc";
        cout << "longestCommonSubsequence of " << text1 << " and  " << text2 << " is "
             << st.longestCommonSubsequence(text1, text2) << endl;
        // cout << "longestCommonString of " << text1 << " and  " << text2 << " is "
        //     << st.longestCommonSubstring(text1, text2) << endl;

        text1 = "abc", text2 = "def";
        cout << "longestCommonSubsequence of " << text1 << " and  " << text2 << " is "
             << st.longestCommonSubsequence(text1, text2) << endl;
        // cout << "longestCommonString of " << text1 << " and  " << text2 << " is "
        //     << st.longestCommonSubstring(text1, text2) << endl;
    }

    // 214. Shortest Palindrome
    string shortestPalindrome(const string &s)
    {
        int len = s.length();
        if (len <= 1)
            return s;
        int i = 0;
        int j = len - 1;
        int counter = 0;
        string ns = s;
        while (counter < j)
        {
            if (ns[i] != s[j])
                ns = ns.substr(0, i) + s[j] + s.substr(counter, len - counter);
            else
                counter++;
            i++;
            j--;
        }
        return ns;
    }

    //    5. Longest Palindromic Substring
    string longestPalindrome(string s)
    {
        //reverse s to t
        // find longest common str of S
        int len = s.length();
        int max = 0, begin = 0;
        for (int m = 0; m < len; m++)
        {
            int j = len - 1;
            int i = m;
            int sum = 0;
            while (i < len && j >= 0)
            {
                if (s[i] != s[j])
                {
                    sum = 0;
                }
                else
                {
                    i++;
                    sum++;
                }
                j--;
            }
            if (sum > max)
            {
                max = sum;
                begin = m;
            }

            if (sum > len - i - 1)
            {
                break;
            }
        }

        if (max <= 1)
            return "";
        //constitute the solution
        return s.substr(begin, max);
    }

    void testlongestPalindrome()
    {
        cout << "longestPalindrome of babad  is " << longestPalindrome("babad") << endl;
        cout << "longestPalindrome of cbbd  is " << longestPalindrome("cbbd") << endl;
    }
};

void testlengthOfLongestSubstringWithKRepeates()
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
        cout << "longest of " << input << " is " << st.lengthOfLongestSubstring(input) << endl;
        cout << "lengthOfLongestSubstringWithKRepeates of " << input << " is " << st.lengthOfLongestSubstringWithKRepeates(input, 3) << endl;
    }
}

#include <algorithm>
// 67. Add Binary
// Runtime: 4 ms, faster than 85.92% of C++ online submissions for Add Binary.
// Memory Usage: 6.6 MB, less than 61.57% of C++ online submissions for Add Binary.
string addBinary(string a, string b)
{
    int carry = 0;
    int i = a.size() - 1;
    int j = b.size() - 1;
    string res = "";
    while (i >= 0 || j >= 0)
    {
        int sum = 0;
        sum += carry;
        if (i >= 0)
            sum += a[i--] - '0';
        if (j >= 0)
            sum += b[j--] - '0';
        res += to_string(sum % 2);
        carry = sum / 2;
    }
    if (carry)
    {
        res += to_string(carry);
    }
    reverse(res.begin(), res.end());
    return res;
}

void testaddBinary()
{
    string a = "11", b = "1";
    cout << a << " + " << b << " = " << addBinary(a, b) << endl;
    a = "1010", b = "1011";
    cout << a << " + " << b << " = " << addBinary(a, b) << endl;
    a = "10", b = "1";
    cout << a << " + " << b << " = " << addBinary(a, b) << endl;
}

// 415. Add Strings
// Runtime: 4 ms, faster than 93.78% of C++ online submissions for Add Strings.
// Memory Usage: 7.1 MB, less than 31.44% of C++ online submissions for Add Strings.
string addStrings(string num1, string num2)
{
    int i = num1.size() - 1;
    int j = num2.size() - 1;
    int carry = 0;
    string res = "";
    while (i >= 0 || j >= 0)
    {
        int sum = carry;
        if (i >= 0)
            sum += num1[i--] - '0';
        if (j >= 0)
            sum += num2[j--] - '0';
        res += to_string(sum % 10);
        carry = sum / 10;
    }
    if (carry)
        res += to_string(carry);
    reverse(res.begin(), res.end());
    return res;
}

void testAddString()
{
    string a = "1", b = "19";
    cout << a << " + " << b << " = " << addStrings(a, b) << endl;
    a = "1", b = "17";
    cout << a << " + " << b << " = " << addStrings(a, b) << endl;
    a = "1", b = "9";
    cout << a << " + " << b << " = " << addStrings(a, b) << endl;
}

#include <array>
// 859. Buddy Strings
// Runtime: 4 ms, faster than 87.09% of C++ online submissions for Buddy Strings.
// Memory Usage: 7.2 MB, less than 6.03% of C++ online submissions for Buddy Strings.
bool buddyStrings(string A, string B)
{
    int sa = A.size();
    if (sa != B.size())
        return false;
    int i = 0;
    int df[2] = {-1};
    int cnts = 0;
    for (i = 0; i < sa; i++)
    {
        if (A[i] == B[i])
        {
            continue;
        }
        else
        {
            if (cnts >= 2)
                return false;
            df[cnts++] = i;
        }
    }
    if (cnts == 1)
        return false;
    if (cnts == 0)
    {
        int counter[26] = {0};
        i = 0;
        while (i < sa)
        {
            counter[A[i] - 'a']++;
            if (counter[A[i] - 'a'] == 2)
                return true;
            i++;
        }
        return false;
    }
    char tmp = A[df[0]];
    A[df[0]] = A[df[1]];
    A[df[1]] = tmp;
    return A == B;
}

void testbuddyStrings()
{
    string A = "ab", B = "ba";
    cout << A << " and " << B << " is " << ((buddyStrings(A, B)) ? "" : "not") << " buddy string" << endl;
    A = "ab", B = "ab";
    cout << A << " and " << B << " is " << ((buddyStrings(A, B)) ? "" : "not") << " buddy string" << endl;
    A = "aa", B = "aa";
    cout << A << " and " << B << " is " << ((buddyStrings(A, B)) ? "" : "not") << " buddy string" << endl;
    A = "aaaaaaabc", B = "aaaaaaacb";
    cout << A << " and " << B << " is " << ((buddyStrings(A, B)) ? "" : "not") << " buddy string" << endl;
}

#include "common.h"

// 1455. Check If a Word Occurs As a Prefix of Any Word in a Sentence
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Check If a Word Occurs As a Prefix of Any Word in a Sentence.
// Memory Usage: 7.9 MB, less than 100.00% of C++ online submissions for Check If a Word Occurs As a Prefix of Any Word in a Sentence.
int isPrefixOfWord(string sentence, string searchWord)
{
    vector<std::string> splts = split(sentence, " ");
    for (int i = 0; i < splts.size(); i++)
    {
        string val = splts[i];
        if (val.find(searchWord) == 0)
            return (i + 1);
    }
    return -1;
}

void testisPrefixOfWord()
{
    string sentence = "i love eating burger", searchWord = "burg";
    cout << searchWord << " is at " << isPrefixOfWord(sentence, searchWord) << " of " << sentence << endl;

    sentence = "this problem is an easy problem", searchWord = "pro";
    cout << searchWord << " is at " << isPrefixOfWord(sentence, searchWord) << " of " << sentence << endl;

    sentence = "i am tired", searchWord = "you";
    cout << searchWord << " is at " << isPrefixOfWord(sentence, searchWord) << " of " << sentence << endl;

    sentence = "i use triple pillow", searchWord = "pill";
    cout << searchWord << " is at " << isPrefixOfWord(sentence, searchWord) << " of " << sentence << endl;

    sentence = "hello from the other side", searchWord = "they";
    cout << searchWord << " is at " << isPrefixOfWord(sentence, searchWord) << " of " << sentence << endl;
}

// 1170. Compare Strings by Frequency of the Smallest Character
// Runtime: 128 ms, faster than 27.66% of C++ online submissions for Compare Strings by Frequency of the Smallest Character.
// Memory Usage: 11.8 MB, less than 5.36% of C++ online submissions for Compare Strings by Frequency of the Smallest Character.
vector<int> numSmallerByFrequency(vector<string> &queries, vector<string> &words)
{
    auto f = [](vector<string> &warray) {
        int sz = warray.size();
        vector<int> cnts(sz, 0);
        for (int i = 0; i < sz; i++)
        {
            string word = warray[i];
            char smallest = 'z' + 1;
            int freq = 0;
            for (int j = 0; j < word.size(); j++)
            {
                if (word[j] < smallest)
                {
                    freq = 1;
                    smallest = word[j];
                }
                else if (word[j] == smallest)
                {
                    freq++;
                }
            }
            cnts[i] = freq;
        }
        return cnts;
    };
    vector<int> qc = f(queries);
    vector<int> wc = f(words);
    for (int i = 0; i < qc.size(); i++)
    {
        int sum = 0;
        for (int j = 0; j < wc.size(); j++)
        {
            if (qc[i] < wc[j])
                sum++;
        }
        qc[i] = sum;
    }
    return qc;
}

// 1446. Consecutive Characters
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Consecutive Characters.
// Memory Usage: 7 MB, less than 100.00% of C++ online submissions for Consecutive Characters.
int maxPower(string s)
{
    int i = 0, j = 1;
    int power = 1;
    while (j < s.size())
    {
        if (s[j] != s[i])
        {
            power = (j - i > power) ? (j - i) : power;
            i = j;
        }
        j++;
    }
    if (j - i != 1)
        power = (j - i > power) ? (j - i) : power;
    return power;
}

void testmaxPower()
{
    string s = "leetcode";
    cout << "max power of " << s << " is " << maxPower(s) << endl;
    s = "abbcccddddeeeeedcba";
    cout << "max power of " << s << " is " << maxPower(s) << endl;
    s = "triplepillooooow";
    cout << "max power of " << s << " is " << maxPower(s) << endl;
    s = "hooraaaaaaaaaaay";
    cout << "max power of " << s << " is " << maxPower(s) << endl;
    s = "tourist";
    cout << "max power of " << s << " is " << maxPower(s) << endl;
}

void testnumSmallerByFrequency()
{
    vector<string> queries = {"cbd"}, words = {"zaaaz"};
    vector<int> res = numSmallerByFrequency(queries, words);
    queries = {"bbb", "cc"}, words = {"a", "aa", "aaa", "aaaa"};
    res = numSmallerByFrequency(queries, words);
}

bool ends_with(const string &a, const string &b)
{
    int sb = b.size();
    int sa = a.size();
    while (sb > 0)
    {
        if (b[sb - 1] == a[sa - 1])
        {
            sb--;
            sa--;
        }
        else
        {
            return false;
        }
    }
    return true;
}
int countBinarySubstrings(string s)
{
    int len = s.size();
    string zero = "";
    string one = "";
    vector<string> patterns;
    int num = len / 2;
    while (num-- > 0)
    {
        zero.append("0");
        one.append("1");
        patterns.push_back(one + zero);
        patterns.push_back(zero + one);
    }
    int cnts = 0;
    int lenp = patterns.size();
    auto counter = [&](int start) {
        for (int i = start; i < lenp; i += 2)
        {
            string pat = patterns[i];
            if (pat == "")
                continue;
            vector<string> arr = split(s, pat);
            int as = arr.size();
            if (arr[0] == s)
                break;
            if (ends_with(s, pat))
                as = as + 1;
            cnts += as - 1;
        }
    };
    counter(0);
    counter(1);
    return cnts;
}

void testcountBinarySubstrings()
{
    string b = "00110011";
    cout << "numer of BinarySubstrings of " << b << " is " << countBinarySubstrings(b) << endl;

    b = "10101";
    cout << "numer of BinarySubstrings of " << b << " is " << countBinarySubstrings(b) << endl;
    b = "00110";
    cout << "numer of BinarySubstrings of " << b << " is " << countBinarySubstrings(b) << endl;
}

int main(int argc, char const *argv[])
{
    // StringTest st;
    // // st.testlongestPalindrome();
    // st.testlongestCommonSubsequence();
    // testaddBinary();
    // testAddString();
    // testbuddyStrings();
    // testisPrefixOfWord();
    // testnumSmallerByFrequency();
    // testmaxPower();
    testcountBinarySubstrings();
    return 0;
}
