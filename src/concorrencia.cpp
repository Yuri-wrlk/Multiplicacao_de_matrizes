#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX_THRDS 4 //numero de processadores
#define max 1000 //tam. max. arquivo

float a[max][max], b[max][max], c[max][max];
int n,nprocs;

void readdata(){
int i,j;

FILE *fpa,*fpb;
/* read matrix a */
fpa = fopen("a","r");
    for (i=0; i < n; i++)
        for (j=0; j < n; j++)
        fscanf(fpa,"%f", &a[i][j]);
    fclose(fpa);

/* read matrix b */
fpb = fopen("b","r");
    for (i=0; i < n; i++)
        for (j=0; j < n; j++)
        fscanf(fpb,"%f", &b[i][j]);
    fclose(fpb);
}

void printdata(){
int i,j;
FILE *fpc;

/* write results */
fpc = fopen("thread_c","w");
    for (i=0; i < n; i++)
        for (j = 0; j < n; j++)
        fprintf(fpc,"%f\n",c[i][j]);
    fclose(fpc);
}

void matmul(int *num_thread){ //funcao que multiplica..threads a chamam.
int i, j, k;
int iprocs, jprocs;
int my_id, i_id,j_id,ilb,iub,jlb,jub;

/* number of processors in i direction */
iprocs = (int) sqrt((double) nprocs);
/* number of processors in j direction */
jprocs = nprocs / iprocs;

my_id = *num_thread; //m_get_myid();
/* get processor ID in i and j dimensions */
i_id = my_id % iprocs;
j_id = my_id / iprocs;
/* find lower and upper bounds of i loop */
ilb = i_id * n / iprocs;
iub = (i_id + 1) * (n / iprocs);

/* find lower and upper bounds of j loop */
jlb = j_id * n / jprocs;
jub = (j_id + 1) * (n / jprocs);

for (i = ilb; i < iub; i++)
    for (j = jlb; j < jub; j++) {
    c[i][j] = 0.0;
        for (k = 0; k < n; k++)
        c[i][j] = c[i][j] + a[i][k] * b [k][j];
    }
}    
pthread_exit (NULL);
}



int main(int argc, char **argv)
{
pthread_t t[MAX_THRDS];
pthread_attr_t attr;
int param[MAX_THRDS];
int i;
void readdata(),matmul(),printdata();
//inicializacao das threads
pthread_attr_init(&attr);
pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);

/* get n and nprocs parameters */
if (argc != 3){
printf("usage: pth_matrix <size of matrices> <number of processors>\n");
exit(1);
}
n = atoi(argv[1]);
nprocs = atoi(argv[2]);

/* reads matrix a and b */
readdata();

/* create threads */
for (i=0; i < nprocs; i++){
param[i]=i;
pthread_create(&t[i], &attr, (void *)matmul, &param[i]);
}

/* wait termination of created threads */
for (i=0; i < nprocs; i++)
pthread_join(t[i], NULL);

/* outputs matrix c */
printdata();
return (0);
}