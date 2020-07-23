

#include <fstream>
#include <algorithm>
#include <bitset>
#include <numeric>
#include <utility>
#include <stack>


#include <iostream>
#include <vector>
using namespace std;


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

void testAlignMemoryOfStruct()
{
    struct Student
    {
        int num; // 偏移 0
        char name[7];//偏移 4
        char sex; // 
        long age;// 偏移 16
    } student1; //size 24

     struct Student5
    {
        //1. 每个成员按照 max（GCC 4，数据成员长度）的倍数进行对齐
        // 2. 结构体按照min（GCC 4，最大数据成员长度）的倍数进行对齐 
        int num; // 偏移 0
        long age;// 偏移 8 
    } student5; //size 16

     struct Student7
    {
        //1. 每个成员按照 max（GCC 4，数据成员长度）的倍数进行对齐
        // 2. 结构体按照min（GCC 4，最大数据成员长度）的倍数进行对齐 
        long age;// 偏移 8 
        int num; // 偏移 0
    } student7; //size 16

    struct Student6
    {
        char num; //
        char age[2];// 偏移 1
    } student6; //size 3

struct Student2
    {
        char name[7];
    } student2;

      struct Student3
    {
        long num; // 按照 4对齐
        char name[5];// 按照 4*2 对齐
        short age;// 按照
        char sex; // 按照 1 对齐
    } student3; //size 24
    

    struct Student4
    {
        long num; // 偏移 0
        short age;// 偏移: 8=len(short)*4
        char name[5];// 偏移： （8 + 2） = len（char）* 10
        char sex; // 偏移： （8+2 + 5）= 15 = len（char）*15
    } student4; //size 16


    cout << "sizeof long: " << sizeof(long) << endl;
    cout << "address of student 1  " << &student1 << " sizeof student1 " << sizeof(student1) << endl;
    cout << "address of student 3  " << &student3 << " sizeof student3 " << sizeof(student3) << endl;
    cout << "address of student 1 num: " << &student1.num << " name: " << &student1.name 
    << " age: " << &student1.age ;
    cout<<" sex: " << &student1.sex <<endl;

    cout << "address of student 2  " << &student2 << " sizeof student2 " << sizeof(student2) << endl;
    cout << "align value of student2  " << alignof(student2) << endl;
}

void testStringOp(){
    ofstream File1("text.txt");
    string d("20160314");
    string y = d.substr(0, 4);
    int k = d.find("2");
    int i = d.find("3");
    string m = d.substr(k + 2, i - k);
    string dd = d.substr(i + 1, 2);
    string n = dd + m + y;
    File1 << n << endl;
    File1.close();
}

void testMulTable(){
    int m, n, k;
    cin >> m >> n >> k;
    cout << mul(m, n, k) << endl;

}

void testConstant(){
    const int aa = 10;
    int *p = (int *)(&aa);
    *p = 20;                                         // can modify value in the constant varible's memory
    cout << "a = " << aa << ", *p = " << *p << endl; // but the constant variable doesn't change
}

void testBitset(){
    std::bitset<4> b;
    std::cout << b << "\n";
    std::cout << b.flip(0) << '\n';
    std::cout << b.flip(2) << '\n';
    std::cout << b.flip() << '\n';
}

void testParentMatch(){
    // [(3+4)*5]/2
    // [(3+4*5]/2
    string input;
    cin >> input;
    string res = match(input) ? "true" : "false";
    cout << res;
}


void testOperPriority(){
    double a = 1;
    if (a == 0.0)
    {
        cout << "a is" << 0 << endl;
    }

    char a1[14] = "Hello, world!";
    int i = 3;
    printf("%d %d\n", ++i, ++i);

    int t = 3;
    int x, y;
    x = y = 2;
    t = x++ || ++y; // A||B, if A is true, don't check B
    cout << "t : " << t << "  y: " << y << endl;

}

int main(int argc, char const *argv[])
{
  testAlignMemoryOfStruct();
    return 0;
}
