#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

void signalHandler(int sig){
    printf("Pid: %d Otrzymano sygnal: %d \n",getpid() ,sig);
}

int main(int argc, char *argv[]) {

    if(argc != 2){
        printf("Wrong arguemnts \n");
        return 1;
    }

    if(strcmp(argv[1], "ignore") == 0){
        printf("%d Raising signal \n", getpid());
        signal(SIGUSR1, SIG_IGN);
        raise(SIGUSR1);
    }
    if(strcmp(argv[1], "handler") == 0){
        printf("%d Raising signal \n", getpid());
        signal(SIGUSR1, signalHandler);
        raise(SIGUSR1);
    }
    if(strcmp(argv[1], "mask") == 0){
        printf("%d Raising signal \n", getpid());
        sigset_t sigSet;
        sigemptyset(&sigSet);
        sigaddset(&sigSet, SIGUSR1);
        sigprocmask(SIG_BLOCK, &sigSet, NULL);
        raise(SIGUSR1);
    }
    if(strcmp(argv[1], "pending") == 0){
        printf("%d Raising signal \n", getpid());
        sigset_t sigSet, pending;
        sigpending(&sigSet);
        sigemptyset(&sigSet);
        sigaddset(&sigSet, SIGUSR1);
        sigprocmask(SIG_BLOCK, &sigSet, NULL);
        raise(SIGUSR1);
        sigpending(&pending);
        if (sigismember(&pending, SIGUSR1) == 1){
            printf("PID: %d Signal is pending \n",getpid());
        }
    }
    pid_t pid = fork();
    if (pid == 0) {
        raise(SIGUSR1);
    }
}