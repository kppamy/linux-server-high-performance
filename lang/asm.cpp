#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
using namespace std;

void test(string &&rv)
{
    string lc = move(rv);
    cout << "address of local rvalue: " << &lc << " " << lc << endl;
}

string gs = "cococco";
const string gcs = "cococcocc";

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

void testmmap()
{
    size_t pagesize = getpagesize();

    printf("System page size: %zu bytes\n", pagesize);

    char *region = mmap(
        (void *)(pagesize * (1 << 20)), // Map from the start of the 2^20th page
        pagesize,                       // for one page length
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_ANON | MAP_PRIVATE, // to a private block of hardware memory
        0,
        0);
    if (region == MAP_FAILED)
    {
        perror("Could not mmap");
    }

    strcpy(region, "Hello, poftut.com");

    printf("Contents of region: %s\n", region);

    int unmap_result = munmap(region, 1 << 10);
    if (unmap_result != 0)
    {
        perror("Could not munmap");
        return 1;
    }
}

int main()
{
    cout << "address of global string: " << &gs << " " << gs << endl;
    cout << "address of global const string: " << &gcs << " " << gcs << endl;

    int *arr = new int[2];
    cout << "new array address:     " << arr << endl;

    std::string lv = "sdjfdk";
    test(lv + lv);

    const string cs = "caycay";
    cout << "address of local const string: " << &cs << " " << cs << endl;

    cout << "address of lvalue: " << &lv << " " << lv << endl;
    std::string lv2 = lv + lv;
    cout << "address of lvalue2: " << &lv2 << " " << lv2 << endl;
    std::string &&rv = "sdjfdk";
    string &&rv2 = lv + lv;
    cout << "address of rvalue: " << &rv << " " << rv << endl;
    cout << "address of rvalue2: " << &rv2 << " " << rv2 << endl;
    cout << "address of function :%p " << test << endl;

    testRvalue();
    testmmap();

    getchar();
    return 0;
}
