#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "funcion_random.h"
#include "funcion_energia.h"
#include "funcion_flip.h"
#include "funcion_poblar.h"
#include "funcion_imprimir.h"
//#include "funcion_conteo.h"

#define N0 	 	1100	//Cantidad de puntos
#define DIM 	32       //dim de la red
#define BE 		0       //campo magnético/kT
#define JE 		0.1          //acoplamiento entre espines/kT
#define JE_MAX 	0.6
#define P 		0.5	       //probabilaidad inicial de ocupación
#define PASO 	0.001		//tamaño del paso

int main()
{
	int L,N,*red;
	double Be,Je,Je_max,p,paso,*tabla;


    srand(time(NULL));
	N=N0;
	L=DIM;
	paso=PASO;
	p=P;
	Be=BE;
	Je=JE;
	Je_max=JE_MAX;
	
	red= malloc(L*L*sizeof(int));
	tabla = malloc(13*sizeof(double));
	
	poblar(p,L,red);					//creamos la red de espines con 1 y -1
	
	imprimir(red,L);

	energias(Be,Je,tabla);				//calculamos las energás para las condiciones iniciales y las posibles configuraciones
	
	flip(red,tabla,N,L);				//termalizamos la red
	
	imprimir(red,L);
	
	for(Je=0.1;Je<Je_max;Je+=paso)
	{
		energias(Be,Je,tabla);


			/*for(i=0;i<5;i++)
			{
				printf("%lf\n",*(tabla+i));
			}

			for(i=8;i<13;i++)
			{
				printf("%lf\n",*(tabla+i));
			}*/

		//imprimir(red,L);
	}

	return 0;
}

#include "funcion_random.c"
#include "funcion_energia.c"
#include "funcion_flip.c"
#include "funcion_poblar.c"
#include "funcion_imprimir.c"
//#include "funcion_conteo.c"