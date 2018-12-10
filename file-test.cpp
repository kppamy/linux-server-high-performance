#include "file-test.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>

void FileTest::testMmap()
{
    int fd = open("./test", O_RDWR | O_CREAT, S_IRWXU);
    if (fd < 0)
    {
        printf("open file failed \n");
    }
    else
    {
        printf("open file fd = %d \n", fd);
    }
    struct stat fst;
    if (fstat(fd, &fst) < 0)
    {
        printf(" file status error \n");
    }
    else
    {
        printf(" file status: %d\n ", fst);
    }
    void *shm;
    if ((shm = mmap(NULL, fst.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    {
        printf(" map file error \n");
    }
    snprintf((char *)shm, 4, "test");
    msync(shm, fst.st_size, MS_ASYNC);
    if (munmap(shm, fst.st_size) < 0)
    {
        printf("munmap wrong");
    }
}

void FileTest::testMmapFamily()
{
    char *fa;
    fa = (char *)mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (fork() == 0)
    {
        printf(" this is a son in pid:  %d,  %d \n ", getpid(), &fa);
        sprintf(fa, "%s", " hello, father, how are you? \n  ");
        sleep(2);
        printf(" Son gets message: %s\n ", fa);
        munmap(fa, 100);
        return;
    }
    else
    {
        sleep(1);
        printf("I am father in pid: %d,  %d\n ", getpid(), &fa);
        printf("father got message: %s\n ", fa);
        sprintf(fa, "%s", " Fine, thanks, son \n  ");
        munmap(fa, 100);
    }
}
void FileTest::testSocket(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf(" Usage:  IP port \n ");
        return;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server = transSockAddr(ip, port);

    int sock = getListenFd(server, 5);

    struct sockaddr_in client;
    int conn = getConnectFd(&client, sock);
    char buf[256];
    int len = -2;
    int oob = -2;
    while (true)
    {
        printf("waiting .............\n");
        oob = sockatmark(conn);
        if (oob == 1)
        {
            len = recv(conn, buf, sizeof(buf), MSG_OOB);
            printf("recv OOB data \n");
        }
        else
        {
            len = recv(conn, buf, sizeof(buf), 0);
        }
        if (len <= 0)
        {
            printf("errno: %d \n", errno);
            break;
        }
        else
        {
            printf("recv data len = %d :%s\n", len, buf);
        }
    }
    close(conn);
    close(sock);
}

void FileTest::testDup(int argc, char const *argv[])
{
    if(argc < 2){
        printf("Usage: IP PORT");
        return;
    }
    sockaddr_in server = transSockAddr(argv[1], atoi(argv[2]));
    int lisfd= getListenFd(server, 5);

    sockaddr_in client;
    int conn = getConnectFd(&client,lisfd);
    close(STDOUT_FILENO);
    int dfd = dup(conn);
    printf("i am test dup call\n");
    char buf[256];
    int len= recv(dfd, buf, sizeof(buf),0);
    printf("recv something form cient: %s\n", buf);
    close(conn);
    close(lisfd);

}

struct sockaddr_in FileTest::transSockAddr(const char *ip, const int port)
{
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(sizeof(address.sin_addr), ip, &address.sin_addr);
    address.sin_port = htons(port);
    return address;
}

int FileTest::getListenFd(sockaddr_in address, int num)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    assert(sock != -1);

    int ret = bind(sock, (const sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, num);
    assert(ret != -1);
    return sock;
}

int FileTest::getConnectFd(struct sockaddr_in *client,int sock)
{
    socklen_t len = sizeof(client);
    int conn = accept(sock, (struct sockaddr *)client, &len);
    assert(conn != -1);
    char remote[INET_ADDRSTRLEN];
    printf("connected with ip: %s, port: %d\n",
           inet_ntop(AF_INET,&client->sin_addr, remote, INET_ADDRSTRLEN), ntohs(client->sin_port));
    return conn;
}

int main(int argc, char const *argv[])
{
    /* code */
    //FileTest::testMmap();
    // FileTest::testMmapFamily();
    // FileTest::testSocket(argc, argv);
    FileTest::testDup(argc, argv);
    return 0;
}