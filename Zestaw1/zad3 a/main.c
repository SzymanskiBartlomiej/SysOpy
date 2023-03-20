#include "library.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/times.h>
#include <dlfcn.h>
#define INPUT_LENGTH 1000
int main(){
#ifdef DYNAMIC

    void *handle = dlopen("./library.so", RTLD_LAZY);
    if (!handle) {
        printf("Failed to dlopen library.so");
        return -1;
    }

    struct memBlock* (*create_memBlock)(int) = dlsym(handle, "create_memBlock");
    void (*wordCount)(struct memBlock *, char *) = dlsym(handle, "wordCount");
    char* (*getIndex)(struct memBlock *, int) = dlsym(handle, "getIndex");
    void (*removeIndex)(struct memBlock *, int) = dlsym(handle, "removeIndex");
    void (*freeArr)(struct memBlock *) = dlsym(handle, "freeArr");

#endif

    struct memBlock* block;
    bool initialized = false;
    char command[INPUT_LENGTH];
    while (1){
        printf("\n >>> ");
        if (fgets(command, INPUT_LENGTH, stdin) == NULL){
            break;
        }

        clock_t start, end;
        double cpu_time_used;
        struct tms start_tms, end_tms;

        start = clock();
        times(&start_tms);

        command[strcspn(command, "\n")] = 0;
        printf("%s",command);
        strtok(command," ");
        char *arg=strtok(NULL," ");
        if(strcmp(command, "init") == 0){
            initialized = true;
            int argInt = atoi(arg);
            block = create_memBlock(argInt);
        }
        else if(strcmp(command,"count") == 0){
            arg[strcspn(arg, "\n")] = 0;
            if(initialized == false){ printf("\n array not initialized");continue;}
            wordCount(block, arg);
        }
        else if(strcmp(command,"show") == 0) {
            if(initialized == false){ printf("\n array not initialized");continue;}
            int argInt = atoi(arg);
            printf("\n%s", getIndex(block,argInt));
        }
        else if(strcmp(command,"delete") == 0) {
            if(initialized == false){ printf("\n array not initialized");continue;}
            int argInt = atoi(arg);
            removeIndex(block,argInt);
            printf("\n value deleted");
        }
        else if(strcmp(command,"destroy") == 0) {
            if(initialized == false){ printf("\n array not initialized");continue;}
            freeArr(block);
            initialized = false;
            printf("\n destroyed sucesfully");
        }
        else{
            printf("\n command not found");
        }
        sleep(1);

        end = clock();
        times(&end_tms);

        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        double usertime = ((double) (end_tms.tms_utime - start_tms.tms_utime)) / sysconf(_SC_CLK_TCK);
        double systemtime = ((double) (end_tms.tms_stime - start_tms.tms_stime)) / sysconf(_SC_CLK_TCK);

        printf("Czas rzeczywisty: %f s\n", cpu_time_used);
        printf("Czas użytkownika: %f s\n", usertime);
        printf("Czas systemowy: %f s\n", systemtime);
    }
    return 0;
}