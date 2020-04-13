 /* Programa para generar una red de LxL de unos y ceros y detectar los clusters.*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define SEED 26//085
#define PROB 0.5
#define L 10

double myrandom(double prob);
int min(int s1,int s2);
int max(int s1,int s2);
int etiqueta_verdadera(int *clase, int s);
int imprimir(int *red,int N);

int main()
{
	int    i,s,s1,s2,frag,j,N;
	double prob,r;
	int *red,*clase;
	s =1;
	s1=0;	// Va a ser el vecino de arriba.
	s2=0;	// Va a ser el vecino de la izquierda.
	frag=2;
	N=L;
	
	red  = (int*)malloc((N*N)*sizeof(int));
	clase= (int*)malloc((N*N)*sizeof(int));

	prob=PROB;

	srand(SEED);
	
	//Generamos la matriz de unos y ceros:
	for(i=0;i<N*N;i++)
		{
			r=myrandom(prob);
			if(r<prob) 
				*(red+i)=0;
			else       
				*(red+i)=1;
		}
	  imprimir(red,N);

	  printf("\n");

	for(s=0;s<N*N;s++)
	{
	*(clase+s)=s;
	}
	
	// Analizamos el primer lugar de la matriz:
	if(*(red)){
		*(red) =frag;
		frag++;
		}
	
	// Analizamos la primera fila, sin el primer lugar:
	for(i=1;i<N;i++){
		s1= *(red+i-1);
		
		if(*(red+i) && s1)  /*s1 es 1.*/
			{ *(red+i) = etiqueta_verdadera(clase, s1);
			}
		if(*(red+i) && !s1)  /*s1 es 0.*/
			{ *(red+i)=frag;
			  frag++;
			}
	}

	// Analizamos la primera columna, sin el primer lugar:
	for(i=1;i<N;i++)
	{ s2 = *(red+(i*N-N));
		if(*(red+(i*N)) && s2)  /*s2 es 1.*/
			{ *(red+(i*N)) = etiqueta_verdadera(clase, s2);
			}
		if(*(red+(i*N)) && !s2)  /*s2 es 0.*/
			{ *(red+(i*N))=frag;
		  	frag++;
		}
	}
	
	// Analizamos el resto de la matriz:
	for(i=1;i<N;i++)
	{ for(j=1;j<N;j++)
		{ s1 = *(red+(i*N+j-1)); //El casillero de la izquierda.
		  s2 = *(red+(i*N+j-N)); //El casillero de arriba.

		  if( *(red+(i*N+j)) && (s1 || s2))
			  { if (s1 && s2 && (etiqueta_verdadera(clase, s2)<etiqueta_verdadera(clase, s1))) // Los dos son 1 y s1 mayor.
					{ *(red+(i*N+j)) = etiqueta_verdadera(clase, s2);
					  *(clase+s1) = -abs(*(clase+s2));
					}
				if (s1 && s2 && (etiqueta_verdadera(clase, s1)<etiqueta_verdadera(clase, s2))) // Los dos son 1 y s2 mayor.
					{ *(red+(i*N+j)) = etiqueta_verdadera(clase, s1);
					  *(clase+s2) = -abs(*(clase+s1));
					}
				if (s1 && s2 && (etiqueta_verdadera(clase, s2)==etiqueta_verdadera(clase, s1))) // Los dos son 1 y son iguales. Elegimos arbitrariamente s2.
					{ *(red+(i*N+j))=etiqueta_verdadera(clase, s2);
					}
				if ((!s1) && s2) // s1 es cero y s2 es uno.
					{ *(red+(i*N+j))=etiqueta_verdadera(clase, s2);
					}
				if (s1 && (!s2)) // s1 es uno y s2 es cero.
					{ *(red+(i*N+j))=etiqueta_verdadera(clase, s1);
					}
			   }

		  if ( *(red+(i*N+j)) && ((!s1) && (!s2))) // los dos son cero.
		  { *(red+(i*N+j))=frag;
			frag++;
		  }
		}
	}

	for(i=0; i<N*N; i++)
		{ *(clase+i)=etiqueta_verdadera(clase, i);
		}


	for(i=0;i<N*N;i++)
		{ *(red+i) = *(clase+*(red+i));
		}

	free(clase);

	  imprimir(red,N);

	  printf("\n");

	return 0;
}

int etiqueta_verdadera(int *clase, int s)
	{ while(*(clase+s)<0){
		s = - *(clase+s);
		}
		
	return *(clase+s);
}

int imprimir(int *red,int N){
	int i,j;

	for (i=0;i<N;i++){
		for (j=0;j<N;j++){
			printf("%2i\t", *(red+N*i+j));
			}
		printf("\n");
		}

	return 0;
}


double myrandom(double prob){
	double r;

	r=(double)rand()/(double)RAND_MAX;

	return r;
	}
