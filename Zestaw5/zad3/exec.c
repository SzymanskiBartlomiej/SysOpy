#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

double f(double x){
    return 4.0/((x * x) + 1.0);
}

double integral(double a, double b, double precision) {
    double sum = 0.0;
    for (double x = a; x < b; x += precision) {
        sum += f(x) * precision;
    }
    return sum;
}

int main(int argc, char* argv[]){
    if (argc != 4){
        printf("wrong num of arg");
        return 0;
    }
    double precision = strtod(argv[1], NULL);
    int i = atoi(argv[2]);
    double interval = 1 / strtod(argv[3], NULL);

    double a = interval * i;
    double b = (i + 1)*interval;

    double value = integral(a, b, precision);

    FILE *file = fopen("/tmp/pipe", "w");
    fwrite(&value, sizeof(double), 1, file);
    fclose(file);
}