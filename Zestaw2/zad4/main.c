#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ftw.h>

long long size = 0;
int printInfo(const char *path, const struct stat *s, int flag){
    if (!S_ISDIR(s->st_mode)) {
        printf("%ld %s\n", s->st_size, path);
        size += s->st_size;
    }
    return 0;
}
int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Enter directory name");
        return 0;
    }
    ftw(argv[1], printInfo, 16);
    printf("Total size - %lld ", size);
}