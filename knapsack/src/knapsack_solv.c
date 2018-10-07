#include "bench.h"
#include "knapsack.h"


static int _knapsack_solv_recursive(KNAPSACK_PROBLEM *p,int i,int w)
{
	if(i==p->len-1)
	{
		if(p->w[i]<=w) 
		{
			p->b[i]=1;
			return p->v[i];
		}
		else
		{
			p->b[i]=0;
			return 0;
		}
	}
	else
	{

		 if(p->w[i]>w)
	    {   
			int v0=_knapsack_solv_recursive(p,i+1,w);
			p->b[i]=0;
			return v0;
		}
		else if(p->w[i]==w)
		{
			memset(p->b+i,0,(p->len-i)*sizeof(int));
			p->b[i]=1;
			return p->v[i];
		}
		else
		{
			int v0,v1,v;
			int* buf=(int*)malloc(sizeof(int)*p->len);
			v0=_knapsack_solv_recursive(p,i+1,w);
			memcpy(buf+i,p->b+i,(p->len-i)*sizeof(int));
			v1=_knapsack_solv_recursive(p,i+1,w-p->w[i])+p->v[i];
			//if(i==1) printf("i=%d v0=%d v1=%d w=%d\r\n",i,v0,v1,w);
			if(v0>v1) /*select v0*/
			{
				//_knapsack_solv_recursive(p,i+1,w);
				memcpy(p->b+i,buf+i,(p->len-i)*sizeof(int));
				p->b[i]=0;
				v=v0;
			}
			else
			{
				p->b[i]=1;
				v=v1;
			}
			free(buf);
			return v;
		}
	}
}

int knapsack_solv_recursive(KNAPSACK_PROBLEM *p)
{
	return _knapsack_solv_recursive(p,0,p->maxw);
}



int knapsack_test()
{
	return knapsack_solv(knapsack_solv_recursive);
}