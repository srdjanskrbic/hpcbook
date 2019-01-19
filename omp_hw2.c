/* ============================================================================
   Fajl:             omp_hw2.c

   Opis:             Drugi primer paralelnog hello world programa koji koristi OpenMP

   Kompajliranje:    gcc -g -Wall -fopenmp -o omp_hw2 omp_hw2.c
   Izvrsavanje:      ./omp_hw2
   ============================================================================
 */

#include <omp.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
int thread_count = strtol(argv[1], NULL, 10);
#pragma omp parallel num_threads(thread_count)
  {
    int tid = omp_get_thread_num();
    printf("Zdravo svete od niti broj %d\n", tid);
    if (tid == 0){
        int numThreads = omp_get_num_threads();
        printf("Ukupan broj niti je %d\n", numThreads);
    }
  }
  return 0;
}
