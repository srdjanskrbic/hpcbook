/* ============================================================================
   Fajl:             omp_hw3.c

   Opis:             Treći primer paralelnog hello world programa koji koristi OpenMP

   Kompajliranje:    gcc -g -Wall -fopenmp -o omp_hw3 omp_hw3.c
   Izvrsavanje:      ./omp_hw3
   ============================================================================
 */
#ifdef _OPENMP
#include <omp.h>
# endif
#include <stdio.h>

void upotreba(char *prog_name);

int main (int argc, char *argv[]) {
  if (argc != 2){
      upotreba(argv[0]);
  }
  int thread_count = strtol(argv[1], NULL, 10); 
  if (thread_count <= 0) {
      upotreba(argv[0]);
  }
#pragma omp parallel num_threads(thread_count)
  {
    # ifdef _OPENMP
      int my_rank = omp_get_thread_num();
      int thread_count = omp_get_num_threads();
    # else
      int my_rank = 0;
      int thread_count = 1;
    # endif
    printf("Zdravo svete od niti broj %d\n", my_rank);
    if (my_rank == 0){
	printf("Ukupan broj niti je %d\n", thread_count);
    }
  }
  return 0;
}

void upotreba(char *prog_name) {
   fprintf(stderr, "upotreba: %s <thread_count>\n", prog_name);
   fprintf(stderr, "   thread_count treba da bude pozitivan ceo broj\n");
   exit(0);
}
