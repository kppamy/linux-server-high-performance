#include <string>
#include <stack>
#include <map>
using namespace std;

// 20. Valid Parentheses
// Runtime: 0 ms, faster than 100.00% of C++ online submissions for Valid Parentheses.
// Memory Usage: 6.6 MB, less than 5.12% of C++ online submissions for Valid Parentheses.
bool isValid(string s)
{
    int len = s.size();
    if (len % 2)
    {
        return false;
    }
    map<char, char> dc;
    dc['('] = ')';
    dc['['] = ']';
    dc['{'] = '}';
    stack<char> data;
    char top;
    for (char c : s)
    {
        if (dc.find(c) != dc.end())
        {
            data.push(dc[c]);
        }
        else
        {
            if(data.size()==0)
                return false;
            top = data.top();
            data.pop();
            if (c != top)
            {
                return false;
            }
        }
    }
    if(data.size()==0)
        return true;
    return false;
}

#include<iostream>
void testsValid(){
    cout<<"()"<<" is "<<(isValid("()")?"":" not ")<<" valid Parentheses"<<endl;
    cout<<"(("<<" is "<<(isValid("((")?"":" not ")<<" valid Parentheses"<<endl;
    cout<<"()[]{}"<<" is "<<(isValid("()[]{}")?"":" not ")<<" valid Parentheses"<<endl;
    cout<<"(]"<<" is "<<(isValid("(]")?"":" not ")<<" valid Parentheses"<<endl;
    cout<<"([)]"<<" is "<<(isValid("([)]")?"":" not ")<<" valid Parentheses"<<endl;
    cout<<"{[]}"<<" is "<<(isValid("{[]}")?"":" not ")<<" valid Parentheses"<<endl;
}

int main(int argc, char const *argv[])
{
    testsValid();
    return 0;
}

