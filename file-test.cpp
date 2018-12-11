#include "file-test.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <assert.h>
#include <sys/types.h>
#include <pthread.h>
#include <sys/select.h>

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
        printf(" this is a son in pid:  %d \n ", getpid());
        sprintf(fa, "%s", " hello, father, how are you? \n  ");
        sleep(2);
        printf(" Son gets message: %s\n ", fa);
        munmap(fa, 100);
        return;
    }
    else
    {
        sleep(1);
        printf("I am father in pid: %d\n ", getpid());
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
    if (argc < 2)
    {
        printf("Usage: IP PORT");
        return;
    }
    sockaddr_in server = transSockAddr(argv[1], atoi(argv[2]));
    int lisfd = getListenFd(server, 5);

    sockaddr_in client;
    int conn = getConnectFd(&client, lisfd);
    close(STDOUT_FILENO);
    int dfd = dup(conn);
    printf("i am test dup call\n");
    char buf[256];
    int len = recv(dfd, buf, sizeof(buf), 0);
    printf("recv something form cient: %s\n", buf);
    close(conn);
    close(lisfd);
}

void FileTest::testPipe()
{
    int fd[2];
    int ret = pipe(fd);
    assert(ret != -1);
    ret = fork();
    assert(ret != -1);
    if (ret == 0)
    {
        close(fd[1]);
        char buf[256];
        int len = read(fd[0], buf, sizeof(buf));
        if (len == -1)
        {
            printf("errno: %d\n", errno);
        }
        else
            printf("recv someting form father len=%d\n, %s\n", len, buf);
        close(fd[0]);
    }
    else
    {
        close(fd[0]);
        const char *data = "hello, child? i am using pip \n";
        fcntl(fd[0], O_NONBLOCK);
        int len = write(fd[1], data, strlen(data));
        if (len == -1)
        {
            printf("errno: %d\n", errno);
        }
        else
            printf("send message to child len=%d\n", len);
        close(fd[1]);
    }
}

void FileTest::testSockPair()
{
    int fd[2];
    int ret = socketpair(PF_UNIX, SOCK_STREAM, 0, fd);
    assert(ret != -1);
    ret = fork();
    if (ret == 0)
    {
        char data[256] = "i am child\n";
        write(fd[1], data, strlen(data));
        sleep(1);
        memset(data, '\0', strlen(data));
        int ret = read(fd[0], data, sizeof(data));
        if (ret == -1)
        {
            printf("errno: %d\n", errno);
        }
        else
        {
            printf("read something from father: %s\n", data);
        }
    }
    else
    {
        char data[256];
        memset(data, '\0', strlen(data));
        read(fd[0], data, sizeof(data));
        printf("read something from child: %s\n", data);
        const char *word = "i am father \n";
        int ret = write(fd[1], word, strlen(word));
        if (ret == -1)
        {
            printf("errno: %d\n", errno);
        }
        else
        {
            printf("wite message to pipe len=%d\n", ret);
        }
    }
    close(fd[0]);
    close(fd[1]);
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

int FileTest::getConnectFd(struct sockaddr_in *client, int sock)
{
    socklen_t len = sizeof(client);
    int conn = accept(sock, (struct sockaddr *)client, &len);
    assert(conn != -1);
    char remote[INET_ADDRSTRLEN];
    printf("connected with ip: %s, port: %d\n",
           inet_ntop(AF_INET, &client->sin_addr, remote, INET_ADDRSTRLEN), ntohs(client->sin_port));
    return conn;
}

void FileTest::testSyncC10K(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf(" Usage:  IP port \n ");
        return;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server = transSockAddr(ip, port);

    const int CLIENT_MAX = 60000;
    int sock = getListenFd(server, CLIENT_MAX);
    int count = 0;
    char buf[256];
    while (count < CLIENT_MAX)
    {
        sockaddr_in client;
        int conn = getConnectFd(&client, sock);
        printf(" connect with client %d\n", count + 1);
        printf(" connect with client in thread: %ld\n", pthread_self());
        memset(buf, '\0', sizeof(buf));
        int len = recv(conn, buf, sizeof(buf), 0);
        printf(" Recv from client %d, %s\n", count + 1, buf);
        count++;
        close(conn);
    }
    close(sock);
}

void FileTest::testAsyncC10K(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf(" Usage:  IP port \n ");
        return;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server = transSockAddr(ip, port);

    const int CLIENT_MAX = 60000;
    int sock = getListenFd(server, CLIENT_MAX);
    int count = 0;
    char buf[256];
    while (count < CLIENT_MAX)
    {
        sockaddr_in client;
        int conn = getConnectFd(&client, sock);
        printf(" connect with client %d\n", count + 1);
        memset(buf, '\0', sizeof(buf));
        int len = recv(conn, buf, sizeof(buf), 0);
        printf(" Recv from client %d, %s\n", count + 1, buf);
        count++;
        close(conn);
    }
    close(sock);
}

void FileTest::testSelect(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf(" Usage:  IP port \n ");
        return;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    struct sockaddr_in server = transSockAddr(ip, port);

    const int CLIENT_MAX = 500;

    fd_set readfd;
    fd_set writefd;
    fd_set excepfd;

    int sock = getListenFd(server, CLIENT_MAX);

    sockaddr_in client;

    int conn = -1;
    char buf[256];
    conn = getConnectFd(&client, sock);
    
    while (true)
    {
        FD_SET(sock, &readfd);
        FD_SET(sock, &excepfd);
        FD_SET(sock, &writefd);
        FD_SET(conn, &readfd);
        FD_SET(conn, &excepfd);
        // FD_SET(conn, &writefd);
        int ret = select(conn + 1, &readfd, &writefd, &excepfd, NULL);
        if(ret == -1){
            printf("select failure !!! \n");
            break;
        }
        if (FD_ISSET(conn, &readfd))
        {
            printf(" get conn read signal in thread: %ld\n\n", pthread_self());
            memset(buf, '\0', sizeof(buf));
            int len = recv(conn, buf, sizeof(buf), 0);
            if(len == 0){
                printf("client is off, quit ourself \n"); 
                break;
            }
            send(conn, "hello, child ", 10, 0);
            printf(" Recv from client  %s\n", buf);
        }
        else if (FD_ISSET(conn, &writefd))
        {
            printf(" get conn write signal in thread :%ld\n\n", pthread_self());
        }
        else if (FD_ISSET(conn, &excepfd))
        {
            printf(" get conn exception signal\n\n");
        }
        else if (FD_ISSET(sock, &readfd))
        {
            printf(" get listfd read signal\n\n");
            sockaddr_in client;
            conn = getConnectFd(&client, sock);
        }
        else if (FD_ISSET(sock, &excepfd))
        {
            printf(" get listfd exception signal\n\n");
        }
        else
        {
            printf(" dont know what we get\n\n");
        }
    }

    close(conn);
    close(sock);
}

int main(int argc, char const *argv[])
{
    /* code */
    //FileTest::testMmap();
    // FileTest::testMmapFamily();
    // FileTest::testSocket(argc, argv);
    // FileTest::testDup(argc, argv);
    // FileTest::testPipe();
    // FileTest::testSockPair();
    // FileTest::testSyncC10K(argc,argv);
    //FileTest::testAsyncC10K(argc, argv);
    FileTest::testSelect(argc, argv);
    return 0;
}
