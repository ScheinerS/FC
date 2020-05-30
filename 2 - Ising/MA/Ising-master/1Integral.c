#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char *argv[]) {
  float delta=2.8, x_n, x_v, r, p=0.0;//, x_i, x_id, x_i2;
  float *xs;
  int i, it=1000000;
  FILE *C_int;

  //sscanf(argv[1], "%f", & delta);

  xs = malloc(it*sizeof(float));

  C_int = fopen("./Calculo_Integral/Calculo_Integral.txt", "a");

  srand(time(NULL));

  x_v = -0.5;    //x inicial.

  for(i=0;i<it;i++) {
    *(xs+i) = 0.0;
  }

  *(xs) = x_v;

  fprintf(C_int, "%0.4f\n", *(xs));

  for(i=1;i<it;i++) {
    r = ((float)rand())/((float)RAND_MAX);

    x_n = x_v + ((float)rand())/((float)RAND_MAX) * (2.0*delta) - delta;    //x nuevo dentro del intervalo.

    if(exp(((x_v*x_v)-(x_n*x_n))/2.0) > r) {
      *(xs+i) = x_n;
      x_v = x_n;
      p++;
    }

    else {
      *(xs+i) = x_v;
    }

    fprintf(C_int, "%0.4f\n", *(xs+i));

  }

  fclose(C_int);

  free(xs);

  return 0;
}
