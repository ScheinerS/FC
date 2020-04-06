// Estime el valor de la probabilidad crı́tica (p_c), registrando los valores de p para los cuales aparece el cluster percolante. Comience con p = 1/2, si el sistema percola repueble la red (usando la misma semilla de números pseudo-aleatorios) con p = p − 1/4. En caso contrario, use p = p + 1/4. Repita este procedimiento sumando o restando 1/8, 1/16, ... , hasta alcanzar la precisión deseada. Promedie luego sobre diferentes realizaciones de la red (semillas).

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

# define L 4
# define SEED 260868
# define PROB 0.5

double myrandom(double prob);
//int seed();
int poblar(int *red, float p, int dim, int sem);
int max(int s1, int s2);
int min(int s1, int s2);


// MAIN:

int main(){
	int i,s,s1,s2,frag,m,M;
	double prob, seed, r;
	int *red, *clase;
	int N = L;
	
	//s = 0;
	//s1 = 0;
	//s2 = 0;
	red = (int*)malloc((N*N)*sizeof(int));
	clase = (int*)malloc((N*N)*sizeof(int));
    prob = PROB;
	seed = SEED;
	//time_t seconds;
	//seconds = time(NULL)
	//printf("seconds:  %d",seconds)
	
	srand(seed);
	
	// Poblamos la red:
	
	//poblar(red, prob, N, seed);
	
	for(i=0;i<N*N;i++){
    
        r = myrandom(prob);

	    if(r<prob){
			*(red+i)=0;
	    }
	    else{
			*(red+i)=1;
       	}

		printf("%i",*( red + i ));
        
        if(i%N==0){
        	printf("\n");
        }
    }
    
    for(i=0;i<N;i++){
        
        // Actualización:
        
        if (s){
			while (*(clase+s)<0){ 
				s=-(*(clase+s));
				*(red+i)=s;
				*(clase+s)=s;
			}
		}

		else{
			*(red+i)=frag;
			*(clase+frag)=frag; // por seguridad. - No entiendo bien qué es esto.
			frag++;
		}

       /*funcion etiqueta_falsa*/
     
       s1= *(red + i - N); /*vecino de arriba*/

       s2= *(red + i - 1); /*vecino de la izquierda*/

       while (*(clase+s1)<0) s1=-(*(clase+s1)); /*etiqueta s1 verdadera*/
     
       while (*(clase+s2)<0) s2=-(*(clase+s2)); /*etiqueta s2 verdadera*/
     
       m=min(s1,s2);
     
       M=max(s1,s2);
     
       *(red+i)=m;
     
       *(clase+m)=m;
     
       if (m<M) *(clase+M)=-m; 
     
       else *(clase+M)=m;    
     
     } 
     
     /*Repasa toda la tira corrigiendo los valores incorrectos*/
     
       for(i=0;i<N*N;i++)
      {
         s=*(red+i);
         
         while (*(clase+s)<0) 

         	s=-(*(clase+s));
            
            *(red+i)=*(clase+s);
      
      }
   
             printf("%i\n",*( clase + s ));

      return 1;
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

	for (i=0;i<N*N;i++){
		*(red+i) = 0; // Se inician todas las casillas en cero (vacías).
		random=((float)rand())/((float) RAND_MAX);    //Valor aleatorio entre 0 y 1.
		if (random<prob){
		*(red+i) = 1; // Llena la casilla.
		}
	}
	
	return 0;
}


int max(int s1, int s2) 
{
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
