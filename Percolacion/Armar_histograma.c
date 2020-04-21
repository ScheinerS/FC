
// Programa que lee el archivo del programa de percolación y arma un vector con los valores para el histograma.

#include <stdio.h>
#include <string.h>

#define	ARCHIVO	"Tamaños_L=32.txt"

int leer_archivo();





int main(){
	
	// Leemos el archivo:
	leer_archivo();
	// Recorremos todas las etiquetas: e=0,...,N*N/2 y para cada una, almacenamos la cantidad de clusters existentes con tamaño "e":
	
	/*
	int count = 0;
	
	*hist = 0;	// Tamaño cero no tiene sentido.
	
	// Recorremos los posibles tamaños de los bloques para el histograma:
	for(int size=1; size<N*N/2+1; size++){
		// Recorremos todos los lugares del vector 'tamaño':
		for(int i=0; i<N*N/2+1; i++){
			// Contamos los que coinciden con el tamaño 'size' que buscamos:
			if(*tamano+i == size){
				count++;
			}
		}
		// Guardamos la cuenta:
		*(hist + size) = count;
		// Reiniciamos el contador para el próximo tamaño que analicemos:
		count = 0;
		
		
	}
	*/
	
	return 0;
}


int leer_archivo(){
	char str[99999];
	FILE * file;
	file = fopen( ARCHIVO , "r");
	if (file) {
		while (fscanf(file, "%s", str)!=EOF)
		    printf("%s",str);
		    }
    fclose(file);
    
    return 0;
}
/*
	sprintf(filename,"Tamaños_L=32.txt");
	
	// Creamos el archivo:
	FILE *fp=fopen(filename,"a");
	
	int i;
	for(i = 0; i < L*L/2+1; i++)
		{
		// Lo guardamos si es no nulo:
		if(*(Y+i)){
			fprintf(fp,"%4d\t%4d\n",*(X+i),*(Y+i));
			}
		}
	
	// Cerramos el archivo:
	fclose(fp);
}
*/

