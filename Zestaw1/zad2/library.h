#ifndef LIBRARY_H
#define LIBRARY_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BLOCK_SIZE 1024
struct memBlock{
    char **arr;
    int maxSize;
    int len;
};

struct memBlock* create_memBlock(int size);
void wordCount(struct memBlock *block, char word[]);
char * getIndex(struct memBlock *block, int index);
void removeIndex(struct memBlock *block, int index);
void freeArr(struct memBlock *block);
#endif