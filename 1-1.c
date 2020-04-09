// Estime el valor de la probabilidad crı́tica (p_c), registrando los valores de p para los cuales aparece el cluster percolante. Comience con p = 1/2, si el sistema percola repueble la red (usando la misma semilla de números pseudo-aleatorios) con p = p − 1/4. En caso contrario, use p = p + 1/4. Repita este procedimiento sumando o restando 1/8, 1/16, ... , hasta alcanzar la precisión deseada. Promedie luego sobre diferentes realizaciones de la red (semillas).

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

# define L 4
# define SEED 26 //0868
# define PROB 0.5

double myrandom(double prob);
//int seed();
int poblar(int *red, float p, int dim, int sem);
int max(int s1, int s2);
int min(int s1, int s2);
int graficar_matriz(int *red,int N);
int etiquetar(int *red, int *clase, int N);

// MAIN:

int main(){
	int i, seed;
	float prob;
	int *red, *clase;
	
	prob=PROB;
	seed=SEED;
	
	red = malloc(L*L*sizeof(int));    //Reserva el espacio necesario para la red.
	clase = malloc(L*L*sizeof(int));    //Reserva el espacio necesario para la red.
	
	
	printf("\nMatriz inicial:\n");
	graficar_matriz(red,L);
	
	// Poblamos la matriz:
	poblar(red, prob, L, seed);
	
	printf("\nMatriz poblada:\n");
	graficar_matriz(red,L);
	
	// Generamos la matriz inicial "clase":
	for(i=0;i<L*L;i++){
		*(clase+i) = i;
	}
	
	printf("\nClases:\n");
	graficar_matriz(clase,L);
	
//	actualizar(red, L); // No funciona.
	
//	etiquetar(red, clase, L);
	
	printf("\nMatriz actualizada:\n");
	//graficar_matriz(clase,L);
	
	
	// Analizamos el primer elemento *(red+0):
	
	if(*(red+0)){
		*(red+0)=2;
	}
	
	// EL BLOQUE QUE SIGUE ESTÁ HACIENDO CUALQUIER COSA. ¿TENDRÍA QUE MIRAR 'FRAG'O ALGO ASÍ? ¿DE DÓNDE SACA EL '2'?
	
	// Código para el primer renglón, arrancando desde j=1 porque j=0 fue el primer elemento:
	int j, s;
	for(j=1; j<L; j++){
		// Miramos el elemento de la izquierda:
		if(*(red+j-1)){
			s = *(red+j-1);	// guardamos la etiqueta del de la izquierda en la variable 's'.
			*(red+1) = s;	// asignamos la etiqueta al valor en el que estamos.	
		}
	}
	
	/*
	for(i=1;i<L;i++){
		
		(código para analizar primer elemento de 2º renglón en adelante
		*(red+L*i+0))

    for(j=1;j<L;j++){
          (código para analizar el resto *(red+L*i+j))
       }
  }
  */

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
	srand(seed);
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
			printf("%i\t", *(red + i*N + j));
		}
		printf("\n");
	}
	return 0;
}

// Función que había hecho antes:
/*
int etiquetar(int *red, int *clase, int N){
	int i;
	int frag = 2;	// guardamos el valor.
	
	// Guardamos los valores en la matriz "clase":
	for(i=0;i<N;i++){	// recorremos la red.
		if(*(red+i)){	// si hay un uno en ese lugar de la red.
			if(*(red+i-N)){ // si hay un uno arriba.
				*(clase+i) = frag;
			}
			
			//frag++;
		}
	}
	//printf("s=%i",s);
	
	return 0;
}
*/

/*
int actualizar(int *red, int N){
	
	int i;
	
	if (s){
		while (*(clase+s)<0) s=-(*(clase+s));
		*(red+i)=s;
		*(clase+s)=s;
	}
	else{
		*(red+i)=frag;
		*(clase+frag)=frag; // por seguridad!
		frag++;
	}
*/

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
