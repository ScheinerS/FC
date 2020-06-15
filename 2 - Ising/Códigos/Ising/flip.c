/*esta función toma un espín al azar en la fila ii columna jj, 
calculamos la energía a primeros vecinos y vemos si lo damos vuelta*/ 

int flip(double *red,double *tabla,int N,int L)
{
	int ii,jj,s,s1,s2,s3,s4,h,w;
	double p;
	
	for (i=0;i<N;i++)
	{
		ii = rand()%L; 									//nos da el resto entre el número al azar y L, con lo cual ii<L
		jj = rand()%L;									//nos da el resto entre el número al azar y L, con lo cual jj<L
		s  = *(red+L*ii+jj);							//el espín en el lugar ii,jj
		s1 = *(red+L*((ii-1)+L)%L+jj); 					//vecino de arriba
		s2 = *(red+L*((ii+1)+L)%L+jj);					//vecino de abajo
		s3 = *(red+L*ii+((jj+1)+L)%L);					//vecino de la derecha
		s4 = *(red+L*ii+((jj-1)+L)%L);					//vecino de la izquierda
		h  = 2*[(-s-s)+2]+2+(-s-s)*(s1+s2+s3+s4)/4;		//calculamos el lugar en la tabla de energías
		w  = *(tabla+h);								//valores de la energía
		p  = myrand();									//
		if (p<w)*(red+L*ii+jj) = -s;					//vemos si damos vuelta el lugar
	}

	return 0;
}