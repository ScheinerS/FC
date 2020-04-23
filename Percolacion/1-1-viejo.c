// Santiago Scheiner
/* Programa para generar una red de LxL de unos y ceros y detectar los clusters.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define PROB	0.55
#define L	32
#define MUESTRAS	27000	// 27000
#define IMPRIMIR_REDES	0	// Para no mostrar las redes en pantalla.
#define GUARDAR_DATOS	0	// Para que se guarden los datos en un TXT.
#define GUARDAR_HISTOGRAMA	1	// Para que se guarde el histograma en un TXT.


double myrandom(double prob);
//int min(int s1,int s2);
//int max(int s1,int s2);
int etiqueta_verdadera(int *clase, int s);
int imprimir(int *red,int N);
int guardar_datos(double *X);
int llenar_matriz(double *hist);
int actualizar_histograma(double *hist, int *tamano);

int main(){
	
	double *hist;
	hist= (double*)malloc((L*L)*sizeof(double));
	
	for(int m=0;m<MUESTRAS;m++){
		llenar_matriz(hist);
		
		printf("Muestra:\t%d / %d\r", m, MUESTRAS);
		fflush(stdout);
		}
	
	return 0;
}




int llenar_matriz(double *hist){
	int    i,s,s1,s2,frag,j,N;
	double prob,r;
	int *red, *clase, *tamano, *etiquetas;
	s =1;
	s1=0;	// Va a ser el vecino de arriba.
	s2=0;	// Va a ser el vecino de la izquierda.
	frag=2;
	N=L;
	
	red  = (int*)malloc((N*N)*sizeof(int));
	clase= (int*)malloc((N*N)*sizeof(int));

	prob=PROB;
	srand(time(NULL));
	
	//Generamos la matriz de unos y ceros:
	for(i=0;i<N*N;i++)
		{
			r=myrandom(prob);
			if(r<prob) 
				*(red+i)=0;
			else       
				*(red+i)=1;
		}
	if(IMPRIMIR_REDES){
		printf("Red:\n");
		imprimir(red,N);
		printf("\n");
	}

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
	for(i=1;i<N;i++){
		for(j=1;j<N;j++){
			s1 = *(red+(i*N+j-1)); //El casillero de la izquierda.
			s2 = *(red+(i*N+j-N)); //El casillero de arriba.

			if( *(red+(i*N+j)) && (s1 || s2)){
				if (s1 && s2 && (etiqueta_verdadera(clase, s2)<etiqueta_verdadera(clase, s1))) // Los dos son 1 y s1 mayor.
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


	for(i=0;i<N*N;i++){
		*(red+i) = *(clase+*(red+i));
		}

	free(clase);
	
	if(IMPRIMIR_REDES){
		printf("Red clasificada:\n");
		imprimir(red,N);
		printf("\n");
	}

	// Contamos la cantidad de clusters que existen con "i" componentes:
	etiquetas = (int*)malloc((N*N)*sizeof(int));	// vector con las etiquetas posibles: {2, 3, ..., N*N/2}.
	tamano = (int*)malloc((N*N)*sizeof(int));	// vector con las cantidades de clusters que hay de cada tamaño: cantidad[i] = # clusters de tamaño "i".
	int count = 0;
	int e;
	etiquetas[0] = etiquetas[1] = 0;	// no hay clustes con etiquetas 0 y 1.
	
//	printf("Etiqueta\tTamaño del cluster\n");

	// Barremos la matriz una vez por cada etiqueta y contamos cuántas veces encontramos cada etiqueta:
	for (e=2;e<N*N/2+1;e++){
		etiquetas[e] = e;
		for(i=0;i<N;i++){
			for(j=0;j<N;j++){
				// Si la clase en ese lugar coincide con la etiqueta que estamos buscando, incrementamos la cuenta:
				if(*(red+(i*N+j))==e){
					count++;
					}					
				}
			}
		tamano[e]=count;
		count = 0;	// Reiniciamos la cuenta para la siguiente etiqueta.
		//printf("%i\t\t%i\n",etiquetas[e],tamano[e]);
		}
	
	actualizar_histograma(hist, tamano);
	
	
	if(GUARDAR_HISTOGRAMA){
		// Guardamos los datos en el archivo:
		guardar_datos(hist);
		}
	
	return 0;
}

int actualizar_histograma(double *hist, int *tamano){
	
	int k;
	
	// Barremos todos los valores que hay en "tamano":
	for (int i=0;i<L*L;i++)
        {
		// Guardamos en "k" el tamaño que tiene el bloque que estamos mirando:
        k = *(tamano+i);
        // Y, si k no es nulo, vamos al lugar "k" del histograma, para incrementarlo en uno:
        if(k){
        	*(hist+k) = (*(hist+k)) + 1.0;
        	//printf("tamano=%d\t\thist[%d]=%lf\n",*(tamano+i),*(tamano+i),*(hist+k));
        	}
        }

	
	return 0;
}


int guardar_datos(double *X){

	char filename[255];
	sprintf(filename,"Tamaños_L=%d_M=%d_prob=%.2f.txt",L,MUESTRAS,PROB);
	// sprintf(filename,"Tamaños_L=32.txt");
	
	// Creamos el archivo:
	FILE *fp=fopen(filename,"w");
	
	int i;
	for(i = 0; i < L*L; i++)
		{
		fprintf(fp,"%4f\n",*(X+i));
		}
	
	// Cerramos el archivo:
	fclose(fp);

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
			printf("%4i", *(red+N*i+j));
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
