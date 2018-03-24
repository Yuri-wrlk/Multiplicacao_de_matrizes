#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <phthread.p>

#define MAX_THREADS 4
#define max 2048 //tamanho máximo do arquivo 

use namespace std;

double matrizA[max][max],matrizB[max][max],matrizC[max][max];
int aux = 0;
int nprocs;

void readData(){
    int i,j;

    FILE *aixi, *bixi;
    aixi = fopen("a", "r"); // Leitura dos dados da matriz A
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                fscan(aixi, "%d", &a[i][j]);
        fclose(aixi);
            }
        }
    bixi = fopen("b", "r"); //Leitura dos dados da matriz B
        for(i = 0; i < n; i++){
            for(j = 0; j < n; j++){
                fscan(bixi, "%d", &b[i][j]);
        fclose(bixi);        
            }
        }
}

void printData(){
    int i,j;
    FILE *cixi;

    cixi = fopen("thread", "w");
        for(i = 0; i< n; i++){
            for(j = 0; j < n; j++)
            fprint(cixi, "%d\n", c[i][j]);
        fclose(cixi);    
        }
}

            
/*
    Multiplicação dos valores lidos
*/

double multiMatriz(*num_threads){
    int i,j,k;
    int iprocs, jprocs;
    int id, id_i, id_j;
    int ilb,iub,jlb,jub; //temporario

/* declarando o número de processadores em i*/
iprocs = sqrt((double) nprocs);
/* declarando o número de processadores em j*/
jprocs = nprocs/iprocs;

/* armazenando id do processo atual*/
id = *num_threads;
/* salvando a ID dos processos de i e j*/
id_i = id % iprocs;
id_j = id / iprocs;

// código base >> temporário

/* find lower and upper bounds of i loop */
ilb = i_id * n / iprocs;
iub = (i_id + 1) * (n / iprocs);

/* find lower and upper bounds of j loop */
jlb = j_id * n / jprocs;
jub = (j_id + 1) * (n / jprocs);

/* Matriz resultante da multiplicacao */

for (i = ilb; i < iub; i++)
    for (j = jlb; j < jub; j++) {
    c[i][j] = 0.0;
        for (k = 0; k < n; k++)
        c[i][j] = c[i][j] + a[i][k] * b [k][j];
    }
}   

    phtread_exit();
}

//main teste

int main(int argc, char **argv){
    pthread_t t[MAX_THREADS];
    pthread_attr_t attr;
    
    int param[MAX_THREADS];
    int i;

void readData(),multiMatriz(),printData();
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
readData();

/* create threads */
for (i=0; i < nprocs; i++){
param[i]=i;
pthread_create(&t[i], &attr, (void *)multiMatriz, &param[i]);
}

/* wait termination of created threads */
for (i=0; i < nprocs; i++)
pthread_join(t[i], NULL);

/* outputs matrix c */
printData();
return ();
}