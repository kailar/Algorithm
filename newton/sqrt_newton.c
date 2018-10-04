#include <stdio.h>
#include <math.h>

double sqrt_newton(double v)
{
	/*
	y=x^2-v;
	x(n+1)=x(n)-f(n)/f'(n) Å£¶Ùµü´ú¹«Ê½ 
	x(n+1)=x(n)-(x(n)*x(n)-v)/(2*x(n));
	      =x(n)/2+v/(2*x(n));
		  =((x(n)+v/x(n))/2;
	*/
	int i;
	double x=1;
	double prex=1;
	for(i=0;i<30;i++)
	{
		x=(x+v/x)/2;
		if(x==prex) break;
		prex=x;
		printf("x[%d]=%e\r\n",i,x);
	}
	printf("mysqrt(%f)=%e sqrt=%e\r\n",v,x,sqrt(v));
	return x;
}

