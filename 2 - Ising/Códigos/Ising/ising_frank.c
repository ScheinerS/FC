#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define N	500
#define L	32
#define J	0.1
#define JMAX	0.6
#define PASO	0.1
#define UMBRAL_CORRELACION	0.1
#define MUESTRAS	50

int    poblar(int *red,int n);
int    build_table(double *tabla, double *energia, double j);
int    observables(int *red,double *m,double *e,double b,int n);
int    flip(int *red, double *tabla, double *energia, double *m,double *e);
double myrand();
int correlation(double *c,double *m,int n);

int main()
{
  int    h,k,*red,n;
  char   filename[500];
  double *tabla,*energia,*e,*m,j,i,jmax,paso, *c, corr;
  FILE   *fp;

  strcpy(filename,"ising.dat");

  fp = fopen(filename,"w"); // abro el archivo donde voy a escribir los datos

  red     = (int*) malloc(L*L * sizeof(int));
  tabla   = (double*) malloc(5*sizeof(double));
  energia = (double*) malloc(5*sizeof(double));
  e       = (double*) malloc(N*sizeof(double));
  m       = (double*) malloc(N*sizeof(double));
  n=100;
  c       = malloc(n*sizeof(double));
 
  j   = J;
  jmax=JMAX;
  paso=PASO;
  
  corr=1;

  build_table(tabla,energia,j);

  poblar(red,L);

  observables(red,m,e,j,L);

  fprintf(fp,"%d %lf %lf %lf\n",0,*(m+0),*(e+0),j);

  // Barremos los valores de J:
  for(i=j;i<jmax;i+=paso)
  {
  		j=i;
  		// Construimos la tabla para esta temperatura:
  		build_table(tabla,energia,j);
		// Calculamos la correlación:
		//corr=correlation(c,m,n);
		// Si la correlación es mayor que el umbral, hacemos otras cien rondas de "flipeo":
		while(UMBRAL_CORRELACION<corr)
		{
			for(h=1;h<100;h++)
			{
      			flip(red,tabla,energia,m+h,e+h);
	      	}
	        // Actualizamos la correlación:
	      	correlation(c,m,n);
	      	corr=*(c+n-1);
	      	printf("%lf\n",*(c+n-1));
		}
		// Una vez que la correlación es suficientemente baja, tomamos muestras para guardar en el archivo:
		for(int muestra; muestra<MUESTRAS; muestra++)
		{
			fprintf(fp,"%d %lf %lf %lf\n",h,*(m+h),*(e+h),j);
		}
   }

  // configuracion final

  printf("\n");

  for(h=0;h<L;h++)
    {
      for(k=0;k<L;k++)
        {
          if (*(red+L*h+k)== 1) printf("+ ");
          if (*(red+L*h+k)==-1) printf("- ");
        }
      printf("\n");
    }

  printf("\n");

  free(m);
  free(e);

  fclose(fp);

  return 0;
}

////////ACA TERMINA EL MAIN

int poblar(int *red,int n) //prob =1 da una matriz de todos unos
{
  int    i;
  double r;
 
  for(i=0;i<n*n;i++)
    {
      r = myrand();

      if (r<0.5) *(red+i)=-1; 
      else       *(red+i)= 1;
    }

  return 1;
}

int build_table(double *tabla, double *energia, double j)
{
  *(tabla+0) = exp(-8.0*j);
  *(tabla+1) = exp(-4.0*j);
  *(tabla+2) = exp(-0.0*j);
  *(tabla+3) = exp(+4.0*j);
  *(tabla+4) = exp(+8.0*j);

  *(energia+0) =  8.0*j;
  *(energia+1) =  4.0*j;
  *(energia+2) =  0.0*j;
  *(energia+3) = -4.0*j;
  *(energia+4) = -8.0*j;

  return 1;
}

int flip(int *red, double *tabla, double *energia, double *m,double *e)
{

  int    h,i,j,s,s1,s2,s3,s4; 
  double p,w,dm,de;

  i = rand()%L;        //elijo un spin al azar
  j = rand()%L;        //elijo un spin al azar

  s = *(red+L*i+j);    // s es ese spin

  s1= *(red+L*(((i-1)+L)%L)+j);
  s2= *(red+L*(((i+1)+L)%L)+j);
  s3= *(red+L*i+(((j-1)+L)%L));
  s4= *(red+L*i+(((j+1)+L)%L));

  h = 2 - 2*(s1+s2+s3+s4)/4;

  if (s==1) 
    {
      w  = *(tabla+h);
      dm = -2.0;
      de = *(energia+h);
    }
  else
    {
      w = *(tabla-h+4);
      dm = 2.0;
      de = *(energia-h+4);
    }

  p = myrand();

  if (p<w) *(red+L*i+j) = -s;
  else
    {
     dm = 0.0;
     de = 0.0;
    }

  *m = (*(m-1)) + dm/(double)(L*L);
  *e = (*(e-1)) + de/(double)(L*L);

  return 1;
}


double myrand()
{
  double p;
  p=(double)rand()/(double)RAND_MAX;

  return p;
}

int observables(int *red,double *m,double *e,double b,int n)
{
  int    i,j,s,s1,s2;

  *m = 0.0;
  *e = 0.0;

  for (i=0;i<n;i++)
    for (j=0;j<n;j++)
      {
         s  = *(red+n*i+j);
         s1 = *(red+L*(((i-1)+L)%L)+j);
         s2 = *(red+L*i+(((j-1)+L)%L));

         *m += (double)(*(red+n*i+j));
         *e += -b*(s*s1+s*s2);
      }
   
  *m = (*m)/(double)(n*n);
  *e = (*e)/(double)(n*n);
 
  return 0;
}

int correlation(double *c,double *m,int n)
{
	int i,k;
	double xi,xk,s0,s1,s2;
	
	for (k=0;k<n;k++)
	{
		s0 = 0.0;
		s1 = 0.0;
		s2 = 0.0;
		
		for (i=0;i<N-n;i++)
		{
			xi = *(m+i);
			xk = *(m+i+k);
			s1 += xi/(double)(N-n);
			s0 += xi*xk/(double)(N-n);
			s2 += xi*xi/(double)(N-n);
		}
		*(c+k) = (s0-s1*s1)/(s2-s1*s1);
	}
	return 1;
}


