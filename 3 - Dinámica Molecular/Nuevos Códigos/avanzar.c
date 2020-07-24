#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int size(char *filename,double *minmax)
{
  int    i,m;
  double r2min,r2max;
  FILE *fp;

  fp = fopen(filename,"r");

  i = fscanf(fp,"%d\n%lf\n%lf\n",&m,&r2min,&r2max);

  *(minmax+0) = r2min;
  *(minmax+1) = r2max;

  i++; // solo para que no salte warning de "unused variable"

  fclose(fp);

  return m;
}

int get(char *filename,double *tabla)
{
  int   i,j,m;
  double r,r2,r2min,r2max,v,f;
  FILE *fp;

  fp = fopen(filename,"r");

  j = fscanf(fp,"%d\n%lf\n%lf\n",&m,&r2min,&r2max);

  for(i=0;i<m;i++) 
    {
      j = fscanf(fp,"%lf %lf %lf %lf\n",&r,&r2,&v,&f);
      
      *(tabla+4*i+0) = r;
      *(tabla+4*i+1) = r2;
      *(tabla+4*i+2) = v;
      *(tabla+4*i+3) = f;
    }

  j++; // no hace nada; es para que no haya un warning!!!

  fclose(fp);

  return m;
}

double fuerza(int N, double L, double *r, double *Fr, double *Frv,double *tabla,int M,double r2min,double r2max) {

  int    h, i, j;
  double dr2,rp2, rpx, rpy, rpz, Fs, Vs, epot;

  for(j=0; j<3*N; j++) {                                                        
    *(Frv + j) = *(Fr + j);          //Fuerza anterior.  
    *(Fr + j) = 0.0;
  }

  epot = 0.0;

  dr2 = (r2max-r2min)/(double)M;

  for(i=0; i<N-1; i++) {
    for(j=i+1; j<N; j++) {

        rpx = *(r + 3*i+0) - *(r + 3*j+0);
        rpy = *(r + 3*i+1) - *(r + 3*j+1);
        rpz = *(r + 3*i+2) - *(r + 3*j+2);

        if(rpx > 0.5 * L) rpx -= L;
        if(rpy > 0.5 * L) rpy -= L;
        if(rpz > 0.5 * L) rpz -= L;

        if(rpx < -0.5 * L) rpx += L;
        if(rpy < -0.5 * L) rpy += L;
        if(rpz < -0.5 * L) rpz += L;

        rp2 = rpx*rpx + rpy*rpy + rpz*rpz;


        if(rp2 < r2max) {

	    h = (int)((rp2-r2min)/dr2);

            Fs = *(tabla+4*h+3);
            Vs = *(tabla+4*h+2);

            *(Fr + 3*i+0) += rpx * Fs;
            *(Fr + 3*i+1) += rpy * Fs;
            *(Fr + 3*i+2) += rpz * Fs;

            *(Fr + 3*j+0) -= rpx * Fs;
            *(Fr + 3*j+1) -= rpy * Fs;
            *(Fr + 3*j+2) -= rpz * Fs;

	    epot += Vs;
            }
      }
    }


  epot /= (double)N;

  return epot;
}

int posiciones(int N, double L, double *r, double *v, double *Fr, double h) {
  int i;

  for(i=0; i<N; i++) {
    *(r+3*i) = *(r+3*i) + *(v+3*i) * h + 0.5 * (*(Fr+3*i+0)) * h*h;

    if(*(r+3*i) > L)   *(r+3*i) -= L;
    if(*(r+3*i) < 0.0) *(r+3*i) += L;

    *(r+3*i+1) = *(r+3*i+1) + *(v+3*i+1) * h + 0.5 * (*(Fr+3*i+1)) * h*h;

    if(*(r+3*i+1) > L)   *(r+3*i+1) -= L;
    if(*(r+3*i+1) < 0.0) *(r+3*i+1) += L;

    *(r+3*i+2) = *(r+3*i+2) + *(v+3*i+2) * h + 0.5 * (*(Fr+3*i+2)) * h*h;

    if(*(r+3*i+2) > L)   *(r+3*i+2) -= L;
    if(*(r+3*i+2) < 0.0) *(r+3*i+2) += L;
  }


  return 0;
}

double velocity_verlet(int N, double *v, double *Fr, double *Frv, double h) {
  int i;
  double E_c=0.0, vx, vy, vz;

  for(i=0; i<N; i++) {
    *(v+3*i+0) = *(v+3*i+0) + (*(Frv+3*i+0) + *(Fr+3*i+0)) * h * 0.5;
    *(v+3*i+1) = *(v+3*i+1) + (*(Frv+3*i+1) + *(Fr+3*i+1)) * h * 0.5;
    *(v+3*i+2) = *(v+3*i+2) + (*(Frv+3*i+2) + *(Fr+3*i+2)) * h * 0.5;

    vx = *(v+3*i+0);
    vy = *(v+3*i+1);
    vz = *(v+3*i+2);

    E_c += 0.5 * (vx*vx + vy*vy + vz*vz);
  }

  E_c /= (double)N;

  return E_c;
}

int rescale(int N,double *v,double factor)
{
  int i;
 
  for (i=0;i<N;i++)
    {
      *(v+3*i+0) = factor * (*(v+3*i+0));
      *(v+3*i+1) = factor * (*(v+3*i+1));
      *(v+3*i+2) = factor * (*(v+3*i+2));
    }

  return 1;
}

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

double presion(int N, double L, double T, double *r, double *Fr) {
  int i,j;
  double rho=(double)N/(L*L*L), V=L*L*L, p, w=0, rpx, rpy, rpz, rp, Frx, Fry, Frz, Frs;

  for(i=0; i<N-1; i++) {
    for(j=i+1; j<N; j++) {
      rpx = *(r + 3*i) - *(r + 3*j);
      rpy = *(r + 3*i+1) - *(r + 3*j+1);
      rpz = *(r + 3*i+2) - *(r + 3*j+2);
      rp = sqrt(rpx*rpx + rpy*rpy + rpz*rpz);

      Frx = *(Fr + 3*i) - *(Fr + 3*j);
      Fry = *(Fr + 3*i+1) - *(Fr + 3*j+1);
      Frz = *(Fr + 3*i+2) - *(Fr + 3*j+2);
      Frs = sqrt(Frx*Frx + Fry*Fry + Frz*Frz);

      w += (rp*Frs)/N;
    }
  }

  p = rho*T + w/(3*V);

  return p;
}

double desp_cuadra_medio(int N, double *r, double *r0){
  int i;
  double rcx, rcy, rcz, rc2;
  for(i=0; i<N-1; i++)
  {
    rcx= *(r+3*i)-*(r0+3*i);
    rcy= *(r+3*i+1)-*(r0+3*i+1);
    rcz= *(r+3*i+2)-*(r0+3*i+2);

    rc2+=rcx*rcx+rcy*rcy*rcz*rcz;
  }

  rc2/=N;

  return rc2;
}

