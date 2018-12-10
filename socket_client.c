#include <netinet/in.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>

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
    if(ret <= 0){
        if (ret == 0)
            fprintf(stderr, "Not in presentation format");
        else
            perror("inet_pton");
        exit(-1);
    }
    addr.sin_port = htons(atoi(argv[2]));

    int sock = socket(PF_INET, SOCK_STREAM, 0);
    ret= connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret== -1)
    {
        printf("errno is %d , server ip: %s , port is: %d\n ", errno, inet_ntoa(addr.sin_addr),ntohs(addr.sin_port));
        if (errno == ECONNREFUSED)
        {
            printf(" ECONNREFUSED \n");
        }
        else if (errno == ETIMEDOUT)
        {
            printf(" ETIMEOUT \n");
        }
    }
    close(sock);
    return 0;
}
