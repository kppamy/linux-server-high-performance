#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

// 409. Longest Palindrome
//  4 ms, faster than 83.73%
// 6.8 MB, less than 86.37%
int longestPalindrome(string s)
{
    int ans = 1;
    int slen = s.size();
    map<char, int> cnt;
    for (int i = 0; i < slen; ++i)
    {
        char c = s[i];
        if (cnt.find(c) != cnt.end())
        {
            cnt[c]++;
        }
        else
            cnt[c] = 1;
    }
    int ones = 0;
    for (auto &[key, val] : cnt)
    {
        if (val % 2)
            ones++;
    }

    return ones > 0 ? (slen - ones + 1) : slen;
}

void testlongestPalindrome()
{
    vector<string> cases = {
        "bananas",
        "a",
        "bb",
        "abccccdd"};
    for (auto &str : cases)
    {
        cout << str << " can format longestPalindrome: " << longestPalindrome(str) << endl;
    }
}

// 227. Basic Calculator II
// 16 ms, faster than 47.73%
//  9.1 MB, less than 50.52%
int calculate(string s)
{
    int nlen = s.size();
    deque<int> sta;
    auto peek = [&s, nlen](int i, int *number) {
        int num = 0;
        while (i < nlen)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }
            int c = s[i] - '0';
            if (c >= 0 && c <= 9)
            {
                num = num * 10 + c;
                i++;
            }
            else
                break;
        }
        *number = num;
        return i;
    };

    for (int i = 0; i < nlen;)
    {

        if (s[i] == ' ')
        {
            i++;
            continue;
        }
        if (s[i] == '+' || s[i] == '-')
        {
            sta.push_back(s[i] - '0');
            i++;
            continue;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            int left;
            i = peek(i, &left);
            sta.push_back(left);
        }
        else
        {
            int left = sta.back();
            sta.pop_back();
            char oper = s[i];
            int right = 0;
            i = peek(i + 1, &right);
            int expr = 0;
            if (oper == '*')
                expr = left * right;
            else
                expr = left / right;
            sta.push_back(expr);
        }
    }
    while (!sta.empty())
    {
        int left = sta.front();
        sta.pop_front();
        if (sta.empty())
            return left;
        char oper = sta.front() + '0';
        sta.pop_front();
        int right = sta.front();
        sta.pop_front();
        int exp = 0;
        if (oper == '-')
        {
            exp = left - right;
        }
        else if (oper == '+')
        {
            exp = left + right;
        }
        if (!sta.empty())
        {
            sta.push_front(exp);
        }
        else
            return exp;
    }
    return 0;
}

void testCalculate()
{
    vector<string> cases = {
        "0-2147483647",
        "1-1+1",
        "42",
        "42+3*4",
        "42+3*40",
        "3+2*2",
        " 3/2 ",
        " 3+5 / 2 ",
    };
    for (auto &&str : cases)
    {
        cout << str << " = " << calculate(str) << endl;
    }
}

// 647. Palindromic Substrings
//  188 ms, faster than 15.31%
// 6.3 MB, less than 97.71%
int countSubstrings(string s)
{
    int len = s.size();
    int ans = len;
    auto isPalindromic = [&s](int start, int end) {
        while (start <= end)
        {
            if (s[start] != s[end])
                return false;
            start++;
            end--;
        }
        return true;
    };
    for (int i = 0; i < len - 1; ++i)
    {
        for (int j = i + 1; j < len; ++j)
        {
            if (isPalindromic(i, j))
                ans++;
        }
    }
    return ans;
}

void testcountSubstrings()
{
    vector<string> cases = {
        "abc",
        "aaa",
        "abab",
    };
    for (auto &&str : cases)
    {
        cout << str << " has " << countSubstrings(str) << " repeated palindromic Substring" << endl;
    }
}

// 686. Repeated String Match
// 172 ms, faster than 20.30%
// 341.6 MB, less than 6.11%
int repeatedStringMatch(string a, string b)
{
    int lena = a.size();
    int lenb = b.size();
    string ra = "";
    int rpt = 1;
    while (true)
    {
        ra = ra + a;
        if (ra.find(b) != -1)
            return rpt;
        if (ra.size() > lena + lenb - 1)
            return -1;
        rpt++;
    }
    return -1;
}

void testRepeatedStringMatch()
{
    string a = "abcd", b = "cdabcdab";
    cout << a << " repeat " << repeatedStringMatch(a, b) << " times can be " << b << endl;

    "a", b = "aa";
    cout << a << " repeat " << repeatedStringMatch(a, b) << " times can be " << b << endl;

    a = "a", b = "a";
    cout << a << " repeat " << repeatedStringMatch(a, b) << " times can be " << b << endl;

    a = "abc", b = "wxyz";
    cout << a << " repeat " << repeatedStringMatch(a, b) << " times can be " << b << endl;
}

// 459. Repeated Substring Pattern
// 20 ms, faster than 77.21%
// 44.1 MB, less than 28.37%
bool repeatedSubstringPattern(string s)
{

    int len = s.size();
    for (int win = len / 2; win > 0; win--)
    {
        if (len % win)
            continue;
        int rpt = len / win;
        string pre = s.substr(0, win);
        string ns = pre;
        while (rpt > 1)
        {
            ns += pre;
            rpt--;
        }
        if (ns == s)
            return true;
    }
    return false;
}

void testrepeatedSubstringPattern()
{
    vector<string> cases = {
        "ababab",
        "bb",
        "abab",
        "aba",
        "abcabcabcabc"};
    for (auto &&str : cases)
    {
        cout << str << " is " << (repeatedSubstringPattern(str) ? "" : " not ") << "repeatedSubstringPattern" << endl;
    }
}

// 205. Isomorphic Strings
//  4 ms, faster than 94.72%
//  6.9 MB, less than 99.64%
bool isIsomorphic(string s, string t)
{
    int ls = s.size();
    map<char, char> dcts;
    map<char, char> rdcts;
    for (int i = 0; i < ls; ++i)
    {
        if (dcts.find(s[i]) != dcts.end())
        {
            s[i] = dcts[s[i]];
        }
        else
        {
            if (rdcts.find(t[i]) != rdcts.end() && rdcts[t[i]] != s[i])
                return false;
            dcts[s[i]] = t[i];
            rdcts[t[i]] = s[i];
            s[i] = t[i];
        }
    }
    return s == t;
}

void testisIsomorphic()
{
    string s = "egcd", t = "adfd";
    cout << s << " and " << t << " is " << (isIsomorphic(s, t) ? "" : " not ") << "isomorphic" << endl;

    s = "badc", t = "baba";
    cout << s << " and " << t << " is " << (isIsomorphic(s, t) ? "" : " not ") << "isomorphic" << endl;

    s = "egg", t = "add";
    cout << s << " and " << t << " is " << (isIsomorphic(s, t) ? "" : " not ") << "isomorphic" << endl;

    s = "foo", t = "bar";
    cout << s << " and " << t << " is " << (isIsomorphic(s, t) ? "" : " not ") << "isomorphic" << endl;

    s = "paper", t = "title";
    cout << s << " and " << t << " is " << (isIsomorphic(s, t) ? "" : " not ") << "isomorphic" << endl;
}

vector<int> kmpJump(const string &str)
{
    int len = str.size();
    vector<int> next(len, -1);
    for (int i = 1, p = -1; i < len; i++)
    {
        while (p != -1 && str[p + 1] != str[i])
        {
            p = next[p];
        }
        if (str[p + 1] == str[i])
        {
            p++;
        }
        next[i] = p;
    }
    return move(next);
}

// 28. Implement strStr()
// 4 ms, faster than 65.35%
// 7 MB, less than 96.63%
int strStr(string haystack, string needle)
{
    int hlen = haystack.size();
    int nlen = needle.size();
    int i = 0;
    vector<int> &&next = kmpJump(needle);
    int matched = -1;
    while (i < hlen)
    {
        while (matched != -1 && haystack[i] != needle[matched + 1])
        {
            matched = next[matched];
        }
        if (needle[matched + 1] == haystack[i])
        {
            matched++;
        }
        if (matched == nlen - 1)
            return i - nlen + 1;
        i++;
    }

    return -1;
}

// 28. Implement strStr()
//  0 ms, faster than 100.00%
//  7 MB, less than 79.47% o
int strStrBruteForce(string haystack, string needle)
{
    int hlen = haystack.size();
    int nlen = needle.size();
    int start = 0, i = start, j = 0;
    while (i < hlen && j < nlen)
    {
        if (needle[j] == haystack[i])
        {
            j++;
            i++;
        }
        else
        {
            j = 0;
            start++;
            i = start;
        }
    }
    if (j == nlen)
        return i - nlen;
    return -1;
}

void testStrStr()
{
    string haystack = "mississippi", needle = "issip";
    cout << needle << " is at " << strStr(haystack, needle) << "th of " << haystack << endl;

    haystack = "mississippi", needle = "issipi";
    cout << needle << " is at " << strStr(haystack, needle) << "th of " << haystack << endl;

    haystack = "hello", needle = "ll";
    cout << needle << " is at " << strStr(haystack, needle) << "th of " << haystack << endl;

    haystack = "aaaaa", needle = "bba";
    cout << needle << " is at " << strStr(haystack, needle) << "th of " << haystack << endl;

    haystack = "", needle = "";
    cout << needle << " is at " << strStr(haystack, needle) << "th of " << haystack << endl;
}

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

    //    5. Longest Palindromic Substring
    string longestPalindrome5(string s)
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

    void testlongestPalindrome5()
    {
        cout << "longestPalindrome of bananas  is " << longestPalindrome5("bananas") << endl;
        cout << "longestPalindrome of babad  is " << longestPalindrome5("babad") << endl;
        cout << "longestPalindrome of cbbd  is " << longestPalindrome5("cbbd") << endl;
        cout << "longestPalindrome of dddddddd  is " << longestPalindrome5("dddddddd") << endl;
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

#include "../common.h"

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

// 696. Count Binary Substrings
// Runtime: 24 ms, faster than 97.23% of C++ online submissions for Count Binary Substrings.
// Memory Usage: 14.4 MB, less than 5.55% of C++ online submissions for Count Binary Substrings.
int countBinarySubstrings(string s)
{
    vector<int> counter;
    int len = s.size();
    int i = 0, j = 1;
    while (j < len)
    {
        if (s[i] != s[j])
        {
            counter.push_back(j - i);
            i = j;
        }
        j++;
    }
    counter.push_back(j - i);
    int sz = counter.size();
    i = 0;
    int sum = 0;
    for (int i = 0; i < sz - 1; i++)
    {
        sum += min(counter[i], counter[i + 1]);
    }
    return sum;
}

void testcountBinarySubstrings()
{
    string b = "00110011";
    cout << "numer of BinarySubstrings of " << b << " is " << countBinarySubstrings(b) << endl;

    b = "10101";
    cout << "numer of BinarySubstrings of " << b << " is " << countBinarySubstrings(b) << endl;
    b = "00110";
    cout << "numer of BinarySubstrings of " << b << " is " << countBinarySubstrings(b) << endl;

    b = "11101000010001001100010110011100010110001110011011011011111000110010100000011111001010100100101011111000100100100000011010010011011100100100011011100111100111010100010100110010110010010011011010001001000101101011010110111001001111010000011000000111101111111101101101110011100001100100000111011010100001101110011110011000110001101010010000110010000100100110000011011011000101100100100010110001110010100100001110101011101100000010001110111011101100011100111101010000110110011111111011110001000100010001010000101010010111001100010111110001000010110110000011010110001000111000001100110110110011010101010011000111001001101100011110001111101101111111000101010100011110101010100011110111010010111000010001101000000101111000101001001110101110100010010101000101110011010100100101010000101101110111101110000111001000011011110001011000011001111100111011101110000000110111110011111101111000001011010100010000010110000011000100110010100001110010010101110100000010011111110111111111011000110101101011111000001110111110111011011101100011100100011100001101111100000100100111111010110111111001000100101010111010100011010000001100110110000110000100001101011011101011001010111001101100110111010110000110110100101100101100101000101101100101000101101101110111001110110111011011100100100010100100001110000101010000111001110010001110010001100000110111011000111101111000101010100101110010010101111101101100101001110010011100100000111110101001000110100111100010111111011010001001001011011111101000110101100001001101000101010101111101000011011010011000100011100100100100100011101111100110010110001000010010100100110111011000110011100100101011011110001011100001000101000111011010010111101111001010101111110010100001011110111010011001111000001001000001011011001001101001000111000010001010000001000111001110000010010111000111000101010010100010000010010001110011101001110110000011011110001010010000000010110101001011001000110110100100111101101111111000101000000001010011100000011110111011010001111100011110000110000110010010101011100100000111001101000111000110001010010101001110110100100000101010110101000000001100001010111011001110100110010101110000100110100100111011110101001010000001001011010011100011111001001100010000010010110111110100010100111101011100111010000000110010000100011001011001101001010110100010101100111010010100111101010110000100000010101110010100010001010100001000101001000110101010100110010010000101100101101110100011101000001000100110011001011010110011001110111110011011001110010000011011010001010100110111111000100110111010101001101110110101001011010001101111000011111000000101001001100111000000000011000010111011010011010101010100011001000000101101010100101111110000111101001100100111010101011000100001100001001100000111101110001010011011111111100001100100000111000000110000001011101010011100001000011101100010010110001100100000100111111110010110010001001001000101000000110110000010111000110011111100111101100000010010100101000101110000101101010101100111011100010110010110000000101100010011100111111001100110001010101110110101001110000000111101010111011100001101110110010010010011110011001001111001111100111110110100110010111010001100000001011100011111010111011011001000110000001101011011110011000010001100110010011100000011111100011100000011000000110110011110110011101110111001110111111100001111111011100011101000111000111000110010101111000011000111110111001001101000100010100010000111111011011110000110110000011001110011111001010010010101011110110110010101101111000010000111000000011010001101000110111000010011101001001100011111010110000101110110101101000001001000010100111001111011000000100111001000110010011001010110111110100011110000000111111000011111101101110100101011101101101010010100100101000110001111011000101100100111011010001010110001101000001111000001101010000111011001100011110100100100011111011101010100000001011011011011101100100110101001011010001100001110010001000110100100110111010110010011001011101111110001111011010010001100111111101101011101111100110111101100010010110000000101011000110111110011011100010000000111111000101111101100101011011110000100000110100011010100111100001111011101010111101111000100111011011011101101111110100111100000011000010101101011001110010100100111101111111100010101100000010010100100010111101010100101100000100111011001110110110001111000100101101011001010111101101000000001011111110010101110100100110011010100100011101111101001110001100101011000010110001101100010000011101100111111010111111101010010000000110110000010011110001010011001101111000011011011010100000101011000110110100001011000000000100100000001011110101111111101110100100010100010111110111111000101000101101011101100011000111011011110100011100001100110100000011000111100110011100000001001000000010101111100110101110111101010101000010010010001100101011000010101010011110100110110110101110111011011011010100010101110010101001000100001100111011111111100100111110101011010101001111110100110111001111111011000010100010100110011101000111111000101111100110100101001101000011010011111010010000101111000011100000001011011101001001111000100011101100010111101101110000001001011101000010111100001011001010100010011000001111010100101001010100010011010101011110110100111100001001001111101110110011000101100101011100111111111101100011111110110011101100110101001100000010010000011001101000110011011111111111101011100110010011010100001000010110111101011010110101100001101100001100011001001011111101010000100001101111011011001101100001000110101101010110111101111110011100110001010111000001101101100001100011000100110001001110110000011011000110011000011001111011111111101011111110001010100111101001010110110010110110000111001001101010101010110111000110110110011100101100001101100010011000010001011110000001111100011111000101111011010010011101111100001110111001011000011111111100111110100101110111100110101100101100011100010100110000011111100101000110000000110111011101111001111001110000000100011111000011001010111000111101100110010011110001011000010011011001011111010110000001001011000110110001010110010000111111111111101000000110110010111000101000110011111010110011000110111110111101010000011010110110010110100001011110101111101110101000110010100000111010010101001010011101000010110110001010011100110100000110001011000100001010100000000001100100100111010110001010010000111110110010010010100010010001111111101100111110100111010110010111000111001001100110101111110100000010010010101010001100001010010100010111011101000100001110100110010100110100111101011010000001111001011111101111101011011100100010110010100000011001000010100100010001001001101101000110010110101111011010010100110110100011010011011100010001000000000110100000000010011011100110100110000111100111100010000111000000011101010010001100110000100000110110011010000111111001001110110010100100100111010100101000110111101100011011100111010101010100101111010011010001011100010010011111000000000101010011100101000100101011100000101010011010011010100110011101010000001101111101101000110110101101100110001010000101011111010001100011000010110110110001111101010100011011100011101001010101110000101110110110000000101111001101001010000000011001001100100011110100111011001111110101110000001110010101110110011110000011101010011001000010110011010111011101010000110010110110100111100000011010101011111111000111110011011111101101001011100110001101010111110000111100010011011110101010101100001001100100111001111111101011000001000101010001111000000110111001111011010011110101001000110011011001000100011000101001011110011001110101110100101110101011100100011111001111000111010101111111101000100111100110000110111010100000011010111001100111110010101100011100110001100000000101110111100111011111000101001100110010000011101011111001101010111101111111010111110010110001111011001110001000001001101100010000001010110010101110111011111011111110111110010111010000111001011111000111100111011011010100100011110111111100001110101111111100011110000001000101001111011101010100110000001111000001111000111110100110101010010101101111110010010111000111100111010010111101101101000110000001101010110011010000000101101011000001110100101001100111010101011111000010111010100101110001010110110100001001111001110100011110111100010010011011111011111011010001010111100010100100001110111110001010010011100000010101010000111011110101100100011101010111110010000101001011110000111001110111001101001100000010010011001010101101010011001011001000111111101000001000010010111001000010000111010101011001100001010010011000100001111110100000111101010011011111111100010011010011110111001011110110100110010101111010000101100100010110010010011010100000010111010101101000101001000000000001000001001001111111111010100001010011000001111011110111111011001010001100001111011100101000010011001000011001100110101110110101101010001010110111101101111011110110111100011000100010110101001111010111111110001000101111111111111001101011010010100010011101101010111001010110111100111000111101101000101000110111100100001101000000100000100100100100001001111001010000101110110010101100011001100011011011101011001110001011111000100111010101000100100100001110110010010100101110100010101011001000110101001001111000001000100000110011011001111011101001011011100000111101001101000101011010011000111111010000010111101001111000000100110110110011110011100100100110111110010001111110101000100101111000011010100000010111111011100010111000010101001100101001101110010000010000000010011011111100000101111001001101010000101110010110100110000001011110000110111100001001001001000110011010110101101111000111011011010001001110111100000001100001011100111001011101110011000111011110010011000011000100010111000011101010110011000001110011110010110001000100110110100110111010000110010101011001101000101011000101011111100010011001111010110101100010101011010011000110101110100000101111110110100011010111001000000101101001101111000100101110010000000101000111001000001001101100001101110010110011100111010110011100010000101100001101000010110001111010011001010001111011001010100110011101011100011111010110101011011100110011110010001101101100110100100110000010111111001011110101101011000011111101100011111100111100001110110110001001100000101000010101100011010111011110001100011000100001001001010110110010101000001110011011101110011010001100000000101110010011000111111100100111010010101101010110101110111100011100111110100101100010001110101111100000100000111000011000100000110111000000111010100001111011111110011111000110000101001000000010111111110001101000010011010010011100100011111001100111001000100001010000011101111111001101110000100101000111001010111011100010001111010001110001100001111000011011010110100100010101111111110000011100011111001010011001010011011011110111101110001000111110100001000000001000101010010011010101101101110000100100000010001001011101010010010100011110111001001010110000101100010000100100011110110010100010111101101001100101010000101110001010110111100001010000111001011001111100110011110010111110001011011010001111000100100110000100010110011111010100010110110111010111111011011001001001110111100111110011100000111100101000110010110000010100010110111000000010110110110001010100101111111110111110010110010010011100010011001111101111001111001001000001100011000001001010110100101010010101011011110100000011001010111100000100100100001010101111111111011101110001010000010011101011101010100111010101000011101011101100001101001101011010100001011000010010000111010111110000011011000110011000001100000001111000101101101111000010100101001001000010101000110011111011110000111111011001011111010001000011111101110010101110011111101001011111000111001001100001010000010101001011100111100010101111001010000110000011101001000111011010000110000000100011110000101010010110000001010000110100110100001100100011100000010001010011111011100111000101101111111011010100110111100011110001100111000101011001010100010011111000000000011010011100010011010111110011101100001001010111000110001111010110101001100100100100100001110010100000010111100001111110100111011011111000111001001010011111001011010010111100011101111101111010110101100110100110011000111100110010110010101111011000111111111000100111101110110010000000111011011101001111100100001010010010111101001100101000010110011000100101101011100101100100011010101101001010110111101100100000000101110101001101000011101000110101111000100100110100110111011101011101011110101101000010110001000111010110011100001110110101001011110000110011111010100100000111110111111010010001011000110101011100100100000000010110110110000111010100010110001000010101110000010110111111000011011011100101001110101100110000000010001110001010000000010110010101000101111010010010111001100011101001001000011010000110110000001001001010011011111010011111110000100101010010100010010000101110111011000111010001001110101100111111101000100001111001110110001100011101111010101100010100001100010101011011100011111110111001011010100011111010010110100110110111111110000101111111001011010111111010110111100111101111001000100001000100010101011110101010010101111000001011010000010101100011101101011100111000101011100010110010011001111000000011101001011010010011001101000101011110001011010100000001111111111110101100110110000101110011011011110110100111101101100010110011001110001011000101110101000101110011000110100110100111011010010110110110001100010001010100100110001011111111000001011111110010110001010011001011010001101010110110000110111110101111101001011010011111011100101100111110101110000000100111101001000111000001010010000101111010011111000011101001100101110000001110111001110001101100011001001010110101011101110011111111100000010011101101100101000111001001010101010000110111100100101110010001111010101011000000110011111010111111001001111001011010000010011000001001111011011000110000010111011111111000111000011101110100111110101001100011100001111011010001001010111111100110100101010001110110100010010100110100011001010110011111001000010101100010101100001110010110111011101111100011010011101001001011001111011011100110001011001011011111011010100000010000111111100101011101001001111010000110100111110011010110010110010111001101101101011011110111011101011111110011101011010111101111001001101000100101000011011101000001100101011001101101100100101111100111101101010001001001111010110010110110000000101001010000101000111110011000011100001101000110010111100101110111100000100100001001111100011101110100111101010000100010101000111110100011100100010111111100100100011111010010101010110111101100110000101010010111000100011111100011001011110101011001100000011010011011011000000000111110000011010101101011001000001101011110011000001010110011000111001110110101110100000101010100001010110110000000100100101111000110011110100111001110010001010001000100110001101000000101101001110001010000110100011101011111010100110111101101011010110000011111100111101001100010000101010001000011100010101111100000110101100110000110001011110001010000110010101001111111111110100010111110011111110001010110100100000101001000110110110111011011000110010110101100011010001110101000011100001010110001110111111000101010001110011010001100000000001010110110101110100110110011101111010000010101111011101011010111010100101000110110001000011111000110000100000011111001110100110101111000010111101000100100000011000110101101110101010000001111011001001001010000001000010001101110001100101000010010110101110100111101000010110001111100111010010001100100011011101011101100000011111010000010010100111110011010011110010011100111011011011010011010011110110110100000111010010111001001000001000000001100011001000000101100011010100101000101011101001000010010000011100001011100000110010100101100011010000010110101000010110111101000101101111100101101111111001001011100100111001000000001001111000100001110111011000110110100010100010111000001000101011110110100111010100001111111001011001111111111100110000100001001100000100001100011010110010011100011011111010011011011100101001100000000011111111101000010101010011101110101111111011001000111110001010101011010100000010001101111011010111000011110001001010111000000010010101000011110100011100010010010101101110110011011110111111111101101011110101111001111000010110110011101101000000001111000101011100110100100000011001110001000010110111000011100011011110000101100010111111111101010001101100110110010101001110000011101110111011111011101100111111111000100101110111000100010001111010111100000001101100110011110000001001010100100011110101011110101100001001101000111110000111011000101101010100000011010111101000000111111100011010110001101010011000111000100000111011000010010101001000010011110010101001000111100111001011001110000101011101000011011011010100111000011010110111100111000100101101111101010100000111011011101000111111101111010100011000111110101111011000010001111010100010010010100001111110001100100100100000110101100001100011111001111011001001001110110011001100100110110001000110111111010011110111100100011111100001010100001100010101011010001001000011110100100100100111001011111000111100111011000110110110111010100010000010111001101111001110000010001111000001000010111001111000111101110111010110011011001011100110000100000110110101011100101100110000000111100100100101010010000111100011101000100110011001100101101001001110000111001000101000010110110110111001111000111111100100110110011011100010111000111001110011000101010011001110000100001001101001111100110011111111111011100101001011000101011011101001110001100001010001011001011110100001111101000000101100011010111001000100011101111010110010110110101010101110100110101010110101010001100100111001010100001111110100100100000100100110111000001100111001001011010111100000111100111100011010000101111111101000001110010001010000110000111001100010111000100010000011110011011000110110111000110010101100100100110001100000110000001100100100111001000110111110111110010110111100010100001000111010101010110010001110010011000011000001111110111111011110111001100000100100001111100001110010101111010011101000100111010100001011011001101010011110011000010101011000110000000111010001111011110110110111000000101010111000111011001110100100000100000101111110101111100111111000100100100100100111011010001001011000100111111100101011111001101101001000100111000010010000010101000001000100110110101000110001110110001101101010101011110111111110010010101100010100001101000101010110110110000100011110101001110010110101011000111110011111000011011101101110101101110110000001000110111010010100100011011100110010110111000110010110000001000000010111101110110001001111001011100100001011111011110110010011011110101101000010110100101000100100101011110011111101011011011001001001110100001100001011111100000111010001001010100010100001101100001001111100101010011110001001010110110000011000100011000110100001110010000010010000001001110001100110010100100000000100001111001100111111001111101011100001101110100011110000010110011011001010001010110011001000011111101011100000110010010110010010001110010000010000000101000011011100010101011001011110111111100010100111001001101111001000111011111110010100001100011101010000100000010001100100100100110100111111001100110010010100111000010101011100001001101101011001000100111010110001000011001100001000011110100110011110110111010100010110111001000100001011110001000010011000111011101010000010111111110000101101110110110111010000010111101001001110000010011101011110000110001101010011000110011000010010111001011011001101011001000001011001101001111101100110110101000111000100001111111000110011000101000100110101010110111010010110100111100100101110011000001000101111111001101001000001000111100000000001010011111010001110110110111000101010011111100100000111110010100100001000011110111101001100101101101101101101010010001001011011010101011101111111110110001100111001110110000100111101110001011010000000001110000110010101010011110010101001110110100100100111110101110011011000011011100101011101001010100100100000001111110100011111101011101100001101001001010000100011000100010010001101010000000011100011101101110000100100001110000011001010010100000010111100000101100111001111110000101100101101110111111111011010000111111011100100111000001111011110010110110100111010100010110001110011011001001111100100001001111001111000101011101110000010000011111010000011000011000010011101111101010011111110110100000000010001011000011111000100010110001101100001010100101101001010001111001000001011111011110000101000011011100000100101010101000011001001111100111000100111100110001000100100111110110001111110110111010111001101001100010001110100011001111011110010001101110101001001100111100111010000110010011011000000001001010101110101000100011001000011100010000001111011101011111110011110110110001001101001000111100001001100011101110101110001000010100010001100001011010111011100110011011010111011001000000111111000011011110011101111101011011101111010011000001110100010100101011011000110111100110100110110111100100000001001010110110101111100100001100111100010101010010011010011010111011010010100110100111011110100111100101000000110110110101000110010010111110101010101110011001101111000110100101101010010000011011001111000101001011100000111000000110010000101100100101011010101111001101010111100100000101101000100010010110110101000111011111100101010100011111010110001111111110001011011101011010010111101001011001000010001100100111111101010010010011111101000011100111011000100101000111110101100110110101111100010100101110001110100011101001100110010010011001110101000011000011000101110000100001001000111110000111010011100000111101100100000101010110001110001010101001010000010001100100000000011011000011001111001010010011000111110011011011100011110100001111111011001100011001101110100101100001010101001111101011101110010111110100111001100001001110010001011011011001001000011001011110000011100110100111111111111110000111101111000101100110000100110001100010101111100000110001111010001111010101001101000111001000110101011100101111011110100100011011110101100100110011001100101110111001100100000011100100111111111011110011010110001111111100010011010110011101011011001010011010001100111111111111001101100011111110110000001010011011101110000010110010100110100111111010011110101110011011111101011010011101100100101111001100111001001001011111110001101011011100000001010011011011011101011011010001110010111100100100101010111000101110011010011110001101010001011010100000111111110011000110110100110110100110100100100000101100000100100110100000110010000001010100001001101110011100101100110001110010010011001001110011100110010001101110000001010111110010110011011010111100110101110100100001000011111111101001110001000110010111110100001011010101111011110101100110001111100000010000000010011001010111101000011111111110011110011110100110110000100010100001001010101100001001100100001100000010000101111011000110010100001101011001011100111000011111110100101011001101001011000101110011010011111011011000010000100000010000010110100101101101100000100001110101011000000100000100011100101001100000101011010100001101111111000001010011111111100000111101111000001100000010000001011001111000100100010010100110000001110101001001001001110000110110000100111011010001110011100001011010111010100010100101010011110011100110111000001001000101100010110110011001010100000100110101111110111000100000101011100010101110101110101110011101110011101010111011110001110001000010011001101000010101001000010011101110000101010101110001100100100110010100010010100011110101000011110010000001011111000101001110101110000001011010101001111000000011001110010110101001001001100100001110100101111001110101000000101111001001110100110111101100110111111001001111001001100101001101110100001101111100110011100010010111000010101010101101000001100101110100110000010111111000010010111110101111010101101001000000001000010001101110000101101111011000101101110000111001001111000100010111000100011101011111111001000001010000010101000000010100111101001001001100101101111011001011010110000000001001001111111001001001110000100000101111110111110010100101100101110000010101101011011010100001011000111100010111001111100001011001110111111001010101101110011110111000100100011001010010101111011110001010101110000100101100000010000000110001011100011000000111000000111111011011010111001000111111111111011111010111010100110101100101111011111011011111110110011001000010011101010111111000001011101001011010111101101101011111011100100100100100100001101000100001010011011011010101111101111010010011100001111110011010001010110100001101101110100000110010111001011101110000111011100010100000110110000111001110001010101010110011000100000010001001110000101110100110000101101010000011111101001001101110010101110111101111001110001111011010111010100111111110100011101011011010101000100111101010000111110101001010110001000100111010001100110101010101100111110100001110110110001100110111001110110010100111001010000000100100110011101000101101111110010101100010110011111100011000011001000010110111111100001000110011010101100001101000000101100110111000100111101111001111100111010010111101001110110010011111010110000011100011110110110101111111001001100000010111001000111001100001010101000011001110010110000000000111100100110000101110110001001110100111000000100110000111111011110111000011010010110100011111101011011111100100110101011110001100011000001011000111111011100010110111001000011101011011110011100000000100101101000001011101111110001010110011001111001001001111101111000110110111111111010100000010100110010000010111100001111101111010000110100010111101101100000000111100101010011111001101001011010000001101110000101111000111110001101110011101000000100101000011111110111110010001001001000010100110101001110100100010111111010111100100110111100000100000010011001101100110011111100111100100000001000011000100100100010000111000111100101011001010101000000001111001100010110111110011111100100100011000101000111110011011011100001111010111010111011000110100111000101010001001111000100011011011111000101101011101111000001110110111000011111100000101000100110001100010000111110001110001011010100100100010101010101111000000011000011111000001111111110101010101100100100101110011001101111000111101100110111000011111101101110111101001001010111101111010101100101100101010000011010000111011101100111011010111011100011001000001110001111011010011111101010011111110010001110101110011110101011011110010011011011011101010100011010000101010111101001011000000001010011000001101110010100000000010010011111110010000010010000110100001111000101101100000100010000111110000011111000111111000000110101000111101111100111001011011001101111010010011100111101011000110111000001111011010111010011111000001111111101100111111111111100010000010001110000111001011011010010111100001110101110100000100001001011010001010101001010100010001100001100011010001110110001110110101100100111101100110100010101111010111000100001001101001110100010110111000011011000100101001111110100010101001000110100101100001101010000001110101011011010011111000100001101100110000011010110011100101010111010011110110111000100110100001101011011010011111000000010101100000110001100001010000110010010010110000100111111111101101000111011101111010100000011110110111110001110101110100000000101001000011001001110111101010110010000111111100110000000101110000111010101101000111111100011100000101111101101011010111011100111001011110111110011101011100100101100100000001111110111101100101101000011011011011110011111101001001000110010010111010010001011001110101101110000001101100101101101100100000010100000100111010101000010111001001110110111001011100001000110101011011101110001000000100000011111101010001111101101000111011101000110111010001010010010111010000000111111100111100000010001000011010011111101110111010111101101000101100110101111100010111001001101101010011100100011011111100111001100011001100111111010011110010111010011100000110001110100000101001101000101110100000000101100001010001001010100110000011111111111010010110100001100101010100011011000011111101111111000101011001010101010100110010011101110110010011111111100000010001101100110011111011111101000010010001010011001101001110011001101111010000011110111101100001001010101110110011010001000110101010100000010001011011100110100000001011111011111001101011101101000100001101000010100001100110110000100111000111100101011000001001011010101101100100000010001000110010001001110111101111001101111011000110000011000011000011010110110111001000111010101100110010011000111010000111100100011010100101000110101100011001100010110010000011111100011011000000001111110101010110100011100010110010101100000111110010010100100101011011111111101000000101011000011111111100111100111010010001100011100111101101111001010111011101001000101010010011110011001100011111000000110110000001111011011001100100001001001111010111001011000111101011100001010111001110111011110000101001001010101000001010010010101101010111100001010101101000101011000100011100010010000111100000011110100100010111011011001000100010000111001000111010110000001010011010001010000011001111000101110111000001011011000100100101011000101110100101011010100011110110010011011011010011101100101001001110000001010110011101011110110001010000111011100001000000111000101111101110001110000001100001000111000101111111011110000011110100110111010000011110100100010101001101110101101111001001101001100111100110010101110000011110010011110110101010011101100101110101101111111111101000111011101010100100110010111111101101101000011111001000111111011000010001011100101101001111110100111111010110000100000111011100101001010010000010010101001011001110000101011011000101001110111100010101101010010010110110101000001000101001101100101001001011001011011100011100000101111111010001000101001101100100010110111110110101011100110001001111101011101000011001010100011111101101001100010100101111000110101000110011010011011100110011110010110000000111000001011100101110010111000110100100110111111001100111001001101001110010100110101111011000111010110010110110010011101010000111001101001101111011001100011001000101110110100001000111011000111111001000001110001110011100001000111101110100101001011111110111110001111101001011110110010111010001101000101100110011110001010111010001110011111110100110001000101110110011011000011100110011100011101110001000111110000100111000010010011111101111011010010110110001101010000000111011000000001000010011100000011011101000110011000001011101101010101100011100001010111100110001111001011011010110110110001001001100001101101110011111110001111101101001000001101111101111110001010101100110001110000100111111110000010000000011011000110010011111001111001011001001100110000000110001000000011101011011100100101111011000010101111000000111101001101100000110011110111100111001111001110011001010011000011101011110000111100001011101111011000100111010110110111001010001010011111101110100111010101100110101001000011010010011000100111000010000001110101000000101111010010010110110100001101010100110010111110110000100111000110010110001110010010101010110001101001000011010011011001110001100101111100001000111001100100111100010000100001110111000100100001011111110001010100111111001100110111110000000111101001001000000000101101100110001101000110110000101101011101101010111100101000110101000101000110010101001000000011010001100100001110011000011101010101001011111001011000111010011001111101100100100100000110001110001010010010100001011011000010111111100111010011000000001000100011110011111010101001001111101100011111100101111011111000001101111011001010110011100000100100000011101101100010100101001011110010010001101000011101001000100110111001100100111111101010101111001000011010001001011001111001101110001110001110010001011001110011001010011110111100000101111011010100110001011000010000001110100111101111010000111101100100100001100010001001001000111010101010100110000110110101111100011110001101000100110001000110011000010011001000001101100010100110100100101110001000111101011100111000111000011100110010110101101111100001111100111100110011111110111101111001111001000010010001010010010110101001110000110011111001101100100101001001000100011010110011100111100011000010100010110101001011101011100101011110101001000101100110111000101010101101011011101011111111011111010011110100000001100100000010110110100111110110101100100110000101101011111110110001000101001110110010001011100001110001010011101111100011001000100001010101011010010110111000000111000001111001101110100111111011010110011010100001100100101010101110011100001000111010011011010011000100000111011110101111110111000101011111001001001101101101000010010111011001000111010001000100110110100011010011010100001000101010010000010110110101101001000111010000110010101110111010001011101100001110000110010000001100101100000010000001001001000100111010001100100000100100110110011111101100110010000001100001001000101100001010110010111110111110001010010100100010111111110001110010010000111111000101100000101001111101010111010001011001001011101101100010001111100100011100000001001100100000110000001011000011110000100001110010001110001001110001001011011111110110101111100001000001000100000110000001011101011110001000010011100110101011111001011000110100001111111011010010101101101001111000110100101000011001100100001000101000110110101000000011011010010001000000011011010011000010000001011100100100111100011010100001001011110100100110100000110001111000110010110010110100100110110101111101000100010011011111010110110111001101010100000110111100111000011011001000110101111110001101101110101100111001111000011101001110000011011000101010111101110010000110100010110101111010011011001100100111000100111111101111111000111100010000101010101000000110001001010001011011001101001011101101110011111100000010100010001101011000011101011101000011011111010110101110001011011111011100110010110010000101101001100000100111010101111001101101100100100000010110110100101110111000000010011000101110100110000110101100100111010110101000001111100011000111010000011000011001001110001011100010100111110111101101111001011111110101111010111000111011001010111101101000011000011001010100111000111000100100111011100001101110101001101100001111010010000011110110000000101100101000100010101100110000110001100100011100111000001000101010111100101110010000100011100100010100010011001000001011110010010001000111100110000101000110000110011011000101001000110110001101001111011010100010111011111011001101100100110111001101101001010101101110101101001100101111100101001111101000100001100101110111011001011110010011010000011101101110001010100111100100010001111111100100000000100000001010000110101000010110010001101101001011000010100001110001001001110001010100011010000011010000101101010100011101110000101110001000110010011001000011101111000110010011101001000000101011100000011001110110011111010010110001001100100100011111001100000101110110110010111010110000000011010001101111000001000100100101111111011000110000100010010111101001111110010100001010010100101111100010100011001001011011000111011010011001010100011111111101001100010010011000010100111100011100011100011000110111111101100101001100011110110011010100110010001111000010111000011100000101101111010010000011110101110000010110111101110011101001000000101010011111011011110011010101101101011110001100011010000000101001000001100000100011001011110001111000100000000000101001111100100001001011101001101100101110100101000110110000100110111111111101000110111001100000001001111001110111111011111110011001011110000100111111011110000011111100010111000011011101100000011110010011001001110100000000010000010000011100110101000001111110110011100000001111001101000101110000000001001111100001010011100100111010000000011001011011000100001011000110001111100111111001110101001110101100100011100010001111110000101010111001111110101111010010001110010010001111010110001000011111011110001010111111100111001010100011100111101101101010000110101110011000011110001001101001010100001101111101011100001101111100011000110000110001001011100100110001110000010100010110011101010001001011101011000111100100000000101100011111011100001110000110011011111100011001111000001011111011001001010110000110110011101011011101101001011110101110100001000010001001011000011001101010011000011000011001010111110100010000101101101010110100111001111000111010000101101100111001111010010001110110100111010000001010111110101000000010100001100000000101000010000001001110111110111110011110110011111001110110110010011010101010001100001101010000011111100001011100100100101101100101001101011110111011100100011111011111101101001010110000110001110100010000010101101110100111000100011101100000110110000000111101000001000011111001010010011010000010101100111110111001111101011000011100110100001001100011100110101110001010000010101011000011001011111111011100011110100000110010010011101001000101111111000100001011010100001010011000000000010010100001111110010010011110110100110100111011100100011001100110010110010110110111001001001110000010100100001011000000110000101110111110010000111001111101011101101111010110000101101101111110010001101100101010111001000000110110111101110101000111010111000001100111100010000000101010101110011000011110111011111101011000111001010010110111110110000001011011011000010110000110110110111011010000010001110001010001100001100010000001100110111111111100000000100101001001001011101001111001000011011001010001110111000100100100110010111001110010010010011010010110010000101101000001100001101010010011111011101000010001010000000101110110100010010111101011110100001110100110111000101011010001111011010000001100010001000000011101111010101010100011101011001000101111110001101101010101011010010010100110100100010101000000000010011010100101111010010100010011000010110000001100010111011001110000110101000101001110011010100000101100110101110001010101011111010101000101101101110011010000111011010011011110110000110100001011100010010101010110011011001000010011101010110111010010100101100011101100010110000101010010010001010100010010111000011101011111110010100001100100000100000000100011111100100100101001010110011010100101111100100011101011111101011010101100111111001100100110001111111110001001001001110010001011010000011000010111110100001000100010110110001011001011110011111011001011001111110101000000110100010100011010010111110010001011001011010001110110100101101100001010100111011011000000000110100011111001010010110000101011101110100100011110001110101101101111001100000101101010011001010000111100000111111011010010111001010100011000101111111111000000000010010101100101010100110000100011000110100100000010101010100100110101111010010011111101101010001000100011000011011001100001110100001110100110001111010010000001101101011001111101110011011011011100100010100010000001110110100010000011011010111110010100110111110100100000011100001010110001000100011001110010111111000110100000100000111110000111010110110011001110010111111001111011011011110000111011010001100011000110101001101111000101011010001000101101111000101000000010001101101100011010100001111111010100000001100010000011001001100101110001110100111000101010110101100111111110001100000000101111010011110111000011001100000001100000100110000001000101010100001100000001011111001101001011101110011001000011001101000100011011101110111001011010111000011111111110000010111100100100000110100100111100000100110010001100111010111000001000100000110111010100010110110011001110001000011101000011010111111111110001000110110011100110011011110110001011001001001011010000000110001100010001001011010010111001010000100100000000101110111100100010111001001110000100001101001011000101110110101110000011011011110000111110001001101101100101110000101111101010000010001100110101011100011101100010001010011111001100100001101010101101010010011100111011011100100011010001010000010100001111111001101000101110111101101110000001001110110001010101110010011010110101001100111110100111111100010010110100101100000110001111111011101010101011011111000100101110100011000101011011101100010101000100100011000001011011000000101010000100110000100111010110101100000110100000101101111011100110000001000101100010111100011010000111001111101100011001000011110010010010001101011000011100000111100000111010000011010111010101000111110111100010000001110000111101000100001010011111110000100101010010101001111011010000011100101001010010101000111010010001010101000100111000010110010011010110001101101011101000011001001100001010111111001011111100001110101001000011110000111010000000110001011000111100011010010011111110010111010111000101001101001010110101110110100010101111111100111110010010101001000001011100010110001011101101110110100100011101000100101110100000111011111110110111010101111000000011001001011100000110011100010100011011101001010110010100101111100110000010000011010111010100011010111111110111100111001001101101000100101010010010111010010100000101101111010011010001100100001110011101000001011110101101000011110000110110000011101101001101100001011010110101000111111110100010010100101101000111000010110010010101010110100111100100101011111111011111100101010101000010011000001001010111101101011011010110011010000100111011110000110101111011110011111001101101011111111010111000010011100110000011110001101011010010111001110110101100000110010110100010000000010111100100011011101000001011011010100010111011001110101011111110101010001100101011110001111001110010110010011001000100110100111011101110011010011010001100100111111111000110110110111111000001001001001101111111111000101010111001110000110111001100011100111010011101110000000100110001111110011001100001111000110011010110000100000000111100000110010010110111101110101110001001000011001001100111110010111100101100010001000110110101110101001001111111111101100100010111010010111110100101000101011001010000110001101100111101000001111010011000011001011010001110110011011111100011101000011000011111111001011101101110100001101011100111000100010101000100001001001010111001101010110000000001100001101100100110010011101010000110001011011000001111101100011101101110100001111101010001010100011000010110101111000101101101011000110110010110011001101111110001110001001100000110111001001010000000110000000100100010101001011100101101011011100100000111110110101110110000011110110011011010001011110101100101100100010000000111010100010000110111100010100101001100111110101001010110010001110111000100100100110001010111110110010101001100101001011111100011010011001111011010011110100010001111010010110111111000101110011011111010011011010010101100010011110111111000100010111100010011101111010110001111010000011000011010011001010110101000001101100101001001000100001100011001010100111011010000110100101100100001111111001010010000110100100010111000011001100000111110100110110110111111110001010001111101011000110111000110101001101010101111101110011100000110110000110111010001100001011010011010100100001000011101110000001010100001000000001111111101111000110101110100000000001000101101101111001011111010111001110101011101101010111110100011110100001100101010110100000100000101010000000110110010100001000100000001111110101111010101010011100101001110111110000101110000100011110101001011110101000110111000011100001110101010111011001111011111111101011001101111010100000100001111101000101001001101001101001100010001101110111110111000001011101100000000010010011000001000011001101000010100000000011011001000001001011001111010110101000110101001101001100111100100000011000000000111110010111100100001101101100110110101011001100110100010101001101000000111110001001111100111100101111010000111101001111011001001101001010010101010111001011111110001110001010101010110011001111000010100010110111001011111000101100010111101010000110010000101011010110001001111100001001011010100000000101011000111001111110100111111110100010001001011011111001111110111001011110010010100000001100101100101011001101101110101000010110010011100011011100011101110100101010010001001101001011100100100001001111111110010001011110011110111001011111101111110100101101111100001011011000000101001101101101111101000101001110011100001011110111111110110101110101010001111100101111000100110110011111101010100101001010101010111010110010110010100001011001111100101010000100101001001101100001111101001011000001000101001000000010111100110011101110000001011110000011011100000001101100111000110111000001001101011010100010011010111100101000111100000011011100100011100111000110100000001100000111111110011011110101011010000010111010001111110010011101101101011011010100000101110000111001010000000000010001011110100111110101110011110001000010001000101011001111110001101011100111100001001011010011001111001100101111001111010100111001000101000110000000110010110101111111011100101001010101101011100111101111011110111000101000000110011010100001110011111111101101010010000110100100001010111010100010011100001001000001000100010110001010110111001101101001010010000110001011011101101101000110101111111001010111111000001011001111110000100100111000000100101011111100000001110101111110001101100010011101100100100101001010100101000011011101000011100111101101000110101101010001111100001110110001000101011000111101110000001011011100110010010100011011100101010110011111011101111100100100010101101100001110010110001001011010000111011110000111100101100100000100110100011000111101111011110000111010011000001000100000101111111011000000001101011111000000000011010000000111101110101111100011101011000100000000110011101111101101010000101100000000000011100011001011001000011111100001110111011110010100111101010000000101110010100000111111111101011110000011011011111000111100100110100010100110111100100111000010100000100011001001111100101110101111011100111011111111111001011001010010010110110100111001010010011011101100110000001000001010011100111001100110101100010100001101000100100001010001110000000100000001111010011111010010110101101111001010010110000000011110110001011000001000011101111010100010110111010010110101101011110000100110100100000101100010101101111110001110011000010000110101011111010010110001011111110101000111000011011100110111000011100100111101001100010110000101001001111001001100000111000101011111101111011001111010000001110101001001001111011001100100100100110100000000111101010000111111101010101011001011110001111000010011001011111110111000011101001000011110110111111100001010001000111111010000111000100101111100011100010010100001010010011110011011101100111111100011000000100101101111001101001111111111101001011000110111010111000001011000001110110001101001001110011111010011011011111001001110000000101010111111100010110101010101100011011111101110010110100111011011101000111100101010100110111010011011100111101101001110111101110110011000001100011001111010001100111100110111001111001101100111100001111100101111000011001011001011101001001010001001111000111101011111111000101000010111001110001001110101000100000000001111101010010010100011011101110101111010101010011000010100100001010011010010111000110000100011010100000111110000000101101111111000101101010111100110011110000111101101110001100101011001100110011111011011011110010011111001001011010011110001001100110101110111100110011011011001101101010111010101011111001101111101010110101100110111110111111010010111111010011011001011100011110101100011100111110110011111011110100111000101111101100011101111111100110000000010000011100011110100111011100011110101011100101011010110001010100001111101111011010001100000011010111110101000000111011001111010001001001001101000100100011100101101101000100101010111011100011111001111010001010100011011100011101110101111110011110010101000110111101011100101100011100101000101101100011011011100100000010100100100110110001011010010000101100011101011111000010111110101001100100111000011101011100010010011110001101010010001001000100100101001111111011011111110001000000101100001010000011011010110010001111011100111001011111100001010010101100001101100001010111100110111010001101010100010000100101011110001001101110001101000011001010101111100100100001010011001001111011111100010101110111110011100000110110001001010101111001001000001110111010110100010100010010001011101100010110001101011100110101010100111010111110000111001111100011000000101001110110000100001000011000110111111110101001111111110111110111000111100100110010110111010100111001010001011001001101011111110011110011011110101010010110111010011010101001100110101111010101000000100000100011000101010000000100000010101111111001111011011101111000101110101010111100010001000010011101011101010101110111111011110110110010010001011001000110000010111101011101100100011010000010011100110101100101100100100100101110000111001011101101110011100100000110010010101110111111000101000110101001001101111100011100010111101100001000111000100100110001110110001111111111010000110010011110001000110110101001101110111011000100001010110100000000000110010100010110100111001101001110001011000010100011001011000011010010001010101101010001010001100100111011101111111011101100010010010111011001101110000010101111111000101000110011011101011111000111001011101100101111010011001101100111101001111110101111110111101010100111011110011001010001001111001011010101100101010101000110100110111011100001000100010000111001001111000100101101000100000110011111001100011101110100001011110001111110010010000010011001110011011011100000110110011111010001100011000111111001111100010101011111010001110101110000010101111010101000001001001001000111010000101001000010100100111000111111010100100001011011100110010101101110110110110101110101100100011111111111000000101111011010001011111001100011101001101010101001111110010100010010010011111000101111010011010100101100100001010011001101100101010101000000011101000000100100011000100001101110101010001110111111001111110100000100010111110000111101000010111000111111100100000010011011100110011111011011010010101111101010110000101000011110011101010111010001100110010111101000000111111011101000111111010000011101011111111110010001001101001111111101101101111100101110110001000111011111011111101001011101111111011101100011001111111011001101001010101001100011101100100010000111011101111100001011010000110000000010011010000101010000101100010001101101001010101010101101000001100110111001010100100110000000100111111010000111101110110101010001011100001101011011101011110100110011111011000100110011110110100001110100001010101110100000101100100000001110110011010000010000001000001001110000010010100001000110111010110001000111101011011100110100000101111011111011001110110100110100111000011110000010001011110011100100001110101000100110101000100100101100101000111011111000110011100011010101000010010101000010011100000000111011100100100000001100111010010011000010110111010001110011010010011001101001";
    cout << "numer of BinarySubstrings of "
         << " is " << countBinarySubstrings(b) << endl;
}

// 14. Longest Common Prefix
// Runtime: 4 ms, faster than 97.68% of C++ online submissions for Longest Common Prefix.
// Memory Usage: 9.6 MB, less than 6.50% of C++ online submissions for Longest Common Prefix.
string longestCommonPrefix(vector<string> &strs)
{
    int len = strs.size();
    if (len == 0)
        return "";
    string prf = "";
    int flen = strs[0].size();
    int j = 0;
    bool go = true;
    while (j < flen && go)
    {
        int cnt = 1;
        char first = strs[0][j];
        for (int i = 1; i < len; i++)
        {
            if (j >= strs[i].size() || strs[i][j] != first)
            {
                go = false;
                break;
            }
            else
                cnt++;
        }
        if (cnt == len)
            prf += first;
        else
            break;
        j++;
    }
    return prf;
}

void testlongestCommonPrefix()
{
    vector<string> str = {"flower", "flow", "flight"};
    printVector(str);
    cout << "testlongestCommonPrefix: " << longestCommonPrefix(str) << endl;

    str = {"dog", "racecar", "car"};
    printVector(str);
    cout << "testlongestCommonPrefix: " << longestCommonPrefix(str) << endl;
}

// 521. Longest Uncommon Subsequence I
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Longest Uncommon Subsequence I.
// Memory Usage: 6.4 MB, less than 100.00% of C++ online submissions for Longest Uncommon Subsequence I.
int findLUSlength(string a, string b)
{
    int lena = a.size();
    int lenb = b.size();
    if (lena != lenb)
    {
        return max(lena, lenb);
    }
    if (a == b)
        return -1;
    return lena;
}

template <typename F, typename P>
void testString(F fun, string funname, P print)
{
    vector<vector<string>> cases = {
        {"aba", "cdc"},
        {"aaa", "bbb"},
        {"aaa", "aaa"},
        {"ylqpejqbalahwr", "yrkzavgdmdgtqpg"},
        {"bl", "yby"},
        {"abcde", "ace"},
        {"abc", "abc"},
        {"abc", "def"},
    };
    for (auto &&test : cases)
    {
        printVector(test);
        auto res = fun(test[0], test[1]);
        cout << funname + " : " << endl;
        print(res);
    }
}

// 344. Reverse String
// Runtime: 28 ms, faster than 97.65% of C++ online submissions for Reverse String.
// Memory Usage: 23.4 MB, less than 32.49% of C++ online submissions for Reverse String.
void reverseString(vector<char> &s)
{
    int len = s.size();
    for (int i = 0; i < len / 2; i++)
    {
        swap(s[i], s[len - 1 - i]);
    }
}

void reverseString(string &s, int start, int len)
{
    for (int i = start, j = start + len - 1; i < start + len / 2; i++, j--)
    {
        swap(s[i], s[j]);
    }
}

// 541. Reverse String II
// Runtime: 4 ms, faster than 99.17% of C++ online submissions for Reverse String II.
// Memory Usage: 7.5 MB, less than 5.98% of C++ online submissions for Reverse String II.
string reverseStr(string s, int k)
{
    int len = s.size();
    for (int i = 0; i < len;)
    {
        if (i + k - 1 < len)
        {
            reverseString(s, i, k);
            i += 2 * k;
        }
        else
        {
            reverseString(s, i, len - i);
            break;
        }
    }
    return s;
}

void testreverseString()
{
    vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    printVector(s);
    reverseString(s);
    cout << "reverseString: " << endl;
    printVector(s);

    s = {'H', 'a', 'n', 'n', 'a', 'h'};
    printVector(s);
    reverseString(s);
    cout << "reverseString: " << endl;
    printVector(s);
}

void testreverseStr()
{
    string s = "abcdefg";
    int k = 2;
    cout << s << endl;
    cout << " after reverse: " << endl;
    cout << reverseStr(s, k) << endl;

    s = "abcdefg";
    k = 3;
    cout << s << endl;
    cout << " after reverse: " << endl;
    cout << reverseStr(s, k) << endl;

    s = "abcdefgsfjlssd";
    k = 3;
    cout << s << endl;
    cout << " after reverse: " << endl;
    cout << reverseStr(s, k) << endl;
}

int selfMatch(string str)
{
    int sum = 0;
    int i = 0;
    int len = str.size();
    if (len <= 1)
        return 0;
    while (i < len - 1)
    {
        string prefix = str.substr(0, i + 1);
        string suffix = str.substr(len - 1 - i, i + 1);
        if (prefix == suffix)
            i++;
        else
            break;
    }
    return i;
}

vector<int> getPrefixFunction(const string &pattern)
{
    int matched = 0;
    int len = pattern.size();
    if (len == 0)
        return {};
    vector<int> prefix(len + 1, 0);
    for (int i = 2; i <= len; i++)
    {
        while (matched > 0 && pattern[matched] != pattern[i - 1])
        {
            matched = prefix[matched];
        }
        if (pattern[matched] == pattern[i - 1])
            matched++;
        prefix[i] = matched;
    }
    return prefix;
}

using namespace std;
// 5. Longest Palindromic Substring
// Runtime: 624 ms, faster than 12.81% of C++ online submissions for Longest Palindromic Substring.
// Memory Usage: 386.7 MB, less than 5.30% of C++ online submissions for Longest Palindromic Substring.
string longestPalindrome52(string s)
{
    int len = s.length();
    string reverse = s;
    std::reverse(reverse.begin(), reverse.end());
    int max = 0, maxi = 0;
    string pali = "";
    vector<vector<int>> dp(len + 1, vector<int>(len + 1, 0));
    auto isPalidrome = [&](int end, int slen) -> bool {
        int i = end - slen + 1;
        while (i != end && i <= end)
        {
            if (s[i] != s[end])
            {
                return false;
            }
            i++;
            end--;
        }
        return true;
    };
    for (int i = 1; i <= len; i++)
    {
        for (int j = 1; j <= len; j++)
        {
            if (s[i - 1] == reverse[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max)
                {
                    max = dp[i][j];
                    maxi = i;
                    int lcs = dp[i][j];
                    while (lcs > max)
                    {
                        if (isPalidrome(i - 1, lcs))
                        {

                            pali = s.substr(i - lcs, lcs);
                            break;
                        }
                        lcs--;
                    }
                }
            }
        }
    }
    while (maxi > 0)
        return pali;
}

// Knuth Morris Pratt not working why?
string longestPalindromeKMP(string s)
{
    int len = s.length();
    string opposite = s;
    std::reverse(opposite.begin(), opposite.end());
    int longest = 0, maxi = 0;
    auto isPalidrome = [&](int end, int slen) -> bool {
        int i = end - slen + 1;
        while (i < end)
        {
            if (s[i] != s[end])
                return false;
            i++;
            end--;
        }
        return true;
    };
    int matched = 0;
    for (int i = 0; i < len; i++)
    {
        int j = 0;
        while (j < len && i + matched < len)
        {
            if (s[i + matched] == opposite[j])
            {
                matched++;
                j++;
            }
            else
            {
                if (matched > longest && isPalidrome(i + matched - 1, matched))
                {
                    longest = matched;
                    maxi = i;
                }
                if (j == len - 1)
                    break;
                if (matched == 0)
                    j++;
                matched = selfMatch(s.substr(i, matched));
            }
        }
        if (s[i + matched - 1] == opposite[j - 1])
        {
            if (matched > longest && isPalidrome(i + matched - 1, matched))
            {
                longest = matched;
                maxi = i;
            }
            matched = selfMatch(s.substr(i, matched));
        }
    }
    return s.substr(maxi, longest);
}

void testlongestPalindrome52()
{

    cout << "longestPalindrome of aacabdkacaa  is " << longestPalindrome52("aacabdkacaa") << endl;
    string s = "ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg";

    cout << "longestPalindrome of  is " << longestPalindrome52(s) << endl;

    s = "slvafhpfjpbqbpcuwxuexavyrtymfydcnvvbvdoitsvumbsvoayefsnusoqmlvatmfzgwlhxtkhdnlmqmyjztlytoxontggyytcezredlrrimcbkyzkrdeshpyyuolsasyyvxfjyjzqksyxtlenaujqcogpqmrbwqbiaweacvkcdxyecairvvhngzdaujypapbhctaoxnjmwhqdzsvpyixyrozyaldmcyizilrmmmvnjbyhlwvpqhnnbausoyoglvogmkrkzppvexiovlxtmustooahwviluumftwnzfbxxrvijjyfybvfnwpjjgdudnyjwoxavlyiarjydlkywmgjqeelrohrqjeflmdyzkqnbqnpaewjdfmdyoazlznzthiuorocncwjrocfpzvkcmxdopisxtatzcpquxyxrdptgxlhlrnwgvee";
    cout << "longestPalindrome of  is " << longestPalindrome52(s) << endl;

    cout << "longestPalindrome of babaddtattarrattatddetartrateedredividerb  is " << longestPalindrome("babaddtattarrattatddetartrateedredividerb") << endl;
    cout << "longestPalindrome of abacab  is " << longestPalindrome52("abacab") << endl;
    cout << "longestPalindrome of abbcccbbbcaaccbababcbcabca  is " << longestPalindrome("abbcccbbbcaaccbababcbcabca") << endl;
    cout << "longestPalindrome of xaabacxcabaaxcabaax  is " << longestPalindrome52("xaabacxcabaaxcabaax") << endl;
    cout << "longestPalindrome of bacabab  is " << longestPalindrome52("bacabab") << endl;
    cout << "longestPalindrome of abb  is " << longestPalindrome52("abb") << endl;
    cout << "longestPalindrome of bananas  is " << longestPalindrome52("bananas") << endl;
    cout << "longestPalindrome of babad  is " << longestPalindrome52("babad") << endl;
    cout << "longestPalindrome of cbbd  is " << longestPalindrome52("cbbd") << endl;
    cout << "longestPalindrome of dddddddd  is " << longestPalindrome52("dddddddd") << endl;
}

bool isPalindrome(const string &s)
{
    int len = s.size();
    int half = len / 2;
    string cp = s.substr(0, half);
    int right = (len % 2) ? (half + 1) : (half);
    std::reverse(cp.begin(), cp.end());
    return cp == s.substr(right, len / 2);
}

// 214. Shortest Palindrome
string shortestPalindromeBF(const string &s)
{
    int len = s.size();
    int end = len;
    while (end > 0)
    {
        if (isPalindrome(s.substr(0, end)))
            break;
        end--;
    }
    if (end == len)
        return s;
    string prefix = s.substr(end, len - end);
    std::reverse(prefix.begin(), prefix.end());
    return prefix + s;
}

// KMP
// Runtime: 4 ms, faster than 95.88% of C++ online submissions for Shortest Palindrome.
// Memory Usage: 8.1 MB, less than 8.08% of C++ online submissions for Shortest Palindrome.
string shortestPalindrome(const string &s)
{
    int slen = s.size();
    if (slen <= 1)
        return s;
    string rev(s);
    std::reverse(rev.begin(), rev.end());
    string pattern = s + '#' + rev;
    int matched = 0;
    int len = 2 * slen + 1;
    vector<int> prefix(len + 1, 0);
    for (int q = 2; q <= len; q++)
    {
        while (matched > 0 && pattern[matched] != pattern[q - 1])
        {
            matched = prefix[matched];
        }
        if (pattern[matched] == pattern[q - 1])
            matched++;
        prefix[q] = matched;
    }
    return rev.substr(0, slen - prefix[len]) + s;
}

void testshortestPalindrome()
{

    string s = "aacecaaa";
    cout << "shortestPalindrome of " << s << " is: " << shortestPalindrome(s) << endl;

    s = "";
    for (int i = 0; i < 10000; i++)
    {
        s += "aaaaa";
    }
    // cout << "shortestPalindrome of is: " << shortestPalindrome(s) << endl;

    s = "abbacd";
    cout << "shortestPalindrome of " << s << " is: " << shortestPalindrome(s) << endl;

    s = "abcd";
    cout << "shortestPalindrome of " << s << " is: " << shortestPalindrome(s) << endl;

    s = "aba";
    cout << "shortestPalindrome of " << s << " is: " << shortestPalindrome(s) << endl;
}

int main(int argc, char const *argv[])
{
    // StringTest st;
    // testlongestPalindrome();
    // st.testlongestCommonSubsequence();
    // testaddBinary();
    // testAddString();
    // testbuddyStrings();
    // testisPrefixOfWord();
    // testnumSmallerByFrequency();
    // testmaxPower();
    // testcountBinarySubstrings();
    // testlongestCommonPrefix();
    // testreverseString();
    // testreverseStr();
    // testshortestPalindrome();
    // testStrStr();
    // testisIsomorphic();
    // testrepeatedSubstringPattern();
    // testRepeatedStringMatch();
    // testcountSubstrings();
    // testCalculate();
    testlongestPalindrome();
    return 0;
}
