#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>



int main(int argc, char *argv[]) {
    if(argc != 2 && argc != 3){
        printf("Wrong arguemnts \n");
        return 1;
    }

    if(strcmp(argv[1], "ignore") == 0){
        printf("%d Raising signal \n", getpid());
        signal(SIGUSR1, SIG_IGN);
        raise(SIGUSR1);
    }
    if(strcmp(argv[1], "mask") == 0 && argc == 2){
        printf("%d Raising signal \n", getpid());
        sigset_t sigSet;
        sigaddset(&sigSet, SIGUSR1);
        sigprocmask(SIG_BLOCK, &sigSet, NULL);
        raise(SIGUSR1);
    }
    if(strcmp(argv[1], "pending") == 0){
        sigset_t sigSet;
        sigpending(&sigSet);
        if(argc == 2){
            printf("%d Raising signal \n", getpid());
            sigemptyset(&sigSet);
            sigaddset(&sigSet, SIGUSR1);
            sigprocmask(SIG_BLOCK, &sigSet, NULL);
            raise(SIGUSR1);

            if (sigismember(&sigSet, SIGUSR1) == 1){
                printf("Parent is pending \n");
            }
        }

        else{
            if(sigismember(&sigSet, SIGUSR1) == 1){
                printf("Child is pending \n");
            }
        }
    }
    if(argc == 2){
        printf("xDD");
        execl(argv[0], argv[0],argv[1] ,"child", NULL);
    }

}