#include <stdio.h>
#include <stdlib.h>
#include <math.h>

use namespace std;

double matrizA[lA][cA],matrizB[lB][cB],matrizC[lA][cB];
double aux = 0;

double leitura(){
    if(cA == lB){
        /*
        Leitura do arquivo - primeira linha
        */
        for(i = 0; i < lA; i++){
        /*
        Leitura dos valores da segunda linha em diante dos arquivos Aixi e Bixi >> linhas e colunas
        */
        // Leitura e escrita: matriz[i][j];
            for(j = 0; j < cA; j++){
            }
        }

        for(i = 0; i < lB; i++){
            for(j = 0; j < cB; j++){
                // Leitura e escrita matriz[i][j];
            }
        }
    }
}    
/*
    Multiplicação dos valores lidos
*/

double multiplica(){
    for(i = 0; i<lA; i++){
        for(j=0; j<cB; j++){
            matrizC[i][j] = 0;
                for(k = 0; k<lB; k++){
                    aux += matrizA[i][k] * matrizB[k][j];
                }
            matrizC[i][j] = aux;
            aux = 0;
        }
    }
    // Salvar saída no arquivo Cixi
    for(i = 0; i < lA; i++){
        for(j = 0; j < cB; j++){
            //escrever matrizC[i][j]
        }
    }
}