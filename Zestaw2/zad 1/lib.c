#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>



int main(int argc, char *argv[]){
    if( argc != 5){
        printf("Wrong num of arguments");
        return 1    ;
    }

    char to_replace = argv[1][0];
    char replacement = argv[2][0];

    FILE *input = fopen(argv[3],"r");
    FILE *output = fopen(argv[4],"w");
    if (!input){
        printf("Can't open input file");
        return 0;
    }
    if (!output){
        printf("Can't open output file");
        return 0;
    }

    fseek(input, 0, SEEK_END);
    long fsize = ftell(input);
    fseek(input, 0, SEEK_SET);

    char *buffer = malloc(fsize + 1);
    fread(buffer, fsize, 1, input);


    for (int i = 0; i< strlen(buffer); i++){
        if (buffer[i] == to_replace){
            buffer[i] = replacement;
        }
    }
    fwrite(buffer, sizeof(char), fsize, output);

    fclose(input);
    fclose(output);

    free(buffer);
}