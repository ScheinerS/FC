//Función correlación entre el paso i y el paso i+n

int correlation(double *c,double *m,int n)
{
	int i,k;
	double xi,xk,s0,s1,s2;
	
	for (k=0;k<n;k++)
	{
		s0 = 0.0;
		s1 = 0.0;
		s2 = 0.0;
		
		for (i=0;i<N-n;i++)
		{
			xi = *(m+i);
			xk = *(m+i+k);
			s1 += xi/(double)(N-n);
			s0 += xi*xk/(double)(N-n);
			s2 += xi*xi/(double)(N-n);
		}
		*(c+k) = (s0-s1*s1)/(s2-s1*s1);
	}
	return 1;
}