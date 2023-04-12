#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
    if( argc != 3){
        printf("Wrong num of arguments");
        return 1    ;
    }

    FILE *input = fopen(argv[1],"r");
    FILE *output = fopen(argv[2],"w");

    if (!input){
        printf("Can't open input file");
        return 0;
    }
    if (!output){
        printf("Can't open output file");
        return 0;
    }

    fseek(input, 0, SEEK_END);
    long size = ftell(input);
    fseek(input, 0, SEEK_SET);

    char buffer[BUFFER_SIZE];
    int remaining_bytes = size % BUFFER_SIZE;
    long num_blocks = size / BUFFER_SIZE;

    if (remaining_bytes > 0) {
        num_blocks += 1;
    }
    for (long block_index = num_blocks-1; block_index >= 0; block_index--) {
        long block_size = BUFFER_SIZE;
        if (block_index == num_blocks-1 && remaining_bytes > 0) {
            block_size = remaining_bytes;
        }
        fseek(input, block_index * BUFFER_SIZE, SEEK_SET);
        fread(buffer, block_size, 1, input);
        for (int i = block_size-1; i >= 0; i--) {
            fputc(buffer[i], output);
        }
    }

    fclose(input);
    fclose(output);

    return 0;
}