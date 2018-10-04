#include <stdio.h>
#include <math.h>


float agm_pi_calc()
{
	double a=1;
	double b=1/sqrt(2.0l);
	int n;
	double serial=0;
	double pi;
	for(n=1;n<8;n++)
	{
		double na=(a+b)/2;
		double nb=sqrt(a*b);
		a=na;b=nb;
		serial+=(1<<(n+1))*((a+b)*(a-b));
	}
	pi=4*a*a/(1-serial);
	printf("pi=%e\r\n",pi);
}