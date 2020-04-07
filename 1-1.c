// Estime el valor de la probabilidad crı́tica (p_c), registrando los valores de p para los cuales aparece el cluster percolante. Comience con p = 1/2, si el sistema percola repueble la red (usando la misma semilla de números pseudo-aleatorios) con p = p − 1/4. En caso contrario, use p = p + 1/4. Repita este procedimiento sumando o restando 1/8, 1/16, ... , hasta alcanzar la precisión deseada. Promedie luego sobre diferentes realizaciones de la red (semillas).

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

# define L 6
# define SEED 260869
# define PROB 0.5

double myrandom(double prob);
//int seed();
int poblar(int *red, float p, int dim, int sem);
int max(int s1, int s2);
int min(int s1, int s2);
int graficar_matriz(int *red,int N);

// MAIN:

int main(){
	int seed;
	float prob;
	int *red;
	
	prob=PROB;
	seed=SEED;
	
	red = malloc(L*L*sizeof(int));    //Reserva el espacio necesario para la red.
	
	printf("\nMatriz inicial:\n");
	graficar_matriz(red,L);
	
	// Poblamos la matriz:
	poblar(red, prob, L, seed);
	
	printf("\nMatriz poblada:\n");
	graficar_matriz(red,L);
	
	return 0;
}

















// Funciones:

double myrandom(double prob)
{
	double r;
	r=(double)rand()/(double)RAND_MAX;
	return r;
}

int poblar(int *red, float prob, int N, int seed){
	float random;
	int i;
	//srand(seed);
	//printf("Poblando la red:\n");
	for (i=0;i<N*N;i++){
		*(red+i) = 0; // Se inician todas las casillas en cero (vacías).
		random=((float)rand())/((float) RAND_MAX);    //Valor aleatorio entre 0 y 1.
		//printf("\nrandom = %f",random);
		
		if (random<prob){
			*(red+i) = 1; // Llena la casilla.
		}
	}
	
	return 0;
}


int graficar_matriz(int *red, int N){
	printf("\n");
	int i, j;
	for(i=0;i<N;i++){
		for(j=0;j<N;j++){
			printf("%i", *(red + i*N + j));
			printf("%i",*( red + i ));
		}
		printf("\n");
	}
	return 0;
}

int max(int s1, int s2){
   int M;
   if (s1 > s2)
      M = s1;
   else
      M = s2;
   return M; 
}

int min(int s1, int s2) 
{
   int m;
   if (s1 > s2)
      m = s2;
   else
      m = s1;
   return m; 
}
