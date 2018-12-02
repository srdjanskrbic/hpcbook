/* Fajl:   omp_sf2.c
 * Opis:   izracunavanje odredjenog integrala koristeci Simpsonovu formulu uz upotrebu redukcije.
 *
 * Ulaz:   a, b, n
 * Izlaz:  aproksimacija vrednosti integrala od a do b funkcije f(x) koristeci n jednakih intervala.
 *
 * Kompajliranje: gcc -g -Wall -lm -fopenmp -o omp_sf2.c omp_sf2.c
 * Upotreba:   ./omp_sf2 <broj_niti>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void Usage(char* prog_name);
double f(double x);    /* Funkcija koju integralimo */
double Simp(double a, double b, int n);

int main(int argc, char* argv[]) {
	double  global_result = 0.0;  /* ova promenljiva ce sadrzati globalni rezultat */
	double  a, b;
	int     n;
	int     thread_count;

	if (argc != 2){
		Usage(argv[0]);
	}
	thread_count = strtol(argv[1], NULL, 10);
	printf("Unesite a, b, i n\n");
	scanf("%lf %lf %d", &a, &b, &n);
	if (n % thread_count != 0) {
		Usage(argv[0]);
	}

#  pragma omp parallel num_threads(thread_count) \
		reduction(+: global_result)
	{
		global_result += Simp(a, b, n);
	}

	printf("Aproksimacija integrala od %f do %f sa %d intervala je %f\n", a, b, n, global_result);
	return 0;
}

void Usage(char* prog_name) {

	fprintf(stderr, "upotreba: %s <broj niti>\n", prog_name);
	fprintf(stderr, "   broj intervala mora biti deljiv brojem niti\n");
	exit(0);
}

double f(double x) {
	double result;
	result = sin(x)*x;
	return result;
}

/*------------------------------------------------------------------
 * Funkcija:    Simp
 * Purpose:     Aproksimira odredjeni integral pomocu Simpsonove formule
 * Ulazni parametri:
 *    a: leva granica integrala
 *    b: desna granica integrala
 *    n: broj intervala
 * Izlazni argument:
 *    global_res_p:  pokazivac na globalni rezultat
 */
double Simp(double a, double b, int n) {
	double  h, x, my_result;
	double  local_a, local_b;
	int  i, local_n;
	int my_rank = omp_get_thread_num();
	int thread_count = omp_get_num_threads();

	h = (b-a)/n;
	local_n = n/thread_count;
	local_a = a + my_rank*local_n*h;
	local_b = local_a + local_n*h;
	my_result = (f(local_a) + f(local_b));
	for (i = 1; i <= local_n-1; i++) {
		x = local_a + i*h;
		if(i%2 != 0){
			my_result += 4*f(x);
		}else{
			my_result += 2*f(x);
		}
	}
	my_result = my_result*h/3;

	return my_result;
}
