/* Fajl:             omp_hw1.c
 *
 * Opis:             Prvi primer paralelnog hello world programa koji koristi OpenMP
 *
 * Kompajliranje:    gcc -g -Wall -fopenmp -o omp_hw1 omp_hw1.c
 * Izvrsavanje:      ./omp_hw1 <number of threads>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void Hello(void);

int main(int argc, char* argv[]) {
	int thread_count = strtol(argv[1], NULL, 10);

#  pragma omp parallel num_threads(thread_count)
	{
		Hello();
	}

	return 0;
}

/*-------------------------------------------------------------------
 * Funkcija:    Hello
 * Opis:        Funkcija koja ispisuje poruku
 */
void Hello(void) {
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();
	printf("Hello from thread %d of %d\n", my_rank, thread_count);
}
