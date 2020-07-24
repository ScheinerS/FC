#ifndef AVANZAR_H
#define AVANZAR_H

#include "math.h"

int    size(char *filename,double *minmax);
int    get(char *filename,double *tabla);
double fuerza(int N, double L, double *r, double *Fr, double *Frv,double *tabla,int M,double r2min,double r2max);
int    posiciones(int N, double L, double *r, double *v, double *Fr, double h);
double velocity_verlet(int N, double *v, double *Fr, double *Frv, double h);
int    rescale(int N,double *v,double factor);
double Coef_V(int N, int L, double *r);
double presion(int N, double L, double T, double *r, double *Fr);
double desp_cuadra_medio(int N, double *r, double *r0);

#endif
