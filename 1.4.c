#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 590

int main(int argc, char **argv) {
    omp_set_num_threads(1);//set number of threads here
    int i, j, k;
    double sum;
    double start, end, avg = 0; // used for timing
    double A[N][N], B[N][N], C[N][N];
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = j*1;
            B[i][j] = i*j+2;
            C[i][j] = j-i*2;
        }
    }

    //averaging the time for 10 runs.
    int x;
    for(x = 0; x < 10; x++){

        start = omp_get_wtime(); //start time measurement

        //#pragma omp parallel for private(i, j, k, sum) shared(A, B, C)
        for (i = 0; i < N; i++) {
            #pragma omp parallel for private(j, k, sum) shared(A, B, C)
            for (j = 0; j < N; j++) {
                sum = 0;
                for (k=0; k < N; k++) {
                    sum += A[i][k]*B[k][j];
                }
                C[i][j] = sum;
            }
        }
        
        end = omp_get_wtime(); //end time measurement
        avg += end - start;
    }

    printf("Time of computation: %f seconds\n", avg / 10);
    return(0);
}
