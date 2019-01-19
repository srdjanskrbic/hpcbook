/* ============================================================================
   Fajl:             omp_hw1.c

   Opis:             Prvi primer paralelnog hello world programa koji koristi OpenMP

   Kompajliranje:    gcc -g -Wall -fopenmp -o omp_hw1 omp_hw1.c
   Izvrsavanje:      ./omp_hw1
   ============================================================================
 */

#include <omp.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
  int numThreads, tid;
#pragma omp parallel private(numThreads, tid)
  {
    tid = omp_get_thread_num();
    printf("Zdravo svete od niti broj %d\n", tid);
    if (tid == 0){
        numThreads = omp_get_num_threads();
        printf("Ukupan broj niti je %d\n", numThreads);
    }
  }
  return 0;
}
