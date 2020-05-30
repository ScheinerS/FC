#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int main(int argc, char *argv[]) {
  float delta, x_n, x_v, r, p=0.0, x_i, x_id, x_i2;
  float *xs_a, *xs_r;
  int i, it=1000000;
  FILE *P_Acep;

  //sscanf(argv[1], "%f", & delta);

  xs_a = malloc(it*sizeof(float));
  xs_r = malloc(it*sizeof(float));

  P_Acep = fopen("./Prob_Acep/Prob_Acep.txt", "a");

  srand(time(NULL));

  x_v = -1;    //x inicial.

  for(i=0;i<it;i++) {
    *(xs_a+i) = 0;
  }

  for(i=0;i<it;i++) {
    *(xs_r+i) = 0;
  }

  *(xs_a) = x_v;
  *(xs_r) = x_v;

  //fprintf(P_Acep, "%0.4f\n", *(xs_a));

  //while(abs((p/it)-0.4)<0.5) {
    //p=0.0;
  for(delta=1; delta<4; delta+=0.001){
    x_i=0;
    x_id=0;
    x_i2=0;
    for(i=1;i<it;i++) {
      r = ((float)rand())/((float)RAND_MAX);

      x_n = x_v + ((float)rand())/((float)RAND_MAX) * (2.0*delta) - delta;    //x nuevo dentro del intervalo.

      if(exp(((x_v*x_v)-(x_n*x_n))/2.0) > r) {
        *(xs_a+i) = x_n;
        x_v = x_n;
        x_i+=x_n;
        x_i2+=x_n*x_n;
        p++;

      }

      else {
        *(xs_r+i) = x_v;
      }

      //fprintf(P_Acep, "%0.4f\n", *(xs_a+i));

    }

    p/=(float)it;

    fprintf(P_Acep, "%0.4f %0.4f\n", delta, p);
    //x_i/=it;
    //x_i2/=it;

    //for(i=0; i<it-1; i++){
    //  x_id+=(*(xs+i+1) * *(xs+i));
    //}
    //x_id/=(float(it)-delta);
    //delta+=0.00001;

  }

  //printf("%f\n", p/it);
/*
  for(i=0; i<10; i++) {
    printf("%f ", *(xs+i));
  }
  printf("\n");

  printf("%0.2f %0.2f\n", x_v, x_n);
*/

  fclose(P_Acep);

  free(xs_a);
  free(xs_r);

  return 0;
}
