//sumamos todos los valores de una matriz

int conteo(int *red, int L)
{ int i, j, c=0;

  for (i=0;i<L;i++)
    { for (j=0;j<L;j++)
        {
          c+=*(red+i*dim+j);
        }
    }
    return c;
}