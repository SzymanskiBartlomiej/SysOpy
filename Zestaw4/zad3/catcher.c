#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <time.h>

int command = 0;
int signalsReceived = 0;
void handler(int sig, siginfo_t* info, void* context){
    command = info->si_value.sival_int;
    printf("Odebrany sygnal: %d \n",command);
    if(command < 1 || command > 5){
        printf("wrong command?");
        return ;
    }
    signalsReceived ++;
    kill(info -> si_pid, SIGUSR1);

}
int main(int argc, char* argv[]){
    struct sigaction act;
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    sigaction(SIGUSR1, &act, NULL);

    printf("pid: %d \n",getpid());

    while(1) {

        if (command == 0){
            pause();
        }
        else if (command == 1){
            for(int i = 0; i < 100; i++){
                printf("%d ", i);
            }
            printf("\n");
            command = 0;
        }
        else if (command == 2){
            time_t now = time(NULL);
            char* timeStr = ctime(&now);
            printf("%s \n", timeStr);
            command = 0;
        }
        else if (command == 3){
            printf("Received %d singals \n",signalsReceived);
            command = 0;
        }
        else if (command == 4){
            time_t now;
            char* timeStr;

            while (command == 4){
                now = time(NULL);
                timeStr = ctime(&now);
                printf("%s \n", timeStr);
                sleep(1);
            }
        }
        else if (command == 5){
            return 1;
        }
    }
}