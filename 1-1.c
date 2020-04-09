#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

# define L 8
# define SEED 26 //0868
# define PROB 0.5

double myrandom(double prob);
//int seed();
int poblar(int *red, float p, int dim, int sem);
int max(int s1, int s2);
int min(int s1, int s2);
int graficar_matriz(int *red,int N);
//int etiquetar(int *red, int *clase, int N);

// MAIN:

int main(){
	int i, seed;
	float prob;
	int *red, *clase;
	
	prob=PROB;
	seed=SEED;
	
	red = malloc(L*L*sizeof(int));    //Reserva el espacio necesario para la red.
	clase = malloc(L*L*sizeof(int));    //Reserva el espacio necesario para la red.
	
	
	// Poblamos la matriz:
	poblar(red, prob, L, seed);
	
	printf("\nMatriz poblada:\n");
	graficar_matriz(red,L);
	
	// Generamos el vector inicial "clase":
	for(i=0;i<L*L;i++){
		*(clase+i) = i;
		}
	
	
	/////////////////////////////////////
	// Buscamos los clusters en la red //
	/////////////////////////////////////
	
	int frag;
	frag=2;
	
	// Analizamos el primer elemento *(red+0):
	if(*(red+0)){
		*(red+0)=frag;
		frag++;		// Para la próxima etiqueta nueva que necesitemos.
		}
	
	
	// Código para el primer renglón, arrancando desde j=1 porque j=0 fue el primer elemento:
	int s;
	for(int j=1; j<L; j++){
		// Si el lugar está ocupado:
		if(*(red+j)){			
			// Miramos si el elemento de la izquierda está ocupado y si lo está, usamos la misma etiqueta:
			if(*(red+j-1)){
				s = *(red+j-1);	// guardamos la etiqueta del de la izquierda en la variable 's'.
				s = *(clase+s);
				*(red+j)=s;		// asignamos la etiqueta de la izquierda a esta casilla.
				}
			// Si la de la izquierda no estaba ocupada:
			else{
				*(red+j)=frag;
				frag++;
				}
			}
		}
	
	// Código para la primera columna, arrancando desde i=1 porque i=0 fue el primer elemento:
	for(int i=1; i<L; i++){
		// Si el lugar está ocupado:
		if(*(red+i*L+0)){			
			// Miramos si el elemento de arriba está ocupado y si lo está, usamos la misma etiqueta:
			if(*(red+(i-1)*L+0)){
				s = *(red+(i-1)*L+0);	// guardamos la etiqueta del de arriba en la variable 's'.
				s = *(clase+s);
				*(red+i*L+0)=s;		// asignamos la etiqueta de arriba a esta casilla.
				}
			// Si la de arriba no estaba ocupada:
			else{
				*(red+i*L+0)=frag;
				frag++;
				}
			}
		}
	
	// Código el bloque que queda de la matriz, arrancando desde i=1 y j = 1:
	for(int i=1; i<L; i++){
		for(int j=1; j<L; j++){
			if(*(red+i*L+j)){
				// Miramos si el elemento de arriba está ocupado:
				if(*(red+(i-1)*L+j)){
					s = *(red+(i-1)*L+j);	// guardamos la etiqueta del de arriba en la variable 's'.
					s = *(clase+s);
					*(red+i*L+j)=s;		// asignamos la etiqueta de arriba a esta casilla.
					}
				else{
					// Miramos si el elemento de la izquierda está ocupado:
					if(*(red+i*L+j-1)){
						s = *(red+i*L+j-1);	// guardamos la etiqueta del de la izquierda en la variable 's'.
						s = *(clase+s);
						*(red+i*L+j)=s;		// asignamos la etiqueta de la izquierda a esta casilla.
						}
					else{
						*(red+i*L+j)=frag;
						frag++;
						}
					}

		
				}
			}
		}
	
	printf("\nMatriz etiquetada:\n");
	graficar_matriz(red,L);

	// Función "actualizar":
	
	/*Repasa toda la tira corrigiendo los valores incorrectos*/

    for(int i=0;i<L*L;i++){
        s=*(red+i);
        
        while (*(clase+s)<0){
			s=-(*(clase+s));
			*(red+i)=*(clase+s);
			}
		}
	
	printf("\nMatriz repasada:\n");		// El "repaso" no está funcionando, todavía.
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
	srand(seed);
	//printf("Poblando la red:\n");
	for (i=0;i<N*N;i++){
		*(red+i) = 0; // Se inician todas las casillas en cero (vacías).
		random=((float)rand())/((float) RAND_MAX);    // Valor aleatorio entre 0 y 1.
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
