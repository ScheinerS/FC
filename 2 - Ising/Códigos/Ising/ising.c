#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N   10000	//Cantidad de puntos
#define L      12	//dim de la red
#define BE		0	//campo magnético/kT
#define JE		0	//acoplamiento entre espines/kT

int main()
{
	int *red,i;
	double Be,Je;

	Be=BE;
	Je=JE;
	red=malloc(L*L*sizeof(int));

	energias(Be,Je)

	red=malloc(L*L*sizeof(int));

	for(i=0,i<N,i++)
	{
		flip(*red,*tabla,N,L);
		
	}
	return 0;
}