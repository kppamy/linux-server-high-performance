#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
// #include <syslog.h>

char command[256];
int main(int argc, char const *argv[])
{
    int rtn;
    // openlog("fork_test", LOG_PID|LOG_CONS, LOG_USER);
    while(1){
        fgets(command,256, stdin);
        command[strlen(command)-1] = 0;
        if(fork()==0){
            // syslog(LOG_INFO,"I am in child process");
            int pid = getpid();
            execlp(command,command);
            printf(" Wairing for input in child process : %d\n", pid);
            perror(command);
            exit(errno);
        }else{
            int pid = getpid();
            printf(" I am in parent process : %d\n", pid);
            // syslog(LOG_INFO, "I am in parent process");
            wait(&rtn);
            printf("child process return, %d\n", rtn);
            // syslog(LOG_INFO, "child process return: %d \n",rtn);
        }
    }
    // closelog();
    return 0;
}
