#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "timer.h"
#include "Lab3IO.h"

int main(int argc, char* argv[]) {
	
	int i, j, k;
	double **Au;
    double *X;
    double temp;
	int size; 
	int *index;
    double start, finish, elapsed;

    int thread_count = atoi(argv[1]);

	// load input and create the unknown vector X
    Lab3LoadInput(&Au, &size);
    X = CreateVec(size);

	index = malloc(size * sizeof(int));

    GET_TIME(start);
# pragma omp parallel for 
    for (i = 0; i < size; ++i)
        index[i] = i;

    if (size == 1)
        X[0] = Au[0][1] / Au[0][0];
    else{
        /*Gaussian elimination*/
        for (k = 0; k < size - 1; ++k){
            /*Pivoting*/
            temp = 0;

            for (i = k, j = 0; i < size; ++i)
                if (temp < Au[index[i]][k] * Au[index[i]][k]){
                    temp = Au[index[i]][k] * Au[index[i]][k];
                    j = i;
                }

            if (j != k)/*swap*/{
                i = index[j];
                index[j] = index[k];
                index[k] = i;
            }
	
            /*calculating*/
# pragma omp parallel for num_threads(thread_count) private(i,j,temp) shared(k,index, size, Au, X)
            for (i = k + 1; i < size; ++i){
                temp = Au[index[i]][k] / Au[index[k]][k];
                for (j = k; j < size + 1; ++j)
                    Au[index[i]][j] -= Au[index[k]][j] * temp;
            }       
        }

        /*Jordan elimination*/
        for (k = size - 1; k > 0; --k){
# pragma omp parallel for private(i, temp) shared(k, size, Au, index, X)
            for (i = k - 1; i >= 0; --i ){
                temp = Au[index[i]][k] / Au[index[k]][k];
                Au[index[i]][k] -= temp * Au[index[k]][k];
                Au[index[i]][size] -= temp * Au[index[k]][size];
            } 
        }

# pragma omp for
        for (k=0; k< size; ++k)
            X[k] = Au[index[k]][size] / Au[index[k]][k];

    }
    GET_TIME(finish);
    elapsed = finish - start;
    Lab3SaveOutput(X, size, elapsed);
}
