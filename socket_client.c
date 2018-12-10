#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("Usage: IP Port\n");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    int ret = inet_pton(AF_INET, argv[1], &addr.sin_addr);
    if (ret <= 0)
    {
        if (ret == 0)
            fprintf(stderr, "Not in presentation format");
        else
            perror("inet_pton");
        exit(-1);
    }
    addr.sin_port = htons(atoi(argv[2]));

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    ret = connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        printf("errno is %d , server ip: %s , port is: %d\n ", errno, inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        if (errno == ECONNREFUSED)
        {
            printf(" ECONNREFUSED \n");
        }
        else if (errno == ETIMEDOUT)
        {
            printf(" ETIMEOUT \n");
        }
    }
    else
    {
        const char *data = "hello, how are you?";
        int len = send(sock, data, strlen(data), 0);
        printf("send data to server len: %d\n", len);
        const char *oob = "Ergency!!!!!!!!";
        len = send(sock, oob, strlen(oob), MSG_OOB);
        printf("send data to server len: %d\n", len);
        const char *data2 = "hello, how do you do?";
        len = send(sock, data2, strlen(data2), 0);
        printf("send data to server len: %d\n", len);

        char read[256];
        while (1)
        {
            memset(read, '\0',sizeof(read));
            len = recv(sock, read, sizeof(read), 0);
            if(len <= 0){
                break;
            }else{
                printf("\n\n recv data from server len: %d: %s\n", len, read);
            }
        }
    }
    close(sock);
    return 0;
}
