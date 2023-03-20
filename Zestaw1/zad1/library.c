#include "library.h"
struct memBlock* create_memBlock(int size){
    struct memBlock* mem = malloc(sizeof(struct memBlock));
    mem->arr = calloc(size, sizeof(char *));
    mem->maxSize = size;
    mem->len = 0;
    return mem;
}
long getFileSize(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}
void wordCount(struct memBlock *block, char path[]){
    char tmpFilePath[] = "/tmp/tmpWordCountXXXXXX";
    mkstemp(tmpFilePath);
    char command[255] = "wc ";
    strcat(command,path);
    strcat(command, " > ");
    strcat(command, tmpFilePath);
    system(command);
    FILE* file = fopen(tmpFilePath,"r");
    long size = getFileSize(file);
    block->arr[block->len] = calloc(size, sizeof(char ));
    fread(block->arr[block->len], sizeof(char ), size, file);
    block->len ++ ;
    fclose(file);
    char removeCommand[] = "rm ";
    strcat(removeCommand, tmpFilePath);

    system(removeCommand );
    return ;
}
char * getIndex(struct memBlock *block, int index){
    if(index < block->len && index >= 0) {
        return block->arr[index];
    }
    return "index do not exists";
}

void removeIndex(struct memBlock *block, int index){
    if(index < block->len && index >= 0){
        free(block->arr[index]);
        block->len --;
    }
    return;
}
void freeArr(struct memBlock *block){
    free(block->arr);
    return;
}