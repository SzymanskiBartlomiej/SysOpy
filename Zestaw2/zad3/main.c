#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>


int main(){
    struct dirent *dent;
    DIR *dir;
    dir = opendir(".");
    struct stat s;
    long long int size;
    while ((dent = readdir(dir)) != NULL) {
            stat(dent->d_name, &s);
            if(!S_ISDIR(s.st_mode)){
                size += s.st_size;
                printf("nazwa : %s rozmiar: %ld \n",dent->d_name, s.st_size);
            }
    }
    printf("Sumaryczny rozmiar %lld \n",size);
    return 0;
}