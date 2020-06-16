//Tabla de nenergías.
//Be va a ser el B* del hamiltoneano, y Je el J*.

double energias(double Be,double Je)
{
	double *tabla;

	tabla = malloc(13*sizeof(double));

	*(tabla+0) =exp(-8*Je-2*Be);
	*(tabla+1) =exp(-4*Je-2*Be);
	*(tabla+2) =exp(-0*Je-2*Be);
	*(tabla+3) =exp(+4*Je-2*Be);
	*(tabla+4) =exp(+8*Je-2*Be);
	*(tabla+5) =0;
	*(tabla+6) =0;
	*(tabla+7) =0;
	*(tabla+8) =exp(-8*Je+2*Be);
	*(tabla+9) =exp(-4*Je+2*Be);
	*(tabla+10)=exp(-0*Je+2*Be);
	*(tabla+11)=exp(+4*Je+2*Be);
	*(tabla+12)=exp(+8*Je+2*Be);

return 0;
}