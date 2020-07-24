#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


double set_box(double *r,int N, double L) {
  int n = cbrt(N), i=0, x, y, z;
  double dL=L/n;

  for(x=0; x<n; x++) {
    for(y=0; y<n; y++) {
      for(z=0; z<n; z++) {

          *(r+3*i) = dL*(x+0.5);
          *(r+3*i+1) = dL*(y+0.5);
          *(r+3*i+2) = dL*(z+0.5);

          i++;

      }
    }
  }

  return 0;
}

double Gaussiana(double nu, double sigma) {
  int n = 10, i;
  double z = 0;

  for(i=0; i<n; i++) {
    z += (double)rand()/(double)RAND_MAX;
  }

  z = sqrt(12*n)*(z/n - 0.5);

  return z*sigma+nu;
}

double set_v(double *v, int N, double T) {
  int i,j;
  double sigma = sqrt(T), E_c=0.0;
  double *VCM;

  VCM = malloc(3*sizeof(double));

  *(VCM) = 0;
  *(VCM + 1) = 0;
  *(VCM + 2) = 0;

  for(i=0; i<3*N; i++) {
    *(v+i) = Gaussiana(0.0,sigma);
  }

  for(i=0; i<N; i++) {
    for(j=0; j<3; j++) {
      *(VCM + j) += *(v + 3*i+j)/N;
    }
  }

  for(i=0; i<N; i++) {
    for(j=0; j<3; j++) {
      *(v + 3*i+j) -= *(VCM + j);
    }
  }

  for(i=0; i<N; i++) {
    E_c += 0.5 * (*(v+3*i) * *(v+3*i) + *(v+3*i+1) * *(v+3*i+1) + *(v+3*i+2) * *(v+3*i+2));
  }

  E_c /= N;

  return E_c;
}
