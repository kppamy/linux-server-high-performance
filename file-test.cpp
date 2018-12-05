#include "file-test.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

void FileTest::testMmap(){
    int fd = open("test",O_RDWR|O_CREAT, S_IRWXU);
    if(fd<0){
        printf("open file failed \n");
    }else{
        printf("open file fd = %d \n", fd);
    }
    struct stat fst;
    if(fstat(fd, &fst)<0){
        printf(" file status error \n");
    }else{
        printf(" file status: %d\n ", fst);
    }
    void* shm;
    if((shm = mmap(NULL,fst.st_size,PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0))== MAP_FAILED){
        printf(" map file error \n");
    }
}