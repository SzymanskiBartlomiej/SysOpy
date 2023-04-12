#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void infoHandler(int sig_no,siginfo_t *info, void *context){
    printf("Signal number %d\n", info->si_signo);
    printf("PID: %d \n", info->si_pid);
    printf("UID: %d \n",info->si_uid);
    printf("System time elapsed %ld\n", info->si_stime);
    printf("User time elapsed %ld\n", info->si_utime);
}


int main(int argc, char *argv[]) {
    struct sigaction action;
    sigemptyset(&action.sa_mask);
    action.sa_sigaction = infoHandler;
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &action, NULL);

    raise(SIGUSR1);
    printf("CHILD:\n");
    pid_t pid = fork();
    if (pid == 0) {
        raise(SIGUSR1);
    }
}