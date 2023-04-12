#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signum)
{
    printf("Received signal %d\n", signum);
}

int main(int argc, char *argv[]) {

    struct sigaction action;
    action.sa_handler = handler;
    action.sa_flags = SA_RESETHAND;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);

    raise(SIGINT);

    raise(SIGINT);

    return 0;
}