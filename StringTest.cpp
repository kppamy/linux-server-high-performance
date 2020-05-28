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
        if (len < k)
        {
            return 0;
        }
        int max = 0;
        int j;
        int i = j + 1;
        int cout[26] = {0};
        for (int j = 0; j < len; j++)
        {
            for (int q = i; q < j; q++)
            {
                int pos = s[q] - 'a';
                cout[pos]++;
                if (cout[pos] == k)
                {
                    max++;
                }
                else
                {
                    bool restart = false;
                    for (int q = 0; q < k - cout[pos]; q++)
                    {
                        if (s[q] != s[j])
                        {
                            restart = true;
                            i = j + 1;
                            break;
                        }
                    }
                    if (!restart)
                    {
                        max = max + k;
                        i = j + k - cout[pos] + 1;
                    }
                }
            }
        }
    }
};

int main(int argc, char const *argv[])
{
    StringTest st;
    string input;
    cout << " a is" << static_cast<int>('a') << endl;
    // while(true){
    // cin>>input;
    // if(input=="q"){
    //     break;
    // }
    // cout<< "longest of "<<input<<" is "<<st.lengthOfLongestSubstring(input)<<endl;
    // }
    return 0;
}
