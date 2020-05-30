#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char *argv[]) {
  float delta, x_n, x_v, r, p=0.0;
  float *xs;
  int i, it=1000000;
  FILE *Corr;

  xs = malloc(it*sizeof(float));

  Corr = fopen("./Corr/Corr.txt", "a");

  srand(time(NULL));

  x_v = -1.0;    //x inicial.

  for(i=0;i<it;i++) {
    *(xs+i) = 0;
  }

  *(xs) = x_v;

  for(delta=2.6; delta<3; delta+=0.01){

    fprintf(Corr, "%0.4f\n", delta);

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

      fprintf(Corr, " %0.4f\n", *(xs+i));

    }

  }

  fclose(Corr);

  free(xs);

  return 0;
}
