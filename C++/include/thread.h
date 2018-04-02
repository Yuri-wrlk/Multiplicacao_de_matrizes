#ifndef _TIME_H
#define _TIME_H

#include <stddef.h>

/* ////////////////////////////////////////////////////////
// Seção 1 -- Medida de tempo
//////////////////////////////////////////////////////// */

typedef long time_t;

/* Esta função devolve a leitura do relógio, em segundos.
// A função também atribui a leitura do relógio (em
// segundos) à variável cujo endereço é x (a menos que x
// seja NULL). Uso típico: instante = time (NULL);
*/
time_t time (time_t *x);


#define CLOCKS_PER_SEC 1000000

typedef long clock_t;

/* A função clock devolve o tempo de CPU decorrido desde o
// início da execução do seu programa. O tempo é medido em
// ciclos do relógio interno. Cada  CLOCKS_PER_SEC ciclos
// correspondem aproximadamente a 1 segundo. Uso típico:
//
//     double start, stop, elapsed;
//     start = (double) clock () / CLOCKS_PER_SEC;
//     . . . [cálculos] . . .
//     stop = (double) clock () / CLOCKS_PER_SEC;
//     elapsed = stop - start;
//
// Cuidado: Depois de aproximadamente 35 minutos, ocorre
// overflow.
*/
clock_t clock (void);

#endif //_TIME_H

