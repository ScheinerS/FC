// Santiago Scheiner
/* Programa para generar una red de LxL de unos y ceros y detectar los clusters.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>


#define PROB	0.55
#define L	64
#define MUESTRAS        27000	// 27000
#define IMPRIMIR_REDES	0	// Para no mostrar las redes en pantalla.
#define GUARDAR_DATOS	0	// Para que se guarden los datos en un TXT.
#define GUARDAR_HISTOGRAMA	1	// Para que se guarde el histograma en un TXT.


int myrandom(double prob);
//int min(int s1,int s2);
//int max(int s1,int s2);
int etiqueta_verdadera(int *clase, int s);
int imprimir(int *red,int N);
int guardar_datos(double *X);
int llenar_matriz(double *hist);

int main(){
 	
 	printf("L=%d\nM=%d\nprob=%.2f\n",L,MUESTRAS,PROB);
 	
    int i,suma;                // agregado por Guillermo Frank
	double *hist;
	FILE *fp;                  // agregado por Guillermo Frank

	hist= (double*)malloc((L*L)*sizeof(double));

        for (i=0;i<L*L;i++) *(hist+i) = 0.0;   // agregado por Guillermo Frank
	
        suma = 0;                              // agregado por Guillermo Frank

	for(int m=0;m<MUESTRAS;m++){

		srand(m+1);		        // agregado por Guillermo Frank

		suma += llenar_matriz(hist);   // modificado por Guillermo Frank
		
		printf("Muestra:\t%d / %d\r", m, MUESTRAS);
		fflush(stdout);
		}
	
        for (i=0;i<L*L;i++) *(hist+i) = (*(hist+i))/(double)suma;   // agregado por Guillermo Frank
		
		char filename[255];
		sprintf(filename,"Datos/histograma_L=%d_M=%d_prob=%.2f.txt",L,MUESTRAS,PROB);

		fp = fopen(filename,"w");      //  fp = fopen("histograma.txt","w");                            // agregado por Guillermo Frank

        for (i=0;i<L*L;i++) fprintf(fp,"%d %lf\n",i,*(hist+i));     // agregado por Guillermo Frank
 
        fclose(fp);                                                 // agregado por Guillermo Frank

	return 0;
}




int llenar_matriz(double *hist){
	int    i,s,s1,s2,frag,j,N;
	int *red, *clase, *etiquetas;
	s =1;
	s1=0;	// Va a ser el vecino de arriba.
	s2=0;	// Va a ser el vecino de la izquierda.
	frag=2;
	N=L;
	
	red  = (int*)malloc((N*N)*sizeof(int));
	clase= (int*)malloc((N*N)*sizeof(int));
	
	//Generamos la matriz de unos y ceros:
	for(i=0;i<N*N;i++)
		{
			*(red+i)=myrandom(PROB);
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
	
//--------------Cambiado por Guillermo Frank:

	for(i=0;i<N*N;i++){
                s = *(red+i);
		*(red+i) = etiqueta_verdadera(clase, s);
		}

//-------------------------------------------

	free(clase);
	
	if(IMPRIMIR_REDES){
		printf("Red clasificada:\n");
		imprimir(red,N);
		printf("\n");
	}

//-------------- Modificado por Guillermo Frank-----------------

	etiquetas = (int*)malloc((N*N)*sizeof(int));

        for (i=0;i<N*N;i++) *(etiquetas+i) = 0;

        for (i=0;i<N*N;i++)
           {
             s = *(red+i);
             (*(etiquetas+s))++;
           }

        *(etiquetas+0) = 0;

        for (i=0;i<N*N;i++)
           {
             j = *(etiquetas+i);
             *(hist+j) = (*(hist+j)) + 1.0;
             if (j) s++;
           }

	*hist = 0.0;
        
	free(etiquetas);

	//if(GUARDAR_HISTOGRAMA) guardar_datos(hist);

        return s;

//--------------------------------------------------------------
	
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
		
	return s;    // corregido por Guillermo Frank
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


int myrandom(double prob){

	int    p;	
	double r;

	r=(double)rand()/(double)RAND_MAX;

	if(r<prob) p=1;
	else p=0;

	return p;
	}
