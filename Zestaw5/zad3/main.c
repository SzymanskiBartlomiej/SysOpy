#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char* argv[]){
    if (argc != 3){
        printf("wrong num of arg");
        return 0;
    }

    int n = atoi(argv[2]);


    double result = 0.0;

    mkfifo("/tmp/pipe", 0777);
    for (int i = 0; i < n; i++){

        pid_t pid = fork();
        if (pid == 0){
            char i_str[50];
            snprintf(i_str, sizeof(i_str), "%d", i);
            execl("exec", "exec",argv[1], i_str, argv[2], NULL);
        }
    }

    FILE* file = fopen("/tmp/pipe","r");
    for (int i = 0; i < n; i++){
        double tmp = 0.0;
        fread(&tmp, sizeof(double), 1, file);
        result += tmp;
    }
    fclose(file);
    printf("\n wynik: %f \n",result);
}