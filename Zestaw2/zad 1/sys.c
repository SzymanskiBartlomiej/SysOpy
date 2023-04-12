#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


int main(int argc, char *argv[]){
    if( argc != 5){
        printf("Wrong num of arguments");
        return 1    ;
    }

    char to_replace = argv[1][0];
    char replacement = argv[2][0];

    int input = open(argv[3], O_RDONLY);
    int output = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (input == -1){
        printf("Can't open input file");
        return 0;
    }
    if (output == -1){
        printf("Can't open output file");
        return 0;
    }

    struct stat statbuf;
    fstat(input, &statbuf);

    size_t size = statbuf.st_size;
    char *buffer = malloc(size);

    read(input, buffer, size);

    for (int i = 0; i< size; i++){
        if (buffer[i] == to_replace){
            buffer[i] = replacement;
        }
    }
    write(output, buffer, size);

    close(input);
    close(output);

    free(buffer);
}