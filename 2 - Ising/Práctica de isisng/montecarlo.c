#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "funcion_random.h"
#include "funcion_trial.h"
#include "funcion_correlacion.h"

#define N   500  //Cantidad de puntos
#define X0  0      //Punto inicial

//Metrópolis Montecarlo

int main()
{
	int i,n;
	double  x,p,w,x0,*m,*c,*l,M,C,L;
	FILE   *fp;
	
	n=N-1;                            //nos dice que vecinos miramos N-n=N-(N-1)=1. Sirve para la correlación.
	m  = malloc(N*sizeof(double)); 	//reservamos espacio para la distribución de x	
	c  = malloc(n*sizeof(double));  //reservamos espacio para los valores de correlación
	l  = malloc(N*sizeof(double));  //reservamops espacio para w(x)
	x0=X0;                          //punto de inicio

	fp = fopen("correlacion.csv","w");

	for(i=0;i<N;i++)
	{
		printf("Proceso1/2:\t%d / %d\r", i, N);
		fflush(stdout);

		p = myrand();
		x = trial(x0);
		w = exp(-0.5*(x*x-x0*x0));
		if (p<w) x0 = x;
		*(m+i)=x; 							//distribución de x
		*(l+i)=w;
	}

	correlation(c,m,n);
	
	for(i=0;i<N;i++)
	{
		M =*(m+i);
		C =*(c+i);
		L =*(l+i);
		fprintf(fp,"%i %lf %lf %lf\n",i,M,L,C);		//numero de pasos,valores de x,valores de w, valores de correlacion.
		printf("Proceso2/2:\t%d / %d\r", i, N);
		fflush(stdout);

	}

return 0;
}

#include "funcion_random.c"
#include "funcion_trial.c"
#include "funcion_correlacion.c"
