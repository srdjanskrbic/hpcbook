#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

void upotreba(char* prog_name);
double f(double x);    /* Funkcija koju integralimo */
void Simp(double a, double b, int n, double* global_res_p);

int main(int argc, char* argv[]) {
  double  global_result = 0.0;  /* ova promenljiva ce sadrzati globalni rezultat */
  double  a, b;
  int     n;
  int     thread_count;

  if (argc != 2){
    upotreba(argv[0]);
  }
  thread_count = strtol(argv[1], NULL, 10);
  printf("Unesite a, b, i n\n");
  scanf("%lf %lf %d", &a, &b, &n);
  if (n % thread_count != 0) {
    upotreba(argv[0]);
  }

#  pragma omp parallel num_threads(thread_count)
  {
    Simp(a, b, n, &global_result);
  }
  printf("Aproksimacija integrala od %f do %f sa %d intervala je %f\n", a, b, n, global_result);
  return 0;
}

void upotreba(char* prog_name) {

  fprintf(stderr, "upotreba: %s <broj niti>\n", prog_name);
  fprintf(stderr, "   broj intervala mora biti deljiv brojem niti\n");
  exit(0);
}

double f(double x) {
  double result = sin(x)/x;
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
void Simp(double a, double b, int n, double* global_res_p) {
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
  
#  pragma omp critical
  {
    *global_res_p += my_result;
  }
}
