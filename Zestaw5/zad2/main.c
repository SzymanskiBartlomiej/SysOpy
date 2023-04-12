#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


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
    if (argc != 3){
        printf("wrong num of arg");
        return 0;
    }

    double precision = strtod(argv[1], NULL);
    int n = atoi(argv[2]);


    double interval = 1.0 / n;
    double result = 0.0;
    int pipes[n];
    for (int i = 0; i < n; i++){
        int fd[2];
        pipe(fd);

        pid_t pid = fork();
        if (pid == 0){
            close(fd[0]);
            double value = integral(interval * i, (i + 1)*interval, precision);
            write(fd[1], &value, sizeof(double));
            return 0;
        }
        else{
            close(fd[1]);
            pipes[i] = fd[0];
        }
    }
    for (int i = 0; i < n; i++){
        double tmp = 0.0;
        read(pipes[i], &tmp, sizeof(double));
        result += tmp;
    }
    printf("\n wynik: %f \n",result);
}