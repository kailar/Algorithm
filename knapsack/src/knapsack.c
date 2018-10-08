
#include "bench.h"
#include "knapsack.h"




int knapsack_solv(knapsack_solv_func func)
{
	int t=0;
	int retv=0;
	int sumv=0,sumw=0;
	int i;
	int len=60;
	KNAPSACK_PROBLEM p;
	if(func==NULL) return -1;
	p.w=(int*)malloc(sizeof(int)*len);
	p.v=(int*)malloc(sizeof(int)*len);
	p.b=(int*)malloc(sizeof(int)*len);
	p.buf=(int*)malloc(sizeof(int)*len);
	for(i=0;i<len;i++)
	{
		p.w[i]=rand()%20+1;
		p.v[i]=rand()%10+1;
		p.b[i]=0;
	}
	p.maxw=30;
	p.len=len;

	t=GetTickCount();
	retv=func(&p);
	t=GetTickCount()-t;
	for(i=0;i<len;i++)
	{
		if(p.b[i]){ sumv+=p.v[i];sumw+=p.w[i];}
		printf("%4d w[%2d] v[%2d] %c\r\n",i,p.w[i],p.v[i],p.b[i]?'+':' ');
	}
	printf("sumw=%d/%d sumv=%d retv=%d time=%dMs\r\n",sumw,p.maxw,sumv,retv,t);
	return sumv;
}