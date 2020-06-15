//creamos la re de espines

int poblar(int *red, float p, int L)
{ float random;
  int i, j;

  for (i=0;i<L;i++)
  { 
  	for (j=0;j<L;j++)
	{
		*(red+L*i+j)=0;							//Asigna por defecto el valor <vacio>.
  		random=myrand();    					//Valor aleatorio entre 0 y 1.
  		if (random<p)
    	{*(red+L*i+j)=1;						//Asigna spin pos. si el valor aleatorio es menor.
    	}
      	else
    	{*(red+L*i+j)=-1;						//Asigna spin neg. si el valor aleatorio es mayor.
    	}
  	}
  }

  return 0;
}