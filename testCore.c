#include <stdlib.h>
#include <stdio.h>
#include <iostream>

void testCore()
{
    char *str = "sdfsdfjk";
    free(str);
}


using namespace std;
class base
{
public:
    base();
    virtual void test();

private:
    char *basePStr;
};
class dumpTest : public base
{
public:
    void test();

private:
    char *childPStr=nullptr;
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
void testDumpInheritated()
{
    dumpTest dump;
    dump.test();
    char *childPStr;
    delete childPStr;
}

int main(int argc, char const *argv[])
{
    /* code */
    // testCore();
    testDumpInheritated();
    return 0;
}
