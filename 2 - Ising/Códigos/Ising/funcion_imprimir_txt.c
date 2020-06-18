//imprime una red en un txt

int imprimir_txt(int *red, int L)         //Imprime una fila debajo de la otra.
{ 
	int i,j;

	char filename[255];
	sprintf(filename,"Datos/red_L=%d.txt",L);
	
	FILE *fp;
	fp = fopen(filename,"w");

  	for (i=0;i<L;i++)
    {
    	for (j=0;j<L;j++)
      	{
      		fprintf(fp,"%2d ", *(red+L*i+j));
      	}
    fprintf(fp, "\n");
    }

    fclose(fp);

  return 0;
}
