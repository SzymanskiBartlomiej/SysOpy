#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>

void searchDir(char* path, char* inputString){
        DIR* dir = opendir(path);
        if (dir == NULL){
            perror("error");
            exit(-1);
        }
        struct dirent *fileOrDir;
        while ((fileOrDir = readdir(dir)) != NULL){
            if(strcmp(fileOrDir->d_name, ".") == 0 || strcmp(fileOrDir->d_name, "..") == 0){
                continue;
            }

            char filePath[PATH_MAX];
            struct stat stats;


            strcpy(filePath, path);
            strcat(filePath, "/");
            strcat(filePath, fileOrDir->d_name);

            stat(filePath, &stats);
            if(S_ISDIR(stats.st_mode)){
                pid_t pid = fork();
                if (pid == 0){
                    searchDir(filePath, inputString);
                    exit(0);
                }
            } else{
                FILE *file = fopen(filePath,"r");
                if (file == NULL){
                    perror("eroor");
                    continue;
                }
                char* fileData = calloc(strlen(inputString), sizeof(char));
                fgets(fileData, strlen(inputString) + 1, file);
                if(strcmp(fileData, inputString) == 0){
                    printf("%s %d \n", path, getpid());
                }
                free(fileData);
            }
        }

}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 0;
    }
    if(strlen(argv[2]) > 255){
        printf("string is too long");
        return 0;
    }
    searchDir(argv[1],argv[2]);
}