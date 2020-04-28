// Bloque que analiza si hay percolación en una red:


int *p   = *(red+0);	// Primer elemento de la primera fila de la matriz.
int *q	 = *(red+N*(N-1));	// Primer elemento de la última fila de la matriz.

int i,j;
int perc = 0;

// Barremos la primera fila:
for (i=0;i<N;i++){
	// Si el lugar está lleno:
	if(*(p+i){
		// Barremos la última fila:
		for (j=0;j<N;j++)
			{
				// Analizamos si las etiquetas de *(p+i) y *(q+j) son iguales, y eso significa que hay percolación:
				if(*(p+i)==*(q+j))
					{
					perc = 1;
					i = j = N;	// Corta los bucles.
					}
			}
		}
	}
