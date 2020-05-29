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
};

int main(int argc, char const *argv[])
{
    StringTest st;
    string input;
    while(true){
    cin>>input;
    if(input=="q"){
        break;
    }
    // cout<< "longest of "<<input<<" is "<<st.lengthOfLongestSubstring(input)<<endl;
    cout<< "lengthOfLongestSubstringWithKRepeates of "<<input<<" is "<<st.lengthOfLongestSubstringWithKRepeates(input,3)<<endl;
    }
    return 0;
}
