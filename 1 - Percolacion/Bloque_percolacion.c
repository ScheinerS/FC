int perco(int *red,int n)
{
  // Bloque que analiza si hay percolación en una red: s=0 (no), s=1 (si)

  int i,j,k,s;
  int *p,*q;

  s = 0;

  for (i=0;i<n*n;i++) 
    {
      *(p+i) = 0;
      *(q+i) = 0;
    }

  for (i=0;i<n;i++) 
    {
      j = *(red+i);
      *(p+j) = 1;

      j = *(red+n*(n-1)+i);
      *(q+j) = 1;
    }

  for (i=0;i<n*n;i++) 
    {
      j = *(p+i);
      k = *(q+i);

      if (j && k) 
        {
          s = 1;
          break;
        }
    }

  return s;
}



