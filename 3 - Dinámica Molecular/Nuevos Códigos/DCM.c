#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#include "visualizacion.h"
#include "inicializar.h"
#include "avanzar.h"

#define NPART      10*10*10
#define LADO       10.3574
#define PASOS      5000
#define SKIP       10
#define TEMP       0.8
#define TEMPMIN    0.1
#define H          0.0001
#define EQUILIBRIO 5000

int main()
{
  int    i,m,j,npart,pasos,equilibrio;
  char   filename[255];
  double *minmax,r2min,r2max,lado,temp,lambda;
  double *tabla,*r,*r0,*v,*f0,*f,ecin,epot,*rcm;
  FILE *fp;

  npart=  NPART;
  lado=   LADO;
  pasos=  PASOS;
  temp=   TEMP;
  equilibrio= EQUILIBRIO;

  fp = fopen("DCM(T=0.8,rho=0.9).dat","w");
  fprintf(fp,"Dcm\n");

  strcpy(filename,"tabla.dat");

  minmax = (double*) malloc(2*sizeof(double));

  m = size(filename,minmax);

  r2min = *(minmax+0);
  r2max = *(minmax+1);

  tabla = (double*) malloc(4*m*sizeof(double));

  get(filename,tabla);

  r   = (double*) malloc(3*npart*sizeof(double));
  r0  = (double*) malloc(3*npart*sizeof(double));
  v   = (double*) malloc(3*npart*sizeof(double));
  f0  = (double*) malloc(3*npart*sizeof(double));
  f   = (double*) malloc(3*npart*sizeof(double));
  rcm = (double*) malloc(pasos*sizeof(double));

  set_box(r,npart,lado);

  ecin  = set_v(v,npart,temp);
  epot  = fuerza(npart,lado,r,f,f0,tabla,m,r2min,r2max);
  lambda= Coef_V(npart,lado,r0);
  printf("%lf\n",lambda );
  //fprintf(fp,"%d %lf %lf %lf %lf\n",0,ecin,epot,ecin+epot);

  //strcpy(filename,"md(N=1000,T=0.8,rho=1.6).lammpstrj");
  //Coef_V(N,L,r);//Nos dá el parametro de orden de Verlet
  

    for (i=0;i<equilibrio;i++)
    {

        posiciones(npart,lado,r,v,f,H);

        epot = fuerza(npart,lado,r,f,f0,tabla,m,r2min,r2max);

        ecin = velocity_verlet(npart,v,f,f0,H);

    }


    for(j=0;j<20*pasos;j++)
    {


          for(i=0;i<npart;i++)//guardamos la posición inicial en r0
          { 
              *(r0+3*i)=*(r+3*i);
              *(r0+3*i+1)=*(r+3*i+1);
              *(r0+3*i+2)=*(r+3*i+2);
          }


          for (i=0;i<pasos;i++)
          {

              posiciones(npart,lado,r,v,f,H);

              epot      += fuerza(npart,lado,r,f,f0,tabla,m,r2min,r2max);

              ecin      += velocity_verlet(npart,v,f,f0,H);

            *(rcm+i)    +=desp_cuadra_medio(npart,r,r0);
          

          //if(i % SKIP == 0) save_lammpstrj(filename,r,v,npart,lado,i);
          }
        


        epot /=pasos;
        ecin /=pasos;      
        
        //fprintf(fp,"%lf %lf %lf\n",ecin,epot,ecin+epot);

      printf("Porcentaje:\t%d/%d\r",j,20*pasos);
      fflush(stdout);   

    }


    for(i=0;i<pasos;i++)
    {
      
      *(rcm+i) = *(rcm+i)/20;

      fprintf(fp,"%d %lf\n",i,*(rcm+i));
    }

    
      


  free(rcm);  
  free(minmax);
  free(tabla);
  free(r);
  free(r0);
  free(v);
  free(f);
  free(f0);
  fclose(fp);

  return 1;
}


#include "visualizacion.c"
#include "inicializar.c"
#include "avanzar.c"