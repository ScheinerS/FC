//imprime una red

int imprimir(double *red, int L)         //Imprime una fila debajo de la otra.
{ 
	int i,j;

  	for (i=0;i<L;i++)
    {
    	for (j=0;j<dim;j++)
      	{
      		printf("%02d ", *(red+L*i+j));
      	}
    printf("\n");
    }

  return 0;
}
