#include "../common.h"

template <int N>
struct Fact
{
    // enum{Value = N * Fact<N-1>::Value};
    const static int Value = N * Fact<N - 1>::Value;
};

template <>
struct Fact<1>
{
    // enum{Value = 1};
    const static int Value = 1;
};

constexpr auto fact(int n)
{
    if (n == 1)
        return 1;
    return n * fact(n - 1);
}

#include <array>
#include <iostream>
void foo(int *p, int len)
{
    return;
}

void testArray()
{
    std::array<int, 4> arr = {1, 2, 3, 4};

    // C 风格接口传参
    // foo(arr, arr.size());           // 非法, 无法隐式转换
    foo(&arr[0], arr.size());
    foo(arr.data(), arr.size());

    // 使用 `std::sort`
    std::sort(arr.begin(), arr.end());
    for (int i = 0; i < 3; i++)
    {
        std::cout << arr[i] << " " << &arr[i] << " ";
    }
    std::cout << std::endl;

    for (auto n : arr)
    {
        std::cout << n << " " << &n << " ";
    }
    std::cout << std::endl;
    // range interation should use reference instead of value
    for (auto &n : arr)
    {
        std::cout << n << " " << &n << " ";
    }
    std::cout << std::endl;
}

#include <iostream>
#include <string>
#include <utility>
void reference(std::string &str)
{
    std::cout << "left value" << std::endl;
}
void reference(std::string &&str)
{
    std::cout << "right value" << std::endl;
}

int testRvalue()
{
    std::string lv1 = "string,"; // lv1 是一个左值
    // std::string&& r1 = s1;           // 非法, s1 在全局上下文中没有声明
    std::string &&rv1 = std::move(lv1);        // 合法, std::move 可以将左值转移为右值
    std::cout << "rv1 = " << rv1 << std::endl; // string,

    const std::string &lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
    // lv2 += "Test";                   // 非法, 引用的右值无法被修改
    std::cout << "lv2 = " << lv2 << std::endl; // string,string

    std::string &&rv2 = lv1 + lv2;             // 合法, 右值引用延长临时对象的生命周期
    rv2 += "string";                           // 合法, 非常量引用能够修改临时变量
    std::cout << "rv2 = " << rv2 << std::endl; // string,string,string,

    reference(rv2);                            // 输出左值，对右值的引用被推导为左值
    reference("string");                       // 输出右值
    reference(std::forward<std::string>(rv2)); // 输出右值
}

#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

void testUnorderedMap()
{
    // 两组结构按同样的顺序初始化
    std::unordered_map<int, std::string> u = {
        {1, "1"},
        {3, "3"},
        {2, "2"}};
    std::map<int, std::string> v = {
        {1, "1"},
        {3, "3"},
        {2, "2"}};

    // 分别对两种容器进行遍历
    std::cout << "std::unordered_map" << std::endl;
    for (const auto &n : u)
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";

    std::cout << std::endl;
    std::cout << "std::map" << std::endl;
    for (const auto &n : v)
        std::cout << "Key:[" << n.first << "] Value:[" << n.second << "]\n";
}

#include <tuple>
#include <iostream>

auto get_student(int id)
{
    // 返回类型被推断为 std::tuple<double, char, std::string>

    if (id == 0)
        return std::make_tuple(3.8, 'A', "张三");
    if (id == 1)
        return std::make_tuple(2.9, 'C', "李四");
    if (id == 2)
        return std::make_tuple(1.7, 'D', "王五");
    return std::make_tuple(0.0, 'D', "null");
    // 如果只写 0 会出现推断错误, 编译失败
}

int testTuple()
{
    auto student = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student) << ", "
              << "成绩: " << std::get<1>(student) << ", "
              << "姓名: " << std::get<2>(student) << '\n';

    double gpa;
    char grade;
    std::string name;

    // 元组进行拆包
    std::tie(gpa, grade, name) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa << ", "
              << "成绩: " << grade << ", "
              << "姓名: " << name << '\n';
}

#include <iostream>
#include <memory>

class A;
class B;

class A
{
public:
    // A 或 B 中至少有一个使用 weak_ptr
    std::weak_ptr<B> pointer;
    A()
    {
        std::cout << "A created" << std::endl;
    }
    ~A()
    {
        std::cout << "A destroyed" << std::endl;
    }
};

class B
{
public:
    std::shared_ptr<A> pointer;
    // std::weak_ptr<A> pointer;

    B()
    {
        std::cout << "B created " << std::endl;
    }
    ~B()
    {
        std::cout << "B destroyed" << std::endl;
    }
};

int testPtr()
{
    std::shared_ptr<A> a = std::make_shared<A>();
    std::shared_ptr<B> b = std::make_shared<B>();
    std::cout << "pointer a cout: " << a->pointer.use_count() << std::endl;

    a->pointer = b;
    std::cout << "pointer a cout: " << a->pointer.use_count() << std::endl;
    std::cout << "pointer b cout: " << b->pointer.use_count() << std::endl;

    std::cout << "pointer a: " << &(a->pointer) << std::endl; // weak_reference不能直接cout
    b->pointer = a;
    std::cout << "pointer b cout: " << b->pointer.use_count() << std::endl;
    a.reset();
    // std::cout<<"pointer a cout: "<<a->pointer.use_count()<<std::endl; //exception
    std::cout << "pointer b cout: " << b->pointer.use_count() << std::endl;

    std::cout << "pointer b: " << (b->pointer) << std::endl;
    // std::cout<<"pointer b: "<<&(b->pointer)<<std::endl;

    return 0;
}

#include <locale.h>

#include <functional>
using namespace std;
void eval(function<int(int)> &f)
{
    cout << "int(int)" << f(3)<<endl;
}

int fii(int a)
{
    cout << "fii ";
    return a;
}

float fdd(double a)
{
    cout << "fdd ";
}

void testFunction()
{
    function<int(int)> func(fii);
    eval(func);
    func = fdd;
    eval(func);
}

int main(int argc, char const *argv[])
{
    /* code */
    // auto value = Fact<7>::Value;
    // auto value = fact(6);
    // testTuple();
    // testUnorderedMap();
    // testArray();
    // std::system("chcp 65001");
    // setlocale(LC_ALL, "CHS");
    // testPtr();
    // testRvalue();
    // timeit(testPrintOrderM);
    // timeit(testPrintOrderFP);
    testFunction();
    return 0;
}
