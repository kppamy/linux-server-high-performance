#include <iostream>
using namespace std;

#include <string>

#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

// 条款3：尽可能使用const
class Text
{
    char *content;
    char *const content_cst;
    // static member doesn't increase class instance memory, it store in global/static mmeory area
    static char *content_static;
    mutable const char *content_mutable;
    mutable char *content_mutable2;

public:
    Text(char *value) : content_cst(value) // explictly initialize const member
    {
        content = value;
        // content_cst = value; // referece or const member can't be initialized inside constructor
    }

    const char &operator[](std::size_t idx) const
    {
        return content[idx];
    }
    // overload, only const difference
    char &operator[](std::size_t idx)
    {
        // return const_cast<char&>(static_cast<const char&>(*this)[idx]); //error
        return const_cast<char &>(static_cast<const char &>((*this)[idx]));
    }

    void setContet(char *c) const
    {
        // content=c; // const member function can't change non-static member
        // content_cst = c;
        content_static = c;
        content_mutable = c;
        content_mutable2 = c;
    }

    void setContet(char *c)
    {
        //cannot assign to non-static data member 'content_cst' with const-qualified type 'char *const'
        // content_cst = c;
        content_static = c;
        content_mutable = c;
        content_mutable2 = c;
    }
};

void testConstPointer()
{
    char greeting[] = "hello";
    char *const p1 = greeting; // p1 is const
                               // p1 = nullptr;  // error
    const char *p2 = greeting; // p2 could change, *p2 is const, but greeting is still can be modified
    cout << *p1 << endl;
    cout << *p2 << endl;
    // *(p2+1)='j'; //error
    greeting[0] = 'j';
    p2 = nullptr;

    const Text text = Text(greeting);
    const char *p = &text[0];
    std::cout << text[0] << std::endl;
}

#include <string.h>
void testConst()
{
    const char *t = "fsfsdf";
    char *p = const_cast<char *>(t);
    // *t='c';
    *p = 'H'; // exception on run time
    cout << *t << endl;
}

// 条款43：学习处理模板化基类内的名称
class CompanyA
{
public:
    void sendClearText(const std::string &msg);
    void sendEncrypted(const std::string &msg);
};
class CompanyB
{
public:
    void sendClearText(const std::string &msg);
    void sendEncrypted(const std::string &msg);
};

class MsgInfo
{
    // ...
};
template <typename Company>
class MsgSender
{
    void sendClear(const MsgInfo)
    {
        std::string msg;
        //产生信息
        Company c;
        c.sendClearText(msg);
    }
    void sendSecret(const MsgInfo &info)
    { /*...*/
    } //与sendClear相似
};

template <typename Company>
class LogMsgSender0 : public MsgSender<Company>
{
public:
    void sendClearMsg(const MsgInfo &info)
    {
        // 发送前记录日志
        // sendClear(info);//调用基类函数，会出现编译错误, compiler says "undeclared"
        // 发送后记录日志
    }
};

class CompanyZ
{
public:
    void sendEncrypted(const std::string &msg);
};

// method 1: 全特化
template <>
class MsgSender<CompanyZ>
{
public:
    void sendSecret(const MsgInfo & info);
};

// method2:  在base class函数被调用前加上“this->”
template <typename Company>
class LogMsgSender : public MsgSender<Company>
{
public:
    void sendClearMsg(const MsgInfo &info)
    {
        // 发送前记录日志
        this->sendClear(info); //调用基类函数
        // 发送后记录日志    
    }
};

// method3:  使用using声明式
template <typename Company>
class LogMsgSender2 : public MsgSender<Company>
{
    using MsgSender<Company>::sendClear; //告诉编译器，sendClear在基类中
public:
    void sendClearMsg(const MsgInfo &info)
    {
        // 发送前记录日志
        sendClear(info); //调用基类函数
        // 发送后记录日志    
    }
};

// method3: 明确指出被调用的函数在base class内（::）， 显示调用（不推荐，可能破坏多态）
template <typename Company>
class LogMsgSender3 : public MsgSender<Company>
{
public:
    void sendClearMsg(const MsgInfo &info)
    {
        // 发送前记录日志
        MsgSender<Company>::sendClear(info); //调用基类函数
        // 发送后记录日志
    }
};

string
f1(const string &s)
{
    static string result = s;
    return result;
}

string f2(const string &s)
{
    string result = s;
    return result;
}

string &f3(const string &s)
{
    string *p = new string;
    *p = s;
    return *p;
}

int *f4()
{
    int a = 10;
    return &a;
}

int *f5()
{
    static int a = 10;
    return &a;
}

int *f6()
{
    int *a = (int *)malloc(sizeof(int) * 10);
    *a = 10;
    *(a + 1) = 11;
    return a;
}

int &f7()
{
    int *a = (int *)malloc(sizeof(int) * 10);
    *a = 10;
    *(a + 1) = 11;
    return *a;
}

int &f8()
{
    int a = 10;
    return a;
}

int main(int argc, char const *argv[])
{

    string s("chenyu");
    string result = f2(s);
    cout << result << endl;
    cout << &s << endl;
    cout << &result << endl;
    int *a = f5();
    cout << (*(a)) << endl;
    // free(a);
    return 0;
}
