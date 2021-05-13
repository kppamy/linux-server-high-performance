#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

// 224. Basic Calculator
int calculate(string s)
{
    int len = s.size();
    int i = 0;
    int ans = 0;
    auto getNum = [](string &s, int &i) {
        string num = "";
        while (true)
        {
            char c = s[i];
            if (c == ' ')
                i++;
            else if (c >= '0' && c <= '9')
            {
                num += c;
            }
            else
            {
                break;
            }
        }
        return num;
    };
    auto string2int = [](string num) {
        int len = num.size();
        int ans = 0;
        for (int i = 0; i < len; i++)
        {
            ans = num[i] - '0' + ans * 10;
        }
        return ans;
    };
    stack<string> sta;
    while (i < len)
    {
        char c = s[i];
        switch (c)
        {
        case ' ':
            i++;
            break;
        case '+':
        case '-':
        case '(':
            sta.push("" + c);
            i++;
            break;
        case ')':

            string sub = "";
            while (sta.top() != "(")
            {
                string tp = sta.top();
                sta.pop();
                sub = sub + tp;
            }
            sta.pop();

            break;
        default:
            sta.push(getNum(s, i));
            break;
        }
    }
}

// 696. Count Binary Substrings
// 24 ms, faster than 84.75%
// 10.4 MB, less than 92.91%
int countBinarySubstrings(string s)
{
    // "00110011"
    // "10101"
    int len = s.size();
    int i = 0, j = 1;
    int sum = 0;
    int prev = 0;
    for (int i = 0; i < len; i++)
    {
        char c = s[i];
        int cnt = 1;
        while (i < len - 1 && s[i + 1] == c)
        {
            i++;
            cnt++;
        }
        sum += min(prev, cnt);
        prev = cnt;
    }

    return sum;
}

// 1143. Longest Common Subsequence
int longestCommonSubsequence(string text1, string text2)
{
    // "bl", "yby"
    int len1 = text1.size(), len2 = text2.size();
    int i = 0, j = 0;
    int cnt = 0;
    while (i < len1 && j < len2)
    {
        if (text1[i] == text2[j])
        {
            j++;
            cnt++;
        }
        i++;
    }
    return cnt;
}

vector<int> jump(string &a)
{
    // ababc
    // aa
    int len = a.size();
    vector<int> pref(len, 0);
    int i = 1;
    int matched = 0; // letters matched before index i
    while (i < len)
    {
        while (matched != 0 && a[matched] != a[i])
        {
            matched = pref[matched];
        }
        if (a[matched] == a[i])
        {
            matched++;
        }
        pref[i] = matched;
        i++;
    }
    return pref;
}

int firstOccurrence(string &a, string &b)
{
    auto &pref = jump(a);
    int lena = a.size();
    int len = b.size();
    int matched = 0;
    int i = 0;
    while (i < len)
    {
        while (matched != 0 && a[matched] != b[i])
        {
            matched = pref[matched];
        }
        if (a[matched] == b[i])
        {
            matched++;
        }
        if (matched == lena)
            return (i - lena + 1);
        i++;
    }
    return -1;
}

// 686. Repeated String Match
int repeatedStringMatch(string a, string b)
{
    int lena = a.size();
    int lenb = b.size();
    string ra = "";
    int rpt = 1;
    while (true)
    {
        ra = ra + a;
        if (firstOccurrence(b, ra) != -1)
            return rpt;
        if (ra.size() > lena + lenb - 1)
            return -1;
        rpt++;
    }
    return -1;
}

// 516. Longest Palindromic Subsequence
// 76 ms, faster than 64.16%
// 72.8 MB, less than 5.69%
int longestPalindromeSubseq(string s)
{
    int len = s.size();
    vector<vector<int>> dp(len, vector<int>(len, 0));
    for (int i = 0; i < len; i++)
    {
        dp[i][i] = 1;
        if (i == len - 1)
            break;
        dp[i][i + 1] = (s[i + 1] == s[i]) ? 2 : 1;
    }
    for (int i = len - 3; i >= 0; i--)
    {
        for (int j = i + 2; j < len; j++)
        {
            dp[i][j] = (s[i] == s[j]) ? (dp[i + 1][j - 1] + 2) : (max(dp[i + 1][j], dp[i][j - 1]));
        }
    }
    return dp[0][len - 1];
}

// 791. Custom Sort String
//  0 ms, faster than 100.00%
//  6 MB, less than 94.18%
string customSortString(string S, string T)
{
    int len = T.size();
    if (len <= 1)
        return T;
    vector<string> dc(26, "");
    for (auto &&c : T)
    {
        dc[c - 'a'] += c;
    }
    string ans = "";
    for (auto &&c : S)
    {
        string rpt = dc[c - 'a'];
        if (rpt != "")
        {
            ans += rpt;
            dc[c - 'a'] = "";
        }
    }
    for (auto &&kv : dc)
    {
        if (kv != "")
            ans += kv;
    }
    return ans;
}

// 345. Reverse Vowels of a String
//  8 ms, faster than 81.08%
//  7.7 MB, less than 94.45%
string reverseVowels(string s)
{
    string vowls = "AEIOUaeiou";
    int len = s.size();
    int i = 0, j = len - 1;
    int swapi = -1;
    int swapj = -1;
    auto swap = [&s](int i, int swapj) {
        char tmp = s[i];
        s[i] = s[swapj];
        s[swapj] = tmp;
    };
    while (i < j)
    {
        while (i < len && vowls.find(s[i]) == -1)
        {
            i++;
        }
        while (j >= 0 && vowls.find(s[j]) == -1)
        {
            j--;
        }
        if (i < j)
            swap(i, j);
        i++;
        j--;
    }
    return s;
}

void reverseVowels()
{

    cout << ".,"
         << " reverseVowels: " << reverseVowels(".,") << endl;
    cout << "Euston saw I was not Sue."
         << " reverseVowels: " << reverseVowels("Euston saw I was not Sue.") << endl;
    cout << "hello"
         << " reverseVowels: " << reverseVowels("hello") << endl;
}

// 58. Length of Last Word
// 0 ms, faster than 100.00%
// 6.4 MB, less than 98.06%
int lengthOfLastWord(string s)
{
    int len = s.size();
    int cnt = 0;
    int j = len - 1;
    for (; j >= 0; --j)
    {
        if (s[j] == ' ')
            continue;
        break;
    }
    for (; j >= 0; --j)
    {
        if (s[j] != ' ')
            cnt++;
        else
        {
            return cnt;
        }
    }
    return cnt;
}

// 38. Count and Say
//  4 ms, faster than 92.73%
//  6.4 MB, less than 98.76%
string countAndSay(int n)
{
    string f = "1";
    for (int i = 2; i <= n; i++)
    {
        int len = f.size();
        int cnt = 1;
        char c = f[0];
        string ans;
        bool flag = false;
        for (int j = 1; j < len; ++j)
        {
            if (f[j] == c)
                cnt++;
            else
            {
                ans.push_back(cnt + 0x30);
                ans.push_back(c);
                c = f[j];
                cnt = 1;
            }
        }
        ans.push_back(cnt + 0x30);
        ans.push_back(c);
        f = ans;
    }
    return f;
}

void testcountAndSay()
{
    cout << "testcountAndSay: " << 4 << " " << countAndSay(4) << endl;
    cout << "testcountAndSay: " << 5 << " " << countAndSay(5) << endl;
}

// 13. Roman to Integer
// 52 ms, faster than 5.30%
// 11.5 MB, less than 5.05%
int romanToInt(string s)
{
    map<char, int> dct;
    dct['I'] = 1;
    dct['V'] = 5;
    dct['X'] = 10;
    dct['L'] = 50;
    dct['C'] = 100;
    dct['D'] = 500;
    dct['M'] = 1000;
    map<string, int> unord;
    unord["IV"] = 4;
    unord["IX"] = 9;
    unord["XL"] = 40;
    unord["XC"] = 90;
    unord["CD"] = 400;
    unord["CM"] = 900;
    int len = s.size();
    int ans = 0;
    for (int i = 0; i < len;)
    {
        string sub = s.substr(i, 2);
        if (unord.find(sub) != unord.end())
        {
            ans += unord[sub];
            i += 2;
        }
        else
        {
            ans += dct[s[i]];
            i++;
        }
    }
    return ans;
}

// 125. Valid Palindrome
//  8 ms, faster than 57.44% o
// 7.3 MB, less than 90.84%
bool isPalindrome(string s)
{
    int i = 0, j = s.size() - 1;
    auto isAlpa = [](char c) {
        return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
    };
    auto isnum = [](char c) {
        return (c >= '0' && c <= '9');
    };
    while (i <= j)
    {
        char ci = s[i];
        char cj = s[j];
        if (!isAlpa(ci) && !isnum(ci))
        {
            i++;
        }
        else if (!isAlpa(cj) && !isnum(cj))
        {
            j--;
        }
        else
        {
            bool ignorecase = isAlpa(ci) && isAlpa(cj) && abs(ci - cj) == 'a' - 'A';
            if (ci != cj && !ignorecase)
            {
                return false;
            }
            i++;
            j--;
        }
    }
    return true;
}

void testisPalindrome()
{
    vector<string> cases = {
        "Aama",
        "0P",
        "A man, a plan, a canal: Panama",
        "race a car",
        "bB",
        "ab&b"};
    for (auto &str : cases)
    {
        cout << str << " is " << (isPalindrome(str) ? " " : " not ") << "Palindrome string" << endl;
    }
}

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
int countBinarySubstringsI(string s)
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

    b = "111100011111001101100010000000110001100010001001011010010111001010000100100000000101110111101";
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

bool isPalindromeOld(const string &s)
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
    // testlongestPalindrome();
    // testisPalindrome();
    // testcountAndSay();
    // reverseVowels();
    cout << longestPalindromeSubseq("bbbab") << endl;
    cout << longestPalindromeSubseq("cbba") << endl;
    return 0;
}
