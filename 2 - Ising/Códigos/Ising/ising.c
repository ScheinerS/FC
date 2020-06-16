#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "funcion_random.h"
#include "funcion_energia.h"
#include "funcion_flip.h"
#include "funcion_poblar.h"
#include "funcion_imprimir.h"

#define N 		10000   	//Cantidad de puntos
#define L 		8       //dim de la red
#define BE 		0       //campo magnético/kT
#define JE 		0.1          //acoplamiento entre espines/kT
#define JE_MAX 	0.6
#define P 		0.8	       //probabilaidad inicial de ocupación
#define PASO 	0.0001		//tamaño del paso

int main()
{
	int i;
	double Be,Je,Je_max,p,paso,*red,*tabla;

	red= malloc(L*L*sizeof(double));
	paso=PASO;
	p=P;
	Be=BE;
	Je=JE;
	Je_max=JE_MAX;
	
	poblar(p,L,red);
	
	for(Je=0.1;Je<Je_max;Je=+paso)
	{
		energias(Be,Je);
	
		for(i=0;i<N;i++)
		{
			flip(red,tabla,N,L);
			//if (i%100==0) printf("%lf\n",w);
			if (i%100==0) imprimir(red,L);
		}
	}

	return 0;
}

#include "funcion_random.c"
#include "funcion_energia.c"
#include "funcion_flip.c"
#include "funcion_poblar.c"
#include "funcion_imprimir.c"