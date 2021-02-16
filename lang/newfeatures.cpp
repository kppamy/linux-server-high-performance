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

void testRvalueOld()
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

class Rvtest
{
public:
    int i = 0;
    Rvtest operator+(const Rvtest &second)
    {
        Rvtest tmp;
        tmp.i = second.i + this->i;
        return std::move(tmp);
    }
};

Rvtest &&testRv(Rvtest &&rv)
{
    std::cout << "before return " << rv.i << " " << &rv.i << std::endl;
    Rvtest &&r = std::move(rv);
    std::cout << "return " << rv.i << " " << &rv.i << std::endl;
    std::cout << "return " << r.i << " " << &r.i << std::endl;
    return std::move(rv);
}

void testRvalue()
{
    Rvtest r1;
    r1.i = 1;
    Rvtest r2;
    r2.i = 2;
    Rvtest &&r3 = testRv(r1 + r2);
    std::cout << "after return " << r3.i << " " << &r3.i << std::endl;
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
}

#include <thread>
#include <future>

using namespace std;


int func()
{
    return 1;
}

void func2(promise<int> &&p)
{
    cout << "task thread id: " << this_thread::get_id() << endl;
    p.set_value(1);
}

void func3(shared_future<int> sf, int who)
{
    if(who==1)
        this_thread::sleep_for(chrono::nanoseconds(1000*1000));
    cout << "func3  thread id: " << this_thread::get_id() << " get shared " << sf.get() << " who: "<<who<<endl;
}

void testOnceCommunication(){
   
    {
        std::promise<void> p;
        auto f=p.get_future();
        std::thread th([](std::future<void> f){
            f.wait();
            // getchar();
            cout<<"1"<<endl;
        }, move(f));
        // getchar();
        cout<<"A";
        p.set_value();
        th.join();
    }

    //  getchar();
    {
        std::promise<void> p;
        auto sf=p.get_future().share();
        std::thread th([sf](){
            sf.wait();
            cout<<"2"<<endl;
        });
    
        cout<<"B";
        p.set_value();
        th.join();
    }

}
void testThead()
{
    cout << "main thread id: " << this_thread::get_id() << endl;
    {
        // auto f=std::async(std::launch::deferred, func);// the same thread
        auto f = std::async(func); // async or sync
        cout << f.get() << endl;   // 未超订：隐式detach，超订隐式join
    }

    {
        promise<int> p;
        shared_future<int> sf = p.get_future().share();

        thread t1(func3, sf, 1);
        thread t2(func3, sf, 2);
        p.set_value(2);
        t1.join(); // t1 和 t2 who run first? do not know...
        t2.join();
    }


    {
        packaged_task<int()> pt(func);
        auto f=pt.get_future();
        async(move(pt));
        // auto f2=async(pt);  // error!!!, 复制拷贝被禁用 
        auto f3=async(move(pt));
        cout<<"get result from packaged task "<<f.get()<<endl;
        // cout<<"get result from packaged task "<<f3.get()<<endl; // wrong !!!!
    }
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
    // testRvalueOld();
    // testRvalue();
    // timeit(testPrintOrderM);
    // timeit(testPrintOrderFP);
    // testFunction();
    // testThead();
    testOnceCommunication();
    // getchar();
    return 0;
}

