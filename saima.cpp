

#include <fstream>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <utility>
#include <stack>


#include <iostream>
#include <vector>
using namespace std;

struct Student
{

    int num;

    char name[7];

    short age;

    char sex;

} student1;

struct Student2
{
    char name[7];
} student2;

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int mul(int n, int m, int k)
{
    if (k <= 0 || n <= 1 || m <= 1)
        return -1;
    vector<int> arr(n * m, 0);
    int i = 0;
    int pos = 0;
    for (i; i < n; i++)
    {
        int j = 0;
        for (j; j < m + 1; j++)
        {
            arr[pos++] = (i + 1) * (j + 1);
        }
    }
    std::sort(arr.begin(), arr.end());
    return arr[k - 1];
}

bool match(string input)
{
    int len = input.length();
    vector<char> s1;
    for (char val : input)
    {
        if (val == '[' || val == ']')
            s1.push_back(val);
        if (val == '(' || val == ')')
            s1.push_back(val);
        if (val == '{' || val == '}')
            s1.push_back(val);
    }
    if (s1.size() == 0)
        return true;
    if (s1.size() % 2 != 0)
    {
        return false;
    }
    int sz = s1.size();
    char top = s1[sz - 1];
    if (top == '[' || top == '(' || top == '{')
        return false;

    int i = 0;

    for (; i < sz; i++)
    {
        if (s1[sz - i - 1] == ')' && s1[i] != '(')
            return false;
        if (s1[sz - i - 1] == ']' && s1[i] != '[')
            return false;
        if (s1[sz - i - 1] == '}' && s1[i] != '{')
            return false;
    }

    return true;
}

int main(int argc, char const *argv[])
{

    string input;
    cin>>input;
    string res= match(input)?"true":"false";
    cout<<res;
    return 0;

    // [(3+4)*5]/2
    // [(3+4*5]/2

    // int m, n, k;
    // cin >> m >> n >> k;
    // cout << mul(m, n, k) << endl;


    // cout << "sizeof long: " << sizeof(long) << endl;
    // cout << "address of student 1  " << &student1 << " sizeof student1 " << sizeof(student1) << endl;
    // cout << "address of student 2  " << &student2 << " sizeof student2 " << sizeof(student2) << endl;
    // cout << "align value of student2  " << alignof(student2) << endl;

    // ofstream File1("text.txt");
    // string d("20160314");
    // string y = d.substr(0, 4);
    // int k = d.find("2");
    // int i = d.find("3");
    // string m = d.substr(k + 2, i - k);
    // string dd = d.substr(i + 1, 2);
    // string n = dd + m + y;
    // File1 << n << endl;
    // File1.close();

    // double a = 1;
    // if (a == 0.0)
    // {
    //     cout << "a is" << 0 << endl;
    // }

    // char a1[14] = "Hello, world!";
    // int i = 3;
    // printf("%d %d\n", ++i, ++i);

    // int t = 3;
    // int x, y;
    // x = y = 2;
    // t = x++ || ++y; // A||B, if A is true, don't check B
    // cout << "t : " << t << "  y: " << y << endl;

    // const int aa = 10;
    // int *p = (int *)(&aa);
    // *p = 20;                                         // can modify value in the constant varible's memory
    // cout << "a = " << aa << ", *p = " << *p << endl; // but the constant variable doesn't change

    // std::bitset<4> b;
    // std::cout << b << "\n";
    // std::cout << b.flip(0) << '\n';
    // std::cout << b.flip(2) << '\n';
    // std::cout << b.flip() << '\n';

    // vector<int> arr{0, 1, 2, 3};

    return 0;
}
