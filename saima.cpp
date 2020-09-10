

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
        int num;      // 偏移 0
        char name[7]; //偏移 4
        char sex;     //
        long age;     // 偏移 16
    } student1;       //size 24

    struct Student5
    {
        int num;  // 偏移 0
        long age; // 偏移 8
    } student5;   //size 16

    struct Student7
    {
        //1. 每个成员的偏移为自身数据类型长度的整数倍
        // 2. 结构体的整体长度为 最大数据成员 类型长度 的整数倍
        //  3. 为节省内存，应将结构体按照类型长度从大到小进行排序
        long age; // 偏移 8
        int num;  // 偏移 0
    } student7;   //size 16

    struct Student6
    {
        char num;    //
        char age[2]; // 偏移 1
    } student6;      //size 3

    struct Student2
    {
        char name[7];
    } student2;

    struct Student3
    {
        long num;     // 按照 4对齐
        char name[5]; // 按照 4*2 对齐
        short age;    // 按照
        char sex;     // 按照 1 对齐
    } student3;       //size 24

    struct Student4
    {
        long num;     // 偏移 0
        short age;    // 偏移: 8=len(short)*4
        char name[5]; // 偏移： （8 + 2） = len（char）* 10
        char sex;     // 偏移： （8+2 + 5）= 15 = len（char）*15
    } student4;       //size 16

    cout << "sizeof long: " << sizeof(long) << endl;
    cout << "address of student 1  " << &student1 << " sizeof student1 " << sizeof(student1) << endl;
    cout << "address of student 3  " << &student3 << " sizeof student3 " << sizeof(student3) << endl;
    cout << "address of student 1 num: " << &student1.num << " name: " << &student1.name
         << " age: " << &student1.age;
    cout << " sex: " << &student1.sex << endl;

    cout << "address of student 2  " << &student2 << " sizeof student2 " << sizeof(student2) << endl;
    cout << "align value of student2  " << alignof(student2) << endl;
}

void testStringOp()
{
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

void testMulTable()
{
    int m, n, k;
    cin >> m >> n >> k;
    cout << mul(m, n, k) << endl;
}

void testConstant()
{
    const int aa = 10;
    int *p = (int *)(&aa);
    *p = 20;                                         // can modify value in the constant varible's memory
    cout << "a = " << aa << ", *p = " << *p << endl; // but the constant variable doesn't change
}

void testBitset()
{
    std::bitset<4> b;
    std::cout << b << "\n";
    std::cout << b.flip(0) << '\n';
    std::cout << b.flip(2) << '\n';
    std::cout << b.flip() << '\n';
}

void testParentMatch()
{
    // [(3+4)*5]/2
    // [(3+4*5]/2
    string input;
    cin >> input;
    string res = match(input) ? "true" : "false";
    cout << res;
}

void testOperPriority()
{
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

class Person
{
public:
    Person(string sn, string sa) : name(sn), address(sa){};
    virtual ~Person(){};
    virtual bool validateStudent()
    {
        cout << "father" << endl;
        return false;
    }

public:
    std::string name = "father";
    std::string address;
};

class Student : public Person
{
public:
    Student(string sn, string sa, string name) : Person(sn, sa), name(name){};
    ~Student(){};
    bool validateStudent()
    {
        cout << "child" << endl;
        return false;
    }

public:
    std::string name;
};

void testPassByReference()
{
    Student s("1", "2", "cay");
    Person &p = s;
    Person p1 = s;
    p.validateStudent();
    p1.validateStudent();
}

#include <stdlib.h>
void testFloat()
{
    float a = -0.5;
    char s[10];
    // itoa(a, s, 2);
    printf("二进制 -->%f %#x\n", a, a);
}

void testPointer()
{
    char *cp;
    int *ip;
    double *dp;
    cout << "sizeof char p " << sizeof(cp) << endl;
    cout << "sizeof int p " << sizeof(ip) << endl;
    cout << "sizeof double p " << sizeof(dp) << endl;

    long a = (long)(((int *)0) + 4);
    printf("%ld \n", a);
}

struct Coco
{
    int val;
    Coco *next;
    Coco() : val(20190827), next(nullptr) {}
    Coco(int val, Coco *co) : val(20190827), next(co) {}
};

void testPassByPointer(Coco *co)
{
    cout << " after pass by pointer, val: " << co->val << " next: " << co->next << endl;
    cout << " next val: " << co->next->val << " next: " << co->next->next << endl;
}
Coco returnStackObject()
{
    Coco co;
    Coco co2;
    co.next = &co2;
    cout << " Before return stack object, val: " << co.val << " next: " << co.next << endl;
    cout << " next val: " << co.next->val << " next: " << co.next->next << endl;
    return co;
}

const Coco returnConstStackObject()
{
    Coco co2;
    const Coco co(20200827, &co2);
    ;
    cout << " Before return const stack object, val: " << co.val << " next: " << co.next << endl;
    cout << " next val: " << co.next->val << " next: " << co.next->next << endl;
    return co;
}

void testPassReturn()
{
    Coco co = returnStackObject();
    cout << " Before pass by pointer, val: " << co.val << " next: " << co.next << endl;
    cout << " next val: " << co.next->val << " next: " << co.next->next << endl;
    testPassByPointer(&co);

    const Coco coconst = returnConstStackObject();
    cout << " after returnConstStackObject, val: " << coconst.val << " next: " << coconst.next << endl;
    cout << " next val: " << coconst.next->val << " next: " << coconst.next->next << endl;
}

#include <string.h>
void testSizet()
{
    const char* t = "fsfsdf";
    // for (size_t i = strlen(t) - 1; i >= 0; i--) //infinite loop
    for (size_t i = strlen(t) - 1; i-- > 0; )
    {
        cout << i << endl;
    }

}

int main(int argc, char const *argv[])
{
    // testAlignMemoryOfStruct();
    // testPassByReference();
    // testFloat();
    // testPointer();
    testSizet();
    return 0;
}
