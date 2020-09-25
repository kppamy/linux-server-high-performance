#include <iostream>
#include <vector>
using namespace std;


void printVector(vector<int> &input){
    for(int v:input){
        cout<<v<<" ";
    }
    cout<<endl;
}

#define LOG(level, format, ...) \
    do { \
        fprintf(stderr, "[%s|%s@%s,%d] " format "/n", \
            level, __func__, __FILE__, __LINE__, ##__VA_ARGS__ ); \
    } while (0)
 
int main()
{

    printf("FUNCINFO:%s\n",__FUNCTION__);
    // LOG(“DEBUG”, "a=%d", 10);
    return 0;
}