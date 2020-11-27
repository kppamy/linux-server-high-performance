#include<memory.h>
void testStackOverflow(char* str){
    char sarr[2];
    memcpy(sarr,str,sizeof(str));
}

#include<iostream>
void hack(){
    std::cout<<"danger!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<std::endl;
}


int main(int argc, char const *argv[])
{
    char* str="sdfdfd";
    testStackOverflow(str);
    std::cout<<"back to main"<<std::endl;
    return 0;
}
