#include "bench.h"
#include "knapsack.h"

static int maxv(int a,int b)
{
	return a>b?a:b;
}
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

int knapsack_solv_dynamic(KNAPSACK_PROBLEM *p)
{
	int*  buf=(int*)malloc(p->len*(p->maxw+1)*sizeof(int));
	int** a=(int**)malloc(p->len*sizeof(int*));/*a[i][j]:第0-i件物品在包剩余重量为j时的最高价值*/
	int i,j,w;
	for(i=0;i<p->len;i++)    a[i]=buf+i*(p->maxw+1);
	for(j=0;j<p->maxw+1;j++) a[0][j]=(j>=p->w[0])?p->v[0]:0;
	for(i=1;i<p->len;i++)
		for(j=0;j<p->maxw+1;j++)
	{
		if(j<p->w[i]) a[i][j]=a[i-1][j];/*当前物件超重:使用前一件物品重量为j的价值*/
		else a[i][j]=maxv(a[i-1][j-p->w[i]]+p->v[i],a[i-1][j]);
	}
	w=p->maxw;
	for(i=p->len-1;i>0;i--)
	{
		p->b[i]=a[i][w]!=a[i-1][w];
		w-=p->b[i]*p->w[i];
	}
	p->b[0]=a[0][w]>0;
	w=a[p->len-1][p->maxw];
	free(a);free(buf);
	return w;
}


int knapsack_test()
{
	//return knapsack_solv(knapsack_solv_recursive);
	return knapsack_solv(knapsack_solv_dynamic);

}