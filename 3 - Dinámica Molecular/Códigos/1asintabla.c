#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double set_box(double *r, int N, double L);
double set_v(double *v, int N, double T);
double Gaussiana(double nu, double sigma);
double fuerza(int N, int L, double *r, double *Fr, double *Frv);
int posiciones(int N, int L, double *r, double *v, double *Fr);
double velocity_verlet(int N, double *v, double *Fr, double *Frv);
double Coef_V(int N, int L,double *r);

int main(int argc, char const *argv[]) {
  int N=512, i, it=4000;
  
  printf("Cantidad de partículas:\t\tN = %d\n",N);
  printf("Cantidad de iteraciones:\tit = %d\n",it);
  
  double L=11.0, T, Vs=0.0, E_c=0.0, lambda_t;
  double *r, *v, *Fr, *Frv;
  FILE *energias;

  srand(time(NULL));

  r = malloc(3*N*sizeof(double));
  v = malloc(3*N*sizeof(double));
  Fr = malloc(3*N*sizeof(double));
  Frv = malloc(3*N*sizeof(double));

  //video = fopen("./Datos/video.lammpstrj", "a");
  


  for(i=0; i<3*N; i++) {
    *(Fr + i) = 0.0;
  }

  for(T=0.4; T<4; T+=0.5) {
  	
  	char filename[255];
  	sprintf(filename,"./Datos/Energias/energias(N=%d,T=%g)",N,T);
	energias = fopen(filename, "w");
  
    //fprintf(energias, "%f\n", T);

    set_box(r,N,L);   //Coloca las particulas en su posición inicial.
    lambda_t = Coef_V(N, L, r);
    Vs = fuerza(N, L, r, Fr, Frv);  //Calculo de Vs.
    E_c = set_v(v,N,T);     //Crea las velocidades iniciales.

    //fprintf(video, "ITEM: TIMESTEP\n");
    //fprintf(video, "0\n");
    //fprintf(video, "ITEM: NUMBER OF ATOMS\n");
    //fprintf(video, "%i\n", N);
    //fprintf(video, "ITEM: BOX BOUNDS pp pp pp\n");
    //fprintf(video, "0 10.000000\n");
    //fprintf(video, "0 10.000000\n");
    //fprintf(video, "0 10.000000\n");
    //fprintf(video, "ITEM: ATOMS id x y z vx vy vz \n");

  
	// Encabezados de las columnas:
	fprintf(energias, "paso Vs E_c Vs+E_c lambda_t\n");
  
	// Paso inicial:
    fprintf(energias, "%i %f %f %f %f\n", 0, Vs, E_c, Vs+E_c, lambda_t);

    //for(i=0; i<N; i++) {
    //  fprintf(video, "%i %f %f %f %f %f %f\n", i, *(r+3*i), *(r+3*i+1), *(r+3*i+2), *(v+3*i), *(v+3*i+1), *(v+3*i+2));
    //}

    for(i=0; i<it; i++) {
      //fprintf(video, "ITEM: TIMESTEP\n");
      //fprintf(video, "%i\n", i+1);
      //fprintf(video, "ITEM: NUMBER OF ATOMS\n");
      //fprintf(video, "%i\n", N);
      //fprintf(video, "ITEM: BOX BOUNDS pp pp pp\n");
      //fprintf(video, "0 10.000000\n");
      //fprintf(video, "0 10.000000\n");
      //fprintf(video, "0 10.000000\n");
      //fprintf(video, "ITEM: ATOMS id x y z vx vy vz\n");


      posiciones(N, L, r, v, Fr);            //Calcula las nuevas posiciones  <----
      lambda_t = Coef_V(N, L, r);
      E_c = 0.0;                                                                //|
      Vs = fuerza(N, L, r, Fr, Frv) ;         //Calculo de fuerzas.                |
      E_c = velocity_verlet(N, v, Fr, Frv);  //Calcula las nuevas velocidades   ---


      //for(j=0; j<N; j++) {
      //  fprintf(video, "%i %f %f %f %f %f %f\n", j, *(r+3*j), *(r+3*j+1), *(r+3*j+2), *(v+3*j), *(v+3*j+1), *(v+3*j+2));
      //}

      fprintf(energias, "%i %f %f %f %f\n", i+1, Vs, E_c, Vs+E_c, lambda_t );

    }
  }

  //fclose(video);
  fclose(energias);

  free(r);
  free(v);
  free(Fr);
  free(Frv);

  return 0;
}


//Ecuaciones Secundarias:
//##########################################################//
double set_box(double *r, int N, double L) {
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
//##########################################################//

//##########################################################//
double Gaussiana(double nu, double sigma) {
  int n = 10, i;
  double z = 0;

  for(i=0; i<n; i++) {
    z += (double)rand()/(double)RAND_MAX;
  }

  z = sqrt(12*n)*(z/n - 0.5);

  return z*sigma+nu;
}
//##########################################################//

//##########################################################//
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
//##########################################################//

//##########################################################//
double fuerza(int N, int L, double *r, double *Fr, double *Frv) {
  int i, j;
  double rp, rp3, rp6, rpx, rpy, rpz, Fs=0.0, Vs=0.0, corr_V=4.0 * (1.0/59605.0 - 1.0/244.0);

  for(j=0; j<3*N; j++) {                                                        //|
    *(Frv + j) = *(Fr + j);                  //Fuerza anterior.                   |
  }

  for(j=0; j<3*N; j++) {
    *(Fr + j) = 0.0;
  }

  for(i=0; i<N-1; i++) {
    for(j=i+1; j<N; j++) {

        rpx = *(r + 3*i) - *(r + 3*j);
        rpy = *(r + 3*i+1) - *(r + 3*j+1);
        rpz = *(r + 3*i+2) - *(r + 3*j+2);

        if(rpx > 0.5 * L) rpx -= L;
        if(rpy > 0.5 * L) rpy -= L;
        if(rpz > 0.5 * L) rpz -= L;

        if(rpx < -0.5 * L) rpx += L;
        if(rpy < -0.5 * L) rpy += L;
        if(rpz < -0.5 * L) rpz += L;

        rp = sqrt(rpx*rpx + rpy*rpy + rpz*rpz);

        rp3 = rp * rp * rp;
        rp6 = rp3 * rp3;

        if(rp < 2.5) {
            Fs = 24.0 * (2.0/ (rp * rp6*rp6) - 1.0/ (rp * rp6));
            Vs += 4.0 * (1.0/(rp6*rp6) - 1.0/rp6);
            Vs -= corr_V;

            *(Fr + 3*i) += Fs * (rpx/rp);
            *(Fr + 3*i+1) += Fs * (rpy/rp);
            *(Fr + 3*i+2) += Fs * (rpz/rp);

            *(Fr + 3*j) -= Fs * (rpx/rp);
            *(Fr + 3*j+1) -= Fs * (rpy/rp);
            *(Fr + 3*j+2) -= Fs * (rpz/rp);
            }
      }
    }


  Vs /= (double)N;

  return Vs;
}
//##########################################################//

//##########################################################//
int posiciones(int N, int L, double *r, double *v, double *Fr) {
  int i;
  double h=0.001;

  for(i=0; i<N; i++) {
    *(r+3*i) = *(r+3*i) + *(v+3*i) * h + 0.5 * (*(Fr+3*i)) * h*h;
    if(*(r+3*i) > L) *(r+3*i) -= L;
    if(*(r+3*i) < 0.0) *(r+3*i) += L;
    *(r+3*i+1) = *(r+3*i+1) + *(v+3*i+1) * h + 0.5 * (*(Fr+3*i+1)) * h*h;
    if(*(r+3*i+1) > L) *(r+3*i+1) -= L;
    if(*(r+3*i+1) < 0.0) *(r+3*i+1) += L;
    *(r+3*i+2) = *(r+3*i+2) + *(v+3*i+2) * h + 0.5 * (*(Fr+3*i+2)) * h*h;
    if(*(r+3*i+2) > L) *(r+3*i+2) -=L;
    if(*(r+3*i+2) < 0.0) *(r+3*i+2) += L;
  }


  return 0;
}
//##########################################################//

//##########################################################//
double velocity_verlet(int N, double *v, double *Fr, double *Frv) {
  int i;
  double h=0.001, E_c=0.0;

  for(i=0; i<N; i++) {
    *(v+3*i) = *(v+3*i) + (*(Frv+3*i) + *(Fr+3*i)) * h * 0.5;
    *(v+3*i+1) = *(v+3*i+1) + (*(Frv+3*i+1) + *(Fr+3*i+1)) * h * 0.5;
    *(v+3*i+2) = *(v+3*i+2) + (*(Frv+3*i+2) + *(Fr+3*i+2)) * h * 0.5;

    E_c += 0.5 * ((*(v+3*i)) * (*(v+3*i)) + (*(v+3*i+1)) * (*(v+3*i+1)) + (*(v+3*i+2)) * (*(v+3*i+2)));
  }

  E_c /= (double)N;

  return E_c;
}
//##########################################################//

//##########################################################//
double Coef_V(int N, int L, double *r) {
  int i;
  double lambda_x=0.0, lambda_y=0.0, lambda_z=0.0, lambda_t=0.0, a=L/cbrt(N);

  for(i=0; i<N-1; i++) {
      lambda_x += cos((2*3.1415/a) * ((*(r+3*i)) - (a * 0.5)));
      lambda_y += cos((2*3.1415/a) * ((*(r+3*i+1)) - (a * 0.5)));
      lambda_z += cos((2*3.1415/a) * ((*(r+3*i+2)) - (a * 0.5)));
      }

    lambda_x /= (double)N;
    lambda_y /= (double)N;
    lambda_z /= (double)N;

    lambda_t = 0.33 * (lambda_x + lambda_y + lambda_z);

  return lambda_t;
}
//##########################################################//
