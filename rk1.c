#include <stdio.h>
#include <math.h>
FILE *fp;

#define TAM 3 //ordem da edo

typedef double (*sistfunc)();

//funções
double funcao1(double x, double y[TAM]) 
{ 
	return(y[2]); 
}
double funcao2(double x, double y[TAM]) 
{ 
	return(y[1]); 
}
double funcao3 (double x, double y[TAM])
{ 
	return(exp(x) - 2*y[2] + y[1] + 2*y[0]); 
}

//função Runge-Kutta
double rk(sistfunc func[], double y[TAM], double x, double h)	
{
	int i;
	double k1[TAM], k2[TAM], k3[TAM], k4[TAM], yp[TAM];
	
	for(i=0;i<TAM;i++)	
	{
		k1[i] = h*func[i](x,y);
	}	
	for(i=0;i<TAM;i++)	
	{
		yp[i] = y[i] + (1/2.0)*k1[i];
	}
	for(i=0;i<TAM;i++)	
	{
		k2[i] = h*func[i](x + 0.5*h,yp);
	}
	for(i=0;i<TAM;i++)	
	{
		yp[i] = y[i] + (1/2.0)*k2[i];
	}
	for(i=0;i<TAM;i++)	
	{
		k3[i] = h*func[i](x + 0.5*h,yp);
	}
	for(i=0;i<TAM;i++)
	{
		yp[i] = y[i] + k3[i];
	}
	for(i=0;i<TAM;i++)	
	{
		k4[i] = h*func[i](x + h,yp);
	}
	for(i=0;i<TAM;i++)
	{
		y[i] += (1/6.0)*(k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
	}
	
	return y[0];
}	

		
main()
{
	int i;
	//Condições inicias sendo passada na funçao
	double y0[TAM] = {1,2,0}; 
	double y[TAM];
	sistfunc equacoes[TAM] = {funcao1,funcao2,funcao3};
	double h,t,tf,ti,n;
	t=ti;
	//intervalo e valor de acréscimo
	ti=0.0;
	tf=3.0;
	n=30.0;
	h=(tf-ti)/n;

	
	fp=fopen("r1.dat", "w");
	
	
	for(i=0;i<TAM;i++)
	{
		y[i] = y0[i];
	}
	
	do
	{
		fprintf(fp, "%lf %lf\n", t, y[0]);
		y[0] = rk(equacoes,y,t,h);
		
		t=t+h;
	
	}while(t<=tf);
	
	fprintf(fp, "%lf %lf\n", t, y[0]);
}	

