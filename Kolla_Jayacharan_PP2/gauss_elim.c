
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>
#include <omp.h>
#include <pthread.h>
#include <unistd.h>

/* Program Parameters */
#define MAXN 2000  /* Max value of N */
int N = 1000;  /* Matrix size */



/* Matrices and vectors */
volatile float A[MAXN][MAXN], B[MAXN], X[MAXN];
/* A * X = B, solve for X */



/*initialise_inputs() Function Will Be Used To Randomly Generate The Input Matrices
 *A, B, And The Resultant Matrix X*/
void initialize_inputs()
{
    int row, col;
    printf("\nInitializing Input Matrices...\n");
    for (col = 0; col < N; col++)
    {
        for (row = 0; row < N; row++)
        {
            A[row][col] = (float)rand() / RAND_MAX+1;
        }
        B[col] = (float)rand() / RAND_MAX+1;
        X[col] = 0.0;
    }
}

/*print_inputs() Function Will Be Used To Display The Input Matrices That Was Generated
 *By Using The initialise_inputs()*/
void print_inputs()
{
    int row, col;
    if (N <= 10)
    {
        printf("\nA =\n\t");
        for (row = 0; row < N; row++)
        {
            for (col = 0; col < N; col++)
            {
                printf("%5.2f%s", A[row][col], (col < N-1) ? ", " : ";\n\t");
            }
        }
        printf("\nB = [");
        for (col = 0; col < N; col++)
        {
            printf("%5.2f%s", B[col], (col < N-1) ? "; " : "]\n");
        }
    }
    else
    {
        printf("Input Initialized Successfully! Input Too Large To Display.\n");
    }
    printf("\n");
}

/*print_X() Function Will Be Used To Display The Resultant Matrix*/
void print_X()
{
    int row;
    if (N <= 10)
    {
        printf("RESULT:\n");
        printf("\nX = [");
        for (row = 0; row < N; row++)
        {
            printf("%5.2f%s", X[row], (row < N-1) ? "; " : "]\n");
        }
    }
}


int main() {
    /* Timing variables */
    struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */
    struct timezone tzdummy;
    clock_t etstart2, etstop2;  /* Elapsed times using times() */
    unsigned long long usecstart, usecstop;
    struct tms cputstart, cputstop;  /* CPU times for my processes */

    //int row, col;

    int norm, row, col;  /* Normalization row, and zeroing
			* element row and col */
    float multiplier;
    int num_thr ;
    printf("ENTER NUMBER OF THREADS");
    scanf("%d",&num_thr);

    /* Initialize A and B */
    initialize_inputs();
    /* Print input matrices */
    print_inputs();


    /*Running the below Gausian Elimination code for Number of threads 1, 2, 4, and 8*/

        /* Start Clock */
        gettimeofday(&etstart, &tzdummy);
        etstart2 = times(&cputstart);

        /* Gaussian Elimination */






        printf("Computing Parallelly...\n");
        /* Gaussian elimination */
        if(num_thr == 1)
        {
#pragma omp barrier
            printf("NUMBER OF THREADS CREATED: %d \n", num_thr);
#pragma omp parallel for num_threads (1) shared(A, B) private(multiplier,row,col)
            for (norm = 0; norm < N - 1; norm++)
            {
                for (row = norm + 1; row < N; row++)
                {
                    multiplier = A[row][norm] / A[norm][norm];
                    for (col = norm; col < N; col++)
                    {
                        A[row][col] -= A[norm][col] * multiplier;
                    }
                    B[row] -= B[norm] * multiplier;
                }
            }
            //	#pragma omg barrier
        }
        if(num_thr == 2)
        {
#pragma omp barrier
            printf("NUMBER OF THREADS CREATED: %d \n", num_t);
#pragma omp parallel for num_threads (2) shared(A, B) private(multiplier,row,col)
            for (norm = 0; norm < N - 1; norm++)
            {
                for (row = norm + 1; row < N; row++)
                {
                    multiplier = A[row][norm] / A[norm][norm];
                    for (col = norm; col < N; col++)
                    {
                        A[row][col] -= A[norm][col] * multiplier;
                    }
                    B[row] -= B[norm] * multiplier;
                }
            }
            //#pragma omp barrier
        }
        if(num_thr == 4)
        {
#pragma omp barrier
            printf("NUMBER OF THREADS CREATED: %d \n", num_thr);
#pragma omp parallel for num_threads (4) shared(A, B) private(multiplier,row,col)
            for (norm = 0; norm < N - 1; norm++)
            {
                for (row = norm + 1; row < N; row++)
                {
                    multiplier = A[row][norm] / A[norm][norm];
                    for (col = norm; col < N; col++)
                    {
                        A[row][col] -= A[norm][col] * multiplier;
                    }
                    B[row] -= B[norm] * multiplier;
                }
            }
            //	#pragma omp barrier
        }
        if(num_thr == 8)
        {
#pragma omp barrier
            printf("NUMBER OF THREADS CREATED: %d \n", num_thr);
#pragma omp parallel for num_threads (8) shared(A, B) private(multiplier,row,col)
            for (norm = 0; norm < N - 1; norm++)
            {
                for (row = norm + 1; row < N; row++)
                {
                    multiplier = A[row][norm] / A[norm][norm];
                    for (col = norm; col < N; col++)
                    {
                        A[row][col] -= A[norm][col] * multiplier;
                    }
                    B[row] -= B[norm] * multiplier;
                }
            }
        }






        /* Stop Clock */
        gettimeofday(&etstop, &tzdummy);
        etstop2 = times(&cputstop);
        usecstart = (unsigned long long) etstart.tv_sec * 1000000 + etstart.tv_usec;
        usecstop = (unsigned long long) etstop.tv_sec * 1000000 + etstop.tv_usec;

        /* Display timing results */
        printf("\nElapsed time = %g ms.\n",
               (float) (usecstop - usecstart) / (float) 1000);
        printf("(CPU times are accurate to the nearest %g ms)\n",
               1.0 / (float) _SC_CLK_TCK * 1000.0);
        printf("My total CPU time for parent = %g ms.\n",
               (float) ((cputstop.tms_utime + cputstop.tms_stime) -
                        (cputstart.tms_utime + cputstart.tms_stime)) /
               (float) _SC_CLK_TCK * 1000);
        printf("My system CPU time for parent = %g ms.\n",
               (float) (cputstop.tms_stime - cputstart.tms_stime) /
               (float) _SC_CLK_TCK * 1000);
        printf("My total CPU time for child processes = %g ms.\n",
               (float) ((cputstop.tms_cutime + cputstop.tms_cstime) -
                        (cputstart.tms_cutime + cputstart.tms_cstime)) /
               (float) _SC_CLK_TCK * 1000);
        printf("--------------------------------------------\n");
        


    /* (Diagonal elements are not normalized to 1.  This is treated in back
    * substitution.)
    */
    /* Back substitution */
    for (row = N - 1; row >= 0; row--)
    {
        X[row] = B[row];
        for (col = N - 1; col > row; col--)
        {
            X[row] -= A[row][col] * X[col];
        }
        X[row] /= A[row][row];
    }

    /* Display output */
    print_X();
}

