
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <limits.h>
#include <string.h>
#include <omp.h>
#include <unistd.h>

#define N 500 /*Size Of The Matrix*/

/*Defining Matrices A & B Are Input Matrices and C is the Output Matrix*/
int A[N][N], B[N][N], C[N][N] = {0};

/*initialise_inputs() Function Will Be Used To Randomly Generate The Input Matrices A, B*/
void initialize_inputs()
{
    int row, col;
    printf("\nInitializing Input Matrices...\n");
    for (col = 0; col < N; col++)
    {
        for (row = 0; row < N; row++)
        {
            A[row][col] = rand() % (N + 1 - 0) + 0; //Range Of Random ==> rand() % (max_number + 1 - minimum_number) + minimum_number
        }
    }
    for (col = 0; col < N; col++)
    {
        for (row = 0; row < N; row++)
        {
            B[row][col] = rand() % (N + 1 - 0) + 0; //Range Of Random ==> rand() % (max_number + 1 - minimum_number) + minimum_number
        }
    }
}

/*print_inputs() Function Will Be Used To Display The Input Matrices That Was Generated
 *By Using The initialise_inputs()*/
void print_inputs()
{
    int row, col;
    if (N < 10)
    {
        printf("\nMatrix A :\n");
        for (row = 0; row < N; row++)
        {
            for (col = 0; col < N; col++)
            {
                printf("%d%s", A[row][col], (col < N-1) ? ", " : ";\n");
            }
        }
        printf("\nMatrix B :\n");
        for (row = 0; row < N; row++)
        {
            for (col = 0; col < N; col++)
            {
                printf("%d%s", B[row][col], (col < N-1) ? ", " : ";\n");
            }
        }
    }
    else
    {
        printf("Input Initialized Successfully! Input And Output Too Large To Display.\n");
    }
    printf("\n");
}

/*print_output() Function Is Used To Print The Resultant Matrix*/
void print_output()
{
    int i, j;
    if(N<10)
    {
        printf("Resultant Matrix :\n");
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%d%s", C[i][j], (j < N - 1) ? ", " : ";\n");
            }
        }
    }
}



int main()
{
    /* Timing variables */
    struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */
    struct timezone tzdummy;
    clock_t etstart2, etstop2;  /* Elapsed times using times() */
    unsigned long long usecstart, usecstop;
    struct tms cputstart, cputstop;  /* CPU times for my processes */
    int num_thr;

    initialize_inputs();
    print_inputs();

    int i, j, k;
    printf("ENTER NUMBER OF THREADS \n");
    scanf("&d",num_thr);



        printf("COMPUTING IN PARALLEL WITH %d THREADS\n", num_thr);
        gettimeofday(&etstart, &tzdummy); /*START CLOCK*/


        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if(num_thr == 1)
                {
#pragma omp parallel for num_threads (1) shared(A, B) private(k)
                    for (k = 0; k < N; k++)
                    {
                        C[i][j] += A[i][k]*B[k][j];
                    }
                }
                if(num_thr== 2)
                {
#pragma omp parallel for num_threads (1) shared(A, B) private(k)
                    for (k = 0; k < N; k++)
                    {
                        C[i][j] += A[i][k]*B[k][j];
                    }
                }
                if(num_thr == 4)
                {
#pragma omp parallel for num_threads (1) shared(A, B) private(k)
                    for (k = 0; k < N; k++)
                    {
                        C[i][j] += A[i][k]*B[k][j];
                    }
                }
                if(num_thr == 8)
                {
#pragma omp parallel for num_threads (1) shared(A, B) private(k)
                    for (k = 0; k < N; k++)
                    {
                        C[i][j] += A[i][k]*B[k][j];
                    }
                }
            }
        }

        gettimeofday(&etstop, &tzdummy);  /*STOP CLOCK*/

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
        printf("-------------------------------------------------------\n");



    /*Print Output Matrix*/
    print_output();
    return 0;
}






