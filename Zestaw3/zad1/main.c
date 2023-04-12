#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/wait.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        return 0;
    }
    pid_t pid;
    int parent = getpid();
    int n = atoi(argv[1]);
    for (int i = 0; i < n; i++){
        if(fork() == 0){
            printf("pid rodzica: %d pid procesu potomnego: %d \n", parent, getpid());
            exit(1);
        }
    }
    while ((pid = wait(NULL)) > 0);
    printf("number of processes %d \n", n);
    return 0;
}