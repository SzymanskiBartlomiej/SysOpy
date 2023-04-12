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


    char c;

    //przesuwa pointer na ostatni bajt koniec inputu
    int p=fseek(input,-1,SEEK_END);
    while(p==0){
        c=fgetc(input);
        fputc(c,output);
        p=fseek(input,-2,SEEK_CUR);
    }

    fclose(input);
    fclose(output);

}