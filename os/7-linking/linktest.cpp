#include<stdio.h>
#include<unistd.h>
#include "vec.h"






int main(int argc, char const *argv[])
{
    int x[2]={1, 1};
    int y[2]={2, 2};
    int z[2];

    pid_t p1=fork();
    if(p1==0){
        y[0]=3;
        y[1]=3;
        printf("I am child process\n");
        addvec(x, y, z, 2);
    }
    printf("PID=%d: addcnt: adress=%d , value=%d \n", p1, &addcnt, addcnt);
    addvec(x, y, z, 2);
    printf("PID=%d: addcnt=%d, z: %d %d \n",p1,addcnt, z[0], z[1]);
    return 0;
}


// gcc -o tlink linktest.cpp libvector.so 