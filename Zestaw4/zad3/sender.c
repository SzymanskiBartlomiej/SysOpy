#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int sig_response = 0;
void handler(int sig){
    printf("received \n");
}

int main(int argc, char* argv[]){
    if(argc < 3){
        printf("Wrong number of arguments");
        return 1;
    }

    sigset_t set;
    sigemptyset(&set);

    signal(SIGUSR1, handler);

    int catcherPid = atoi(argv[1]);
    for (int i = 2; i < argc; i++){

        int command = atoi(argv[i]);



        union sigval value;
        value.sival_int = command;

        sigqueue(catcherPid, SIGUSR1, value);
        sigsuspend(&set);
    }
}