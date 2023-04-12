#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signum)
{
    printf("Received signal %d\n", signum);
    sleep(5);
}

int main(int argc, char *argv[]) {

    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = SA_NODEFER;
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);

    raise(SIGUSR1);

    raise(SIGUSR1);

    return 0;
}