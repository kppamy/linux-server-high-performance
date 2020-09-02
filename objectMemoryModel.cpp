#include<iostream>
// using namespace std;

int global_v0;
int global_val = 0;

const int const_global_val = 0; // no symbol generated ?

class test
{
private:
    int val;
};

class subtest:test{

};





int main(int argc, char const *argv[])
{
    test tt;  // no symbol generated ?
    test t2=tt;  // no symbol generated ?
    int val=sizeof(tt);  // no symbol generated ?
    printf(" global_val %d\n", global_val);
    printf(" sizeof(int) %d\n", sizeof(int));
    printf(" sizeof(long) %d\n", sizeof(long));
    printf(" sizeof(float) %d\n", sizeof(float));
    printf(" sizeof(double) %d\n", sizeof(double));
    printf(" sizeof(long long) %d\n", sizeof(long long));
    // cout<<"size test "<<sizeof(test)<<endl;
    // std::cout<<"size test instance "<<sizeof(tt)<<std::endl;
    return 0;
}
