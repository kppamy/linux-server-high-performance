// 作者：一颗大白菜
// 链接：https : //zhuanlan.zhihu.com/p/46605905
// 来源：知乎
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

#include "stdio.h"
#include <iostream>
#include "stdlib.h"
using namespace std;
class base
{
private:
    int father;

public:
    base();
    virtual void test();
private:
    char *basePStr;
};
class dumpTest : public base
{
private:
    int child;

public:
    void test();

private:
    char *childPStr;
};
base::base()
{
    basePStr = "test_info";
}
void base::test()
{
    cout << basePStr << endl;
}
void dumpTest::test()
{
    cout << "dumpTest" << endl;
    delete childPStr;
}
void dumpCrash()
{
    char *pStr = "test_content";
    free(pStr);
}
int main()
{
    dumpTest dump;
    dump.test();
    return 0;
}